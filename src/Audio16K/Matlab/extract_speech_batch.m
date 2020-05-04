%% paramters
ir_type = "16k";
ir_version = "1";
ir_angles = 0:45:359; 
speech_types = ["cmu_us_awb_arctic", "cmu_us_bdl_arctic", "cmu_us_jmk_arctic", "cmu_us_ksp_arctic", "cmu_us_rms_arctic"];

%% run
for i=1:length(ir_angles)
    filename_ir = type + "_" + version + "_" + ir_angles(i) + "degree";
    fprintf(filename_ir + "\n");
    for j=1:length(speech_types)
        filename_speech = speech_types(i);
        fprintf(filename_speech + "\n");
        run("extract_speech.m");
    end
end