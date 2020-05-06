%% parameters
ir_fs = 16000;
speech_fs = 16000;
mic_N = 2;
%filename_speech = "cmu_us_awb_arctic";
%filename_ir = "16k_1_180degree";
filepath_speech = "../../../../database/cmu_us/" +  filename_speech + "/" + "wav" + "/";
filepath_ir = "../../../../recording/ir/" + filename_ir + "_short.wav";
filepath_output = "../../../../recording/speech/";

%% load impulse response
ir = audioread(filepath_ir);
ir_N = length(ir);

%% generat speech files index
speech_files = dir(filepath_speech);
speech_files = {speech_files.name};
speech_files = speech_files(3:end);
speech_files_N = length(speech_files);

%% for every speech file
fprintf("process:" + "\n");
for speech_file_n=1:speech_files_N
    fprintf(speech_file_n + "/" + speech_files_N + "\n");
    %% load speech file
    speech = audioread(filepath_speech + speech_files(speech_file_n));
    speech_N = length(speech);
    
    %% adapt sampling rates
    fs = max([ir_fs, speech_fs]);
    
    %% convolve
    irspeech = zeros(speech_N + ir_N - 1, mic_N);
    for mic_n = 1:mic_N
        irspeech(:, mic_n) = fconv(speech, ir(:, mic_n));
    end
    irspeech = irspeech ./ max(max(abs(irspeech)));

    %% output
    audiowrite(filepath_output + filename_speech + "_" + speech_file_n + "_" + filename_ir + ".wav", irspeech, fs);

end
