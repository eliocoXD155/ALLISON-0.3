#include "stm32f4xx_hal.h"
#include "fatfs.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "funciones.h"
#include "SD_driver.h"
#include "textos.h"
#include "string.h"
#include "spi_driver.h"

//Import de Variables y parametros 

extern eSTADOS bandera; 
char resultado[26] ={0};
extern char textos[][22];
extern UART_HandleTypeDef huart2;
extern void led_ok(void);



/*Parametros para el selftest del CC3220

Los comandos AT se envian como hexadecimales para poder incluir el <CR> el cual
es un parametro necesario para que el CC3220 pueda reconocer el final de los comandos
para luego procesarlos.

*/

extern UART_HandleTypeDef huart3;
uint8_t CMD_STA_MODE[]={0x61, 0x74, 0x2B, 0x77, 0x6C, 0x61, 0x6E, 0x73, 0x65, 0x74, 0x6D, 0x6F, 0x64, 0x65, 0x3D, 0x53, 0x54, 0x41, 0x0D, 0x0A};
uint8_t CMD_ADD_Net[]={0x61, 0x74, 0x2B, 0x77, 0x6C, 0x61, 0x6E, 0x70, 0x72, 0x6F, 0x66, 0x69, 0x6C, 0x65, 0x61, 0x64, 0x64, 0x3D, 0x57, 0x69, 0x66, 0x69, 0x2C, 0x2C, 0x57, 0x50, 0x41, 0x5F, 0x57, 0x50, 0x41, 0x32, 0x2C, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x2C, 0x2C, 0x2C, 0x2C, 0x31, 0x35, 0x0A, 0x0D};
uint8_t CMD_PING[]={0x61 , 0x74 , 0x2B , 0x6E , 0x65 , 0x74 , 0x61 , 0x70 , 0x70 , 0x70 , 0x69 , 0x6E , 0x67 , 0x3D , 0x49 , 0x4E , 0x45 , 0x54 , 0x2C , 0x31 , 0x39 , 0x32 , 0x2E , 0x31 , 0x36 , 0x38 , 0x2E , 0x31 , 0x2E , 0x31 , 0x2C , 0x33 , 0x32 , 0x2C , 0x31 , 0x30 , 0x2C , 0x35 , 0x30 , 0x30 , 0x2C , 0x34 , 0x2C , 0x30 , 0x0A , 0x0D};

/*El STM32 tiene ciertos conflictos con el puerto USB y los UART, hay prblemas 
	al momentto de usar ambos puertos en simultaneo por lo que se se prueban los puertos UART
	al inicio del selftest para liberar dichos puertos y evitar estos problemas.
	
	TODOS LOS RESULTADOS SON ALMACENADOS EN UN ARREGLO PARA SER MOSTRADOS AL FINAL DE LA PRUEBA
	
	*/

void selftest(void)
	{ 
		//Comunicacion con la impresora, este algoritmo envia un comando de status y luego recibe la respuesta
		
		resultado[10] = com_MB_Printer();
		
		/*Prueba del puerto UART, se envia un string por TX y se recibe por TX del mismo puerto, se comparan 
		los datos enviados y recibidos, si son iguales, la comunicacion fue exitosa*/
		
		resultado[12] = UART_Display();
		
		/*La prueba inicia presionando el boton SW1 y al mismo tiempo se prueba el boton, el resultado se guarda en el arreglo.
		El algoritmo espera cierto tiempo hasta que se presione el boton, una vez finalizado la prueba inicia automaticamente 
		con un resultado de ERROR para la prueba del switch*/
		
		resultado[1]=prueba_sw();
		
		HAL_Delay(100);
		
		/*La prueba de memorias se raliza con los puertos SPI configurados en el STM32, tambien se prueba la bateria de 3V3
		Al inicio de la prueba, se escribiran datos en las memorias y posteriormente se pedira apagar y encender la tarjeta,
		con el fin de verificar si la data fue almacenada correctamente en las memorias y si la bateria logro mantener 
		la alimentacion en las memorias, si todo esto se cumple los resltados para las memorias RAM, FLASH y FISCAL seran OK
		similarmente para la prueba de bateria*/
		
		prueba_drv_spi1();
		
		/*La prueba del USB consiste en poder recbir exitosamente el caracter s, pasado cierto tiempo si no se recibe el caracter
		el resultado para esta prueba sera ERROR*/
		
		resultado[0]=com_USB_PC();
		
		HAL_Delay(500);
		led_ok();
		
		/*Prueba de puertos GPIO, se pedira conectar los jumpers JP1 y JP2*/
		mensaje_USB(MENSAJE_PROBANDO_GPIO);
		HAL_Delay(100);
		resultado[2]=prueba_jp1();
		HAL_Delay(100);
		resultado[3]=prueba_jp2();
		HAL_Delay(100);
		
		/*Prueba del drawer, se envia el comando de abrir gabeta, la MB enviara el pulso para poder abrirla, si 
		se logra abrir se debe presionar el boton SW1 para confirmar el resultado, de lo contrario el resultado sera ERROR*/
		resultado[11] = drawer();
		
		/*Prueba de tarjeta SD, se verifica que este el montaje junto con una tarjeta SD y se verifica que se pueda acceder a 
		dicha memoria*/

		resultado[8] = prueba_drv_sdio();
		
		/*Los resultados de la prueba de los SPI se procesan con una pequena maquina de estados y se va llenando el arreglo
		de los resultados*/
		
		if (bandera.estado.error_memoria_ram1==OK){resultado[4] = (MENSAJE_RAM_1_OK);}
			else{resultado[4] =(MENSAJE_RAM_1_ERROR);}

		if (bandera.estado.error_memoria_flash==OK) {resultado[5] = (MENSAJE_FLASH_OK);}
			else{resultado[5] =(MENSAJE_FLASH_ERROR);}

		if (bandera.estado.error_spi_gprs==OK){resultado[6] = MENSAJE_SPI_GPRS_OK;}
			else{resultado[6] =MENSAJE_SPI_GPRS_ERROR;}
			
		if (bandera.estado.error_memoria_fiscal_1==OK) {resultado[7] = MENSAJE_MEM_FISCAL_1_OK;}
			else{resultado[7] =MENSAJE_MEM_FISCAL_1_ERROR;}
					
			
		if (bandera.estado.error_bateria==OK && bandera.estado.error_bateria_escribir==OK) {resultado[9] = (MENSAJE_BATERIA_OK);}
		  else{resultado[9] =(MENSAJE_BATERIA_ERROR);}
			
			//Muestra de todos los resultados de cada prueba
			int x1;		 
			mensaje_USB(MENSAJE_ESPACIO);
			mensaje_USB(MENSAJE_RESULTADOS);
				for(x1=0;x1<13;x1++){
		
					mensaje_USB(resultado[x1]);
					HAL_Delay(100);
				}
				mensaje_USB(MENSAJE_ESPACIO);
				
				//NOP, delay para limpiar buffer
		char PING1[]="\n\n ****FIRST PING ATTEMPT**** \n\n";
		
		
		mensaje_USB(MENSAJE_CC32);
		
		CDC_Transmit_FS((uint8_t *)PING1, strlen(PING1));
		

  }
	
	
	/*La prueba del CC3220 se realiza cargando previamente el firmware de comandos AT al modulo y posterior configuracion
	de los pines para la comunicacion por el UART y encendido de LEDS, una vez completado este paso se enciende el modulo 
	a traves del pin NRESET *pin 60 del ST* Una vez encendido el CC32 el envia automaticamente la configuracion por defecto
	Se envian 3 comandos, el primero es para configurar el modulo en modo STA para poder conectarse a una red, luego envia
	el comando para agregar la red a la cual se desea conectar finalmente se envia el comando para hacer PING al default gateway*/
	
	
void CC32_Selftest(void){
	
	//Declaracion de variables
	
	char	CCtxt[1304];
	char	CCtxt2[652];
	
	char PING2[]="\n\n ****SECOND PING ATTEMPT**** \n\n";
	
	/*Funcion de recepcion de datos por interrupciones (se debe habilitar en cada puerdo UART desde el Cube MX)
	Esta funcion se ejecuta cada vez que llega un dato, tiene mayor prioridad que el resto de las funciones
	por lo que se puede seguir ejecutando el algoritmo y paralelamente recibir datos*/
	
	HAL_UART_Receive_IT(&huart3,(uint8_t*)CCtxt,1302);
 
	int d = 2;
	int p1 =0;     		//p1, p2 Cantidad de veces que se debe intentar mandar el mensaje por USB hasta que se envia exitosamente
	int p2 = 1;
	
	
	/*Primer mensaje en pantalla*/
	
	/*while(p1){
			led_ok();
			CDC_Transmit_FS((uint8_t *)PING1, strlen(PING1));
			p1--;
	}*/
	
	/*Loop para 2 ciclos de comandos*/
	
	while(d!=0){
		HAL_Delay(2000);
		
		/*Encendido del modulo CC3220*/
		
		HAL_GPIO_WritePin(CC32_RESET_GPIO_Port,CC32_RESET_Pin,GPIO_PIN_SET);

		led_ERR();
		HAL_Delay(2000);

		/*Envio de comandos*/
			
			led_ok();
			HAL_UART_Transmit(&huart3,(uint8_t*)CMD_STA_MODE,sizeof(CMD_STA_MODE),HAL_MAX_DELAY);
			HAL_Delay(1000);
			led_ok();
			HAL_UART_Transmit(&huart3,(uint8_t*)CMD_ADD_Net,sizeof(CMD_ADD_Net),HAL_MAX_DELAY);
			HAL_Delay(1000);
			led_ok();
			HAL_UART_Transmit(&huart3,(uint8_t*)CMD_PING,sizeof(CMD_PING),HAL_MAX_DELAY);
      HAL_Delay(1000);			
		
		
		led_ERR();
		
		/*Envio de primeros resultados por USB*/
		
		
		d--;
		/*Segundo mensaje en pantalla*/
		
		if(d==1){
		while(p2){
		CDC_Transmit_FS((uint8_t *)CCtxt, strlen(CCtxt));
		HAL_Delay(500);
 
		led_ok();
		led_ok();
		led_ok();
		CDC_Transmit_FS((uint8_t *)PING2, strlen(PING2));
		p2--;}
		
		//memset(CCtxt,'\n',strlen(CCtxt));
		HAL_GPIO_WritePin(CC32_RESET_GPIO_Port,CC32_RESET_Pin,GPIO_PIN_RESET);
		
	}else{
		while(p1<=strlen(CCtxt2)){
			CCtxt2[p1]=CCtxt[(strlen(CCtxt)/2)+p1];
			p1++;
		}
		CDC_Transmit_FS((uint8_t *)CCtxt2, strlen(CCtxt2));
		led_ok();
	}
		
			
		
	}
	
	while(1){
	
	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
	
	}

}


