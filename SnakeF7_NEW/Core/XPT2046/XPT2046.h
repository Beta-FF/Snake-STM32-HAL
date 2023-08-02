#ifndef __XPT2046_H
#define __XPT2046_H

#include "main.h"
#include <stdbool.h>

extern SPI_HandleTypeDef hspi1;


#define __XPT2046_CS_SET()    HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_SET)
#define __XPT2046_CS_CLR()    HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET)
//#define __XPT2046_IRQ_READ()  HAL_GPIO_ReadPin(TP_IRQ_GPIO_Port, TP_IRQ_Pin)

void xpt2046_init(void);
void xpt2046_read_xy(uint16_t *phwXpos, uint16_t *phwYpos);
bool xpt2046_twice_read_xy(uint16_t *phwXpos, uint16_t *phwYpos);

#endif



