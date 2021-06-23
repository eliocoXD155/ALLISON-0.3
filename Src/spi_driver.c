#include <stdio.h>
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#include "main.h"
#include "funciones.h"
#include "textos.h"
#include "stm32f4xx_hal.h"
#include "spi_driver.h"

#define FALSE 0
#define TRUE  1

eSTADOS bandera; 
HAL_StatusTypeDef status;
extern SPI_HandleTypeDef hspi1;
//extern SPI_HandleTypeDef hspi2;
extern void MX_GPIO_Init(void);
extern void led_ok(void);
enum DISPOSITIVOS
{
	ram_1,
	ram_2,
	flash,
	fiscal_1,
	fiscal_2,
	expansion,
	ninguno
};

#define FLASH_REQUEST 0x9F
#define FLASH_MANUFACTURER_ID 0x20  //DAMEFIC
#define FLASH_MEMORY_TYPE 0x80   		//DAMEFIC
#define FLASH_MEMORY_CAPACITY 0x14  //DAMEFIC

#define RAM_WRITE 0x02
#define RAM_READ 0x03

#define MAX_DISPLAY		30

/* SPI1 init function */
//void MX_SPI1_Init(void)
//{

//  hspi1.Instance = SPI1;
//  hspi1.Init.Mode = SPI_MODE_MASTER;
//  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
//  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
//  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
//  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
//  hspi1.Init.NSS = SPI_NSS_SOFT;
//  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
//  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
//  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
//  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
//  hspi1.Init.CRCPolynomial = 10;
//  if (HAL_SPI_Init(&hspi1) != HAL_OK)
//  {
//    Error_Handler();
//  }
//}
GPIO_InitTypeDef GPIO_InitStruct;

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, SPI1_NSS5_Pin|DAMEF_RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIO_SPIEXT_MISO_GPIO_Port, GPIO_SPIEXT_MISO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI1_NSS1_GPIO_Port, SPI1_NSS1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, RST_RM_Pin|SPI1_NSS3_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RST_WM_Pin|GPIO_SPIEXT_SCK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_11|RTS_MCU_CTS_PC_TTL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LED1_Pin|LED2_Pin|RTS_MCU_CTS_VISOR_TTL_Pin|PS_SD1_Pin
                          |SDIO_EJ_RST_Pin|LED2MCU_Pin|LED1MCU_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(VBUS_B_GPIO_Port, VBUS_B_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : SPI1_NSS5_Pin DAMEF_RST_Pin */
  GPIO_InitStruct.Pin = SPI1_NSS5_Pin|DAMEF_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : DET_FM_Pin PE8 CTS_MCU_RTS_PC_TTL_Pin */
  GPIO_InitStruct.Pin = DET_FM_Pin|GPIO_PIN_8|CTS_MCU_RTS_PC_TTL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : GPIO_SPIEXT_CS_Pin GPIO_SPIEXT_MOSI_Pin */
  GPIO_InitStruct.Pin = GPIO_SPIEXT_CS_Pin|GPIO_SPIEXT_MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : GPIO_SPIEXT_MISO_Pin */
  GPIO_InitStruct.Pin = GPIO_SPIEXT_MISO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIO_SPIEXT_MISO_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI1_NSS1_Pin */
  GPIO_InitStruct.Pin = SPI1_NSS1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI1_NSS1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RST_RM_Pin SPI1_NSS3_Pin */
  GPIO_InitStruct.Pin = RST_RM_Pin|SPI1_NSS3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : RST_WM_Pin GPIO_SPIEXT_SCK_Pin */
  GPIO_InitStruct.Pin = RST_WM_Pin|GPIO_SPIEXT_SCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PE7 PE10 PE11 RTS_MCU_CTS_PC_TTL_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_11|RTS_MCU_CTS_PC_TTL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : BOTON_Pin */
  GPIO_InitStruct.Pin = BOTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BOTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_Pin LED2_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : CTS_MCU_RTS_VISOR_TTL_Pin SDIO_CARD_DET1_Pin */
  GPIO_InitStruct.Pin = CTS_MCU_RTS_VISOR_TTL_Pin|SDIO_CARD_DET1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : RTS_MCU_CTS_VISOR_TTL_Pin SDIO_EJ_RST_Pin LED2MCU_Pin LED1MCU_Pin */
  GPIO_InitStruct.Pin = RTS_MCU_CTS_VISOR_TTL_Pin|SDIO_EJ_RST_Pin|LED2MCU_Pin|LED1MCU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : JP1_Pin JP2_Pin */
  GPIO_InitStruct.Pin = JP1_Pin|JP2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : VBUS_B_Pin */
  GPIO_InitStruct.Pin = VBUS_B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(VBUS_B_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PS_SD1_Pin */
  GPIO_InitStruct.Pin = PS_SD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(PS_SD1_GPIO_Port, &GPIO_InitStruct);

}

void swap_gpio(){  //invierte la configuracion del gpio para las pruebas del puerto de expasion
	  //Configure GPIO pin : GPIO_SPIEXT_MISO_Pin 
  GPIO_InitStruct.Pin = GPIO_SPIEXT_MISO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT; 
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  //GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIO_SPIEXT_MISO_GPIO_Port, &GPIO_InitStruct);
	
	  //Configure GPIO pins : GPIO_SPIEXT_CS_Pin GPIO_SPIEXT_MOSI_Pin 
  GPIO_InitStruct.Pin = GPIO_SPIEXT_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
		  //Configure GPIO pins : GPIO_SPIEXT_CS_Pin GPIO_SPIEXT_MOSI_Pin 
  GPIO_InitStruct.Pin = GPIO_SPIEXT_MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	  //Configure GPIO pins : GPIO_SPIEXT_SCK_Pin 
	GPIO_InitStruct.Pin = GPIO_SPIEXT_SCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
}

void selecciona_dispositivo(uint8_t dispositivo)
{
	switch (dispositivo)
	{
		case ram_1:
		{		
			HAL_GPIO_WritePin(SPI1_NSS1_GPIO_Port, SPI1_NSS1_Pin, GPIO_PIN_RESET);
			//HAL_GPIO_WritePin(SPI1_NSS2_GPIO_Port, SPI1_NSS2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_NSS3_GPIO_Port, SPI1_NSS3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_NSS5_GPIO_Port, SPI1_NSS5_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_NSS5_GPIO_Port, DAMEF_RST_Pin, GPIO_PIN_SET);			
			break;
		}
		
		case ram_2:
		{		
			HAL_GPIO_WritePin(SPI1_NSS1_GPIO_Port, SPI1_NSS1_Pin, GPIO_PIN_SET);
			//HAL_GPIO_WritePin(SPI1_NSS2_GPIO_Port, SPI1_NSS2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SPI1_NSS3_GPIO_Port, SPI1_NSS3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_NSS5_GPIO_Port, SPI1_NSS5_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_NSS5_GPIO_Port, DAMEF_RST_Pin, GPIO_PIN_SET);
			break;
		}
		
		case flash:
		{		
			HAL_GPIO_WritePin(SPI1_NSS1_GPIO_Port, SPI1_NSS1_Pin, GPIO_PIN_SET);
			//HAL_GPIO_WritePin(SPI1_NSS2_GPIO_Port, SPI1_NSS2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_NSS3_GPIO_Port, SPI1_NSS3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SPI1_NSS5_GPIO_Port, SPI1_NSS5_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_NSS5_GPIO_Port, DAMEF_RST_Pin, GPIO_PIN_SET);
			break;
		}

		case fiscal_1:
		{
			HAL_GPIO_WritePin(SPI1_NSS1_GPIO_Port, SPI1_NSS1_Pin, GPIO_PIN_SET);
			//HAL_GPIO_WritePin(SPI1_NSS2_GPIO_Port, SPI1_NSS2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_NSS3_GPIO_Port, SPI1_NSS3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_NSS5_GPIO_Port, SPI1_NSS5_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SPI1_NSS5_GPIO_Port, DAMEF_RST_Pin, GPIO_PIN_SET);
			break;
		}		
		
		case fiscal_2:
		{
			HAL_GPIO_WritePin(SPI1_NSS1_GPIO_Port, SPI1_NSS1_Pin, GPIO_PIN_SET);
		//	HAL_GPIO_WritePin(SPI1_NSS2_GPIO_Port, SPI1_NSS2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_NSS3_GPIO_Port, SPI1_NSS3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_NSS5_GPIO_Port, SPI1_NSS5_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_NSS5_GPIO_Port, DAMEF_RST_Pin, GPIO_PIN_RESET);
			break;
		}
		
		case ninguno:
		{		
			HAL_GPIO_WritePin(SPI1_NSS1_GPIO_Port, SPI1_NSS1_Pin, GPIO_PIN_SET);
			//HAL_GPIO_WritePin(SPI1_NSS2_GPIO_Port, SPI1_NSS2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_NSS3_GPIO_Port, SPI1_NSS3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_NSS5_GPIO_Port, SPI1_NSS5_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_NSS5_GPIO_Port, DAMEF_RST_Pin, GPIO_PIN_SET);
			break;
		}
		}		
	}


void escribe_memoria_ram(uint8_t dispositivo, uint8_t *direccion1, uint8_t *direccion2, uint8_t *direccion3, uint8_t *comando, uint8_t *dato)
{	
//	uint8_t vector_direccion[3]={0};
//	
//	vector_direccion[1] = direccion << 8;
//	vector_direccion[2] = direccion << 0;

			selecciona_dispositivo(dispositivo);
			status= HAL_SPI_Transmit(&hspi1, comando, sizeof(uint8_t),1000);
			if (status!=HAL_OK||bandera.estado.error_memoria_spi_escribir==ERROR){bandera.estado.error_memoria_spi_escribir=ERROR;
			}else	{bandera.estado.error_memoria_spi_escribir=OK;}
			status=	HAL_SPI_Transmit(&hspi1, direccion1, sizeof(uint8_t),1000);
			if (status!=HAL_OK||bandera.estado.error_memoria_spi_escribir==ERROR){bandera.estado.error_memoria_spi_escribir=ERROR;
			}else	{bandera.estado.error_memoria_spi_escribir=OK;}
			status= HAL_SPI_Transmit(&hspi1, direccion2, sizeof(uint8_t),1000);
			if (status!=HAL_OK||bandera.estado.error_memoria_spi_escribir==ERROR){bandera.estado.error_memoria_spi_escribir=ERROR;
			}else	{bandera.estado.error_memoria_spi_escribir=OK;}
			status= HAL_SPI_Transmit(&hspi1, direccion3, sizeof(uint8_t),1000);
			if (status!=HAL_OK||bandera.estado.error_memoria_spi_escribir==ERROR){bandera.estado.error_memoria_spi_escribir=ERROR;
			}else	{bandera.estado.error_memoria_spi_escribir=OK;}
			status= HAL_SPI_Transmit(&hspi1, dato, sizeof(uint8_t),1000);
	
			if(status != HAL_OK)
			{
				bandera.estado.error_memoria_spi_escribir=ERROR;
			}
			else
			{
				bandera.estado.error_memoria_spi_escribir=OK;
			}
//		HAL_SPI_Transmit(&hspi1, vector_direccion, sizeof(uint8_t),1000);				
			selecciona_dispositivo(ninguno);
			HAL_Delay(100);
	
}


void lee_memoria_ram(uint8_t dispositivo, uint8_t *direccion1, uint8_t *direccion2, uint8_t *direccion3, uint8_t *comando, uint8_t *dato)
{
//	uint8_t vector_direccion[3]={0};
//	
//	vector_direccion[1] = direccion << 8;
//	vector_direccion[2] = direccion << 0;
			unsigned int estado;
			selecciona_dispositivo(dispositivo);
			estado=status;
			estado= HAL_SPI_Transmit(&hspi1,comando, sizeof(uint8_t),1000);
			if (estado!=HAL_OK||bandera.estado.error_memoria_spi_escribir==ERROR){bandera.estado.error_memoria_spi_escribir=ERROR;
			}else	{bandera.estado.error_memoria_spi_escribir=OK;}
			estado= HAL_SPI_Transmit(&hspi1, direccion1, sizeof(uint8_t),1000);
			if (estado!=HAL_OK||bandera.estado.error_memoria_spi_escribir==ERROR){bandera.estado.error_memoria_spi_escribir=ERROR;
			}else	{bandera.estado.error_memoria_spi_escribir=OK;}
			estado=HAL_SPI_Transmit(&hspi1, direccion2, sizeof(uint8_t),1000);
			if (estado!=HAL_OK||bandera.estado.error_memoria_spi_escribir==ERROR){bandera.estado.error_memoria_spi_escribir=ERROR;
			}else	{bandera.estado.error_memoria_spi_escribir=OK;}
			estado= HAL_SPI_Transmit(&hspi1, direccion3, sizeof(uint8_t),1000);
			if (estado!=HAL_OK||bandera.estado.error_memoria_spi_escribir==ERROR){bandera.estado.error_memoria_spi_escribir=ERROR;
			}else	{bandera.estado.error_memoria_spi_escribir=OK;}
			
//			HAL_SPI_Transmit(&hspi1, vector_direccion, sizeof(uint8_t),1000);
			status=HAL_SPI_Receive(&hspi1,dato, sizeof(uint8_t),1000);
			if(status != HAL_OK)
			{
				bandera.estado.error_memoria_spi_leer=ERROR;
			}
			else
			{
				bandera.estado.error_memoria_spi_leer=OK;
			}
			selecciona_dispositivo(ninguno);
			HAL_Delay(100);
}




void lee_memoria_flash(uint8_t *comando, uint8_t *dato1, uint8_t *dato2, uint8_t *dato3)
{
//	uint8_t vector_direccion[3]={0};
//	
//	vector_direccion[1] = direccion << 8;
//	vector_direccion[2] = direccion << 0;

			selecciona_dispositivo(flash);
			status = HAL_SPI_Transmit(&hspi1,comando, sizeof(uint8_t),1000);
			if (status!=HAL_OK)
			{
				bandera.estado.error_memoria_spi_escribir=ERROR;
			}
			else
			{				
				bandera.estado.error_memoria_spi_escribir=OK;	
			}	
			
				
//				status = 0;
//				status=status + HAL_SPI_Receive(&hspi1,dato1, sizeof(uint8_t),1000);
//				status=status + HAL_SPI_Receive(&hspi1,dato2, sizeof(uint8_t),1000);
//				status=status + HAL_SPI_Receive(&hspi1,dato3, sizeof(uint8_t),1000);
				status = HAL_SPI_Receive(&hspi1,dato1, sizeof(uint8_t),1000);
				if (status!=HAL_OK||bandera.estado.error_memoria_spi_leer==ERROR){bandera.estado.error_memoria_spi_leer=ERROR;
				}else	{bandera.estado.error_memoria_spi_leer=OK;}
				status = HAL_SPI_Receive(&hspi1,dato2, sizeof(uint8_t),1000);
				if (status!=HAL_OK||bandera.estado.error_memoria_spi_leer==ERROR){bandera.estado.error_memoria_spi_leer=ERROR;
				}else	{bandera.estado.error_memoria_spi_leer=OK;}
				status = HAL_SPI_Receive(&hspi1,dato3, sizeof(uint8_t),1000);
				if (status!=HAL_OK||bandera.estado.error_memoria_spi_leer==ERROR){bandera.estado.error_memoria_spi_leer=ERROR;
				}else	{bandera.estado.error_memoria_spi_leer=OK;}
			
			selecciona_dispositivo(ninguno);
//			status = 0;
			HAL_Delay(100);	

}

int status_error(HAL_StatusTypeDef status){
			if(status==HAL_OK){ return OK;
			}else{
			return ERROR;
			}
}

void lee_memoria_fiscal(uint8_t dispositivo, uint8_t *comando, uint8_t *dato1, uint8_t *dato2, uint8_t *dato3)
{
//	uint8_t vector_direccion[3]={0};
//	
//	vector_direccion[1] = direccion << 8;
//	vector_direccion[2] = direccion << 0;

			selecciona_dispositivo(dispositivo);
			status = HAL_SPI_Transmit(&hspi1,comando, sizeof(uint8_t),1000);
			if (status!=HAL_OK)
			{
				bandera.estado.error_memoria_spi_escribir=ERROR;
			}
			else
			{				
				bandera.estado.error_memoria_spi_escribir=OK;
			}
			
//			status = 0;
			status= HAL_SPI_Receive(&hspi1,dato1, sizeof(uint8_t),1000);
			if (status!=HAL_OK||bandera.estado.error_memoria_spi_leer==ERROR){bandera.estado.error_memoria_spi_leer=ERROR;
			}else	{bandera.estado.error_memoria_spi_leer=OK;}
			status= HAL_SPI_Receive(&hspi1,dato2, sizeof(uint8_t),1000);
			if (status!=HAL_OK||bandera.estado.error_memoria_spi_leer==ERROR){bandera.estado.error_memoria_spi_leer=ERROR;
			}else	{bandera.estado.error_memoria_spi_leer=OK;}
			status= HAL_SPI_Receive(&hspi1,dato3, sizeof(uint8_t),1000);
			if (status!=HAL_OK||bandera.estado.error_memoria_spi_leer==ERROR){bandera.estado.error_memoria_spi_leer=ERROR;
			}else	{bandera.estado.error_memoria_spi_leer=OK;}
			
//			if (status!=HAL_OK)
//			{
//				bandera.estado.error_memoria_spi_leer=ERROR;
//			}
//			else
//			{
//				bandera.estado.error_memoria_spi_leer=OK;			
//			}
			selecciona_dispositivo(ninguno);
//			status = 0;
			HAL_Delay(100);	
}







//Funcion para probar la memoria RAM 1 (U13) y la memoria RAM 2 (U14)***************************************************
void prueba_mem_ram(uint8_t dispositivo)
{
	uint8_t direccion1 = 0x00;
	uint8_t direccion2 = 0x00;	
	uint8_t direccion3 = 0xFF;
	uint8_t comando_escribir_ram = 0x02;
	uint8_t comando_leer_ram = 0x03;
	uint8_t dato_leido = 0;
	uint8_t dato_enviado = 90;
	

	
	selecciona_dispositivo(dispositivo);
	escribe_memoria_ram(dispositivo, &direccion1, &direccion2, &direccion3, &comando_escribir_ram, &dato_enviado);
	selecciona_dispositivo(ninguno);
	
	HAL_Delay(300);	
	
	selecciona_dispositivo(dispositivo);
	lee_memoria_ram(dispositivo, &direccion1, &direccion2, &direccion3, &comando_leer_ram, &dato_leido);
	selecciona_dispositivo(ninguno);
	
	switch (dispositivo)
	{
		case ram_1:
		{	
			if (dato_enviado==dato_leido)
			{
					bandera.estado.error_memoria_ram1=OK;
			}
			else
			{
					bandera.estado.error_memoria_ram1=ERROR;
			}
			break;
		}
		
		case ram_2:
		{		
			if (dato_enviado==dato_leido)
			{
				bandera.estado.error_memoria_ram2=OK;
			}
		else
			{
				bandera.estado.error_memoria_ram2=ERROR;
			}	
			break;
		}
		
	}
}



//Funcion para probar la memoria FLASH (U3)***************************************************
void prueba_mem_flash(void)
{	
	uint8_t dato_leido1 = 0;
	uint8_t dato_leido2 = 0;
	uint8_t dato_leido3 = 0;
	uint8_t comando_id_flash = 0x9f;
	
	//	HAL_GPIO_WritePin(GPIOB,SPI1_RST_WM_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,RST_WM_Pin,GPIO_PIN_SET);
	HAL_Delay(50);
	
	selecciona_dispositivo(flash);
	lee_memoria_flash(&comando_id_flash, &dato_leido1, &dato_leido2, &dato_leido3);
	selecciona_dispositivo(ninguno);
	
		if ((dato_leido1!=0xBF) || (dato_leido2!=0x26) || (dato_leido3!=0x41))
		{
			bandera.estado.error_memoria_flash=ERROR;
		}
		else
		{
				bandera.estado.error_memoria_flash=OK;			
		}	
}


////Funcion para probar la memoria Fiscal  (conector FM)***************************************************
void prueba_mem_fiscal(uint8_t dispositivo)
{	
	uint8_t dato_leido1 = 0;
	uint8_t dato_leido2 = 0;
	uint8_t dato_leido3 = 0;
	uint8_t comando_id_fiscal = 0x9f;
	
	selecciona_dispositivo(dispositivo);
	lee_memoria_fiscal(dispositivo, &comando_id_fiscal, &dato_leido1, &dato_leido2, &dato_leido3);
	selecciona_dispositivo(ninguno);
	
/*	
		switch (dispositivo)
	{
		case fiscal_1:
		{	
		if ((dato_leido1!=FLASH_MANUFACTURER_ID) || (dato_leido2!=FLASH_MEMORY_TYPE) || (dato_leido3!=FLASH_MEMORY_CAPACITY)) 
		{
			bandera.estado.error_memoria_fiscal_1=ERROR;
		}
		else
		{
				bandera.estado.error_memoria_fiscal_1=OK;			
		}
			break;
		}
		
		case fiscal_2:
		{		
		if ((dato_leido1!=FLASH_MANUFACTURER_ID) || (dato_leido2!=FLASH_MEMORY_TYPE) || (dato_leido3!=FLASH_MEMORY_CAPACITY))
		{
			bandera.estado.error_memoria_fiscal_2=ERROR;
		}
		else
		{
				bandera.estado.error_memoria_fiscal_2=OK;			
		}
			break;
		}
		
	}
	
*/	

		if(dato_leido1!=FLASH_MANUFACTURER_ID){bandera.estado.error_memoria_fiscal_1=ERROR;}
		else{bandera.estado.error_memoria_fiscal_1=OK;}
		if(dato_leido2!=FLASH_MEMORY_TYPE){bandera.estado.error_memoria_fiscal_1=ERROR;}
		else{bandera.estado.error_memoria_fiscal_1=OK;}
		if(dato_leido3!=FLASH_MEMORY_CAPACITY){bandera.estado.error_memoria_fiscal_1=ERROR;}
		else{bandera.estado.error_memoria_fiscal_1=OK;}
	
}

void prueba_mem_ram_read(uint8_t dispositivo)
{
	uint8_t direccion1 = 0x05;  //registro escogido para guardar el dato a consultar
	uint8_t direccion2 = 0x05;	
	uint8_t direccion3 = 0xFF;
//	uint8_t comando_escribir_ram = 0x02;
	uint8_t comando_leer_ram = 0x03;
	uint8_t dato_leido = 0;
	uint8_t dato_enviado = 90;
	

	
//	selecciona_dispositivo(dispositivo);
//	escribe_memoria_ram(dispositivo, &direccion1, &direccion2, &direccion3, &comando_escribir_ram, &dato_enviado);
//	selecciona_dispositivo(ninguno);
	
	HAL_Delay(100);	
	
	selecciona_dispositivo(dispositivo);
	lee_memoria_ram(dispositivo, &direccion1, &direccion2, &direccion3, &comando_leer_ram, &dato_leido);
	selecciona_dispositivo(ninguno);
	
	switch (dispositivo)
	{
		case ram_1:
		{	
			if (dato_enviado==dato_leido)
			{
					bandera.estado.error_bateria=OK;
			}
			else
			{
					bandera.estado.error_bateria=ERROR;
			}
			break;
		}
	}
}

void prueba_mem_ram_write(uint8_t dispositivo, bool prueba)
{
	uint8_t direccion1 = 0x05;  //registro escogido para guardar el dato a consultar
	uint8_t direccion2 = 0x05;	
	uint8_t direccion3 = 0xFF;
	uint8_t comando_escribir_ram = 0x02;
	uint8_t comando_leer_ram = 0x03;
	uint8_t dato_leido = 0;
	uint8_t dato_enviado;
	
	
	if(prueba){dato_enviado=90;} //SI PRUEBA ES TRUE QUIERE DECIR QUE NO TIENE EL DATO GUARDADO, SI ES FALSE YA LO LEYO
		else{dato_enviado= 0xFF;}
	
	selecciona_dispositivo(dispositivo);
	escribe_memoria_ram(dispositivo, &direccion1, &direccion2, &direccion3, &comando_escribir_ram, &dato_enviado);
	selecciona_dispositivo(ninguno);
	
	HAL_Delay(100);	
	
	selecciona_dispositivo(dispositivo);
	lee_memoria_ram(dispositivo, &direccion1, &direccion2, &direccion3, &comando_leer_ram, &dato_leido);
	selecciona_dispositivo(ninguno);
	
	switch (dispositivo)
	{
		case ram_1:
		{	
			if (dato_enviado==dato_leido)
			{
					bandera.estado.error_bateria_escribir=OK;
			}
			else
			{
					bandera.estado.error_bateria_escribir=ERROR;
			}
			break;
		}
	}
}


void prueba_bateria(){
		
		if(bandera.estado.error_memoria_ram1==OK){  //si la ram1 esta buena, entonces va a pedir reiniciar
			prueba_mem_ram_read(ram_1);
			if(bandera.estado.error_bateria==ERROR){
				prueba_mem_ram_write(ram_1, TRUE);
				mensaje_USB(MENSAJE_PRUEBA_BATERIA);
			
				
				while(HAL_GPIO_ReadPin(GPIOD,BOTON_Pin)!=0){HAL_Delay(50);}  //si presionas s2, se salta la prueba
				//while(1);
				mensaje_USB(MENSAJE_NO_BATERIA);
				prueba_mem_ram_write(ram_1, FALSE);
				bandera.estado.error_bateria=ERROR;
					
				//prueba_drv_usb_recibir();   //espera una s para saltarse la bateria
			}else{prueba_mem_ram_write(ram_1, FALSE);
			}
		}
	//testigo_led(bandera.estado.error_bateria);

	}


void prueba_spi_ext(){

	
			//const uint8_t dat = 0b11111111;
			//char spi_buf[20];
	
			//Primera corrida de gpio spi. Con la configuracion original de los pines
			HAL_GPIO_WritePin(GPIO_SPIEXT_MISO_GPIO_Port,GPIO_SPIEXT_MISO_Pin,GPIO_PIN_RESET);
	    //HAL_SPI_Transmit(&hspi2,(uint8_t *)&dat,8,100);
			HAL_Delay(30);
			if (HAL_GPIO_ReadPin(GPIO_SPIEXT_CS_GPIO_Port,GPIO_SPIEXT_CS_Pin)!=0){		
					bandera.estado.error_spi_cs_miso=ERROR;
					//HAL_Delay(50);	
				}
			else{	
					bandera.estado.error_spi_cs_miso=OK;
				}
			
			HAL_GPIO_WritePin(GPIO_SPIEXT_SCK_GPIO_Port,GPIO_SPIEXT_SCK_Pin,GPIO_PIN_SET);
			HAL_Delay(30);				
			HAL_GPIO_WritePin(GPIO_SPIEXT_SCK_GPIO_Port,GPIO_SPIEXT_SCK_Pin,GPIO_PIN_RESET);
			HAL_Delay(30);
			if (HAL_GPIO_ReadPin(GPIO_SPIEXT_MOSI_GPIO_Port,GPIO_SPIEXT_MOSI_Pin)!=0){		
					bandera.estado.error_spi_sck_mosi=ERROR;
					//HAL_Delay(50);	
				}
			else{	
					bandera.estado.error_spi_sck_mosi=OK;
				}
			//Inversion de pines para probar
			
				
			swap_gpio();
//			
			
			//Primera corrida de gpio spi. Con la configuracion original de los pines
			HAL_GPIO_WritePin(GPIO_SPIEXT_CS_GPIO_Port,GPIO_SPIEXT_CS_Pin,GPIO_PIN_SET);
//			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
			HAL_Delay(30);
			if (HAL_GPIO_ReadPin(GPIO_SPIEXT_MISO_GPIO_Port,GPIO_SPIEXT_MISO_Pin)==0){		
					bandera.estado.error_spi_miso_cs=ERROR;
					HAL_Delay(50);	
				}
			else{	
					bandera.estado.error_spi_miso_cs=OK;
				}
			
			HAL_GPIO_WritePin(GPIO_SPIEXT_MOSI_GPIO_Port,GPIO_SPIEXT_MOSI_Pin,GPIO_PIN_SET);
//		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
			HAL_Delay(30);
			if (HAL_GPIO_ReadPin(GPIO_SPIEXT_SCK_GPIO_Port,GPIO_SPIEXT_SCK_Pin)!=1){		
					bandera.estado.error_spi_mosi_sck=ERROR;
					//HAL_Delay(50);	
				}
			else{	
					bandera.estado.error_spi_mosi_sck=OK;
				}
			MX_GPIO_Init();
	
			if(bandera.estado.error_spi_miso_cs==ERROR || bandera.estado.error_spi_mosi_sck==ERROR || bandera.estado.error_spi_sck_mosi==ERROR || bandera.estado.error_spi_sck_mosi==ERROR){
				bandera.estado.error_spi_gprs=ERROR;
			}else{
				bandera.estado.error_spi_gprs=OK;
			}
	//testigo_led(bandera.estado.error_spi_gprs);
}
	
void prueba_drv_spi1(void)
{	
		led_ok();
		prueba_mem_ram(ram_1);
		HAL_Delay(50);
		prueba_bateria();
		HAL_Delay(50);
		//prueba_mem_ram(ram_2);
		//HAL_Delay(50);
		prueba_mem_fiscal(fiscal_1);
		HAL_Delay(50);
		prueba_mem_flash();
		HAL_Delay(50);
	  prueba_spi_ext();
		//prueba_mem_fiscal(expansion);

}
