%% paramters
ir_type = "16k";
ir_version = "1";
ir_angles = 0:45:359; 
speech_types = ["cmu_us_awb_arctic", "cmu_us_bdl_arctic", "cmu_us_jmk_arctic", "cmu_us_ksp_arctic", "cmu_us_rms_arctic", "cmu_us_slt_arctic", "cmu_us_clb_arctic"];
featuretype = "magnitude"; % fft, raw
fftN = 512;
mic_N = 2;
ang_N = 8;
fs = 16000;
max_filesamples = 113599;
max_files = 1132;
start_threshold = 0.1;
start_shift_s = -0.1;

%% run
if featuretype == "magnitude"
    max_filesamples = ceil(max_filesamples / (fftN / 2 + 1)) * (fftN / 2 + 1);
end
for j=1:length(speech_types)
    filename_speech = speech_types(j);
    fprintf(filename_speech + "\n");
    filepath_input = "../../../../recording/speech/";
    filepath_output = "../../../../../Shared/SoundLocalization/speech_database/";
    filepath_speech_input = filepath_input + fs/1000 + "khz/" + filename_speech + "/";
    filepath_speech_output = filepath_output + fs/1000 + "khz/" + "/";
    %% generat speech files index
    speech_files = dir(filepath_speech_input);
    speech_files = {speech_files.name};
    speech_files = speech_files(3:end);
    speech_files_N = max_files;
    data = zeros(max_filesamples * speech_files_N * ang_N, mic_N, "single");
    output_file_n = 0;
    fprintf("process:" + speech_types(j) + "\n");
    for speech_file_n = 1:speech_files_N
        fprintf(speech_file_n + "/" + speech_files_N + "\n");
        for i=1:length(ir_angles)
            %% for every speech file
            output_file_n = output_file_n + 1;
            
            %% load speech file
            filename_ir = ir_type + "_" + ir_version + "_" + ir_angles(i) + "degree";
            try
                raw = audioread(filepath_speech_input + filename_speech + "_" + speech_file_n + "_" + filename_ir + ".wav");
            catch
                break
            end
            %% features
            index = ((output_file_n - 1) * max_filesamples) + 1;            
            if featuretype == "magnitude"
                for mic_i = 1:mic_N
                    start = raw > start_threshold;
                    start_ix = [find(start(:,1),1) find(start(:,2),1)];
                    start_ix = min(start_ix);
                    start_ix = start_ix + start_shift_s * fs;
                    if start_ix < 1
                        start_ix = 1;
                    end
                    rawstart = zeros(length(raw), mic_N);
                    rawstart(1:end-start_ix+1,:) = raw(start_ix:end,:);
                    feature = spectrogram(rawstart(:, mic_i), fftN);
                    feature = abs(feature);
                    feature = feature(:);
                    feature_N = length(feature);
                    data(index:index + feature_N - 1, mic_i) = feature;
                end
                data(index:index + feature_N - 1, :) =  data(index:index + feature_N - 1, :) / max(max(abs(data(index:index + feature_N - 1, :))));
            else
                feature_N = length(feature);
                data(index:index + feature_N - 1, :) = feature;
            end
        end
    end
    %% output
    audiowrite(filepath_speech_output + speech_types(j) + "_" + featuretype + ".wav", data, fs, 'BitsPerSample',16);    
end