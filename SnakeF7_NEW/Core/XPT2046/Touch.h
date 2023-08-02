#ifndef __TOUCH_H_
#define __TOUCH_H_

#include "main.h"

#define TP_PRESS_DOWN           0x80
#define TP_PRESSED              0x40

#define __SPI_2div SPI1->CR1 &= (~SPI_CR1_SPE); hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2; HAL_SPI_Init(&hspi1); SPI1->CR1 |=  SPI_CR1_SPE

#define __SPI_128div SPI1->CR1 &= (~SPI_CR1_SPE); hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128; HAL_SPI_Init(&hspi1); SPI1->CR1 |=  SPI_CR1_SPE

typedef struct {
	uint16_t hwXpos0;
	uint16_t hwYpos0;
	uint16_t hwXpos;
	uint16_t hwYpos;
	uint8_t chStatus;
	uint8_t chType;
	short iXoff;
	short iYoff;
	float fXfac;
	float fYfac;
} tp_dev_t;

 void tp_init(void);
 void tp_adjust(void);
 void tp_dialog(void);
 void tp_draw_board(void);
 uint8_t tp_scan(uint8_t chCoordType);

#endif



