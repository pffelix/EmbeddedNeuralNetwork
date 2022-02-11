<!-- #######  Neural Networks for STM32L475 MicroConroller Implementation #########-->
<p align="center">
<img src="images/setup.png">
</p>
<h1 style="color: #5e9ca0;">Neural Networks for STM32L475 Cortex-M4 Microcontroller</h1>
<h2 style="color: #2e6c80;">Implementation usable for Direction of Arrival (DoA) classification</h2>
<p>&nbsp;</p>

### Content
The presented firmware allows to classify the direction of arrival (DoA) of a spoken utterance by exploiting the sound reflection and scattering pattern of a microcontroller board and its surrounding area. Related fundamental research on the topic has been open-sourced in https://github.com/swing-research/scatsense.


### Architecture
We trained for the task a tiny convolutional neural network (CNN) with Tensorflow. We convolve the CMU speech recording database with measured impulse responses at varying direction of arrival. As input layer we use the extracted magnitude spectrum. As output layer we use the horizontal direction of arrival in 45° steps. We show in the following the used network architecture.

<p align="center">
<img src="images/network.png">
</p>

We provide for the shown room a pre-trained and quantized Tensorflow network with small memory footprint. In addition, we provide IPython Notebook and MATLAB Code to train tinyML networks fitting to a custom room setup. For hardware implementation of the networks we used the STMicroelectronics B-L475E-IOT01A - STM32L4 Discovery kit IoT node with X-Cube-AI Expansion Package. It provides an ARM Cortex-M4 processor, a MP34DT01 PDM microphone and additional 64-Mbit QSPI flash memory. We show in the following the hardware architecture we use for model inference.

<p align="center">
<img src="images/architecture.png">
</p>
### Implementation
After flashing the Firmware in "src/Firmware/MDK-ARM/" with Keil on the B-L475E-IOT01A Discovery kit, the recording can be started by pressing the USER button.
The user has then 3 seconds time to formulate the utterance. After it the DoA prediction is performed.
The network implementation consumes at prediction 18KB flash, 26KB Ram and 59mW power.
After perfoming the prediction the microcontroller prints the prediction probability for each of the 8 horizontal incidence angles over UART.

<p align="center">
<img src="images/prediction.png">
</p>
<p><span style="color: #0000ff;"><strong>&nbsp;Source-Code folder structure: (/src/)</strong></span></p>
<ol style="list-style: none; font-size: 14px; line-height: 32px; font-weight: bold;">
<li style="clear: both;">"/AudioRecording" folder contains C-code to record audio (Sine-Sweeps in the project) from different angles for varying sample rates and send over UART.<br /></li>
<li style="clear: both;">"/Matlab" folder contains Matlab-code for impulse response extraction of the sine-sweep recorded angles, convolving them with CMU speech database and saving .wav files of extracted features (Short-Time Fourier Transforms).<br /></li>
<li style="clear: both;">"/PythonCode" folder contains Python and IPython Notebook code for neural network development, quantization, and verification.<br /></li>
<li style="clear: both;">"/Firmware" folder contains final implemented classification C-code to extract the features using the CMSIS DSP library and predict the incident angle of sound using the pre-trained Tensorflow library.<br /></li>
<li style="clear: both;">"/QmnFirmware" folder contains feature extraction and classification C-code based on Qmn format instead of floating-point as in the firmware. UNDER DEVELOPMENT<br /></li>
</ol>
<p><span style="color: #0000ff;"><strong>&nbsp;Generated reports folder structure: (/reports/)</strong></span></p>
<ol style="list-style: none; font-size: 14px; line-height: 32px; font-weight: bold;">
<li style="clear: both;">This folder contains reports of the verified neural network variations on the target on the verification dataset and comparison in an Excel format.</li>
</ol>

### Authors
Felix Pfreundtner and Parham Davami
