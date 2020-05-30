%% paramters
ir_type = "16k";
ir_version = "1";
ir_angles = 0:45:359; 
speech_types = ["cmu_us_bdl_arctic", "cmu_us_jmk_arctic", "cmu_us_ksp_arctic", "cmu_us_rms_arctic", "cmu_us_slt_arctic", "cmu_us_clb_arctic"];

%% run
for i=1:length(ir_angles)
    filename_ir = ir_type + "_" + ir_version + "_" + ir_angles(i) + "degree";
    fprintf(filename_ir + "\n");
    for j=1:length(speech_types)
        filename_speech = speech_types(j);
        fprintf(filename_speech + "\n");
        run("extract_speech.m");
    end
end