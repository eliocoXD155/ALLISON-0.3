#include <stdio.h>
#include "main.h"
#include "stm32f4xx_hal.h"
#include "fatfs.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "funciones.h"
#include "textos.h"

extern int8_t CDC_Receive_FS  (uint8_t* pbuf, uint32_t *Len);
uint32_t len=1;


extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;
extern char textos[][26];

uint8_t buffer[64];
uint8_t usbdat[64];
uint8_t cut[2]={0x1b,0x69};
uint8_t statusp[2]={0x1b,0x76};
uint8_t draw[5]={0x1b,0x70,0x00,0x50,0x50};
uint8_t usb[64];
//#include "system.h"
//#include "config.h"

uint8_t cFlagLLego;
int x;
char msn[26];




void ALLISON_init(){

	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
	HAL_Delay(500);
	//mensaje_USB(resultado[11]);
	
		mensaje_USB(MENSAJE_ESPACIO);
		//HAL_Delay(100);
		mensaje_USB(MENSAJE_MARCA);
		//HAL_Delay(100);
		mensaje_USB(MENSAJE_TITULO_TARJETA);
		//HAL_Delay(100);
		mensaje_USB(MENSAJE_MARCA);
		//HAL_Delay(100);
};

void CC32_init(void){

	char CC1[]="-------CC3220 TEST-------\n";
	char CC2[]="---SENDING COMMANDS---\n";
	 
	CDC_Transmit_FS((uint8_t *)CC1, strlen((char *)CC1));
	HAL_Delay(100);
	CDC_Transmit_FS((uint8_t *)CC2, strlen((char *)CC2));
	
}

void mensaje_USB(int txt){


    strcpy(msn,textos[txt]);
		CDC_Transmit_FS((uint8_t *)msn, 26);
		HAL_Delay(500);

}
void mensaje(char *txt){


    strcpy(msn,txt);
		CDC_Transmit_FS((uint8_t *)msn, 26);
		HAL_Delay(500);

}

void led_ok(void){

  HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
	HAL_Delay(500);
}

void led_ERR(void){

  HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
	HAL_Delay(500);
}

void led_off(void){

  HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
	
}

int prueba_jp1(void){ //Prueba los puestos JP1 y JP2. Tienen que tener un jumper a la hora de conectarse.

	x=0;
	mensaje_USB(MENSAJE_PULSAR_JP1);
	
  while(x<=10){
		if(HAL_GPIO_ReadPin(JP1_GPIO_Port,JP1_Pin)!=1 ){
			led_ok();
			mensaje_USB(MENSAJE_PRUEBA_LISTA);
			return MENSAJE_JP1_OK;
			
		}
		led_ERR();
		HAL_Delay(50);
	x++;
	}
		return MENSAJE_JP1_ERROR;
	}
	
	
int prueba_jp2(void){
	x=0;
	mensaje_USB(MENSAJE_PULSAR_JP2);
	
  while(x<=10){
		if(HAL_GPIO_ReadPin(JP2_GPIO_Port,JP2_Pin)!=1 ){
			led_ok();
			mensaje_USB(MENSAJE_PRUEBA_LISTA);
			return MENSAJE_JP2_OK;
			
		}
		led_ERR();
		HAL_Delay(50);
	x++;
	}

	return MENSAJE_JP2_ERROR;	
	}
	//testigo_led(bandera.estado.error_jp2);		


int prueba_led(void){

	for(x=0;x<=3;x++){
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
		HAL_Delay(500);
	}
	return MENSAJE_LED_OK;
}

int prueba_sw(void){
	mensaje_USB(MENSAJE_PULSAR_PULSADOR);
  while(x<=10){
		if(HAL_GPIO_ReadPin(GPIOD,BOTON_Pin)!=1){
			led_ok();
			mensaje_USB(MENSAJE_ESPACIO);
			mensaje_USB(MENSAJE_INICIANDO_TEST);
			return MENSAJE_PUL_S1_OK;
			
		}
		led_ERR();
		HAL_Delay(50);
	x++;
	}

	return MENSAJE_PUL_S1_ERROR;
}


int com_USB_PC(void)	{
	int t = 0;
		
		char *mensaje = "\nUSB OK\n";
		uint32_t len=1;
		mensaje_USB(MENSAJE_REPETIR);
		//CDC_Transmit_FS((uint8_t *)mensaje, strlen(mensaje));
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
	
		while(t<10){
			led_ERR();
			if (usbdat[0]==0x73){
				
				//CDC_Transmit_FS((uint8_t *)mensaje, strlen(mensaje));
				led_ok();
				memset (usbdat, '\0',64);	
				
				return MENSAJE_USB_DEVICE_OK;
				
			}
			//
			t++;		
		}
		
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
		return MENSAJE_USB_DEVICE_ERROR;
 }

 int com_MB_Printer(void)	{
	int y=10;
  char a_recibir[]=".";
	 HAL_UART_Receive_IT(&huart2,(uint8_t*)a_recibir,1);
	 while(y){
	HAL_UART_Transmit_IT(&huart2,(uint8_t*)statusp,2);
	HAL_Delay(50);
	y--;
	 }
	 if(a_recibir[0]==0x00||a_recibir[0]==0x0C ){
	 led_ok();
	 return MENSAJE_UART_PRINTER_OK;
	 }
	 else{
	 led_ERR();
	 return MENSAJE_UART_PRINTER_ERROR;
	 }
	 

 }
  int UART_Display(void)	{
uint8_t i;
	char a_enviar[9]="Usart 2!";
	char a_recibir[9] = {0};

//		mensaje_display((uint8_t*)mensaje,MENSAJE_ENVIE_CHAR);

	for (i=0;i<=sizeof(a_recibir);i++)
	{
			HAL_UART_Transmit_IT(&huart6,(uint8_t*)&a_enviar[i],1);
			HAL_UART_Receive_IT(&huart6,(uint8_t*)&a_recibir[i],1);	
			HAL_Delay(50);		
	}
		
	if(strcmp(a_recibir,"Usart 2!")==0 && prueba_rts_cts())	{
		
		return MENSAJE_UART_VISOR_OK;				
	}else{
	return MENSAJE_UART_VISOR_ERROR;
	}
}

int prueba_rts_cts(void){
		HAL_GPIO_WritePin(RTS_MCU_CTS_VISOR_TTL_GPIO_Port,RTS_MCU_CTS_VISOR_TTL_Pin,GPIO_PIN_SET);
		HAL_Delay(30);
		if (HAL_GPIO_ReadPin(CTS_MCU_RTS_VISOR_TTL_GPIO_Port,CTS_MCU_RTS_VISOR_TTL_Pin)==1){
				led_ok();
				return 1;
				//HAL_Delay(50);	
		}else {return 0;}
}


 int drawer(void)	{
	int x=0;
	char dra1[]="-------DRAWER TEST-------\n";
	 char dra2[]="PUSH SW1 IF DRAWER OK\n";
	 
	 CDC_Transmit_FS((uint8_t *)dra1, strlen((char *)dra1));
	 
	 HAL_UART_Transmit_IT(&huart2,(uint8_t*)draw,5);
	 led_ok();
	 HAL_Delay(100);
	 CDC_Transmit_FS((uint8_t *)dra2, strlen((char *)dra2));
		while(x<=10){
		if(HAL_GPIO_ReadPin(GPIOD,BOTON_Pin)!=1){
			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
			return MENSAJE_DRAWER_OK;
			
		}
		led_ERR();
		HAL_Delay(50);
	x++;
	}
return MENSAJE_DRAWER_ERR;
	
 }
 
 
 
 
 int COM_TEST_WIFI(void){
	 //no funciona
	 uint8_t dataT[4]= "hola";
	 uint8_t dataR[8]="";
	 
   HAL_UART_Transmit(&huart3,dataT,4,HAL_MAX_DELAY);
		
	if(!HAL_UART_Receive(&huart3,dataR,8,1000)){
	  HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
    HAL_Delay(1000);
		//CDC_Transmit_FS((uint8_t *)dataR, 8);
		memset(dataR,0,8);
		return MENSAJE_UART_CC32_OK;
	}else{
		return MENSAJE_UART_CC32_ERROR;	
	}

}
 
