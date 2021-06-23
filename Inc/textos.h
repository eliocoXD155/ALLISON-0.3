
//***************************************************************************************************************//
//                                                    Definiciones                                               //
//***************************************************************************************************************//
	
	enum INDICADORES 
 {
	SIN_MENSAJE            				=-1,
  MENSAJE_MARCA          				=0,
  MENSAJE_TITULO_TARJETA 				=1,
  MENSAJE_USB_DEVICE_OK  				=2,
  MENSAJE_USB_DEVICE_ERROR      =3,
	MENSAJE_PUL_S1_OK     				=4,
  MENSAJE_PUL_S1_ERROR  				=5,
  MENSAJE_SDIO_OK        				=6,
  MENSAJE_SDIO_ERROR     				=7,
  MENSAJE_SDIO_FILE_OK          =8,
  MENSAJE_SDIO_FILE_ERROR     	=9,
  MENSAJE_MEM_FISCAL_1_OK     	=10,
  MENSAJE_MEM_FISCAL_1_ERROR  	=11,
  MENSAJE_SPI_GPRS_OK          	=12,
  MENSAJE_SPI_GPRS_ERROR       	=13,
  MENSAJE_MEM_FISCAL_2_OK     	=14,
  MENSAJE_MEM_FISCAL_2_ERROR   	=15,
  MENSAJE_UART_VISOR_OK        	=16,
  MENSAJE_UART_VISOR_ERROR     	=17,
	MENSAJE_UART_CC32_OK					=18,
  MENSAJE_UART_CC32_ERROR				=19,
  MENSAJE_UART_PRINTER_OK				=20,
  MENSAJE_UART_PRINTER_ERROR		=21,
	MENSAJE_PUSH_SW           		=22,
 	MENSAJE_ENVIE_CHAR						=23,
	MENSAJE_LED_OK								=24,
	MENSAJE_LED_ERROR							=25,
	MENSAJE_RAM_1_OK     					=26,
  MENSAJE_RAM_1_ERROR     			=27,
  MENSAJE_FLASH_OK        			=28,
  MENSAJE_FLASH_ERROR     			=29,
  MENSAJE_ESPACIOS     					=30,  //AGREGADO
	MENSAJE_PRUEBA_LISTA 					=31,
	MENSAJE_PROBANDO_USB 					=32,
 	MENSAJE_PROBANDO_GPIO   			=33,	//AGREGADO
	MENSAJE_PROBANDO_SPI 					=34,
	MENSAJE_PROBANDO_USART 				=35,
	MENSAJE_PROBANDO_SDIO 				=36,
  MENSAJE_PULSAR_PULSADOR				=37,
  MENSAJE_PRUEBA_USB						=38,
	MENSAJE_INICIANDO_TEST				=39,
	MENSAJE_PRUEBA_EXP						=40,
	MENSAJE_JP1_OK          			=41,
	MENSAJE_JP1_ERROR       			=42,
	MENSAJE_JP2_OK          			=43,
	MENSAJE_JP2_ERROR       			=44,
	MENSAJE_PRUEBA_BATERIA				=45,
	MENSAJE_BATERIA_OK  					=46,
	MENSAJE_BATERIA_ERROR					=47,
	MENSAJE_ESPACIO								=48,
	MENSAJE_SALTO_DE_LINEA				=49,
	MENSAJE_REPETIR								=50,
	MENSAJE_JP1_NOCONECTADO				=51,
	MENSAJE_JP2_NOCONECTADO				=52,
	MENSAJE_PULSAR_JP1						=53,
	MENSAJE_PULSAR_JP2						=54,
	MENSAJE_NO_BATERIA						=55,
	MENSAJE_RESULTADOS      			=56,
	MENSAJE_DRAWER_OK       			=57,
	MENSAJE_DRAWER_ERR       			=58,
  MENSAJE_REPETIR2							=59,
	MENSAJE_CC32					    		=60,
	MENSAJE_CC32_ERR			    		=61,
	MENSAJE_CC32_PING_ERR			    =62
 };
 
 
void fun(void);

 