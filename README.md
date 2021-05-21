
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8" />
	<meta name="generator" content="HelpNDoc Personal Edition 6.1.0.206">
	<title>EMBO</title>
	<style type="text/css">
	/* ========== Text Styles ========== */
hr { color: #000000}
body, table, span.rvts0 /* Normal text */
{
 font-size: 10pt;
 font-family: 'Arial', 'Helvetica', sans-serif;
 font-style: normal;
 font-weight: normal;
 color: #000000;
 text-decoration: none;
}
span.rvts1 /* Heading */
{
 font-weight: bold;
 color: #0000ff;
}
span.rvts2 /* Subheading */
{
 font-weight: bold;
 color: #000080;
}
span.rvts3 /* Keywords */
{
 font-style: italic;
 color: #800000;
}
a.rvts4, span.rvts4 /* Jump 1 */
{
 color: #008000;
 text-decoration: underline;
}
a.rvts5, span.rvts5 /* Jump 2 */
{
 color: #008000;
 text-decoration: underline;
}
span.rvts6
{
}
span.rvts7
{
 font-weight: bold;
 color: #0000ff;
}
span.rvts8
{
 font-weight: bold;
 color: #000080;
}
span.rvts9
{
 font-style: italic;
 color: #800000;
}
a.rvts10, span.rvts10
{
 color: #008000;
 text-decoration: underline;
}
span.rvts11
{
 font-size: 12pt;
 font-family: 'Verdana', 'Geneva', sans-serif;
 color: #000000;
}
a.rvts12, span.rvts12
{
 font-size: 12pt;
 font-family: 'Verdana', 'Geneva', sans-serif;
 color: #000000;
 text-decoration: underline;
}
span.rvts13
{
 font-size: 12pt;
 font-family: 'Verdana', 'Geneva', sans-serif;
 color: #000000;
 text-decoration: underline;
}
span.rvts14
{
 font-size: 12pt;
 font-family: 'Verdana', 'Geneva', sans-serif;
 font-weight: bold;
 color: #000000;
}
span.rvts15
{
 font-size: 18pt;
 font-family: 'Verdana', 'Geneva', sans-serif;
 font-weight: bold;
 color: #000000;
}
span.rvts16 /* Font Style */
{
 font-family: 'Tahoma', 'Geneva', sans-serif;
 font-style: italic;
 color: #c0c0c0;
}
a.rvts17, span.rvts17 /* Font Style */
{
 font-family: 'Tahoma', 'Geneva', sans-serif;
 font-style: italic;
 color: #6666ff;
 text-decoration: underline;
}
span.rvts18
{
 font-size: 12pt;
 font-family: 'Times New Roman', 'Times', serif;
 color: #000000;
}
/* ========== Para Styles ========== */
p,ul,ol /* Paragraph Style */
{
 text-align: left;
 text-indent: 0px;
 padding: 0px 0px 0px 0px;
 margin: 0px 0px 0px 0px;
}
.rvps1 /* Centered */
{
 text-align: center;
}
.rvps2
{
}
.rvps3
{
 text-align: center;
}
.rvps4
{
 text-align: justify;
 text-justify: inter-word;
 text-align-last: auto;
}
.rvps5 /* Paragraph Style */
{
 text-align: center;
 margin: 10px 0px 10px 0px;
}
/* ========== Lists ========== */
.list0 {text-indent: 0px; padding: 0; margin: 0 0 0 24px; list-style-position: outside; list-style-type: disc;}
.list1 {text-indent: 0px; padding: 0; margin: 0 0 0 48px; list-style-position: outside; list-style-type: circle;}
.list2 {text-indent: 0px; padding: 0; margin: 0 0 0 48px; list-style-position: outside; list-style-type: square;}
.list3 {text-indent: 0px; padding: 0; margin: 0 0 0 48px; list-style-position: outside; list-style-type: disc;}

	
		.copyright {
			font-style: italic;
			padding-top: 20px;
		}
	</style>
</head>

<body>
<p class="rvps3"><span class="rvts15">EMBedded Oscilloscope</span></p>
<p class="rvps3"><span class="rvts15"><br/></span></p>
<p class="rvps3"><img width="146" height="146" alt="" style="padding : 1px;" src="https://raw.githubusercontent.com/parezj/EMBO/master/img/icon.png"></p>
<p class="rvps3"><span class="rvts11"><br/></span></p>
<p class="rvps2"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts11">EMBO consists of 3 primary devices (oscilloscope, logic analyzer, voltmeter) and 3 secondary devices (counter, PWM and signal generator). The multiplatform PC application can be run on Windows, Linux and macOS operating systems. Stable firmware is available for STM32 series F1, F3 and L4 in HEX format, other series L0 and G0 are currently supported experimentally. The EMBO oscilloscope is intended to serve as a cheap and accessible tool for all electronics enthusiasts.</span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts13">Supported MCUs:</span></p>
<ul style="text-indent: 0px; padding: 0; margin: 0 0 0 24px; list-style-position: outside; list-style-type: disc;">
<li class="rvps4"><span class="rvts14">STM32F103C8</span></li>
<li class="rvps4"><span class="rvts14">STM32F103RE</span></li>
<li class="rvps4"><span class="rvts14">STM32F303RE</span></li>
<li class="rvps4"><span class="rvts14">STM32L412KB</span></li>
</ul>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts11">More yet to come...</span></p>
<p class="rvps2"><span class="rvts11"><br/></span></p>
<p></p>
<p class="rvps5" style="clear: both;"><span class="rvts16"></span><span class="rvts17"></span></p>
<a name="Prameters"></a><h1>Parameters</h1>
<p></p>
<p class="rvps3"><img width="890" height="390" alt="" style="padding : 1px;" src="https://raw.githubusercontent.com/parezj/EMBO/master/img/params1.png"></p>
<p class="rvps3"><span class="rvts6"><br/></span></p>
<p class="rvps3"><img width="889" height="381" alt="" style="padding : 1px;" src="https://raw.githubusercontent.com/parezj/EMBO/master/img/params2.png"></p
<p></p>
<p class="rvps5" style="clear: both;"><span class="rvts16"></span><span class="rvts17"></span></p>
<a name="Connection"></a><h1>Connection</h1>
<p></p>
<p class="rvps3"><img width="773" height="287" alt="" style="padding : 1px;" src="https://raw.githubusercontent.com/parezj/EMBO/master/img/comm_types_png_en.png"></p>
<p></p>
<p class="rvps5" style="clear: both;"><span class="rvts16"></span><span class="rvts17"></span></p>
<a name="Pinout"></a><h1>Pinout</h1>
<p></p>
<p></p>
<p class="rvps5" style="clear: both;"><span class="rvts16"></span><span class="rvts17"></span></p>
<a name="STM32F103C8"></a><h2>STM32F103C8</h2>
<p></p>
<p class="rvps3"><img width="598" height="540" alt="" style="padding : 1px;" src="https://raw.githubusercontent.com/parezj/EMBO/master/img/pinout_bluepill_png_en.png"></p>
<p></p>
<p class="rvps5" style="clear: both;"><span class="rvts16"></span><span class="rvts17"></span></p>
<a name="STM32F303RE"></a><h2>STM32F303RE</h2>
<p></p>
<p class="rvps3"><img width="679" height="697" alt="" style="padding : 1px;" src="https://raw.githubusercontent.com/parezj/EMBO/master/img/pinout_f303_png_en.png"></p>
<p></p>
<p class="rvps5" style="clear: both;"><span class="rvts16"></span><span class="rvts17"></span></p>
<a name="PCApp"></a><h1>PC App</h1>
<p></p>
<p></p>
<p class="rvps5" style="clear: both;"><span class="rvts16"></span><span class="rvts17"></span></p>
<a name="MainWindow"></a><h2>Main Window</h2>
<p></p>
<p class="rvps4"><span class="rvts11">After starting the PC application, the user gets to the main window with the selection of individual devices. On the left is a list of available ports (in the case of Windows OS these are COM ports, in the case of a UNIX-like system these are tty ports. The user selects the port and connects to the oscilloscope. The three panels on the right are displayed. about the microcontroller and firmware, in the middle panel there are primary devices and their parameters and in the bottom panel secondary devices are available.</span></p>
<p class="rvps3"><span class="rvts6"><br/></span></p>
<p class="rvps3"><img width="714" height="547" alt="" style="padding : 1px;" src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/main2.png"></p>
<p class="rvps3"><span class="rvts18"><br/></span></p>
<p class="rvps4"><span class="rvts11">The bottom bar (status bar) contains information about the current session, which is ideally updated with a period of 10 ms. Latency indicates the response time of the oscilloscope and Uptime indicates the time since power-up. If the communication is busy (the oscilloscope sends a lot of data), the latency can increase up to hundreds of ms when using UART (ST-LINK).</span></p>
<p class="rvps2"><span class="rvts13"><br/></span></p>
<p class="rvps2"><span class="rvts13">Description of device parameters:</span><span class="rvts11">&nbsp;</span></p>
<ul style="text-indent: 0px; padding: 0; margin: 0 0 0 24px; list-style-position: outside; list-style-type: disc;">
<li class="rvps2"><span class="rvts14">Fs</span><span class="rvts11">&nbsp;— sampling frequency in samples per second</span></li>
<li class="rvps2"><span class="rvts14">Mem</span><span class="rvts11">&nbsp;— memory depth in samples </span></li>
<li class="rvps2"><span class="rvts14">Bits</span><span class="rvts11">&nbsp;— resolution in bits </span></li>
<li class="rvps2"><span class="rvts14">Mode</span><span class="rvts11">&nbsp;— device mode (4ch 4ADC = 4 channels per 4 ADC) </span></li>
<li class="rvps2"><span class="rvts14">Port</span><span class="rvts11">&nbsp;— assignment of microcontroller ports to device channels (C0 = PC0) </span></li>
<li class="rvps2"><span class="rvts14">Max freq</span><span class="rvts11">&nbsp;— maximum frequency of input or output signal</span></li>
</ul>
<p class="rvps2"><span class="rvts11"><br/></span></p>
<p class="rvps2"><span class="rvts11"><br/></span></p>
<p></p>
<p class="rvps5" style="clear: both;"><span class="rvts16"></span><span class="rvts17"></span></p>
<a name="Oscilloscope"></a><h2>Oscilloscope</h2>
<p></p>
<p class="rvps4"><span class="rvts11">The oscilloscope is a key device of the whole system. The oscilloscope window is divided into two main blocks. In the left block there is an interactive graph, under which lie measuring elements and cursor controls. The most important controls are concentrated in the right blocks. Auxiliary and additional functions are controlled from the top menu. The lower part of the screen is set aside for the status bar.</span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps3"><img width="833" height="518" alt="" style="padding : 1px;" src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/scope.png"></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts13">Description of control panels: </span></p>
<ul style="text-indent: 0px; padding: 0; margin: 0 0 0 24px; list-style-position: outside; list-style-type: disc;">
<li class="rvps4"><span class="rvts14">Main panel</span><span class="rvts11">&nbsp;— located at the top right, basic modes (Run, Stop, Single) </span></li>
<li class="rvps4"><span class="rvts14">Trigger</span><span class="rvts11">&nbsp;— trigger settings </span></li>
<li class="rvps4"><span class="rvts14">Horizontal</span><span class="rvts11">&nbsp;— time base setting, resp. sampling frequency and memory </span></li>
<li class="rvps4"><span class="rvts14">Vertical</span><span class="rvts11">&nbsp;— channel settings and their gain and shift </span></li>
<li class="rvps4"><span class="rvts14">Utils</span><span class="rvts11">&nbsp;— additional functions (averaging, resolution, FFT) </span></li>
<li class="rvps4"><span class="rvts14">Cursors</span><span class="rvts11">&nbsp;— control of cursors </span></li>
<li class="rvps4"><span class="rvts14">Measure</span><span class="rvts11">&nbsp;— indicators of measured parameters</span></li>
</ul>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts14">Main panel </span></p>
<p class="rvps4"><span class="rvts11">As with most oscilloscopes, EMBO has 3 main modes: Run, Stop and Single. The implementation of these modes is inspired by desktop digital oscilloscopes (Agilent, Tektronix). Run mode is the primary mode with continuous data acquisition. Stop mode is used to stop acquisition and signal analysis. The special Single mode is used to capture a single event. Furthermore, in this panel, the user has the option to reset the zoom or the entire device.</span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts14">Trigger</span></p>
<p class="rvps4"><span class="rvts11">The trigger setting is also inspired by desktop devices. The default is always Auto mode, which combines the functionality of Normal mode with a timeout that allows you to see the signal in all cases. There is also an adjustable Slope, Channel, Level and pre-trigger. In Normal and Single mode, the user has the option to force a trigger, which serves as a quick preview. The indicator LED named Trig´d lights up green if the trigger was successful (flashes with each new message).</span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts14">Horizontal</span></p>
<p class="rvps4"><span class="rvts11">Horizontal parameters can be set in 2 modes. In manual mode, the user sets the sampling frequency (Fs) and memory depth per channel (Mem). In automatic mode, these 2 parameters are optimized based on the total length of the displayed signal (Width). This approach was chosen because the classic grid and settings (second / division) do not make sense here, because the graph is interactive and the user can freely zoom and move with it. Below are 2 important pieces of information. Real sampling frequency (Real Fs) with an accuracy of 6 orders of magnitude is required for sampling at the equivalent time and subsequent frequency recalculation. The maximum permissible impedance of the source signal is described in detail in the chapter.</span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts14">Vertical</span><span class="rvts11">&nbsp;</span></p>
<p class="rvps4"><span class="rvts11">Vertical adjustment allows you to turn on individual channels, adjust their gain and offset.</span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts14">Utils, Cursors and Measure </span></p>
<p class="rvps4"><span class="rvts11">Averaging is suitable for smoothing the interfered signal. Optional 8-bit mode speeds up data transfer at the expense of reduced resolution, and FFT turns on spectral analysis mode. Cursors are used to measure the signal in both axes and the measured parameters (Measure) represent the basic information about the signal.</span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts13">Description of the top menu: </span></p>
<ul style="text-indent: 0px; padding: 0; margin: 0 0 0 24px; list-style-position: outside; list-style-type: disc;">
<li class="rvps4"><span class="rvts14">Export</span><span class="rvts11">&nbsp;— export data in CSV, TXT format or as a screenshot </span></li>
<li class="rvps4"><span class="rvts14">Plot</span><span class="rvts11">&nbsp;— graph display and interpolation settings </span></li>
<li class="rvps4"><span class="rvts14">Measure</span><span class="rvts11">&nbsp;— setting of measured parameters </span></li>
<li class="rvps4"><span class="rvts14">FFT</span><span class="rvts11">&nbsp;— melting of FFT spectral analysis </span></li>
<li class="rvps4"><span class="rvts14">Math</span><span class="rvts11">&nbsp;— control of special modes (difference, XY)</span></li>
</ul>
<p></p>
<p class="rvps5" style="clear: both;"><span class="rvts16"></span><span class="rvts17"></span></p>
<a name="LogicAnalyzer"></a><h2>Logic Analyzer</h2>
<p></p>
<p class="rvps4"><span class="rvts11">The logic analyzer provides additional oscilloscope functionality for fast digital signals. Like the oscilloscope, the instrument is divided into two main blocks. In the left block there is an interactive graph that dynamically displays the appropriate number of channels, unlike the oscilloscope but below it. In the right blocks are the main controls coming from the oscilloscope. Additional functions are controlled again from the top menu. The lower part of the screen is set aside for the status bar.</span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps3"><img width="851" height="470" alt="" style="padding : 1px;" src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/la.png"></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts11">Most controls share the same functionality and design with the oscilloscope. The difference is with the trigger, where the trigger level is missing, on the contrary, the possibility to trigger on both edges (Both) has been added. Furthermore, the vertical gain and offset are missing because they do not make sense for the logic analyzer. Similarly, averaging mode, bit resolution, and FFT are also missing. </span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts13">Description of control panels: </span></p>
<ul style="text-indent: 0px; padding: 0; margin: 0 0 0 24px; list-style-position: outside; list-style-type: disc;">
<li class="rvps4"><span class="rvts14">Main panel</span><span class="rvts11">&nbsp;— located at the top right, basic modes (Run, Stop, Single) </span></li>
<li class="rvps4"><span class="rvts14">Trigger</span><span class="rvts11">&nbsp;— trigger settings </span></li>
<li class="rvps4"><span class="rvts14">Horizontal</span><span class="rvts11">&nbsp;— time base setting, resp. sampling frequency and memory </span></li>
<li class="rvps4"><span class="rvts14">Vertical</span><span class="rvts11">&nbsp;— selection of displayed channels </span></li>
<li class="rvps4"><span class="rvts14">Utils</span><span class="rvts11">&nbsp;— cursor control, data analysis (to be added later)</span></li>
</ul>
<p></p>
<p class="rvps5" style="clear: both;"><span class="rvts16"></span><span class="rvts17"></span></p>
<a name="Voltmeter"></a><h2>Voltmeter</h2>
<p></p>
<p class="rvps4"><span class="rvts11">The voltmeter is the last primary instrument of the EMBO oscilloscope. Its window is again divided into two main blocks. In the left block there is an interactive graph, under which the measured parameters and the cursor driver are displayed. In the right block there are 4 channel panels below them and below them is the main control panel (Settings).</span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps3"><img width="845" height="428" alt="" style="padding : 1px;" src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/vm.png"></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts13">Description of adjustable parameters: </span></p>
<ul style="text-indent: 0px; padding: 0; margin: 0 0 0 24px; list-style-position: outside; list-style-type: disc;">
<li class="rvps4"><span class="rvts14">Scale</span><span class="rvts11">&nbsp;— a constant by which the channel voltage is multiplied </span></li>
<li class="rvps4"><span class="rvts14">Average</span><span class="rvts11">&nbsp;— number of averaged values (1 means off) </span></li>
<li class="rvps4"><span class="rvts14">Plot Points</span><span class="rvts11">&nbsp;— the number of displayed points in the graph</span></li>
</ul>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts11">The sampling frequency is fixed at 100 Sps. This is twice the frequency of the mains voltage. When averaging mode is off, the NPLC (Number of Power Line Cycles) value is 0.5. If we increase this value (by increasing the Average value), we will significantly suppress the induced 50 Hz noise. The higher the value of Average, resp. NPLC, the slower the voltmeter measures and the more noise is suppressed. The Average mode therefore increases the accuracy of constant signal measurements. </span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts11">In addition to the main settings, you can use additional options from the top menu, which is similar to the oscilloscope. In addition to standard settings, such as interpolation or setting of measured parameters, for example, continuous recording to a file (CSV or TXT) can be switched on. The recorded signal will have a sampling frequency of 100 Sps.</span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p></p>
<p class="rvps5" style="clear: both;"><span class="rvts16"></span><span class="rvts17"></span></p>
<a name="Counter"></a><h2>Counter</h2>
<p></p>
<p class="rvps4"><span class="rvts11">The counter is a simple secondary device that can be operated in parallel with other devices. Slow mode (for signals up to approx. 1 MHz) and Fast mode (for signals from approx. 1 MHz) can be set. For slow signals, the measurement takes longer. If no signal is detected within 2 seconds, a timeout occurs. When used with an oscilloscope or logic analyzer at the maximum sampling frequency, DMA overload and sample dropping may occur.</span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps3"><img width="313" height="287" alt="" style="padding : 1px;" src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/cntr.png"></p>
<p></p>
<p class="rvps5" style="clear: both;"><span class="rvts16"></span><span class="rvts17"></span></p>
<a name="PWMGenerator"></a><h2>PWM Generator</h2>
<p></p>
<p class="rvps4"><span class="rvts11">The PWM signal generator exists with either 1 or 2 channels. In the case of 2 channels, it is a synchronous generator that can be used to control motors or to simulate signals from a quadrature encoder. The frequency is set the same for both channels. You can also set the shift separately for the channel and the offset of the second channel. Again, it should be emphasized that at high values of the sampling frequency of the oscilloscope, the measured signal may be adversely affected.</span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps3"><img width="374" height="472" alt="" style="padding : 1px;" src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/pwm.png"></p>
<p></p>
<p class="rvps5" style="clear: both;"><span class="rvts16"></span><span class="rvts17"></span></p>
<a name="SignalGenerator"></a><h2>Signal Generator</h2>
<p></p>
<p class="rvps4"><span class="rvts11">The signal generator is a secondary optional device that uses a 12-bit DAC. It is only available for those microcontrollers that have a DAC, such as the F303RE. The user can set the frequency, amplitude and offset. At high frequencies, the size of the output buffer is dynamically reduced, ie the samples per period (Size), so that the DAC manages to generate. The real frequency of the generated signal and the magnitude of the amplitude in millivolts are also shown. In Constant mode, the generator acts as a voltage source. </span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps3"><img width="536" height="330" alt="" style="padding : 1px;" src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/sgen.png"></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts13">Operation modes: </span></p>
<ul style="text-indent: 0px; padding: 0; margin: 0 0 0 24px; list-style-position: outside; list-style-type: disc;">
<li class="rvps4"><span class="rvts14">Constant</span></li>
<li class="rvps4"><span class="rvts14">Sine</span></li>
<li class="rvps4"><span class="rvts14">Triangle</span><span class="rvts11">&nbsp;</span></li>
<li class="rvps4"><span class="rvts14">Sawtooth</span></li>
<li class="rvps4"><span class="rvts14">Square</span></li>
<li class="rvps4"><span class="rvts14">Noise</span></li>
</ul>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p class="rvps4"><span class="rvts11"><br/></span></p>
<p></p>
<p class="rvps5" style="clear: both;"><span class="rvts16"></span><span class="rvts17"></span></p>
</body>
</html>

