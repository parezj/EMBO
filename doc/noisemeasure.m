%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                  Noise measurement                  %
%             with Matlab Implementation              %
%                                                     %
% Author: M.Sc. Eng. Hristo Zhivomirov       07/15/12 %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function noisemeasure(x, fs, w)

% function: noisemeasure(x, fs)
% x - singnal in the time domain
% fs - sampling frequency, Hz

% signal length
N = length(x);

% time vector
t = (0:N-1)/fs;

% remove the DC component
x = x - mean(x);

% PSD (Power Spectral Density ,Vrms^2/Hz)
% [PSD,F] = PWELCH(X,WINDOW,NOVERLAP,NFFT,Fs)
win = hanning(w, 'periodic');
[PSD, f] = pwelch(x, win, w/2, N, fs, 'onesided');
PSDdB = 10*log10(PSD);

% PS (Power spectrum, Vrms^2) & AS (Amplitude Spectrum, Vrms)
S1 = sum(win);
S2 = sum(win.^2);
NENBW = length(win)*S2/(S1^2);
ENBW = (fs/N)*NENBW;
PS = PSD.*ENBW;
PSdB = 10*log10(PS);
AS = sqrt(PS);
ASdB = 20*log10(AS);

% plot the signal
figure(1)
subplot(2, 1, 1)
plot(t, x, 'r')
grid on
hold on
lim = 1.1*max(abs(x));
xlim([0 max(t)])
ylim([-lim lim])
set(gca, 'FontName', 'Times New Roman', 'FontSize', 13)
xlabel('Time, s')
ylabel('Amplitude, V')
title('Signal in the time domain')

% plot the AS
subplot(2, 3, 4)
plot(f, ASdB, 'r', 'LineWidth', 2)
grid on
xlim([0 max(f)])
set(gca, 'FontName', 'Times New Roman', 'FontSize', 13)
xlabel('Frequency, Hz')
ylabel('Magnitude, dBV_{rms}')
title('Amplitude Spectrum of the signal')

% plot the PS
subplot(2, 3, 5)
plot(f, PSdB, 'r', 'LineWidth', 2)
grid on
xlim([0 max(f)])
set(gca, 'FontName', 'Times New Roman', 'FontSize', 13)
xlabel('Frequency, Hz')
ylabel('Magnitude, dBV_{rms}^2')
title('Power Spectrum of the signal')

% plot the PSD 
subplot(2, 3, 6)
plot(f, PSDdB, 'r', 'LineWidth', 2)
grid on
xlim([0 max(f)])
set(gca, 'FontName', 'Times New Roman', 'FontSize', 13)
xlabel('Frequency, Hz')
ylabel('Magnitude, dBV_{rms}^{2}/Hz (dBW/Hz)')
title('Power Spectral Density of the signal')

% A-weighting filter
xA = filterA(x, fs, 0);     % filtering

% PSD (Power Spectral Density ,Vrms^2/Hz) of the weighted signal
win = hanning(512);
[PSDA, f] = pwelch(xA, win, 256, N, fs, 'onesided');
PSDAdB = 10*log10(PSDA);

% plot the A-weighted signal
subplot(2, 1, 1)
plot(t, xA, '-b')
legend('Original signal', 'A-weighted signal')

% displey the average PSD & ASD before A-weighting
PSDavr = mean(PSD);
ASDavr = sqrt(PSDavr);
disp(['Average Amplitude Spectral Density before A-weighting = ' num2str(ASDavr) ' Vrms/sqrtHz'])
disp(['Average Power Spectral Density before A-weighting = ' num2str(PSDavr) ' Vrms^2/Hz'])

% displey the average PSD & ASD after A-weighting
PSDAavr = mean(PSDA);
ASDAavr = sqrt(PSDAavr);
disp(['Average Amplitude Spectral Density after A-weighting = ' num2str(ASDAavr) ' Vrms/sqrtHz'])
disp(['Average Power Spectral Density after A-weighting = ' num2str(PSDAavr) ' Vrms^2/Hz'])

% calculating output noise U, Vrms (by Oscilloscope) before A-weighting (Reference To Output)
Urms_noise_O = 1000*(max(x) - min(x))/6.8; % calculating the output noise in mVrms using 99.7% assurance
disp(['Output noise (by Oscilloscope) before A-weighting = ' num2str(Urms_noise_O) ' mVrms or ' num2str(20*log10(Urms_noise_O/1000)) ' dBV'])

% calculating output noise U, Vrms (by TrueRMS Voltmeter) before A-weighting (Reference To Output)
Urms_noise_V = 1000*sqrt(mean(x.^2));
disp(['Output noise (by TrueRMS Voltmeter) before A-weighting = ' num2str(Urms_noise_V) ' mVrms or ' num2str(20*log10(Urms_noise_V/1000)) ' dBV'])

% calculating output noise U, Vrms (by Oscilloscope) after A-weighting (Reference To Output)
Urms_noise_OA = 1000*(max(xA) - min(xA))/6.8; % calculating the output noise in mVrms using 99.7% assurance
disp(['Output noise (by Oscilloscope) after A-weighting = ' num2str(Urms_noise_OA) ' mVrms or ' num2str(20*log10(Urms_noise_OA/1000)) ' dBV'])

% calculating output noise U, Vrms (by TrueRMS Voltmeter) after A-weighting (Reference To Output)
Urms_noise_VA = 1000*sqrt(mean(xA.^2));
disp(['Output noise (by TrueRMS Voltmeter) after A-weighting = ' num2str(Urms_noise_VA) ' mVrms or ' num2str(20*log10(Urms_noise_VA/1000)) ' dBV'])