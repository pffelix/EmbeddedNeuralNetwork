%% load file
clear
clc
nOrder = 6;
fs = 15988;
filepath = '../../../../recording/recs/16k_1_0degree.log';
fileID = fopen(filepath,'r');
%y = fscanf (fileID);
y = regexp(fileread(filepath), '\r?\n', 'split');
y = cellfun(@str2num,y,'UniformOutput',false);
y = y(~cellfun('isempty',y));
y = cell2mat(y);
fclose(fileID);

%% process file

L = length(y)/2;
y1 = y(1:L);
y1 = y1/32768;
y2 = y(L+1:L*2);
y2 = y2/32768;
t = 0:1/fs:(L-1)/fs;

%% plot file

figure
subplot (2,2,1);
plot (t,y1);
subplot (2,2,2);
plot (t,y2);

subplot (2,2,3);
n = 2^nextpow2(L);
Y = fft(y1,n);
P2 = abs(Y/L);
P1 = P2(1:n/2+1);
P1(2:end-1) = 2*P1(2:end-1);
plot(0:(fs/n):(fs/2-fs/n),P1(1:n/2))

subplot (2,2,4);
n = 2^nextpow2(L);
Y = fft(y2,n);
P2 = abs(Y/L);
P1 = P2(1:n/2+1);
P1(2:end-1) = 2*P1(2:end-1);
plot(0:(fs/n):(fs/2-fs/n),P1(1:n/2))



%Filtering the results
figure
subplot (2,2,3);
wn = [200 5000]/(fs/2); % filter band
[b,a] = butter (nOrder,wn);
y1f = filter (b,a,y1);
Y = fft(y1f,n);
P2 = abs(Y/L);
P1 = P2(1:n/2+1);
P1(2:end-1) = 2*P1(2:end-1);
plot(0:(fs/n):(fs/2-fs/n),P1(1:n/2))

subplot (2,2,4);
wn = [200 5000]/(fs/2); % filter band
[b,a] = butter (nOrder,wn);
y2f = filter (b,a,y2);
Y = fft(y2f,n);
P2 = abs(Y/L);
P1 = P2(1:n/2+1);
P1(2:end-1) = 2*P1(2:end-1);
plot(0:(fs/n):(fs/2-fs/n),P1(1:n/2))

subplot (2,2,1);
plot (t,y1f);
subplot (2,2,2);
plot (t,y2f);



figure
subplot (2,1,1);
spectrogram (y1f,floor(fs/20),[],[],fs,'yaxis');
subplot (2,1,2);
spectrogram (y2f,floor(fs/20),[],[],fs,'yaxis');

%% play file
player = audioplayer(y1,fs);
play (player)

%player = audioplayer(y2,fs);
%play (player)
