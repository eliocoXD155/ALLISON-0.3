#include "system.h"
#include "config.h"

eSTADOS bandera;   		// banderas generales
Memoria_TypeDef memoria;		// seleccion de memorias Conectads al SPI6 Flash, RAM1, RAM2
//FATFS SDFatFs;																// Objeto del Tipo FAT File SD
//FIL MyFileSD;

FATFS mi_FATFS;
FIL mi_archivo;

Funciones_TypeDef funciones;

FRESULT res;
HAL_StatusTypeDef status;
USBD_StatusTypeDef resul;

