/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "fatfs.h"
#include "i2c.h"
#include "i2s.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdlib.h"
#include "audio.h"
#include "blinker.h"
#include "flash.h"
#include "ssd1306.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t enableBlink = 1;
uint8_t flashRecordingState = 0;
FIL audio_file;
uint8_t oledLineX = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_SPI1_Init();
  MX_FATFS_Init();
  MX_I2S3_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
#if OLED_ENABLE == 1U
  ssd1306_Init();
  HAL_Delay(500);
  oledLineX = 127;
  uint8_t oledLineHeight = 0;

  ssd1306_SetColor(Black);
  ssd1306_Fill();
  ssd1306_UpdateScreen();
  HAL_Delay(500);
  ssd1306_SetColor(White);
  ssd1306_Fill();
  ssd1306_UpdateScreen();
  HAL_Delay(500);
  ssd1306_SetColor(Black);
  ssd1306_Fill();
  ssd1306_UpdateScreen();
  HAL_Delay(500);

//  while (1) {
//	  ssd1306_SetColor(Black);
//	  ssd1306_DrawVerticalLine(oledLineX - 1, 0, 64);
//
//	  ssd1306_SetColor(White);
//	  ssd1306_DrawVerticalLine(oledLineX, 32 - (oledLineHeight >> 1), oledLineHeight);
//
//	  ssd1306_UpdateScreen();
//
//	  if (--oledLineX > 127)
//		  oledLineX = 127;
//
//	  HAL_Delay(10);
//
//	  oledLineHeight = rand() % 64;
//  }

#endif
  audio_Start();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  processFlashRecording();

    /* USER CODE END WHILE */

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == USER_BUTTON_Pin) {
		if (flashRecordingState == 0)
			flashRecordingState = 1;
		else if (flashRecordingState == 2)
			flashRecordingState = 3;
		else
			flashRecordingState = 0;
	}
}

void processFlashRecording() {
	if (flashRecordingState == 0)
	  return;

	if (flashRecordingState == 1) {
		// Init file
		if (flashRecordingState == 1) {
			if (flash_Mount() != FR_OK) {
				blinker_Heartbeat(100, 4, 250, 4, -1);
			}

			if (flash_OpenFile(&audio_file, "audio_board.pcm") != FR_OK) {
				blinker_Heartbeat(200, 4, 500, 2, -1);
			}

			flashRecordingState = 2;
		}
	} else if (flashRecordingState == 2 && *audio_BufferUpdated() == 1) {
		// Write file
		if (flash_WriteAppend(&audio_file, audio_GetBuffer(), AUDIO_FRAME_SIZE * 2) != FR_OK) {
			blinker_Heartbeat(200, 2, 500, 2, -1);
		}

#if OLED_ENABLE == 1U
		visualisePCM();
#endif
		blinker_BlinkOnce();
	} else if (flashRecordingState == 3) {
		flash_CloseFile(&audio_file);
		flash_Unmount();
		flashRecordingState = 0;
	}
}

void visualisePCM() {
	int16_t *audioFrameBuffer = audio_GetBuffer();
	int16_t maxAudioFrameValue = 0;

	for (int i = 10; i < AUDIO_FRAME_SIZE; i++) {
		if (maxAudioFrameValue < abs(audioFrameBuffer[i]) && abs(audioFrameBuffer[i]) <= 512)
			maxAudioFrameValue = abs(audioFrameBuffer[i]);
	}

	maxAudioFrameValue /= 8;

	if (maxAudioFrameValue > 64)
		maxAudioFrameValue = 64;

	if (maxAudioFrameValue == 0)
		maxAudioFrameValue = 1;

	uint16_t lineH = (uint16_t)maxAudioFrameValue;

	ssd1306_SetColor(Black);
	if (oledLineX == 0)
		ssd1306_DrawVerticalLine(127, 0, 64);
	else
		ssd1306_DrawVerticalLine(oledLineX - 1, 0, 64);

	ssd1306_SetColor(White);
	ssd1306_DrawVerticalLine(oledLineX, 32 - (lineH >> 1), lineH);

	ssd1306_UpdateScreen();

	if (--oledLineX == 255)
		oledLineX = 127;
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
