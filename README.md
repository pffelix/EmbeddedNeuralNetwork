<!-- #######  Machine Learning on MicroConrollers Project #########-->
<h1 style="color: #5e9ca0;">Machine Learning on Micro Controllers Course <span style="color: #2b2301;">Project:</span></h1>
<h2 style="color: #2e6c80;">Indoor Speech Localization</h2>
<p>&nbsp;</p>
<p>for generated incident angle dependent speech files, literature papers, photos, and other files please go to the following link:</p>
<p style="text-align: center;"><a title="ML_on_MCU_SoundLocalization" href="https://polybox.ethz.ch/index.php/s/dZg2X58Fk4XyTp1" target="_blank" rel="noopener">ETH Zurich Polybox</a></p>
<p style="color: #2e6c80;"><span style="color: #0000ff;">Source-Codes folder structure: (/src/)</span></p>
<ol style="list-style: none; font-size: 14px; line-height: 32px; font-weight: bold;">
<li style="clear: both;">"/AudioRecording" folder contains C-code to record audio (Sine-Sweeps in the project) from different angles for varying sample rates and send over UART</li>
<li style="clear: both;"><br />"/Firmware" folder contains final implemented classification C-code to predict the incident angle of sound</li>
<li style="clear: both;"></li>
<li style="clear: both;"></li>
<li style="clear: both;">"/QmnFirmware" folder contains feature extraction and classification C-code based on Qmn format instead of floating-point as in the firmware. UNDER DEVELOPMENT</li>
<li style="clear: both;"></li>
<li style="clear: both;"></li>
<li style="clear: both;">"/Matlab" folder contains Matlab-code for impulse response extraction of the sine-sweep recorded angles, convolving them with CMU speech database and saving .wav files of extracted features (Short-Time Fourier Transforms).</li>
<li style="clear: both;"></li>
<li style="clear: both;"></li>
<li style="clear: both;">"/PythonCode" folder contains Python-code for neural network development, quantization, and verification.</li>
</ol>
<p><span style="color: #0000ff;"><strong>&nbsp;generated Reports folder structure: (/reports/)</strong></span></p>
<ol style="list-style: none; font-size: 14px; line-height: 32px; font-weight: bold;">
<li style="clear: both;">This folder contains reports of the verified neural networks on the target on the verification dataset and comparison in an Excel format.</li>
</ol>