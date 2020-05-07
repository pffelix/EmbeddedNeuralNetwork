%% paramters
type = "48k";
version = "1";
angles = 0:45:359; 

%% run
for i=1:length(angles)
    filename = type + "_" + version + "_" + angles(i) + "degree";
    fprintf(filename + "\n");
    run("extract_impulse_response.m");
end