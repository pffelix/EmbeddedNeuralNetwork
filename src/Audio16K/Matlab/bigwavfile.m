%% paramters
ir_type = "16k";
ir_version = "1";
ir_angles = 0:45:359; 
speech_types = ["cmu_us_bdl_arctic", "cmu_us_jmk_arctic", "cmu_us_ksp_arctic", "cmu_us_rms_arctic", "cmu_us_slt_arctic", "cmu_us_clb_arctic"];
mic_N = 2;
fs = 16000;
max_length = 113599;

%% run
for j=1:length(speech_types)
    filename_speech = speech_types(j);
    fprintf(filename_speech + "\n");
    filepath_output = "../../../../recording/speech/";
    filepath_speech = filepath_output + fs/1000 + "khz/" + filename_speech + "/";
    %% generat speech files index
    speech_files = dir(filepath_speech);
    speech_files = {speech_files.name};
    speech_files = speech_files(3:end);
    speech_files_N = length(speech_files);
    data = zeros(max_length * speech_files_N, mic_N);
    for i=1:length(ir_angles)
        %% for every speech file
        fprintf("process:" + "\n");
        for speech_file_n = 1:speech_files_N
            fprintf(speech_file_n + "/" + speech_files_N + "\n");
            
            %% load speech file
            filename_ir = ir_type + "_" + ir_version + "_" + ir_angles(i) + "degree";
            irspeech = audioread(filepath_speech + filename_speech + "_" + speech_file_n + "_" + filename_ir + ".wav");
            speech_N = length(irspeech);
            index_1 = ((speech_file_n-1) * max_length) + 1;
            index_2 = ((speech_file_n) * max_length);
            data(index_1:index_1 + speech_N - 1, :) = irspeech;
        end
        
        %% output
        audiowrite(filepath_speech + "all.wav", data, fs);

    end
end