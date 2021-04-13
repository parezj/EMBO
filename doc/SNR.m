%% data - STM32F103

%data = csvread("./EMBO_SCOPE_600kSps_600Hz.csv", 1, 0);
data1 = csvread("./__600k/EMBO_SCOPE_20210411_193148186.csv", 1, 0);
%data = csvread("./EMBO_SCOPE_6kSps_6Hz.csv", 1, 0);
data2 = csvread("./__6k/EMBO_SCOPE_20210411_193028554.csv", 1, 0);
fs1 = 600000;
fs2 = 6000;

c = containers.Map;
c('black')   = [0,      0,      0     ];
c('blue')    = [0,      0.4470, 0.7410];
c('orange')  = [0.8500, 0.3250, 0.0980];
c('red')     = [0.6350, 0.0780, 0.1840];

X1 = (data1(:,1) * 1000) + 4;
X2 = data2(:,1) * 1000;
N = length(X1);
t1 = (0:N-1)/fs1;
t2 = (0:N-1)/fs2;

rms1 = rms(X1)
std1 = std(X1)
snr1 = 20*log10(rms(X1)/std(X1))

rms2 = rms(X2)
std2 = std(X2)
snr2 = 20*log10(rms(X2)/std(X2))

%% SNR 

%ws1 = 512;
%ws2 = 32;

%[PSD1, f1] = pwelch(X,hanning(ws1, 'periodic'),ws1/2,N,fs, 'onesided');
%PSDdB1 = 10*log10(fftshift(PSD1/max(PSD1)));

%[PSD2, f2] = pwelch(X,hanning(ws2, 'periodic'),ws2/2,N,fs, 'onesided');
%PSDdB2 = 10*log10(fftshift(PSD2/max(PSD2)));

trim = 30;
X_lp1 = lowpass(X1, 1000, fs1);
X_lp1 = X_lp1(trim:end-trim);
t_lp1 = t1(trim:end-trim);

X_lp2 = lowpass(X2, 10, fs2);
X_lp2 = X_lp2(trim:end-trim);
t_lp2 = t2(trim:end-trim);

figure

subplot(2, 2, 1)
plot(t1 * 1000, X1, 'LineWidth', 1);hold on;
plot(t_lp1 * 1000, X_lp1, 'LineWidth', 2);hold on;
title("V_{BAT} (f_S = 600 kHz, T_S = 125 ns, 5000 S)");
xlabel("Čas [ms]")
ylabel("Napětí [mV]")
grid on;
l=legend('původní signál','filtrovaný signál','Location','northeast');
l.FontSize = 18;
ylim([1765 1795]);
xlim([0 8.33]);
set(gca, 'FontSize', 20)

subplot(2, 2, 2)
plot(t2 * 1000, X2, 'LineWidth', 1);hold on;
plot(t_lp2 * 1000, X_lp2, 'LineWidth', 2);hold on;
title("V_{BAT} (f_S = 6 kHz, T_S = 20 \mus, 5000 S)");
xlabel("Čas [ms]")
ylabel("Napětí [mV]")
grid on;
l=legend('původní signál','filtrovaný signál','Location','northeast');
l.FontSize = 18;
ylim([1765 1795]);
xlim([0 833]);
set(gca, 'FontSize', 20)

%{
subplot(2, 1, 2)
snr(X, fs)
%plot(f1*2,PSDdB1); hold on;
%plot(f2*2,PSDdB2); hold on;
title("Amplitudové spektrum měřeného signálu");
xlabel("Frekvence [Hz]")
ylabel("Amplituda [dBV_{rms}]")
grid on;
%l=legend('Hanning 512','Hanning 32','Location','northeast');
%l.FontSize = 18;
set(gca, 'FontSize', 20)
%}

subplot(2, 2, 3)
AllValue = X1;
fill([rms1-std1 rms1-std1 rms1+std1 rms1+std1], [1 10000 10000 1], [.9 .9 .9], 'linestyle', '--','LineWidth',2,'facealpha',0.7); hold on;
histogram(AllValue,'BinWidth',0.8,'facecolor', c('blue'));
title("SNR = " + round(snr1,2) + " dB \rightarrow ENOB = " + round(enob1,2) + " bit");
xline(rms1,'color', 'red','LineWidth',2), 
l=legend(" \sigma      = ±" + round(std1,1) + " mV",' bin   = 0.8 mV'," U_{rms} = " + round(rms1/1000,3) + " V",'Location','northeast');
l.FontSize = 18;
hold off
grid on;
xlim([1765 1795]);
xlabel("Napětí [mV]")
ylabel("Četnost [-]")
set(gca, 'FontSize', 20)
set(gca, 'YScale', 'log')


subplot(2, 2, 4)
AllValue = X2;
fill([rms2-std2 rms2-std2 rms2+std2 rms2+std2], [1 10000 10000 1], [.9 .9 .9], 'linestyle', '--','LineWidth',2,'facealpha',0.7); hold on;
histogram(AllValue,'BinWidth',0.8,'facecolor', c('blue'));
title("SNR = " + round(snr2,2) + " dB \rightarrow ENOB = " + round(enob2,2) + " bit");
xline(rms2,'color', 'red','LineWidth',2), 
l=legend(" \sigma      = ±" + round(std2,1) + " mV",' bin   = 0.8 mV'," U_{rms} = " + round(rms2/1000,3) + " V",'Location','northeast');
l.FontSize = 18;
hold off
grid on;
xlim([1765 1795]);
xlabel("Napětí [mV]")
ylabel("Četnost [-]")
set(gca, 'FontSize', 20)
set(gca, 'YScale', 'log')


%% Qe

enob1 = (snr1 - 1.76) / 6.02
enob2 = (snr2 - 1.76) / 6.02

[a, b] = linfit_([6000 600000], [enob2 enob1]);

t = 1:1:857000;
offset = 0.001;
ref = 0;

lsb = a*t + b;

t = t / 1000000;

qe_real = vLSB(lsb);

qe_real_m = ref-(qe_real/2);
qe_real_m0 = qe_real_m(1);
qe_real_m1 = qe_real_m(end);

qe_real_p = ref+(qe_real/2);
qe_real_p0 = qe_real_p(1);
qe_real_p1 = qe_real_p(end);

qe_ideal = vLSB(12);

figure
hold on;
fill([t(1)-offset t(1)-offset t(end)+offset t(end)+offset], [qe_real_m0 qe_real_p0 qe_real_p1 qe_real_m1], [.8 .8 .8], 'linestyle', '-','LineWidth',3,'facealpha',0.4,'edgecolor', c('orange')); hold on;
fill([t(1)-offset t(1)-offset t(end)+offset t(end)+offset], [ref-(qe_ideal/2) ref+(qe_ideal/2) ref+(qe_ideal/2) ref-(qe_ideal/2)], [.6 .6 .6], 'linestyle', '--','LineWidth',2,'facealpha',0.4,'edgecolor', c('black')); hold on;
yline(ref, 'color', c('blue'),'LineWidth',3)
l=legend(" STM32F103 ADC   Q_e = ± 1.5-2.0 mV", " ideální 12-bit ADC  Q_e = ± 0.4 mV", " nulová chyba (analogový signál)" , 'Location','best');
l.FontSize = 18;
grid on;
title('Porovnání kvantizační chyby ideálního a reálného AD převodníku (STM32F103)');
xlabel("Vzorkovací frekvence [MHz]")
ylabel("Kvantizační chyba [mV]")
xlim([0 0.857]);
ylim([-4 4]);
set(gca, 'FontSize', 20)

function val = vLSB(N)
    val = 3300 ./((2.^N)-1);
end

% y = ax + b
function [a, b] = linfit_(x, y)
    X = [ones(numel(x),1),x.'];
    p = X\(y.');
    b = p(1);
    a = p(2);
end