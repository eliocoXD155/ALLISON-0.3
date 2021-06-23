char pMensaje[][27 + 1] =
{
    //         Descriptores     ////
    "*************************",//00    
    "**** SELF-TEST ALLIS ****",//01  
		"USB DEVICE         | OK  ",//02
		"USB DEVICE         | ERR ",//03
		"USB_HOST						| OK  ",//04
	  "USB_HOST						| ERR ",//05     
	  "BUTTON S2          | OK  ",//06
	  "BUTTON S2          | ERR ",//07
		"TAMPER             | OK  ",//08
	  "TAMPER             | ERR ",//09
		"SDIO MOUNT         | OK  ",//10
		"SDIO MOUNT         | ERR ",//11
		"SD FILE            | OK  ",//12
		"SD FILE            | ERR ",//13
		"FM MEMORY          | OK  ",//14
		"FM MEMORY          | ERR ",//15
		"EXP1               | OK  ",//16
		"EXP1               | ERR ",//17
		"MEM. FISCAL 2      | OK  ",//18
		"MEM. FISCAL 2      | ERR ",//19
		"UART VISOR         | OK  ",//20
		"UART VISOR         | ERR ",//21
		"UART PC            | OK  ",//22
		"UART PC            | ERR ",//23
		"UART PRINTER       | OK  ",//24
		"UART PRINTER       | ERR ",//25
		"Envie un caracter        ",//26
		"LED                | OK  ",//27
		"LED                | ERR ",//28
		"RAM 1              | OK  ",//29
		"RAM 1              | ERR ",//30
		"RAM 2              | OK  ",//31
		"RAM 2              | ERR ",//32
		"FLASH MEMORY       | OK  ",//33
		"FLASH MEMORY       | ERR ",//34
		"\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r",//35
		"-----------OK------------",//36
		"   **  TESTING  USB  **  ",//37
		"   **  TESTING GPIO  **  ",//38
		"   **  TESTING SPI   **  ",//39
		"   **  TESTING USART **  ",//40
		"   **  TESTING SDIO  **  ",//41
		" **  TESTING USB HOST ** ",//42
		"---> PRESS S2 BUTTON <---",//43
		"-----> PRESS TAMPER <----",//44
		"--->PRESS 'S' TO START<--",//45 "---->ENVIA UNA 'S'       " MENSAJE DE ANTES
		" TAMPER IS NOT CONNECTED ",//46
		"  **STARTING SELFTEST**  ",//47
		"---->CONECTE MODULO EXP  ",//48
		"JUMPER JP1         | OK  ",//49
		"JUMPER JP1         | ERR ",//50
		"JUMPER JP2         | OK  ",//51
		"JUMPER JP2         | ERR ",//52
		"PLEASE RESTART THE DEVICE",//53
		"BATTERY            | OK  ",//54
		"BATTERY            | ERR ",//55
		"RTC                | OK  ",//56
		"RTC                | ERR ",//57
		"   **  TESTING RTC  **   ",//58
		"    ",//59
		" \r\r\r\r\r\r\r\r\r\r\r\r",//60
		"SEND 'S' TO REPEAT THE ST",//61
		"        JP1 ERROR        ",//62
		"        JP2 ERROR        ",//63
		"------> CLOSE JP1 <------",//64
		"------> CLOSE JP2 <------",//65
		"  BATTERY TEST SKIPPED   ",//66
		"     S2 BUTTON ERROR     ",//67
		
//    //Personalizacion                           
//    "NOMBRE:"         ,           //39
//    "RIF/CI:"         ,           //40  
//    "DIRECCION:"      ,           //41    
//    "FACTURA:"        ,           //42    
//    "FECHA:"          ,           //43    
//    "CONTROL:"        ,           //44    
//    "DOC. ABIERTO!!  ",           //45  
//    //Mensajes de Envio                    
//    "ENVIANDO...     ",           //46
//    "ENVIO EXITOSO!! ",           //47
//    //Mensajes de Error                     
//    "ERROR TIMEOUT   ",           //48      
//    "ERROR DE INGRESO",           //49
//    "ERROR DE COMANDO",           //50
//    "NRO:            ",           //51        
//    "VALOR:          ",           //52  
//    "DEP:            ",           //53  
//    "PLU:            ",           //54  
//    "TASA:           ",           //55  
//    "PREC:           ",           //56  
//    "MAX:            ",           //57  
//    "COD:            ",           //58  
//    "TECLA:          ",           //59
//    "*** MODO  PC ***",           //60
//    "   SIN CAJERO",            	//61
//    "CLAVE:",                     //62      
//    "   CALCULADORA   ",					//63
//    "   Math ERROR   ",					//64
//		"+               ",					//65
//		"-               ",					//66
//		"x               ",					//67
//		"/               ",					//68
//		"%               ",					//69
//		"=               ",					//70
//		"BORRADO OK!!!",						//71
//		"BORRANDO...",							//72
//		"BORRADO ERROR!!!",					//73
//		"PROG OK!!!",								//74
//		"PROG ERROR!!!",            //75
//		"  REPORTE PLU   ",         //76
//		"  REPORTE DEP   ",					//77
//		"STOCK:          ",					//78
//		"STOCK EN CERO   "					//79
};