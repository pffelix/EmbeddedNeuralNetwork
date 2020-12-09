<!-- #######  Neural Networks for STM32L475 MicroConroller Implementation #########-->
![image_setup](images/setup.png?raw=true)
<h1 style="color: #5e9ca0;">Neural Networks for STM32L475 Microcontroller</h1>
<h2 style="color: #2e6c80;">Implementation usable for Indoor Speech Localization</h2>
<p>&nbsp;</p>
<p><span style="color: #0000ff;"><strong>&nbsp;Source-Code folder structure: (/src/)</strong></span></p>
<ol style="list-style: none; font-size: 14px; line-height: 32px; font-weight: bold;">
<li style="clear: both;">"/AudioRecording" folder contains C-code to record audio (Sine-Sweeps in the project) from different angles for varying sample rates and send over UART.<br /></li>
<li style="clear: both;">"/Matlab" folder contains Matlab-code for impulse response extraction of the sine-sweep recorded angles, convolving them with CMU speech database and saving .wav files of extracted features (Short-Time Fourier Transforms).<br /></li>
<li style="clear: both;">"/PythonCode" folder contains Python and IPython Notebook code for neural network development, quantization, and verification.<br /></li>
<li style="clear: both;">"/Firmware" folder contains final implemented classification C-code to predict the incident angle of sound.<br /></li>
<li style="clear: both;">"/QmnFirmware" folder contains feature extraction and classification C-code based on Qmn format instead of floating-point as in the firmware. UNDER DEVELOPMENT<br /></li>
</ol>
<p><span style="color: #0000ff;"><strong>&nbsp;Generated reports folder structure: (/reports/)</strong></span></p>
<ol style="list-style: none; font-size: 14px; line-height: 32px; font-weight: bold;">
<li style="clear: both;">This folder contains reports of the verified neural networks on the target on the verification dataset and comparison in an Excel format.</li>
</ol>