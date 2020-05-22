%% config
set(0,'defaultfigurecolor',[1 1 1]);
set(0, 'defaultFigurePosition', [          178        1483         580         529 ]    );
fs = 16000;

%%
figure(1)
plot_on = true;
if plot_on
    path = "E:\Eigene Dateien\Eigene Dokumente\Polybox\EmbeddedLocalization\database\cmu_us\cmu_us_jmk_arctic\wav\arctic_a0001.wav";
    [data, fs] = audioread(path);
    data = data(1:49000,:);
    spectrogram(data,128,120,128,16000, 'yaxis')
    set(gca,'FontSize', 28);
end

%%
figure(2)
plot_on = true;
if plot_on
    path = "E:\Eigene Dateien\Eigene Dokumente\Polybox\EmbeddedLocalization\recording\ir\16k_1_0degree_short.wav";
    [data, fs] = audioread(path);
    data = data(1:end/10,:);
    t = (1:length(data))/fs;
    plot(t, data)
    ylim([-1,1]);
    legend("left", "right")
    ylabel("Amplitude");
    xlabel("Time");
    set(gca,'FontSize', 28);
end

%%
figure(3)
plot_on = true;
if plot_on
    path = "E:\Eigene Dateien\Eigene Dokumente\Polybox\EmbeddedLocalization\database\cmu_us\cmu_us_jmk_arctic\wav\arctic_a0001.wav";
    [data, fs] = audioread(path);
    data = data(1:49000,:);
    t = (1:length(data))/fs;
    plot(t, data, 'g')
    ylim([-1,1]);
    ylabel("Amplitude");
    xlabel("Time");
    set(gca,'FontSize', 28);
end