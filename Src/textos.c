char textos[][26] =
{
    //         Descriptores     ////
    "*************************\n",//00    
    "****SELF-TEST ALLISON****\n",//01  
		"USB COM            | OK  \n",//02
		"USB COM            | ERR \n",//03
	  "BUTTON S1          | OK  \n",//04
	  "BUTTON S1          | ERR \n",//05
		"SDIO MOUNT         | OK  \n",//06
		"SDIO MOUNT         | ERR \n",//07
		"SD FILE            | OK  \n",//08
		"SD FILE            | ERR \n",//09
		"FM MEMORY          | OK  \n",//10
		"FM MEMORY          | ERR \n",//11
		"EXP1               | OK  \n",//12
		"EXP1               | ERR \n",//13
		"MEM. FISCAL 2      | OK  \n",//14
		"MEM. FISCAL 2      | ERR \n",//15
		"UART6 VISOR        | OK  \n",//16
		"UART6 VISOR        | ERR \n",//17
		"UART3 CC3220       | OK  \n",//18
		"UART3 CC3220       | ERR \n",//19
		"UART2 PRINTER      | OK  \n",//20
		"UART2 PRINTER      | ERR \n",//21
		"PRESIONE EL SW           \n",//22
		"Envie un caracter        \n",//23
		"LED                | OK  \n",//24
		"LED                | ERR \n",//25
		"RAM 1              | OK  \n",//26
		"RAM 1              | ERR \n",//27
		"FLASH MEMORY       | OK  \n",//28
		"FLASH MEMORY       | ERR \n",//29
		"\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r",//30
		"-----------OK------------\n",//31
		"   **  TESTING  USB  **  \n",//32
		"\n  **  TESTING GPIO  **  \n",//33
		"   **  TESTING SPI   **  \n",//34
		"   **  TESTING USART **  \n",//35
		"   **  TESTING SDIO  **  \n",//36
		"PRESS S1 BUTTON  TO START\n",//37
		"--->PRESS 'S' TO START<--\n",//38 "---->ENVIA UNA 'S'       " MENSAJE DE ANTES
		"  **STARTING SELFTEST**  \n",//39
		"---->CONECTE MODULO EXP  \n",//40
		"JUMPER JP1         | OK  \n",//41
		"JUMPER JP1         | ERR \n",//42
		"JUMPER JP2         | OK  \n",//43
		"JUMPER JP2         | ERR \n",//44
		"BATERY TEST..restart dev \n",//45
		"BATTERY            | OK  \n",//46
		"BATTERY            | ERR \n",//47
		"                         \n" ,//48
		" \r\r\r\r\r\r\r\r\r\r\r\r"  ,//49
		"         SEND 'S'        \n",//50
		"        JP1 ERROR        \n",//51
		"        JP2 ERROR        \n",//52
		"------> CLOSE JP1 <------\n",//53
		"------> CLOSE JP2 <------\n",//54
		"  BATTERY TEST SKIPPED   \n",//55
		"     SELFTEST RESULT     \n",//56
		"DRAWER             | OK  \n",//57
		"DRAWER             | ERR \n",//58
		"    TO REPEAT SELFTEST   \n",//59
		"     ***CC3220 TEST***   \n",//60
		"       NETWORK ERROR     \n",//61
		"PING ERROR, SENDING AGAIN\n",//62
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

void fun(void){};