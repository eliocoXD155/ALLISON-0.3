#include "SD_driver.h"
#include "stm32f4xx_hal_sd.h"
#include "string.h"
#include "textos.h"
#include "spi_driver.h"
#include "ff.h"
#include "funciones.h"

extern void led_ok(void);
extern void led_ERR(void);
extern SD_HandleTypeDef hsd;
//extern HAL_SD_CardInfoTypedef SDCardInfo;

FATFS mi_FATFS;
FIL mi_archivo;
extern eSTADOS bandera;


uint32_t byteswritten, bytesread;	
extern char SDPath[4];
FRESULT res;
char nombre_archivo_leer[]="TESTSD.TXT";
char nombre_archivo_escribir[]="TESTSD.TXT";
char mensaje_enviar[]="SD selftest text message";
uint8_t mensaje_recibir[100] = {0};
UINT bit_prueba;

/* SDIO init function */
//void MX_SDIO_SD_Init(void)
//{

//  hsd.Instance = SDIO;
//  hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
//  hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
//  hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
//  hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
//  hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
//  hsd.Init.ClockDiv = 0;

//}

//FUncion para escribir un archivo de texto a la SD*******************************
/*
void escribir (void)
{
	HAL_GPIO_WritePin(GPIOD,LED1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD,LED2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,PS_SD1_Pin,GPIO_PIN_RESET);
	
//	HAL_Delay(1000);
	
		//f_close(&mi_archivo);
		//res = f_mkfs((TCHAR const*)SDPath, 0, 0);
		//if(SDCardInfo.SD_cid.ManufacturerID==0x03){bandera.estado.error_sdio_leer_archivo=OK;}
		HAL_Delay(50);
		bandera.estado.error_sdio_montaje=OK;
		res = f_open(&mi_archivo, "TESTSD.TXT",FA_CREATE_ALWAYS | FA_WRITE );
		if (res != FR_OK)
			{
				bandera.estado.error_sdio_abrir_escribir=ERROR;
//				Error_Handler();
			}
			else
				{
				bandera.estado.error_sdio_abrir_escribir=OK;					
				res = f_write(&mi_archivo, mensaje_enviar, sizeof(mensaje_enviar),(void*)&byteswritten);
					if((byteswritten==0)||(res!=FR_OK))
						{
							bandera.estado.error_sdio_escribir_archivo=ERROR;							
//							Error_Handler();
						}
				else
					{
						bandera.estado.error_sdio_escribir_archivo=OK;
						f_close(&mi_archivo);
						HAL_GPIO_WritePin(GPIOD,LED2_Pin,GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOD,LED1_Pin,GPIO_PIN_RESET);
						HAL_Delay(50);
						HAL_GPIO_WritePin(GPIOD,LED2_Pin,GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOD,LED1_Pin,GPIO_PIN_RESET);
					}

				}
		}

	

	*/
	
//Funcion para leer un archivo desde la SD	

void leer (void)
{
	HAL_GPIO_WritePin(GPIOD,LED1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD,LED2_Pin,GPIO_PIN_RESET);
//	HAL_Delay(1000);
	

		//res = f_open(&mi_archivo, nombre_archivo_leer, FA_READ | FA_OPEN_ALWAYS);
		//res = f_open(&mi_archivo, nombre_archivo_leer, FA_READ);
		if (f_open(&mi_archivo, nombre_archivo_leer, FA_READ) == FR_NO_FILE)
			{
				bandera.estado.error_sdio_abrir_leer=ERROR;
				led_ERR();
//				Error_Handler();
			}
			//else
				//{
					//bandera.estado.error_sdio_abrir_leer=OK;
					//res = f_read(&mi_archivo, mensaje_recibir, sizeof(mensaje_recibir), &bytesread);
					//if((bytesread==0)||(res!=FR_OK))
					//	{
					//		bandera.estado.error_sdio_leer_archivo=ERROR;							
//							Error_Handler();
					//	}
				else
					{
						bandera.estado.error_sdio_leer_archivo=OK;
						//f_close(&mi_archivo);
						led_ok();			
				}
	}
	
  /* USER CODE BEGIN 1 */
		
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
//  HAL_Init();

//  /* Configure the system clock */
//  SystemClock_Config();

//  /* Initialize all configured peripherals */
//  MX_GPIO_Init();
//  MX_SDIO_SD_Init();
//  MX_FATFS_Init();
//}

/*
void formatear(void){  //formatea la tarjeta sd
		res = f_mkfs((TCHAR const*)SDPath, 0, 0);
		if(res!=FR_OK)
						{
							bandera.estado.error_sdio_formatear=ERROR;							
//							Error_Handler();
						}
				else
					{
						bandera.estado.error_sdio_formatear=OK;
						HAL_GPIO_WritePin(GPIOD,LED2_Pin,GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOD,LED1_Pin,GPIO_PIN_RESET);
						HAL_Delay(50);
						HAL_GPIO_WritePin(GPIOD,LED2_Pin,GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOD,LED1_Pin,GPIO_PIN_RESET);				
				}
}

void getfree(void){
	DWORD fre_clust;
	res = f_getfree((TCHAR const*)SDPath, &fre_clust, (FATFS**)&mi_FATFS);
	HAL_Delay(50);
	if(res!=FR_OK)
				{
					bandera.estado.error_sdio_formatear=ERROR;							
//							Error_Handler();
				}
		else
			{
				bandera.estado.error_sdio_formatear=OK;
				HAL_GPIO_WritePin(GPIOD,LED2_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOD,LED1_Pin,GPIO_PIN_RESET);
				HAL_Delay(50);
				HAL_GPIO_WritePin(GPIOD,LED2_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOD,LED1_Pin,GPIO_PIN_RESET);				
		}
}
*/

int montar_sd(void){
	char read[10];
	UINT byte;
	//res = f_mount(&mi_FATFS, SDPath,0);
	if(f_mount(&mi_FATFS, SDPath,1) == FR_OK)
	{
		f_open(&mi_archivo, nombre_archivo_leer, FA_READ | FA_OPEN_ALWAYS);
		f_read(&mi_archivo,read,10,&byte);
				if(strlen(read)!=0){
					led_ok();
					f_close(&mi_archivo);
					return MENSAJE_SDIO_OK;
					
				}else{
				led_ERR();
				f_close(&mi_archivo);
				return MENSAJE_SDIO_ERROR;
				
				
				}
		
		
	}else{
		
	led_ERR();
	return MENSAJE_SDIO_ERROR;

	
	}
}
int prueba_drv_sdio(void)
{		int r;
		//**********--Agregado/eliminar luego--******************************//
		/*HAL_GPIO_WritePin(GPIOD,SDIO_EJ_RST_Pin,GPIO_PIN_RESET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOD,SDIO_EJ_RST_Pin,GPIO_PIN_SET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(GPIOD,SDIO_EJ_RST_Pin,GPIO_PIN_RESET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOD,SDIO_EJ_RST_Pin,GPIO_PIN_SET);*/
		//******************************************************************//
		r = montar_sd();
	return r;
	/*	HAL_Delay(50);
		//escribir();
		HAL_Delay(50);
		leer();
		HAL_Delay(50);
		//getfree();
	//	formatear();
		HAL_Delay(50);
		montar_sd();*/
	
	/*if((bandera.estado.error_sdio_leer_archivo==ERROR)||
			(bandera.estado.error_sdio_abrir_leer==ERROR)||
			(bandera.estado.error_sdio_montaje==ERROR)||
			(bandera.estado.error_sdio_escribir_archivo==ERROR)||
			(bandera.estado.error_sdio_abrir_escribir==ERROR)||
			(bandera.estado.error_sdio_montaje==ERROR)||
			(bandera.estado.error_sdio_formatear==ERROR))
	{
		bandera.estado.error_modulo_sdio=ERROR;
	}
	else
	{
			bandera.estado.error_modulo_sdio=OK;
	}*/
  /* USER CODE BEGIN 3 */
}
  /* USER CODE END 3 */

