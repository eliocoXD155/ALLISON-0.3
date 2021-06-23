#include <stdbool.h>
#include "stm32f4xx_hal.h"




void MX_SPI1_Init(void);
void prueba_mem_fiscal(uint8_t dispositivo);
void prueba_mem_ram(uint8_t dispositivo);
void prueba_mem_flash(void);
void selecciona_dispositivo(uint8_t dispositivo);
void prueba_drv_spi1(void);

void escribe_memoria_ram(uint8_t dispositivo, uint8_t *direccion1, uint8_t *direccion2, uint8_t *direccion3, uint8_t *comando, uint8_t *dato);

void lee_memoria_ram(uint8_t dispositivo, uint8_t *direccion1, uint8_t *direccion2, uint8_t *direccion3, uint8_t *comando, uint8_t *dato);
void lee_memoria_fiscal(uint8_t dispositivo, uint8_t *comando, uint8_t *dato1, uint8_t *dato2, uint8_t *dato3);
void lee_memoria_flash(uint8_t *comando, uint8_t *dato1, uint8_t *dato2, uint8_t *dato3);

int status_error(HAL_StatusTypeDef status);

#define OK    0
#define ERROR 1

//**************Estructura de banderas del sistema**************//
typedef union
{
   struct
   {			
			unsigned error_uart_wifi:1;
			unsigned error_modulo_wifi:1;
			unsigned error_spi_impresora:1;
			unsigned error_spi_memorias:1;
			unsigned error_memoria_ram1_ini:1;	
			unsigned error_memoria_ram1_read:1;
			unsigned error_memoria_ram1_write:1;
			unsigned error_memoria_ram:1;
			
			unsigned error_memoria_fiscal_1:1;
			unsigned error_memoria_fiscal_2:1;
			unsigned error_memoria_ram1:1;
			unsigned error_memoria_spi_escribir:1;
			unsigned error_memoria_spi_leer:1;
			
			unsigned error_memoria_ram2:1;
			unsigned error_spi_gprs:1;
			unsigned error_spi_miso_cs:1;
			unsigned error_spi_sck_mosi:1;
			unsigned error_spi_cs_miso:1;
			unsigned error_spi_mosi_sck:1;
			unsigned error_memoria_flash:1;
			unsigned error_modulo_sdio:1;
			unsigned error_sdio_abrir_leer:1;
			unsigned error_sdio_abrir_escribir:1;	
			unsigned error_sdio_escribir_archivo:1;
			unsigned error_sdio_leer_archivo:1;			
			unsigned error_sdio_montaje:1;			
			unsigned error_modulo_sdio_create:1;
			unsigned error_sdio_formatear:1;	
			
			unsigned error_memoria_ram2_ini:1;
			unsigned error_led_pin1:1;
			unsigned error_led_pin2:1;			
			unsigned error_memoria_ram2_read:1;
			unsigned error_memoria_ram2_write:1;
			
			unsigned error_usb_device:1;
			unsigned error_usb_host:1;
			unsigned error_gpio1:1;
			unsigned error_gpio2:1;
			unsigned pulsador_gpio1:1;
			unsigned pulsador_gpio2:1;
			
			unsigned error_pulsador:1;
			unsigned error_led:1;
			unsigned error_tamper_rtc:1;
			unsigned error_tamper_det:1;			
			unsigned error_tamper:1;			
		
			unsigned error_uart_printer:1;
			unsigned error_uart_pc:1;
			unsigned error_uart_pc_rxtx:1;
			unsigned error_uart_pc_rts_cts:1;
			unsigned error_uart_visor:1;
			unsigned error_uart_visor_rxtx:1;
			unsigned error_uart_visor_ini:1;
			unsigned error_uart_visor_rts_cts:1;
			unsigned error_uart_pc_ini:1;
			unsigned error_uart_printer_ini:1;			
			unsigned error_uart_gprs:1;
			unsigned error_uart_ej:1;
			unsigned error_uart_smartcard:1;
			unsigned error_spi_damefic:1;
			unsigned error_uart_rts_cts:1;
			
			unsigned error_jp1:1;
			unsigned error_jp2:1;
			unsigned error_bateria:1;
			unsigned error_bateria_escribir:1;
			unsigned error_rtc:1;
			
			unsigned no_usado2:1;
			
  }estado;									// -----
	uint8_t cFlag[8];				// 56/8 = 7 bytes
	
} eSTADOS;

void prueba_drv_spi1(void);

