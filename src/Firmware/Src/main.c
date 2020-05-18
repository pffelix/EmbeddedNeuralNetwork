/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_x-cube-ai.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <arm_math.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/*
********************      Exact Sample Rates:
														16000   -->> 	15988
														24000   -->>  24038
														32000   -->>  32609
														40000   -->>  40179
														44100		-->>  44118
														48000   -->>  48077
*/
#define SampleRate	16000 //16000/24000/32000/40000/44000/48000

#define ShiftRight	16		// Adjust Shift right to your loudness


#define mem0BaseAddr 0x00000000
#define mem1BaseAddr 0x00400000
#define QUEUELENGTH 512
#define QUEUELENGTH_Half 256
#define QueDataHalf_1st	0
#define QueDataHalf_2nd	64
#define QueDataHalf_3rd	128
#define QueDataHalf_4th	192
#define QueDataFull_1st	256
#define QueDataFull_2nd	320
#define QueDataFull_3rd	384
#define QueDataFull_4th	448
#define HAL_QSPI_TIMEOUT	180000U // 180 sec //

// define
#define CEILING(x,y) (((x) + (y) - 1) / (y))
#define RecSeconds 3
#define RecN RecSeconds * SampleRate
#define FftN 512
#define FfthalfN ((FftN / 2) + 1)
#define FftNSave ((FftN / 8) + 1)
//#define FftT CEILING(RecN, FftN)
#define FftT 96
#define FeatureN RecN
#define MicN 2
#define UNUSEDVARIABLE(x) (void)(x)
	

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

DFSDM_Filter_HandleTypeDef hdfsdm1_filter0;
DFSDM_Filter_HandleTypeDef hdfsdm1_filter1;
DFSDM_Channel_HandleTypeDef hdfsdm1_channel1;
DFSDM_Channel_HandleTypeDef hdfsdm1_channel2;
DMA_HandleTypeDef hdma_dfsdm1_flt0;
DMA_HandleTypeDef hdma_dfsdm1_flt1;

QSPI_HandleTypeDef hqspi;

TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart1;

DMA_HandleTypeDef hdma_memtomem_dma2_channel1;
/* USER CODE BEGIN PV */
volatile bool bufferFull = false;
volatile bool bufferHalfFull = false;
volatile bool recording = false;
volatile bool qspiSendReady = true;

QSPI_CommandTypeDef QSPI_Cmd;
uint32_t mem0Addr = mem0BaseAddr;
uint32_t mem1Addr = mem1BaseAddr;

uint8_t recMem1[256],recMem0[256];
int16_t sendMem1[128],sendMem0[128];
int32_t recBuff1[QUEUELENGTH],recBuff0[QUEUELENGTH];
int16_t amplitude0,amplitude1;

uint8_t state=0;

uint16_t numFull=0,numDetected=0;

// Feature extraction variables
arm_cfft_radix2_instance_f32 fft_struct;
// declare
float32_t* recBuffer;
float32_t* fftBuffer;
uint16_t Fftt;
uint16_t Fftn;
uint8_t Micn;

float32_t mag_max0,mag_max1,mag_max;

// Feature output == NN input data
float32_t featureBuffer[FftT][FftNSave][MicN];
// NN output data
float32_t outputclassified[8];
// 
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_DFSDM1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_QUADSPI_Init(void);
static void MX_TIM1_Init(void);
static void MX_CRC_Init(void);
/* USER CODE BEGIN PFP */

// QSPI memory related functions
static void QSPI_WriteEnable(QSPI_HandleTypeDef *hqspi);
static void QSPI_AutoPollingMemReady(QSPI_HandleTypeDef *hqspi);
static void QSPI_AutoPollingMemReadyIT(QSPI_HandleTypeDef *hqspi);
static void QSPI_Erase(QSPI_HandleTypeDef *QSPIHandle);
static void QSPI_Initilize(QSPI_HandleTypeDef *hqspi);
static void QSPI_Send(QSPI_HandleTypeDef *hqspi,uint8_t *sendData,uint32_t NbData, uint32_t Addr);
static void QSPI_Receive(QSPI_HandleTypeDef *hqspi,uint8_t *receiveData,uint32_t NbData, uint32_t Addr);

// Feature calculation functions
void featureInit(void);
void featureUpdate(float32_t* inputBuffer);
void featureClean(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#ifdef __GNUC__
/* With GCC/RAISONANCE, small msg_info (option LD Linker->Libraries->Small msg_info
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the serial port and Loop until the end of transmission */
  while (HAL_OK != HAL_UART_Transmit(&huart1, (uint8_t *) &ch, 1, 30000))
  {
    ;
  }
  return ch;
}

/**
  * @brief Retargets the C library scanf function to the USART.
  * @param None
  * @retval None
  */
GETCHAR_PROTOTYPE
{
  /* Place your implementation of fgetc here */
  /* e.g. readwrite a character to the USART2 and Loop until the end of transmission */
  uint8_t ch = 0;
  while (HAL_OK != HAL_UART_Receive(&huart1, (uint8_t *)&ch, 1, 30000))
  {
    ;
  }
  return ch;
}


void HAL_DFSDM_FilterRegConvCpltCallback(DFSDM_Filter_HandleTypeDef *hdfsdm_filter)
{
	if (hdfsdm_filter == &hdfsdm1_filter0){
		numFull++;
		if (!bufferFull){
			numDetected++;
			bufferFull = true;
		}
	}
}
void HAL_DFSDM_FilterRegConvHalfCpltCallback(DFSDM_Filter_HandleTypeDef *hdfsdm_filter)
{
	if (!bufferHalfFull && hdfsdm_filter == &hdfsdm1_filter0)
		bufferHalfFull = true;
}
void HAL_QSPI_StatusMatchCallback(QSPI_HandleTypeDef *hqspi)
{
	qspiSendReady = true;
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == PushButton_Pin){
		switch (state){
			case 0:
				HAL_GPIO_WritePin (LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
				state = 1;
			break;
			case 1:
				HAL_GPIO_WritePin (LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
				state = 2;
			break;
			case 2:
				HAL_GPIO_WritePin (LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
				state = 0;
			break;
		}
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_DFSDM1_Init();
  MX_USART1_UART_Init();
  MX_QUADSPI_Init();
  MX_TIM1_Init();
  MX_CRC_Init();
  MX_X_CUBE_AI_Init();
  /* USER CODE BEGIN 2 */
	printf("Hello\n");
	
	//	Initilize the QSPI
	HAL_NVIC_DisableIRQ (EXTI15_10_IRQn);
	QSPI_Initilize (&hqspi);
	printf("Initilize memory Done\n");
	HAL_NVIC_EnableIRQ (EXTI15_10_IRQn);
	
	// Init feature calculation
	printf("init feature calculation\n");
	featureInit();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		switch (state){
			case 0: //Idle time at the start before recording
				printf("Idle\n");
				numDetected = 0;
				numFull = 0;
				mem0Addr = mem0BaseAddr;
				mem1Addr = mem1BaseAddr;
				recording = false;
				HAL_Delay (1000);
				featureClean();
				break;
			
			case 1: //Start Recording and send to mem on every half full
							
				// Start Recording Command for both channels
				if (recording == false){
					recording = true;
					if(HAL_OK != HAL_DFSDM_FilterRegularStart_DMA(&hdfsdm1_filter1, recBuff1, QUEUELENGTH)){
						printf("error in filter1\n");
						Error_Handler();
					}
					if(HAL_OK != HAL_DFSDM_FilterRegularStart_DMA(&hdfsdm1_filter0, recBuff0, QUEUELENGTH)){
						printf("error in filter0\n");
						Error_Handler();
					}
					printf("Wait for 3sec for valid data\n");
					HAL_Delay(3000);
					printf("started recording\n");
				}
				
				// Save data to qspi flash mem
				// First, shift data to the right for sufficient amount, according to your speaker's volume
				// Then, send 16bit data to the 16bit registers with DMA
				// Finally, save data through qspi on the flash memory
				if (bufferHalfFull){
					
					for(int i=QueDataHalf_1st;i<QueDataHalf_3rd;i++){
						recBuff0[i] = recBuff0[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff0[QueDataHalf_1st],(uint32_t)sendMem0,128);
					HAL_DMA_PollForTransfer (&hdma_memtomem_dma2_channel1,HAL_DMA_FULL_TRANSFER,10);
					QSPI_Send (&hqspi,(uint8_t *)sendMem0,256,mem0Addr);
					mem0Addr +=256;
					
					for(int i=QueDataHalf_1st;i<QueDataHalf_3rd;i++){
						recBuff1[i] = recBuff1[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff1[QueDataHalf_1st],(uint32_t)sendMem1,128);
					HAL_DMA_PollForTransfer (&hdma_memtomem_dma2_channel1,HAL_DMA_FULL_TRANSFER,10);
					QSPI_Send (&hqspi,(uint8_t *)sendMem1,256,mem1Addr);
					mem1Addr +=256;
					
					
					for(int i=QueDataHalf_3rd;i<QUEUELENGTH_Half;i++){
						recBuff0[i] = recBuff0[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff0[QueDataHalf_3rd],(uint32_t)sendMem0,128);
					HAL_DMA_PollForTransfer (&hdma_memtomem_dma2_channel1,HAL_DMA_FULL_TRANSFER,10);
					QSPI_Send (&hqspi,(uint8_t *)sendMem0,256,mem0Addr);
					mem0Addr +=256;
					
					for(int i=QueDataHalf_3rd;i<QUEUELENGTH_Half;i++){
						recBuff1[i] = recBuff1[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff1[QueDataHalf_3rd],(uint32_t)sendMem1,128);
					HAL_DMA_PollForTransfer (&hdma_memtomem_dma2_channel1,HAL_DMA_FULL_TRANSFER,10);
					QSPI_Send (&hqspi,(uint8_t *)sendMem1,256,mem1Addr);
					mem1Addr +=256;
					
					bufferHalfFull = false;
				}
				
				if (bufferFull){					
					
					for(int i=QueDataFull_1st;i<QueDataFull_3rd;i++){
						recBuff0[i] = recBuff0[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff0[QueDataFull_1st],(uint32_t)sendMem0,128);
					HAL_DMA_PollForTransfer (&hdma_memtomem_dma2_channel1,HAL_DMA_FULL_TRANSFER,10);
					QSPI_Send (&hqspi,(uint8_t *)sendMem0,256,mem0Addr);
					mem0Addr +=256;
					
					for(int i=QueDataFull_1st;i<QueDataFull_3rd;i++){
						recBuff1[i] = recBuff1[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff1[QueDataFull_1st],(uint32_t)sendMem1,128);
					HAL_DMA_PollForTransfer (&hdma_memtomem_dma2_channel1,HAL_DMA_FULL_TRANSFER,10);
					QSPI_Send (&hqspi,(uint8_t *)sendMem1,256,mem1Addr);
					mem1Addr +=256;
					
					
					for(int i=QueDataFull_3rd;i<QUEUELENGTH;i++){
						recBuff0[i] = recBuff0[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff0[QueDataFull_3rd],(uint32_t)sendMem0,128);
					HAL_DMA_PollForTransfer (&hdma_memtomem_dma2_channel1,HAL_DMA_FULL_TRANSFER,10);
					QSPI_Send (&hqspi,(uint8_t *)sendMem0,256,mem0Addr);
					mem0Addr +=256;
					
					for(int i=QueDataFull_3rd;i<QUEUELENGTH;i++){
						recBuff1[i] = recBuff1[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff1[QueDataFull_3rd],(uint32_t)sendMem1,128);
					HAL_DMA_PollForTransfer (&hdma_memtomem_dma2_channel1,HAL_DMA_FULL_TRANSFER,10);
					QSPI_Send (&hqspi,(uint8_t *)sendMem1,256,mem1Addr);
					mem1Addr +=256;
					
					bufferFull = false;
				}
				break;
			case 2: // Recording Done, Sending Data over UART to the system
				HAL_DFSDM_FilterRegularStop_DMA (&hdfsdm1_filter1);
				HAL_DFSDM_FilterRegularStop_DMA (&hdfsdm1_filter0);
				recording = false;
				HAL_NVIC_DisableIRQ (EXTI15_10_IRQn);
				printf("Stopped Recording and Send Data Over\n");
			
				if (bufferHalfFull){					
					
					for(int i=QueDataHalf_1st;i<QueDataHalf_3rd;i++){
						recBuff0[i] = recBuff0[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff0[QueDataHalf_1st],(uint32_t)sendMem0,128);
					QSPI_Send (&hqspi,(uint8_t *)sendMem0,256,mem0Addr);
					mem0Addr +=256;
					
					for(int i=QueDataHalf_1st;i<QueDataHalf_3rd;i++){
						recBuff1[i] = recBuff1[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff1[QueDataHalf_1st],(uint32_t)sendMem1,128);
					QSPI_Send (&hqspi,(uint8_t *)sendMem1,256,mem1Addr);
					mem1Addr +=256;
					
					
					for(int i=QueDataHalf_3rd;i<QUEUELENGTH_Half;i++){
						recBuff0[i] = recBuff0[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff0[QueDataHalf_3rd],(uint32_t)sendMem0,128);
					QSPI_Send (&hqspi,(uint8_t *)sendMem0,256,mem0Addr);
					mem0Addr +=256;
					
					for(int i=QueDataHalf_3rd;i<QUEUELENGTH_Half;i++){
						recBuff1[i] = recBuff1[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff1[QueDataHalf_3rd],(uint32_t)sendMem1,128);
					QSPI_Send (&hqspi,(uint8_t *)sendMem1,256,mem1Addr);
					mem1Addr +=256;
					
					bufferHalfFull = false;
				}
				
				if (bufferFull){					
					
					for(int i=QueDataFull_1st;i<QueDataFull_3rd;i++){
						recBuff0[i] = recBuff0[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff0[QueDataFull_1st],(uint32_t)sendMem0,128);
					QSPI_Send (&hqspi,(uint8_t *)sendMem0,256,mem0Addr);
					mem0Addr +=256;
					
					for(int i=QueDataFull_1st;i<QueDataFull_3rd;i++){
						recBuff1[i] = recBuff1[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff1[QueDataFull_1st],(uint32_t)sendMem1,128);
					QSPI_Send (&hqspi,(uint8_t *)sendMem1,256,mem1Addr);
					mem1Addr +=256;
					
					
					for(int i=QueDataFull_3rd;i<QUEUELENGTH;i++){
						recBuff0[i] = recBuff0[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff0[QueDataFull_3rd],(uint32_t)sendMem0,128);
					QSPI_Send (&hqspi,(uint8_t *)sendMem0,256,mem0Addr);
					mem0Addr +=256;
					
					for(int i=QueDataFull_3rd;i<QUEUELENGTH;i++){
						recBuff1[i] = recBuff1[i]>>ShiftRight;
					}
					HAL_DMA_Start (&hdma_memtomem_dma2_channel1,(uint32_t)&recBuff1[QueDataFull_3rd],(uint32_t)sendMem1,128);
					QSPI_Send (&hqspi,(uint8_t *)sendMem1,256,mem1Addr);
					mem1Addr +=256;
					
					bufferFull = false;
				}
				


				// Recieve data from QSPI mem and send over UART
				// First part of data is from channel 0
				// Second part of data is from channel 1
				printf ("Number of buffer full: %d\n",numFull);
				printf ("Number of detected full: %d\n",numDetected);
				mem0Addr -=256;
				Micn = 0; // microphone number
				Fftn = 0; // fft bin number
				Fftt = 0; // fft window number
				for (uint32_t addr=mem0BaseAddr; addr<=mem0Addr; addr+=256){
					QSPI_Receive (&hqspi,recMem0,256,addr);
					for (int i=0;i<256;i+=2){
						amplitude0 = (int16_t)(((uint16_t) recMem0[i]) + (((uint16_t) recMem0[i+1])<<8));
						//printf ("%i\n",amplitude0);
						// Update feature calculation
						if(Fftt < FftT){
							recBuffer[Fftn] = ((float32_t)amplitude0)/32768.0f;
							if(Fftn == FftN){
								Fftn = 0;
								featureUpdate(recBuffer);
								Fftt += 1;
							}else{
								Fftn += 1;
							}
						}
					}
				}
				mem1Addr -=256;
				Micn = 1;
				Fftn = 0;
				Fftt = 0;
				for (uint32_t addr=mem1BaseAddr; addr<=mem1Addr; addr+=256){
					QSPI_Receive (&hqspi,recMem1,256,addr);
					for (int i=0;i<256;i+=2){
						amplitude1 = (int16_t)(((uint16_t) recMem1[i]) + (((uint16_t) recMem1[i+1])<<8));
						//printf ("%i\n",amplitude1);
						// Update feature calculation
						if(Fftt < FftT){
							recBuffer[Fftn] = ((float32_t)amplitude1)/32768.0f;
							if(Fftn == FftN){
								Fftn = 0;
								featureUpdate(recBuffer);
								Fftt += 1;
							}else{
								Fftn += 1;
							}
						}
					}
				}
				
		
				printf ("Finished Sending Data, Erasing memory\n");
				QSPI_Erase (&hqspi);
				
				printf ("Extracted Size: %d * %d * %d\n",Fftt,FftNSave,MicN);
				
				// normalize
				mag_max0 = mag_max0/32768.0f;
				mag_max1 = mag_max1/32768.0f;
				mag_max = mag_max1 > mag_max0 ? mag_max1 : mag_max0;
				for (int i=0;i<FftT;i++){
					for (int j=0;j<FftNSave;j++){
							featureBuffer[i][j][0] = (featureBuffer[i][j][0]/mag_max);
							featureBuffer[i][j][1] = (featureBuffer[i][j][1]/mag_max);
							printf ("%f\n",featureBuffer[i][j][0]);
					}
				}
				
				printf ("Prediction:\n");
				
				MX_X_CUBE_AI_Process();
				
				
				
				while (!qspiSendReady);
				printf ("Erasing Done\n");
				HAL_NVIC_EnableIRQ (EXTI15_10_IRQn);
				state = 0;
				
				
				// Finish feature calculation
				//featureFinish();
				
				break;
		}

    /* USER CODE END WHILE */

  //MX_X_CUBE_AI_Process();
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_SAI1
                              |RCC_PERIPHCLK_DFSDM1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLLSAI1;
  PeriphClkInit.Dfsdm1ClockSelection = RCC_DFSDM1CLKSOURCE_PCLK;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_HSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 4;
	if (SampleRate == 16000) 									
		PeriphClkInit.PLLSAI1.PLLSAI1N = 77;
	else if(SampleRate == 24000)
		PeriphClkInit.PLLSAI1.PLLSAI1N = 35;
	else if(SampleRate == 32000)
		PeriphClkInit.PLLSAI1.PLLSAI1N = 84;
	else if(SampleRate == 40000)
		PeriphClkInit.PLLSAI1.PLLSAI1N = 63;
	else if(SampleRate == 48000)
		PeriphClkInit.PLLSAI1.PLLSAI1N = 70;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_SAI1CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage 
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief DFSDM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DFSDM1_Init(void)
{

  /* USER CODE BEGIN DFSDM1_Init 0 */
	/*																					// Add this part to the SystemClock_Config function whenever recreating code from cube
	if (SampleRate == 16000) 									
		PeriphClkInit.PLLSAI1.PLLSAI1N = 77;
	else if(SampleRate == 24000)
		PeriphClkInit.PLLSAI1.PLLSAI1N = 35;
	else if(SampleRate == 32000)
		PeriphClkInit.PLLSAI1.PLLSAI1N = 84;
	else if(SampleRate == 40000)
		PeriphClkInit.PLLSAI1.PLLSAI1N = 63;
	else if(SampleRate == 48000)
		PeriphClkInit.PLLSAI1.PLLSAI1N = 70;
	*/
	int clockdivider;														// Add clockdivider instead of the value whenever recreating code from cube
	if (SampleRate == 16000)
		clockdivider = 43;
	else if (SampleRate == 24000)
		clockdivider = 13;
	else if (SampleRate == 32000)
		clockdivider = 23;
	else if (SampleRate == 40000)
		clockdivider = 14;
	else if (SampleRate == 44100)
		clockdivider = 17;
	else if (SampleRate == 48000)
		clockdivider = 13;

  /* USER CODE END DFSDM1_Init 0 */

  /* USER CODE BEGIN DFSDM1_Init 1 */

  /* USER CODE END DFSDM1_Init 1 */
  hdfsdm1_filter0.Instance = DFSDM1_Filter0;
  hdfsdm1_filter0.Init.RegularParam.Trigger = DFSDM_FILTER_SW_TRIGGER;
  hdfsdm1_filter0.Init.RegularParam.FastMode = ENABLE;
  hdfsdm1_filter0.Init.RegularParam.DmaMode = ENABLE;
  hdfsdm1_filter0.Init.FilterParam.SincOrder = DFSDM_FILTER_SINC4_ORDER;
  hdfsdm1_filter0.Init.FilterParam.Oversampling = 64;
  hdfsdm1_filter0.Init.FilterParam.IntOversampling = 1;
  if (HAL_DFSDM_FilterInit(&hdfsdm1_filter0) != HAL_OK)
  {
    Error_Handler();
  }
  hdfsdm1_filter1.Instance = DFSDM1_Filter1;
  hdfsdm1_filter1.Init.RegularParam.Trigger = DFSDM_FILTER_SYNC_TRIGGER;
  hdfsdm1_filter1.Init.RegularParam.FastMode = ENABLE;
  hdfsdm1_filter1.Init.RegularParam.DmaMode = ENABLE;
  hdfsdm1_filter1.Init.FilterParam.SincOrder = DFSDM_FILTER_SINC4_ORDER;
  hdfsdm1_filter1.Init.FilterParam.Oversampling = 64;
  hdfsdm1_filter1.Init.FilterParam.IntOversampling = 1;
  if (HAL_DFSDM_FilterInit(&hdfsdm1_filter1) != HAL_OK)
  {
    Error_Handler();
  }
  hdfsdm1_channel1.Instance = DFSDM1_Channel1;
  hdfsdm1_channel1.Init.OutputClock.Activation = ENABLE;
  hdfsdm1_channel1.Init.OutputClock.Selection = DFSDM_CHANNEL_OUTPUT_CLOCK_AUDIO;
  hdfsdm1_channel1.Init.OutputClock.Divider = clockdivider;
  hdfsdm1_channel1.Init.Input.Multiplexer = DFSDM_CHANNEL_EXTERNAL_INPUTS;
  hdfsdm1_channel1.Init.Input.DataPacking = DFSDM_CHANNEL_STANDARD_MODE;
  hdfsdm1_channel1.Init.Input.Pins = DFSDM_CHANNEL_FOLLOWING_CHANNEL_PINS;
  hdfsdm1_channel1.Init.SerialInterface.Type = DFSDM_CHANNEL_SPI_FALLING;
  hdfsdm1_channel1.Init.SerialInterface.SpiClock = DFSDM_CHANNEL_SPI_CLOCK_INTERNAL;
  hdfsdm1_channel1.Init.Awd.FilterOrder = DFSDM_CHANNEL_FASTSINC_ORDER;
  hdfsdm1_channel1.Init.Awd.Oversampling = 1;
  hdfsdm1_channel1.Init.Offset = 0;
  hdfsdm1_channel1.Init.RightBitShift = 0x00;
  if (HAL_DFSDM_ChannelInit(&hdfsdm1_channel1) != HAL_OK)
  {
    Error_Handler();
  }
  hdfsdm1_channel2.Instance = DFSDM1_Channel2;
  hdfsdm1_channel2.Init.OutputClock.Activation = ENABLE;
  hdfsdm1_channel2.Init.OutputClock.Selection = DFSDM_CHANNEL_OUTPUT_CLOCK_AUDIO;
  hdfsdm1_channel2.Init.OutputClock.Divider = clockdivider;
  hdfsdm1_channel2.Init.Input.Multiplexer = DFSDM_CHANNEL_EXTERNAL_INPUTS;
  hdfsdm1_channel2.Init.Input.DataPacking = DFSDM_CHANNEL_STANDARD_MODE;
  hdfsdm1_channel2.Init.Input.Pins = DFSDM_CHANNEL_SAME_CHANNEL_PINS;
  hdfsdm1_channel2.Init.SerialInterface.Type = DFSDM_CHANNEL_SPI_RISING;
  hdfsdm1_channel2.Init.SerialInterface.SpiClock = DFSDM_CHANNEL_SPI_CLOCK_INTERNAL;
  hdfsdm1_channel2.Init.Awd.FilterOrder = DFSDM_CHANNEL_FASTSINC_ORDER;
  hdfsdm1_channel2.Init.Awd.Oversampling = 1;
  hdfsdm1_channel2.Init.Offset = 0;
  hdfsdm1_channel2.Init.RightBitShift = 0x00;
  if (HAL_DFSDM_ChannelInit(&hdfsdm1_channel2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DFSDM_FilterConfigRegChannel(&hdfsdm1_filter0, DFSDM_CHANNEL_2, DFSDM_CONTINUOUS_CONV_ON) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DFSDM_FilterConfigRegChannel(&hdfsdm1_filter1, DFSDM_CHANNEL_1, DFSDM_CONTINUOUS_CONV_ON) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DFSDM1_Init 2 */

  /* USER CODE END DFSDM1_Init 2 */

}

/**
  * @brief QUADSPI Initialization Function
  * @param None
  * @retval None
  */
static void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  /* QUADSPI parameter configuration*/
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 0;
  hqspi.Init.FifoThreshold = 1;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE;
  hqspi.Init.FlashSize = 22;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */

  /* USER CODE END QUADSPI_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 79;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/** 
  * Enable DMA controller clock
  * Configure DMA for memory to memory transfers
  *   hdma_memtomem_dma2_channel1
  */
static void MX_DMA_Init(void) 
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* Configure DMA request hdma_memtomem_dma2_channel1 on DMA2_Channel1 */
  hdma_memtomem_dma2_channel1.Instance = DMA2_Channel1;
  hdma_memtomem_dma2_channel1.Init.Request = DMA_REQUEST_0;
  hdma_memtomem_dma2_channel1.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma2_channel1.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma2_channel1.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma2_channel1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_memtomem_dma2_channel1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
  hdma_memtomem_dma2_channel1.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma2_channel1.Init.Priority = DMA_PRIORITY_LOW;
  if (HAL_DMA_Init(&hdma_memtomem_dma2_channel1) != HAL_OK)
  {
    Error_Handler( );
  }

  /* DMA interrupt init */
  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PushButton_Pin */
  GPIO_InitStruct.Pin = PushButton_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PushButton_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED2_Pin */
  GPIO_InitStruct.Pin = LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
/**
  * @brief  This function send a Write Enable and wait it is effective.
  * @param  hqspi: QSPI handle
  * @retval None
  */
static void QSPI_WriteEnable(QSPI_HandleTypeDef *QSPIHandle)
{
  QSPI_AutoPollingTypeDef sConfig;

  /* Enable write operations ------------------------------------------ */
	QSPI_Cmd.InstructionMode		= QSPI_INSTRUCTION_1_LINE;
	QSPI_Cmd.AddressSize				= QSPI_ADDRESS_24_BITS;
  QSPI_Cmd.AlternateByteMode	= QSPI_ALTERNATE_BYTES_NONE;
	QSPI_Cmd.AlternateBytes			= 0;
	QSPI_Cmd.AlternateBytesSize = 0;
  QSPI_Cmd.DdrMode						= QSPI_DDR_MODE_DISABLE;
	QSPI_Cmd.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
  QSPI_Cmd.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;    // No change needed till this point
	QSPI_Cmd.Instruction				= 0x06;
	QSPI_Cmd.Address						= 0;
	QSPI_Cmd.AddressMode				= QSPI_ADDRESS_NONE;
	QSPI_Cmd.DummyCycles				= 0;
	QSPI_Cmd.DataMode						= QSPI_DATA_NONE;
	QSPI_Cmd.NbData							= 0;

  if (HAL_QSPI_Command(QSPIHandle, &QSPI_Cmd, HAL_QSPI_TIMEOUT) != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Configure automatic polling mode to wait for write enabling ---- */  
  sConfig.Match           = 0x02;
  sConfig.Mask            = 0x02;
  sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 1;
  sConfig.Interval        = 0x10;
  sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

	QSPI_Cmd.Instruction				= 0x05;
	QSPI_Cmd.Address						= 0;
	QSPI_Cmd.AddressMode				= QSPI_ADDRESS_NONE;
	QSPI_Cmd.DummyCycles				= 0;
	QSPI_Cmd.DataMode						= QSPI_DATA_1_LINE;
	QSPI_Cmd.NbData							= 1;

  if (HAL_QSPI_AutoPolling(QSPIHandle, &QSPI_Cmd, &sConfig, HAL_QSPI_TIMEOUT) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function read the SR of the memory and wait the EOP. Blocking mode
  * @param  hqspi: QSPI handle
  * @retval None
  */
static void QSPI_AutoPollingMemReady(QSPI_HandleTypeDef *QSPIHandle)
{
  QSPI_AutoPollingTypeDef sConfig;

  /* Configure automatic polling mode to wait for memory ready ------ */  
  
	QSPI_Cmd.Instruction				= 0x05;
	QSPI_Cmd.Address						= 0;
	QSPI_Cmd.AddressMode				= QSPI_ADDRESS_NONE;
	QSPI_Cmd.DummyCycles				= 0;
	QSPI_Cmd.DataMode						= QSPI_DATA_1_LINE;
	QSPI_Cmd.NbData							= 1;

  sConfig.Match           = 0x00;
  sConfig.Mask            = 0x01;
  sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 1;
  sConfig.Interval        = 0x10;
  sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

  if (HAL_QSPI_AutoPolling(QSPIHandle, &QSPI_Cmd, &sConfig,HAL_QSPI_TIMEOUT) != HAL_OK)
  {
    Error_Handler();
  }
}
/**
  * @brief  This function read the SR of the memory and wait the EOP. Non-Blocking mode
  * @param  hqspi: QSPI handle
  * @retval None
  */
static void QSPI_AutoPollingMemReadyIT(QSPI_HandleTypeDef *QSPIHandle)
{
  QSPI_AutoPollingTypeDef sConfig;

  /* Configure automatic polling mode to wait for memory ready ------ */  
  
	QSPI_Cmd.Instruction				= 0x05;
	QSPI_Cmd.Address						= 0;
	QSPI_Cmd.AddressMode				= QSPI_ADDRESS_NONE;
	QSPI_Cmd.DummyCycles				= 0;
	QSPI_Cmd.DataMode						= QSPI_DATA_1_LINE;
	QSPI_Cmd.NbData							= 1;

  sConfig.Match           = 0x00;
  sConfig.Mask            = 0x01;
  sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 1;
  sConfig.Interval        = 0x10;
  sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

  if (HAL_QSPI_AutoPolling_IT(QSPIHandle, &QSPI_Cmd, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
}
static void QSPI_Erase(QSPI_HandleTypeDef *QSPIHandle)
{
	//	Erase whole chip before programming
	QSPI_WriteEnable (QSPIHandle);
	QSPI_Cmd.Instruction			= 0x60;
	QSPI_Cmd.Address					= 0;
	QSPI_Cmd.AddressMode			= QSPI_ADDRESS_NONE;
	QSPI_Cmd.DummyCycles			= 0;
	QSPI_Cmd.DataMode					= QSPI_DATA_NONE;
	QSPI_Cmd.NbData						= 0;
	HAL_QSPI_Command (QSPIHandle,&QSPI_Cmd,HAL_QSPI_TIMEOUT);
	QSPI_AutoPollingMemReadyIT (QSPIHandle);
	qspiSendReady = false;
}

static void QSPI_Initilize(QSPI_HandleTypeDef *QSPIHandle)
{
	uint8_t data[3];
	QSPI_Cmd.InstructionMode		= QSPI_INSTRUCTION_1_LINE;
	QSPI_Cmd.AddressSize				= QSPI_ADDRESS_24_BITS;
  QSPI_Cmd.AlternateByteMode	= QSPI_ALTERNATE_BYTES_NONE;
	QSPI_Cmd.AlternateBytes			= 0;
	QSPI_Cmd.AlternateBytesSize = 0;
  QSPI_Cmd.DdrMode						= QSPI_DDR_MODE_DISABLE;
	QSPI_Cmd.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
  QSPI_Cmd.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;    // No change needed till this point
	QSPI_Cmd.Instruction				= 0x05;
	QSPI_Cmd.Address						= 0;
	QSPI_Cmd.AddressMode				= QSPI_ADDRESS_1_LINE;
	QSPI_Cmd.DummyCycles				= 0;
	QSPI_Cmd.DataMode						= QSPI_DATA_1_LINE;
	QSPI_Cmd.NbData							= 1;


	//	Read Status Register at First
	QSPI_Cmd.Instruction			= 0x05;
	QSPI_Cmd.Address					= 0;
	QSPI_Cmd.AddressMode			= QSPI_ADDRESS_NONE;
	QSPI_Cmd.DummyCycles			= 0;
	QSPI_Cmd.DataMode					= QSPI_DATA_1_LINE;
	QSPI_Cmd.NbData						= 1;
	if (HAL_QSPI_Command (QSPIHandle,&QSPI_Cmd,HAL_QSPI_TIMEOUT) != HAL_OK){
		Error_Handler();
	}
	if (HAL_QSPI_Receive (QSPIHandle,&data[0],HAL_QSPI_TIMEOUT) != HAL_OK){
		Error_Handler();
	}
	if ((data[0]&0x40) != 0x40){
		Error_Handler ();
	}
	//printf("Status Reg : %d\n" , data[0]);
	
	//  Set Status and Configuration Registers
	data[0] = 64;
	data[1] = 0;
	data[2] = 2;
	QSPI_WriteEnable (QSPIHandle);
	QSPI_Cmd.Instruction			= 0x01;
	QSPI_Cmd.Address					= 0;
	QSPI_Cmd.AddressMode			= QSPI_ADDRESS_NONE;
	QSPI_Cmd.DummyCycles			= 0;
	QSPI_Cmd.DataMode					= QSPI_DATA_1_LINE;
	QSPI_Cmd.NbData						= 3;
	HAL_QSPI_Command (QSPIHandle,&QSPI_Cmd,HAL_QSPI_TIMEOUT);
	HAL_QSPI_Transmit (QSPIHandle,data,HAL_QSPI_TIMEOUT);
	QSPI_AutoPollingMemReady (QSPIHandle);
	
	HAL_Delay (100);
	
	//	Read Configuration Register
	QSPI_Cmd.Instruction			= 0x15;
	QSPI_Cmd.Address					= 0;
	QSPI_Cmd.AddressMode			= QSPI_ADDRESS_NONE;
	QSPI_Cmd.DummyCycles			= 0;
	QSPI_Cmd.DataMode					= QSPI_DATA_1_LINE;
	QSPI_Cmd.NbData						= 2;
	if (HAL_QSPI_Command (QSPIHandle,&QSPI_Cmd,HAL_QSPI_TIMEOUT) != HAL_OK){
		Error_Handler();
	}
	if (HAL_QSPI_Receive (QSPIHandle,&data[0],HAL_QSPI_TIMEOUT) != HAL_OK){
		Error_Handler();
	}
	//printf("Configuration Reg : %d,%d\n" , data[0], data[1]);

	//	Erase whole chip before programming
	/*QSPI_WriteEnable (QSPIHandle);
	QSPI_Cmd.Instruction			= 0x60;
	QSPI_Cmd.Address					= 0;
	QSPI_Cmd.AddressMode			= QSPI_ADDRESS_NONE;
	QSPI_Cmd.DummyCycles			= 0;
	QSPI_Cmd.DataMode					= QSPI_DATA_NONE;
	QSPI_Cmd.NbData						= 0;
	HAL_QSPI_Command (QSPIHandle,&QSPI_Cmd,HAL_QSPI_TIMEOUT);
	QSPI_AutoPollingMemReady (QSPIHandle);*/
	
}

static void QSPI_Send(QSPI_HandleTypeDef *QSPIHandle, uint8_t *sendData, uint32_t NbData, uint32_t Addr)
{
	if (NbData>256){	// Max send data one page (256 Bytes)
		Error_Handler();
	}
	while (!qspiSendReady);
	QSPI_WriteEnable (QSPIHandle);
	QSPI_Cmd.Instruction			= 0x38;
	QSPI_Cmd.Address					= Addr;
	QSPI_Cmd.AddressMode			= QSPI_ADDRESS_4_LINES;
	QSPI_Cmd.DummyCycles			= 0;
	QSPI_Cmd.DataMode					= QSPI_DATA_4_LINES;
	QSPI_Cmd.NbData						= NbData;
	HAL_QSPI_Command (QSPIHandle,&QSPI_Cmd,1);
	HAL_QSPI_Transmit (QSPIHandle,sendData,1);
	QSPI_AutoPollingMemReadyIT (QSPIHandle);
	qspiSendReady = false;
	
}

static void QSPI_Receive(QSPI_HandleTypeDef *QSPIHandle, uint8_t *receiveData, uint32_t NbData, uint32_t Addr)
{
	if (NbData>256){	// Max send data one page (256 Bytes)
		Error_Handler();
	}
	QSPI_Cmd.Instruction			= 0x6B;
	QSPI_Cmd.Address					= Addr;
	QSPI_Cmd.AddressMode			= QSPI_ADDRESS_1_LINE;
	QSPI_Cmd.DummyCycles			= 8;
	QSPI_Cmd.DataMode					= QSPI_DATA_4_LINES;
	QSPI_Cmd.NbData						= NbData;
	HAL_QSPI_Command (QSPIHandle,&QSPI_Cmd,HAL_QSPI_TIMEOUT);
	HAL_QSPI_Receive (QSPIHandle,receiveData,HAL_QSPI_TIMEOUT);
	QSPI_AutoPollingMemReady (QSPIHandle);
	
}

// Feature calculation functions
/**
  * @brief Initialize feature extraction
  * @retval None
  */
void featureInit(void){
		
	// init fft library
	arm_cfft_radix2_init_f32(&fft_struct, FftN, 0, 0);
	//fft_struct.fftLen = FftN;
	
	// init buffers
	recBuffer= (float32_t*)calloc(FftN, sizeof(float32_t));
	fftBuffer = (float32_t*)calloc(2*FftN, sizeof(float32_t));
	Fftt = 0;
	Fftn = 0;
	mag_max0 = 0;
	mag_max1 = 0;
}
/**
  * @brief Update feature extraction
  * @retval None
  */
void featureUpdate(float32_t* inputBuffer){

		// fill left FFT buffer
		for(int i = 0; i < FftN; i++){
			fftBuffer[2 * i] = inputBuffer[i]; // real
			fftBuffer[2 * i + 1] = 0; // imaginary
			inputBuffer[i] = 0;
		}
		
		// run fft calculation
		arm_cfft_radix2_f32(&fft_struct, fftBuffer);
		
		// extract magnitude
		float32_t real;
		float32_t imag;
		for(int i = 0; i < FfthalfN; i++){
			real = fftBuffer[2 * i];
			imag = fftBuffer[2 * i + 1];
			arm_sqrt_f32(real * real + imag * imag, &inputBuffer[i]);

			if(inputBuffer[i] > mag_max0 && Micn == 0){
				mag_max0 = inputBuffer[i];
			} else if (inputBuffer[i] > mag_max1 && Micn == 1){
				mag_max1 = inputBuffer[i];
			}
		}
	
		// normalize magnitude and save into the featureBuffer
		for(int i = 0; i < FfthalfN; i++){
			if (i%4 == 0)
				featureBuffer[Fftt][i/4][Micn] = inputBuffer[i];
		}
}
/**
  * @brief Clean feature extraction
  * @retval None
  */
void featureClean(void){

		// clean buffers
		Fftt = 0;
		Fftn = 0;		
		mag_max0 = 0;
		mag_max1 = 0;
		for (int m = 0; m < FftT; m++) {
			for (int n = 0; n < FftNSave; n++) {
				for (int o = 0; o < MicN; o++) {
					featureBuffer[m][n][o] = 0;
				}
			}
		}

		if(recBuffer){
			for (int m = 0; m < FftN; m++) {
				recBuffer[m] = 0;
			}
		}
		
		if(fftBuffer){
			for (int m = 0; m < FftN * 2; m++) {
				fftBuffer[m] = 0;
			}
		}
}			
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	printf("We have error\n");
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
