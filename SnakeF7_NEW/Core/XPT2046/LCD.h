/**
  ******************************************************************************
  * @file    xxx.h
  * @author  Waveshare Team
  * @version 
  * @date    xx-xx-2014
  * @brief   xxxxx.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WAVESHARE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _LCD_H_
#define _LCD_H_

/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include <stdlib.h>
#include "main.h"

extern SPI_HandleTypeDef hspi1;
#define lcd_SPI          hspi1
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define __LCD_BKL_SET()     HAL_GPIO_WritePin(TFT_BL_GPIO_Port, TFT_BL_Pin, GPIO_PIN_SET)
#define __LCD_BKL_CLR()     HAL_GPIO_WritePin(TFT_BL_GPIO_Port, TFT_BL_Pin, GPIO_PIN_RESET)

#define __LCD_CS_SET()      HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_SET)
#define __LCD_CS_CLR()      HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET)

#define __LCD_DC_SET()      HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_SET)
#define __LCD_DC_CLR()      HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_RESET)

#define __LCD_WRITE_BYTE(__DATA)        HAL_SPI_Transmit(&hspi1, &__DATA, 1, 100)

#define __SPI_16Bit_set lcd_SPI.Instance->CR1 &= (~SPI_CR1_SPE); lcd_SPI.Init.DataSize = SPI_DATASIZE_16BIT; HAL_SPI_Init(&lcd_SPI); lcd_SPI.Instance->CR1 |=  SPI_CR1_SPE

#define __SPI_8Bit_set lcd_SPI.Instance->CR1 &= (~SPI_CR1_SPE); lcd_SPI.Init.DataSize = SPI_DATASIZE_8BIT; HAL_SPI_Init(&lcd_SPI); lcd_SPI.Instance->CR1 |=  SPI_CR1_SPE

#define LCD_WIDTH    240
#define LCD_HEIGHT   320

#define CHAR_WIDTH    6
#define CHAR_HEIGHT	  8
#define FONT_1206    12
#define FONT_1608    16

#define WHITE          0xFFFF
#define BLACK          0x0000	  
#define BLUE           0x001F  
#define BRED           0XF81F
#define GRED 		   0XFFE0
#define GBLUE		   0X07FF
#define RED            0xF800
#define MAGENTA        0xF81F
#define GREEN          0x07E0
#define CYAN           0x7FFF
#define YELLOW         0xFFE0
#define BROWN 		   0XBC40 
#define BRRED 		   0XFC07 
#define GRAY  		   0X8430 

#define LCD_CMD                0
#define LCD_DATA               1

/* Exported functions ------------------------------------------------------- */


 void lcd_init(void);
 void lcd_clear_screen(uint16_t hwColor);
 void lcd_draw_point(uint16_t hwXpos, uint16_t hwYpos, uint16_t hwColor);
 void lcd_display_char(uint16_t hwXpos, //specify x position.
                         uint16_t hwYpos, //specify y position.
                         uint8_t chChr,   //a char is display.
                         uint8_t chSize,  //specify the size of the char
                         uint16_t hwColor); //specify the color of the char
 void lcd_display_num(uint16_t hwXpos,  //specify x position.
                          uint16_t hwYpos, //specify y position.
                          uint32_t chNum,  //a number is display.
                          uint8_t chLen,   //length ot the number
                          uint8_t chSize,  //specify the size of the number
                          uint16_t hwColor); //specify the color of the number
 void lcd_display_string(uint16_t hwXpos, //specify x position.
                         uint16_t hwYpos,   //specify y position.
                         const uint8_t *pchString,  //a pointer to string
                         uint8_t chSize,    // the size of the string 
                         uint16_t hwColor);  // specify the color of the string 
 void lcd_draw_line(uint16_t hwXpos0, //specify x0 position.
                      uint16_t hwYpos0, //specify y0 position.
                      uint16_t hwXpos1, //specify x1 position.
                      uint16_t hwYpos1, //specify y1 position.
                      uint16_t hwColor); //specify the color of the line                     
 void lcd_draw_circle(uint16_t hwXpos,  //specify x position.
                        uint16_t hwYpos,  //specify y position.
                        uint16_t hwRadius, //specify the radius of the circle.
                        uint16_t hwColor);  //specify the color of the circle.
 void lcd_fill_rect(uint16_t hwXpos,  //specify x position.
                   uint16_t hwYpos,  //specify y position.
                   uint16_t hwWidth, //specify the width of the rectangle.
                   uint16_t hwHeight, //specify the height of the rectangle.
                   uint16_t hwColor);  //specify the color of rectangle.
 void lcd_draw_v_line(uint16_t hwXpos, //specify x position.
                        uint16_t hwYpos, //specify y position. 
                        uint16_t hwHeight, //specify the height of the vertical line.
                        uint16_t hwColor);  //specify the color of the vertical line.
 void lcd_draw_h_line(uint16_t hwXpos, //specify x position.
                        uint16_t hwYpos,  //specify y position. 
                        uint16_t hwWidth, //specify the width of the horizonal line.
                        uint16_t hwColor); //specify the color of the horizonal line.
 void lcd_draw_rect(uint16_t hwXpos,  //specify x position.
                      uint16_t hwYpos,  //specify y position.
                      uint16_t hwWidth, //specify the width of the rectangle.
                      uint16_t hwHeight, //specify the height of the rectangle.
                      uint16_t hwColor);  //specify the color of rectangle.
void lcd_set_window(uint16_t hwXpos, uint16_t hwYpos, uint16_t hwWidth, uint16_t hwHeight);
void lcd_write_register(uint8_t chRegister, uint8_t chValue);
void lcd_write_byte(uint8_t chByte, uint8_t chCmd);
void lcd_write_word(uint16_t hwData);

void ILI9341_Draw_Horizontal_Line(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Colour);
void ILI9341_Draw_Vertical_Line(uint16_t X, uint16_t Y, uint16_t Height, uint16_t Colour);
void ILI9341_Draw_Hollow_Rectangle_Coord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t Colour);
void lcd_draw_mono_image(const unsigned  char* Image_Array, uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height, uint16_t Colour, uint8_t Size);

#endif
/*-------------------------------END OF FILE-------------------------------*/

