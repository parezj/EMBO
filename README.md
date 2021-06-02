<p float="left" align="center">
  <img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/icon.png" alt="EMBO" width="150" />
  &nbsp;&nbsp;&nbsp;&nbsp;
  <a href="https://meas.fel.cvut.cz/" alt="CTU"><img src="https://raw.githubusercontent.com/parezj/EMBO/master/src/software-qt/EMBO/resources/img/ctu_meas.png" height="150" /></a>
</p>

# EMBO - EMBedded Oscilloscope
> Download **[HERE](https://github.com/parezj/EMBO/releases)**  

EMBO consists of 3 primary devices (oscilloscope, logic analyzer, voltmeter) and 3 secondary devices (counter, PWM and signal generator). The multiplatform PC application can be run on Windows, Linux and macOS operating systems. Stable firmware is available for STM32 series F1, F3 and L4 in HEX format, other series L0 and G0 are currently supported experimentally. The EMBO oscilloscope is intended to serve as a cheap and accessible tool for all electronics enthusiasts. 

This work was created as part of my diploma thesis at [FEE CTU](https://meas.fel.cvut.cz/) in Prague (Department of Measurement) under the supervision of doc. Fischer and with the help of Ing. Hladík from STMicroelectronics. I would like to thank them for perfect support. Whole EMBO is published under the MIT license. 

Supported MCUs:
- **STM32F103C8**
- **STM32F103RE**
- **STM32F303RE**
- **STM32L412KB**

*More yet to come... (L0, G0, G4, F4)*

1. [Parameters](#1-Parameters)
2. [Connection](#2-Connection)
3. [Pinout](#3-Pinout)
4. [PC App Description](#4-PC-App-Description)
5. [PC App Class Diagram](#5-PC-App-Class-Diagram)
6. [FW Block Diagram](#6-FW-Block-Diagram)
7. [Used IP](#7-Used-IP)


## 1. Parameters

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/params1.png" alt="EMBO params 1" width="700">
</div>

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/params2.png" alt="EMBO params 2" width="700">
</div>

## 2. Connection

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/comm_types_png_en.png" alt="EMBO comm" width="700">
</div>

## 3. Pinout

### STM32F103C8 (Blue Pill)

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/pinout_bluepill_png_en.png" alt="EMBO pinout bluepill" width="500">
</div>

### STM32F303RE (Nucleo-64)

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/pinout_f303_png_en.png" alt="EMBO pinout F303" width="600">
</div>

## 4. PC App Description

### Main Window 
After starting the PC application, the user gets to the main window with the selection of individual devices. On the left is a list of available ports (in the case of Windows OS these are COM ports, in the case of a UNIX-like system these are tty ports. The user selects the port and connects to the oscilloscope. The three panels on the right are displayed. about the microcontroller and firmware, in the middle panel there are primary devices and their parameters and in the bottom panel secondary devices are available.

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/main2.png" alt="EMBO main2" width="700">
</div>

The bottom bar (status bar) contains information about the current session, which is ideally updated with a period of 10 ms. Latency indicates the response time of the oscilloscope and Uptime indicates the time since power-up. If the communication is busy (the oscilloscope sends a lot of data), the latency can increase up to hundreds of ms when using UART (ST-LINK).

Description of device parameters: 
- **Fs** — sampling frequency in samples per second
- **Mem** — memory depth in samples 
- **Bits** — resolution in bits 
- **Mode** — device mode (4ch 4ADC = 4 channels per 4 ADC) 
- **Port** — assignment of microcontroller ports to device channels (C0 = PC0) 
- **Max freq** — maximum frequency of input or output signal

### Oscilloscope 
The oscilloscope is a key device of the whole system. The oscilloscope window is divided into two main blocks. In the left block there is an interactive graph, under which lie measuring elements and cursor controls. The most important controls are concentrated in the right blocks. Auxiliary and additional functions are controlled from the top menu. The lower part of the screen is set aside for the status bar.

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/scope.png" alt="EMBO scope" width="800">
</div>

Description of control panels: 
- **Main panel** — located at the top right, basic modes (Run, Stop, Single) 
- **Trigger** — trigger settings 
- **Horizontal** — time base setting, resp. sampling frequency and memory 
- **Vertical** — channel settings and their gain and shift 
- **Utils** — additional functions (averaging, resolution, FFT) 
- **Cursors** — control of cursors 
- **Measure** — indicators of measured parameters

#### Main panel 
As with most oscilloscopes, EMBO has 3 main modes: Run, Stop and Single. The implementation of these modes is inspired by desktop digital oscilloscopes (Agilent, Tektronix). Run mode is the primary mode with continuous data acquisition. Stop mode is used to stop acquisition and signal analysis. The special Single mode is used to capture a single event. Furthermore, in this panel, the user has the option to reset the zoom or the entire device.

#### Trigger
The trigger setting is also inspired by desktop devices. The default is always Auto mode, which combines the functionality of Normal mode with a timeout that allows you to see the signal in all cases. There is also an adjustable Slope, Channel, Level and pre-trigger. In Normal and Single mode, the user has the option to force a trigger, which serves as a quick preview. The indicator LED named Trig´d lights up green if the trigger was successful (flashes with each new message).

#### Horizontal
Horizontal parameters can be set in 2 modes. In manual mode, the user sets the sampling frequency (Fs) and memory depth per channel (Mem). In automatic mode, these 2 parameters are optimized based on the total length of the displayed signal (Width). This approach was chosen because the classic grid and settings (second / division) do not make sense here, because the graph is interactive and the user can freely zoom and move with it. Below are 2 important pieces of information. Real sampling frequency (Real Fs) with an accuracy of 6 orders of magnitude is required for sampling at the equivalent time and subsequent frequency recalculation. The maximum permissible impedance of the source signal is described in detail in the chapter.

#### Vertical 
Vertical adjustment allows you to turn on individual channels, adjust their gain and offset.

#### Utils, Cursors and Measure 
Averaging is suitable for smoothing the interfered signal. Optional 8-bit mode speeds up data transfer at the expense of reduced resolution, and FFT turns on spectral analysis mode. Cursors are used to measure the signal in both axes and the measured parameters (Measure) represent the basic information about the signal.

Description of the top menu: 
- **Export** — export data in CSV, TXT format or as a screenshot 
- **Plot** — graph display and interpolation settings 
- **Measure** — setting of measured parameters 
- **FFT** — melting of FFT spectral analysis 
- **Math** — control of special modes (difference, XY)

### Logic Analyzer 
The logic analyzer provides additional oscilloscope functionality for fast digital signals. Like the oscilloscope, the instrument is divided into two main blocks. In the left block there is an interactive graph that dynamically displays the appropriate number of channels, unlike the oscilloscope but below it. In the right blocks are the main controls coming from the oscilloscope. Additional functions are controlled again from the top menu. The lower part of the screen is set aside for the status bar.

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/la.png" alt="EMBO la" width="800">
</div>

Most controls share the same functionality and design with the oscilloscope. The difference is with the trigger, where the trigger level is missing, on the contrary, the possibility to trigger on both edges (Both) has been added. Furthermore, the vertical gain and offset are missing because they do not make sense for the logic analyzer. Similarly, averaging mode, bit resolution, and FFT are also missing. 

Description of control panels: 
- **Main panel** — located at the top right, basic modes (Run, Stop, Single) 
- **Trigger** — trigger settings 
- **Horizontal** — time base setting, resp. sampling frequency and memory 
- **Vertical** — selection of displayed channels 
- **Utils** — cursor control, data analysis (to be added later)

### Voltmeter 
The voltmeter is the last primary instrument of the EMBO oscilloscope. Its window is again divided into two main blocks. In the left block there is an interactive graph, under which the measured parameters and the cursor driver are displayed. In the right block there are 4 channel panels below them and below them is the main control panel (Settings).

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/vm.png" alt="EMBO vm" width="800">
</div>

Description of adjustable parameters: 
- **Scale** — a constant by which the channel voltage is multiplied 
- **Average** — number of averaged values (1 means off) 
- **Plot Points** — the number of displayed points in the graph

The sampling frequency is fixed at 100 Sps. This is twice the frequency of the mains voltage. When averaging mode is off, the NPLC (Number of Power Line Cycles) value is 0.5. If we increase this value (by increasing the Average value), we will significantly suppress the induced 50 Hz noise. The higher the value of Average, resp. NPLC, the slower the voltmeter measures and the more noise is suppressed. The Average mode therefore increases the accuracy of constant signal measurements. 

In addition to the main settings, you can use additional options from the top menu, which is similar to the oscilloscope. In addition to standard settings, such as interpolation or setting of measured parameters, for example, continuous recording to a file (CSV or TXT) can be switched on. The recorded signal will have a sampling frequency of 100 Sps.

### Counter 
The counter is a simple secondary device that can be operated in parallel with other devices. Slow mode (for signals up to approx. 1 MHz) and Fast mode (for signals from approx. 1 MHz) can be set. For slow signals, the measurement takes longer. If no signal is detected within 2 seconds, a timeout occurs. When used with an oscilloscope or logic analyzer at the maximum sampling frequency, DMA overload and sample dropping may occur.

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/cntr.png" alt="EMBO cntr" width="250">
</div>

### PWM Generator 
The PWM signal generator exists with either 1 or 2 channels. In the case of 2 channels, it is a synchronous generator that can be used to control motors or to simulate signals from a quadrature encoder. The frequency is set the same for both channels. You can also set the shift separately for the channel and the offset of the second channel. Again, it should be emphasized that at high values of the sampling frequency of the oscilloscope, the measured signal may be adversely affected.

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/pwm.png" alt="EMBO pwm" width="300">
</div>

### Signal Generator 
The signal generator is a secondary optional device that uses a 12-bit DAC. It is only available for those microcontrollers that have a DAC, such as the F303RE. The user can set the frequency, amplitude and offset. At high frequencies, the size of the output buffer is dynamically reduced, ie the samples per period (Size), so that the DAC manages to generate. The real frequency of the generated signal and the magnitude of the amplitude in millivolts are also shown. In Constant mode, the generator acts as a voltage source. 

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/sgen.png" alt="EMBO sgen" width="450">
</div>

Operation modes: 
- **Constant**
- **Sine**
- **Triangle**
- **Sawtooth**
- **Square**
- **Noise**

## 5. PC App Class Diagram

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/qt_classes_png_en.png" alt="EMBO PC class diagram" width="700">
</div>

## 6. FW Block Diagram

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/periferie_png_en.png" alt="EMBO fw block diagram" width="700">
</div>

## 7. Used IP
- **[SCPI Parser](https://github.com/j123b567/scpi-parser)**  (Jan Breuer)
- **[FreeRTOS](https://www.freertos.org/)**
- **[SEGGER SystemView](https://www.segger.com/products/development-tools/systemview/)**
- **[QCustomPlot](https://www.qcustomplot.com/)**
- **[FFTW3](http://www.fftw.org/)**
- **[qBreakpad](https://github.com/buzzySmile/qBreakpad)**
- **[Google Breakpad](https://github.com/google/breakpad)**
- **[QSimpleUpdater](https://github.com/alex-spataru/QSimpleUpdater)**


