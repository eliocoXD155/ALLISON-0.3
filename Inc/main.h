/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI1_NSS5_Pin GPIO_PIN_2
#define SPI1_NSS5_GPIO_Port GPIOE
#define DET_FM_Pin GPIO_PIN_3
#define DET_FM_GPIO_Port GPIOE
#define DAMEF_RST_Pin GPIO_PIN_4
#define DAMEF_RST_GPIO_Port GPIOE
#define GPIO_SPIEXT_CS_Pin GPIO_PIN_1
#define GPIO_SPIEXT_CS_GPIO_Port GPIOC
#define GPIO_SPIEXT_MISO_Pin GPIO_PIN_2
#define GPIO_SPIEXT_MISO_GPIO_Port GPIOC
#define GPIO_SPIEXT_MOSI_Pin GPIO_PIN_3
#define GPIO_SPIEXT_MOSI_GPIO_Port GPIOC
#define TX_MCU_RX_PRINTER_TTL_Pin GPIO_PIN_2
#define TX_MCU_RX_PRINTER_TTL_GPIO_Port GPIOA
#define RX_MCU_TX_PRINTER_TTL_Pin GPIO_PIN_3
#define RX_MCU_TX_PRINTER_TTL_GPIO_Port GPIOA
#define SPI1_NSS1_Pin GPIO_PIN_4
#define SPI1_NSS1_GPIO_Port GPIOA
#define RST_RM_Pin GPIO_PIN_4
#define RST_RM_GPIO_Port GPIOC
#define SPI1_NSS3_Pin GPIO_PIN_5
#define SPI1_NSS3_GPIO_Port GPIOC
#define RST_WM_Pin GPIO_PIN_0
#define RST_WM_GPIO_Port GPIOB
#define CTS_MCU_RTS_PC_TTL_Pin GPIO_PIN_14
#define CTS_MCU_RTS_PC_TTL_GPIO_Port GPIOE
#define RTS_MCU_CTS_PC_TTL_Pin GPIO_PIN_15
#define RTS_MCU_CTS_PC_TTL_GPIO_Port GPIOE
#define GPIO_SPIEXT_SCK_Pin GPIO_PIN_13
#define GPIO_SPIEXT_SCK_GPIO_Port GPIOB
#define TX_WIFI_Pin GPIO_PIN_8
#define TX_WIFI_GPIO_Port GPIOD
#define BOTON_Pin GPIO_PIN_10
#define BOTON_GPIO_Port GPIOD
#define LED1_Pin GPIO_PIN_11
#define LED1_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_12
#define LED2_GPIO_Port GPIOD
#define CC32_RESET_Pin GPIO_PIN_13
#define CC32_RESET_GPIO_Port GPIOD
#define CTS_MCU_RTS_VISOR_TTL_Pin GPIO_PIN_14
#define CTS_MCU_RTS_VISOR_TTL_GPIO_Port GPIOD
#define RTS_MCU_CTS_VISOR_TTL_Pin GPIO_PIN_15
#define RTS_MCU_CTS_VISOR_TTL_GPIO_Port GPIOD
#define TX_MCU_RX_VISOR_TTL_Pin GPIO_PIN_6
#define TX_MCU_RX_VISOR_TTL_GPIO_Port GPIOC
#define RX_MCU_TX_VISOR_TTL_Pin GPIO_PIN_7
#define RX_MCU_TX_VISOR_TTL_GPIO_Port GPIOC
#define SDIO_D0_Pin GPIO_PIN_8
#define SDIO_D0_GPIO_Port GPIOC
#define JP1_Pin GPIO_PIN_8
#define JP1_GPIO_Port GPIOA
#define VBUS_B_Pin GPIO_PIN_9
#define VBUS_B_GPIO_Port GPIOA
#define JP2_Pin GPIO_PIN_10
#define JP2_GPIO_Port GPIOA
#define DM_B_USB1_Pin GPIO_PIN_11
#define DM_B_USB1_GPIO_Port GPIOA
#define DP_B_USB1_Pin GPIO_PIN_12
#define DP_B_USB1_GPIO_Port GPIOA
#define SDIO_CLK_SPI3_MOSI_Pin GPIO_PIN_12
#define SDIO_CLK_SPI3_MOSI_GPIO_Port GPIOC
#define SDIO_CARD_DET1_Pin GPIO_PIN_0
#define SDIO_CARD_DET1_GPIO_Port GPIOD
#define PS_SD1_Pin GPIO_PIN_1
#define PS_SD1_GPIO_Port GPIOD
#define SDIO_EJ_RST_Pin GPIO_PIN_3
#define SDIO_EJ_RST_GPIO_Port GPIOD
#define LED2MCU_Pin GPIO_PIN_5
#define LED2MCU_GPIO_Port GPIOD
#define LED1MCU_Pin GPIO_PIN_7
#define LED1MCU_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
