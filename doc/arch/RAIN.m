%% data - STM32F103

k_adc_f1 = [1.5, 7.5, 13.5, 28.5, 41.5, 55.5, 71.5, 239.5];
c_adc_f1 = 0.000000000008;
r_adc_f1 = 1000;
f_adc_f1 = 12000000;

%% data - STM32F303

k_adc_f3 = [1.5, 2.5, 4.5, 7.5, 19.5, 61.5, 181.5, 601.5];
c_adc_f3 = 0.000000000005;
r_adc_f3 = 1000;
f_adc_f3 = 72000000;

%% data - STM32L412

k_adc_l4 = [2.5, 6.5, 12.5, 24.5, 47.5, 92.5, 247.5, 640.5];
c_adc_l4 = 0.000000000005;
r_adc_l4 = 1000;
f_adc_l4 = 80000000;

%% fs - vzorkovaci frekvence

fs_f1_12 = fConv(k_adc_f1, f_adc_f1, 12) / 1000000;
fs_f3_12 = fConv(k_adc_f3, f_adc_f3, 12) / 1000000;
fs_l4_12 = fConv(k_adc_l4, f_adc_l4, 12) / 1000000;
fs_f3_8 = fConv(k_adc_f3, f_adc_f3, 8) / 1000000;
fs_l4_8 = fConv(k_adc_l4, f_adc_l4, 8) / 1000000;

%% Rin - max. vstupni impedance

Rin_f1_12 = R_AINmax(k_adc_f1, f_adc_f1, c_adc_f1, 12, r_adc_f1)
Rin_f3_12 = R_AINmax(k_adc_f3, f_adc_f3, c_adc_f3, 12, r_adc_f3)
Rin_l4_12 = R_AINmax(k_adc_l4, f_adc_l4, c_adc_l4, 12, r_adc_l4)
Rin_f3_8 = R_AINmax(k_adc_f3, f_adc_f3, c_adc_f3, 8, r_adc_f3)
Rin_l4_8 = R_AINmax(k_adc_l4, f_adc_l4, c_adc_l4, 8, r_adc_l4)

Rin_f1_12(Rin_f1_12 < 0) = 0;
Rin_f3_12(Rin_f3_12 < 0) = 0;
Rin_l4_12(Rin_l4_12 < 0) = 0;
Rin_f3_8(Rin_f3_8 < 0) = 0;
Rin_l4_8(Rin_l4_8 < 0) = 0;

Rin_f1_12_positive = Rin_f1_12(Rin_f1_12 > 0);
Rin_f3_12_positive = Rin_f3_12(Rin_f3_12 > 0);
Rin_l4_12_positive = Rin_l4_12(Rin_l4_12 > 0);
Rin_f3_8_positive = Rin_f3_8(Rin_f3_8 > 0);
Rin_l4_8_positive = Rin_l4_8(Rin_l4_8 > 0);

%% fin - max. vstupni frekvence 
fin_f1_12 = f_AINmax(Rin_f1_12_positive, 7, 3);
fin_f3_12 = f_AINmax(Rin_f3_12_positive, 7, 3);
fin_l4_12 = f_AINmax(Rin_l4_12_positive, 7, 3);
fin_f3_8 = f_AINmax(Rin_f3_8_positive, 7, 3);
fin_l4_8 = f_AINmax(Rin_l4_8_positive, 7, 3);

fin_f1_12(1) = [];
Rin_f1_12_positive(1) = [];
fin_f3_12(1) = [];
Rin_f3_12_positive(1) = [];

%% grafy 

figure
plot(fs_f1_12, Rin_f1_12, '-*', 'LineWidth', 3, 'MarkerSize', 7); hold on;
plot(fs_f3_12, Rin_f3_12, '-*', 'LineWidth', 3, 'MarkerSize', 7); hold on;
plot(fs_l4_12, Rin_l4_12, '-*', 'LineWidth', 3, 'MarkerSize', 7); hold on;
plot(fs_f3_8, Rin_f3_8, '-*', 'LineWidth', 3, 'MarkerSize', 7); hold on;
plot(fs_l4_8, Rin_l4_8, '-*', 'LineWidth', 3, 'MarkerSize', 7); hold on;
title("Závislost maximální vstupní impedance ADC STM32 na vzorkovací frekvenci");
l=legend('F103 - 12 bit','F303 - 12 bit','L412 - 12 bit','F303 - 8 bit','L412 - 8 bit','Location','northeast');
l.FontSize = 18;
set(gca, 'YScale', 'log')
xlabel("Vzorkovací frekvence [MHz]")
ylabel("Maximální vstupní impedance [Ohm]")
grid on;
set(gca, 'FontSize', 20)

figure
plot(fin_f1_12, Rin_f1_12_positive, '-*', 'LineWidth', 2); hold on;
%plot(fin_f3_12, Rin_f3_12_positive, '-*', 'LineWidth', 2); hold on;
%plot(fin_l4_12, Rin_l4_12_positive, '-*', 'LineWidth', 2); hold on;
%plot(fin_f3_8, Rin_f3_8_positive, '-*', 'LineWidth', 2); hold on;
%plot(fin_l4_8, Rin_l4_8_positive, '-*', 'LineWidth', 2); hold on;
title("Závislost maximální vstupní impedance ADC STM32 na frekvenci vstupního signálu");
l=legend('F103 - 12 bit','F303 - 12 bit','L412 - 12 bit','F303 - 8 bit','L412 - 8 bit','Location','northeast');
l.FontSize = 18;
set(gca, 'YScale', 'log')
xlabel("Frekvence vstupního signálu[Hz]")
ylabel("Maximální vstupní impedance [Ohm]")
grid on;
set(gca, 'FontSize', 20)

%% funkce

function R = R_AINmax(k, f, c, n, r)
    R = ((k - 0.5) / (f * c * log(2^(n+2)))) - r;
end

function f = f_AINmax(r, c, cp)
    f = 1 ./ (10 * r * ((c + cp)*10^-12));
end

function f = fConv(k, fADC, bit)
    f = fADC ./ (k + bit + 0.5);
end