/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>

#include "../XPT2046/XPT2046.h"
#include "../XPT2046/LCD.h"
#include "../XPT2046/Touch.h"
#include "../XPT2046/5x5_font.h"
#include "../XPT2046/graphics.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define FRAME_Free		0
#define FRAME_Snake		10
#define FRAME_Block		11
#define FRAME_Food		12
#define FRAME_Turtle	13

#define MOVE_LEFT	1
#define MOVE_RIGHT	2
#define MOVE_UP		3
#define MOVE_DOWN	4

#define food	0
#define turtle	1

#define normal	0
#define maze	1

#define head_x snake[0][0]
#define head_y snake[0][1]
#define tail_x snake[snake_lenght - 1][0]
#define tail_y snake[snake_lenght - 1][1]
#define tail_x_old snake[snake_lenght][0]
#define tail_y_old snake[snake_lenght][1]
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 ADC_HandleTypeDef hadc3;

RNG_HandleTypeDef hrng;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
const uint16_t Classic_GREEN	 = 0x9660;
const uint16_t ClassicFont_GREEN = 0x0000;
const uint16_t LCD1602_GREEN	 = 0xCFA4;
const uint16_t LCD1602Font_GREEN = 0x4322;
const uint16_t LCD1602_BLUE		 = 0x0358;
const uint16_t LCD1602Font_BLUE	 = 0xB79F;
const uint16_t LCD1602_RED		 = 0xF800;
const uint16_t LCD1602Font_RED	 = 0x0000;
const uint16_t OLED_BLUE		 = 0x0000;
const uint16_t OLEDFont_BLUE	 = 0x1F9E;
const uint16_t OLED_YELLOW	 	 = 0x0000;
const uint16_t OLEDFont_YELLOW	 = 0xFF80;
const uint16_t OLED_WHITE	 	 = 0x0000;
const uint16_t OLEDFont_WHITE	 = 0xFFFF;
const uint16_t CUSTOM_YELLOW	 = 0xFF80;
const uint16_t CUSTOM_YELLOWFont = 0x0000;
const uint16_t FALLOUT			 = 0x19A4;
const uint16_t FALLOUTFont		 = 0x168D;

const uint8_t field_width = 12;
const uint8_t field_height = 15;

const char classic[] = "Classic";
const char lcd_green[] = "LCD Green";
const char lcd_blue[] = "LCD Blue";
const char lcd_red[]  = "LCD Red";
const char oled_b[] = "OLED B";
const char oled_y[] = "OLED Y";
const char oled_w[] = "OLED W";
const char fallout[]  = "Fallout";
const char yellow[]  = "Yellow";


struct btn {
	uint8_t up, down, left, right, center;
} btn;

uint8_t move_dir = 3;
uint8_t move_dir_old = 3;
uint8_t snake_lenght = 3;
uint8_t turtle_exist = 0;
uint8_t eating = 0;

uint8_t go_game = 0;
uint16_t score = 0;
uint8_t turtles = 0;
uint16_t speed = 500;

uint8_t color_pack = 1;
uint16_t main_color = 0x9660;
uint16_t font_color = 0x0000;

uint32_t sys_t0 = 0;
uint32_t sys_t1 = 0;
uint32_t sys_t2 = 0;
uint32_t sys_t3 = 0;

int8_t snake[300][2];
char str[32];
uint8_t field[13][16]; //[16][13]

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC3_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_RNG_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void joy_direction() {
	HAL_ADC_Start(&hadc3);
	HAL_ADC_PollForConversion(&hadc3, 20);
	uint16_t adc_x = HAL_ADC_GetValue(&hadc3);
	HAL_ADC_Start(&hadc3);
	HAL_ADC_PollForConversion(&hadc3, 20);
	uint16_t adc_y = HAL_ADC_GetValue(&hadc3);

	/*HAL_ADCEx_InjectedStart(&hadc3);
	HAL_ADC_PollForConversion(&hadc3, 20);
	uint16_t adc_x = HAL_ADCEx_InjectedGetValue(&hadc3, ADC_INJECTED_RANK_1);
	uint16_t adc_y = HAL_ADCEx_InjectedGetValue(&hadc3, ADC_INJECTED_RANK_2);
	*/

	//HAL_UART_Transmit(&huart2, (uint8_t*)str, sprintf(str, "x=%d y=%d\r\n", adc_x, adc_y), 100);

	//joy_x_state <<= 1;
	//joy_y_state <<= 1;
	if(adc_x > 225) { move_dir = MOVE_RIGHT; return; }
	if(adc_x < 25) { move_dir = MOVE_LEFT; return; }
	if(adc_y > 225) { move_dir = MOVE_UP; return; }
	if(adc_y < 25) { move_dir = MOVE_DOWN; return; }
	//move_dir = 0;
}

void joy_digit() {
	HAL_ADC_Start(&hadc3);
	HAL_ADC_PollForConversion(&hadc3, 20);
	uint16_t adc_x = HAL_ADC_GetValue(&hadc3);
	HAL_ADC_Start(&hadc3);
	HAL_ADC_PollForConversion(&hadc3, 20);
	uint16_t adc_y = HAL_ADC_GetValue(&hadc3);

	HAL_UART_Transmit(&huart3, (uint8_t*)str, sprintf(str, "x=%d y=%d\r\n", adc_x, adc_y), 100);

	btn.left <<= 1;
	btn.right <<= 1;
	btn.up <<= 1;
	btn.down <<= 1;
	if(adc_x < 225) btn.left |= 1;
	if(adc_x > 25) btn.right |= 1;
	if(adc_y < 225) btn.down |= 1;
	if(adc_y > 25) btn.up |= 1;
}

void draw_snake() {
	lcd_fill_rect(tail_x_old*16+16, tail_y_old*16+52, 16, 16, main_color);
	//ILI9341_Draw_Rectangle(tail_x_old*16+16, tail_y_old*16+52, 16, 16, main_color); //�������� ������

	int32_t Image_addr = 0;
	switch(move_dir) {
		case MOVE_UP: Image_addr = &Image_head_U; break;
		case MOVE_LEFT: Image_addr = &Image_head_L; break;
		case MOVE_RIGHT: Image_addr = &Image_head_R; break;
		case MOVE_DOWN: Image_addr = &Image_head_D; break;
	}
	lcd_draw_mono_image(Image_addr, head_x*16+16, head_y*16+52, 8, 8, font_color, 2);

	lcd_fill_rect(snake[1][0]*16+16, snake[1][1]*16+52, 16, 16, main_color);
	if(eating == 1) {
		switch(move_dir) {
			case MOVE_UP:  Image_addr = &Image_body_food_U_D; break;
			case MOVE_DOWN: Image_addr = &Image_body_food_U_D; break;
			case MOVE_LEFT: Image_addr = &Image_body_food_L_R; break;
			case MOVE_RIGHT: Image_addr = &Image_body_food_L_R; break;
		}
		eating = 0;
	} else
	if(move_dir_old == MOVE_RIGHT) {
		switch(move_dir) {
			case MOVE_UP:  Image_addr = &Image_body_UtoL; break;
			case MOVE_DOWN: Image_addr = &Image_body_DtoL; break;
			case MOVE_RIGHT: Image_addr = &Image_body_L_R; break;
		}
	} else
	if(move_dir_old == MOVE_UP) {
		switch(move_dir) {
			case MOVE_LEFT:  Image_addr = &Image_body_DtoL; break;
			case MOVE_RIGHT: Image_addr = &Image_body_DtoR; break;
			case MOVE_UP: Image_addr = &Image_body_U_D; break;
		}
	} else
	if(move_dir_old == MOVE_DOWN) {
		switch(move_dir) {
			case MOVE_LEFT:  Image_addr = &Image_body_UtoL; break;
			case MOVE_RIGHT: Image_addr = &Image_body_UtoR; break;
			case MOVE_DOWN: Image_addr = &Image_body_U_D; break;
		}
	} else
	if(move_dir_old == MOVE_LEFT) {
		switch(move_dir) {
			case MOVE_UP:  Image_addr = &Image_body_UtoR; break;
			case MOVE_DOWN: Image_addr = &Image_body_DtoR; break;
			case MOVE_LEFT: Image_addr = &Image_body_L_R; break;
		}
	}
	lcd_draw_mono_image(Image_addr, snake[1][0]*16+16, snake[1][1]*16+52, 8, 8, font_color, 2);

	lcd_fill_rect(tail_x*16+16, tail_y*16+52, 16, 16, main_color);
	if(tail_y == snake[snake_lenght-2][1]) {
		if(tail_x < snake[snake_lenght-2][0]) Image_addr = &Image_tail_R;
		if(tail_x > snake[snake_lenght-2][0]) Image_addr = &Image_tail_L;
	}
	if(tail_x == snake[snake_lenght-2][0]) {
		if(tail_y < snake[snake_lenght-2][1]) Image_addr = &Image_tail_D;
		if(tail_y > snake[snake_lenght-2][1]) Image_addr = &Image_tail_U;
	}
	lcd_draw_mono_image(Image_addr, tail_x*16+16, tail_y*16+52, 8, 8, font_color, 2);
}

void snake_to_field() {
	for(int s=0; s<snake_lenght; s++) {
	field[snake[s][0]][snake[s][1]] = FRAME_Snake;
	}
	field[tail_x_old][tail_y_old] = FRAME_Free;
}

void upd_score() {
	sprintf(str, "%04d", score);
	ILI9341_Draw_Text(str, 6, 2, font_color, 3, main_color);
}

void upd_turtles() {
	sprintf(str, "%02d", turtles);
	ILI9341_Draw_Text(str, 199, 2, font_color, 3, main_color);
}

void draw_interface(uint8_t game_mode){
	lcd_clear_screen(main_color);
	lcd_draw_mono_image(Image_big_turtle, 162, 8, 32, 16, font_color, 1);
	upd_score();
	upd_turtles();
	for(int r=0; r<46; r++) {
		lcd_fill_rect(r*5+5, 32, 4, 4, font_color);
		lcd_fill_rect(r*5+5, 42, 4, 4, font_color);
		lcd_fill_rect(r*5+5, 312, 4, 4, font_color);
	}
	for(int s=0; s<54; s++) {
		lcd_fill_rect(5, s*5+42, 4, 4, font_color);
		lcd_fill_rect(230, s*5+42, 4, 4, font_color);
	}
	if(game_mode == 2) {
		for(int s=0; s<4; s++) {
			field[s][0] = field[s+9][0] = field[s][15] = field[s+9][15] = FRAME_Block;
			lcd_draw_mono_image(Image_Block, s*16+16,		52, 16, 16, font_color, 1);
			lcd_draw_mono_image(Image_Block, (s+9)*16+16,	52, 16, 16, font_color, 1);
			lcd_draw_mono_image(Image_Block, s*16+16,		15*16+52, 16, 16, font_color, 1);
			lcd_draw_mono_image(Image_Block, (s+9)*16+16,	15*16+52, 16, 16, font_color, 1);
		}
		for(int s=0; s<4; s++) {
			field[0][s] = field[0][s+12] = field[12][s] = field[12][s+12] = FRAME_Block;
			lcd_draw_mono_image(Image_Block, 16,		s*16+52, 16, 16, font_color, 1);
			lcd_draw_mono_image(Image_Block, 16,		(s+12)*16+52, 16, 16, font_color, 1);
			lcd_draw_mono_image(Image_Block, 12*16+16,	s*16+52, 16, 16, font_color, 1);
			lcd_draw_mono_image(Image_Block, 12*16+16,	(s+12)*16+52, 16, 16, font_color, 1);
		}
		for(int r=4; r<12; r++) {
			field[4][r] = field[8][r] = FRAME_Block;
			lcd_draw_mono_image(Image_Block, 4*16+16, r*16+52, 16, 16, font_color, 1);
			lcd_draw_mono_image(Image_Block, 8*16+16, r*16+52, 16, 16, font_color, 1);
		}

	}
}

void new_snake(uint8_t start_x, uint8_t start_y) {
	head_x = start_x;
	head_y = start_y;
	snake[1][0] = start_x;
	snake[1][1] = start_y + 1;
	tail_x = start_x;
	tail_y = start_y + 2;
	tail_x_old = start_x;
	tail_y_old = start_y + 3;
	snake[snake_lenght + 1][0] = start_x;
	snake[snake_lenght + 1][1] = start_y + 4;
}

void game_over() {
	lcd_fill_rect(91, 2, 56, 32, main_color);
	ILI9341_Draw_Text("GAME", 96, 2, font_color, 2, main_color);
	ILI9341_Draw_Text("OVER", 96, 18, font_color, 2, main_color);
	while(1) {
		ILI9341_Draw_Hollow_Rectangle_Coord(91, 2, 147, 34, font_color);
		ILI9341_Draw_Hollow_Rectangle_Coord(90, 1, 148, 35, font_color);
		HAL_Delay(250);
		ILI9341_Draw_Hollow_Rectangle_Coord(91, 2, 147, 34, main_color);
		ILI9341_Draw_Hollow_Rectangle_Coord(90, 1, 148, 35, main_color);
		HAL_Delay(250);
	}
}

void add_food(uint8_t food_or_turtle) {
	uint8_t food_x, food_y;
	do {
		do {
		food_x = (HAL_RNG_GetRandomNumber(&hrng) & 0x0F);
		} while(food_x > field_width);
		food_y = (HAL_RNG_GetRandomNumber(&hrng) & 0x0F);
	} while(field[food_x][food_y] != FRAME_Free);
	switch(food_or_turtle) {
	case food: field[food_x][food_y] = FRAME_Food;
			lcd_draw_mono_image(Image_food, food_x*16+16, food_y*16+52, 8, 8, font_color, 2);
			break;
	case turtle: field[food_x][food_y] = FRAME_Turtle;
			lcd_draw_mono_image(Image_turtle, food_x*16+16, food_y*16+52, 16, 16, font_color, 1);
			break;
	}
}

void check_contact() {
	switch(field[head_x][head_y]) {
		case FRAME_Snake: game_over(); break;

		case FRAME_Block: game_over(); break;

		case FRAME_Food:
			eating = 1;
			snake_lenght++;
			score += 5;
			speed -= 10;
			if(speed < 150) speed = 150;
			upd_score();
			add_food(food); break;

		case FRAME_Turtle:
			eating = 1;
			snake_lenght++;
			score += 15;
			turtles++;
			speed -= 10;
			if(speed < 150) speed = 150;
			upd_score();
			upd_turtles();
			turtle_exist = 0; break;
	}
}

void shift_arr_snake() {
	for(uint8_t c=snake_lenght+1; c>0; c--) {
		snake[c][0] = snake[c-1][0];
		snake[c][1] = snake[c-1][1];
	}
}

void move_snake() {
	if((move_dir == MOVE_LEFT) & (move_dir_old == MOVE_RIGHT)) move_dir = MOVE_RIGHT;
	if((move_dir == MOVE_RIGHT) & (move_dir_old == MOVE_LEFT)) move_dir = MOVE_LEFT;
	if((move_dir == MOVE_UP) & (move_dir_old == MOVE_DOWN)) move_dir = MOVE_DOWN;
	if((move_dir == MOVE_DOWN) & (move_dir_old == MOVE_UP)) move_dir = MOVE_UP;
	switch(move_dir) {
	  case MOVE_LEFT:

		   shift_arr_snake();
		   head_x--;
		   if(head_x < 0) head_x = field_width;
		   break;

	  case MOVE_RIGHT:
		   //if(move_dir_old == MOVE_LEFT) { return; }
		   shift_arr_snake();
		   head_x++;
		   if(head_x > field_width) head_x = 0;
		   break;

	  case MOVE_UP:
		   //if(move_dir_old == MOVE_DOWN) { return; }
		   shift_arr_snake();
		   head_y--;
		   if(head_y < 0) head_y = field_height;
		   break;

	  case MOVE_DOWN:
		   //if(move_dir_old == MOVE_UP) { return; }
		   shift_arr_snake();
		   head_y++;
		   if(head_y > field_height) head_y = 0;
		   break;
	}
}

void draw_arrow(uint8_t arrow) {
	uint8_t text_x = 15;
	uint8_t text_y = 168;
	switch(arrow) {
		case 1: ILI9341_Draw_Text(">", text_x, text_y+24, font_color, 3, main_color);
				ILI9341_Draw_Text(" ", text_x, text_y+48, font_color, 3, main_color);
				ILI9341_Draw_Text(" ", text_x, text_y+96, font_color, 3, main_color);
		break;
		case 2: ILI9341_Draw_Text(" ", text_x, text_y+24, font_color, 3, main_color);
				ILI9341_Draw_Text(">", text_x, text_y+48, font_color, 3, main_color);
				ILI9341_Draw_Text(" ", text_x, text_y+96, font_color, 3, main_color);
		break;
		case 3: ILI9341_Draw_Text(" ", text_x, text_y+24, font_color, 3, main_color);
				ILI9341_Draw_Text(" ", text_x, text_y+48, font_color, 3, main_color);
				ILI9341_Draw_Text(">", text_x, text_y+96, font_color, 3, main_color);

		break;
	}
}

void draw_menu(uint8_t st) {
	lcd_clear_screen(main_color);
	uint8_t text_x = 15;
	uint8_t text_y = 168;
	lcd_draw_mono_image(Image_snake_logo, 24, 20, 96, 64, font_color, 2);
	ILI9341_Draw_Text("NEW GAME:", text_x, text_y, font_color, 3, main_color);
	ILI9341_Draw_Text("  NORMAL", text_x, text_y+24, font_color, 3, main_color);
	ILI9341_Draw_Text("  MAZE", text_x, text_y+48, font_color, 3, main_color);
	ILI9341_Draw_Text("COLOR: ", text_x, text_y+72, font_color, 3, main_color);
	switch(color_pack) {
	case 1: ILI9341_Draw_Text(classic, text_x+36, text_y+96, font_color, 3, main_color); break;
	case 2: ILI9341_Draw_Text(lcd_green, text_x+36, text_y+96, font_color, 3, main_color); break;
	case 3: ILI9341_Draw_Text(lcd_blue, text_x+36, text_y+96, font_color, 3, main_color); break;
	case 4: ILI9341_Draw_Text(lcd_red, text_x+36, text_y+96, font_color, 3, main_color); break;
	case 5: ILI9341_Draw_Text(oled_b, text_x+36, text_y+96, font_color, 3, main_color); break;
	case 6: ILI9341_Draw_Text(oled_y, text_x+36, text_y+96, font_color, 3, main_color); break;
	case 7: ILI9341_Draw_Text(oled_w, text_x+36, text_y+96, font_color, 3, main_color); break;
	case 8: ILI9341_Draw_Text(fallout, text_x+36, text_y+96, font_color, 3, main_color); break;
	case 9: ILI9341_Draw_Text(yellow, text_x+36, text_y+96, font_color, 3, main_color); break;
	}
	switch(st) {
		case 1: ILI9341_Draw_Text(">", text_x, text_y+24, font_color, 3, main_color);
				ILI9341_Draw_Text(" ", text_x, text_y+48, font_color, 3, main_color);
				ILI9341_Draw_Text(" ", text_x, text_y+96, font_color, 3, main_color);
		break;
		case 2: ILI9341_Draw_Text(" ", text_x, text_y+24, font_color, 3, main_color);
				ILI9341_Draw_Text(">", text_x, text_y+48, font_color, 3, main_color);
				ILI9341_Draw_Text(" ", text_x, text_y+96, font_color, 3, main_color);
		break;
		case 3: ILI9341_Draw_Text(" ", text_x, text_y+24, font_color, 3, main_color);
				ILI9341_Draw_Text(" ", text_x, text_y+48, font_color, 3, main_color);
				ILI9341_Draw_Text(">", text_x, text_y+96, font_color, 3, main_color);

		break;
	}
}

void change_color(uint8_t q) {
	switch(q) {
	case 1: main_color = Classic_GREEN; font_color = ClassicFont_GREEN; break;
	case 2: main_color = LCD1602_GREEN; font_color = LCD1602Font_GREEN; break;
	case 3: main_color = LCD1602_BLUE; font_color = LCD1602Font_BLUE; break;
	case 4: main_color = LCD1602_RED; font_color = LCD1602Font_RED; break;
	case 5: main_color = OLED_BLUE; font_color = OLEDFont_BLUE; break;
	case 6: main_color = OLED_YELLOW; font_color = OLEDFont_YELLOW; break;
	case 7: main_color = OLED_WHITE; font_color = OLEDFont_WHITE; break;
	case 8: main_color = FALLOUT; font_color = FALLOUTFont; break;
	case 9: main_color = CUSTOM_YELLOW; font_color = CUSTOM_YELLOWFont; break;
	}
}

void menu() {
	uint8_t state = 1;
	uint8_t l_r = 2;
	draw_menu(state);

	while(go_game == 0) {
		if(HAL_GetTick()-sys_t0>150) {
			sys_t0 = HAL_GetTick();
			joy_digit();
			if(((btn.up & 2) == 0) & ((btn.up & 1) == 1)) state++;
			if(((btn.down & 2) == 0) & ((btn.down & 1) == 1)) state--;
			if(state > 3) state = 3;
			if(state < 1) state = 1;
			if(((btn.right & 2) == 0) & ((btn.right & 1) == 1)) l_r--;
			if(((btn.left & 2) == 0) & ((btn.left & 1) == 1)) l_r++;
			if(l_r > 3) l_r = 3;
			if(l_r < 1) l_r = 1;

			draw_arrow(state);

			if((state == 1) & (l_r == 3)) go_game = 1;
			if((state == 2) & (l_r == 3)) go_game = 2;
			if((state == 3) & (l_r == 3)) {
				l_r = 2;
				color_pack++;
				if(color_pack > 9) color_pack = 1;
				change_color(color_pack);
				draw_menu(state);
			}
			if((state == 3) & (l_r == 1)) {
				l_r = 2;
				color_pack--;
				if(color_pack < 1) color_pack = 9;
				change_color(color_pack);
				draw_menu(state);
			}
		}
	}
}

void start_game() {
	new_snake(6, 7);
	draw_snake();
	HAL_Delay(500);
	add_food(food);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC3_Init();
  MX_SPI1_Init();
  MX_USART3_UART_Init();
  MX_RNG_Init();
  /* USER CODE BEGIN 2 */

  lcd_init(); //ILI9341_Init();
    //ILI9341_Set_Rotation(SCREEN_VERTICAL_2);

  //  while(1) {
  //	  lcd_clear_screen(BLUE);
  //	  lcd_fill_rect(10, 10, 2, 2, RED);
  //	  HAL_Delay(300);
  //	  lcd_fill_rect(50, 10, 3, 3, RED);
  //	  HAL_Delay(300);
  //	  lcd_fill_rect(10, 100, 4, 4, RED);
  //	  HAL_Delay(300);
  //	  lcd_fill_rect(50, 100, 5, 5, RED);
  //	  HAL_Delay(300);
  //
  //  }

    menu();
    draw_interface(go_game);
    start_game();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // Read Joy and set direction
	  	  if(HAL_GetTick()-sys_t0>100) {
	  		  sys_t0 = HAL_GetTick();
	  		  joy_direction();
	  	  }
	  	  // Move snake
	  	  if(HAL_GetTick()-sys_t1>speed) {
	  		  sys_t1 = HAL_GetTick();
	  		  move_snake();
	  		  check_contact();
	  		  snake_to_field();
	  		  draw_snake();
	  		  move_dir_old = move_dir;
	  	  }
	  	  // Add turtle
	  	  if(HAL_GetTick()-sys_t2>10000) {
	  		  sys_t2 = HAL_GetTick();
	  		  if(turtle_exist == 0) {
	  			  add_food(turtle);
	  			  turtle_exist = 1;
	  		  }
	  	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};
  ADC_InjectionConfTypeDef sConfigInjected = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV6;
  hadc3.Init.Resolution = ADC_RESOLUTION_8B;
  hadc3.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = ENABLE;
  hadc3.Init.NbrOfDiscConversion = 1;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 2;
  hadc3.Init.DMAContinuousRequests = DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configures for the selected ADC injected channel its corresponding rank in the sequencer and its sample time
  */
  sConfigInjected.InjectedChannel = ADC_CHANNEL_5;
  sConfigInjected.InjectedRank = ADC_INJECTED_RANK_1;
  sConfigInjected.InjectedNbrOfConversion = 2;
  sConfigInjected.InjectedSamplingTime = ADC_SAMPLETIME_3CYCLES;
  sConfigInjected.ExternalTrigInjecConvEdge = ADC_EXTERNALTRIGINJECCONVEDGE_NONE;
  sConfigInjected.ExternalTrigInjecConv = ADC_INJECTED_SOFTWARE_START;
  sConfigInjected.AutoInjectedConv = DISABLE;
  sConfigInjected.InjectedDiscontinuousConvMode = DISABLE;
  sConfigInjected.InjectedOffset = 0;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc3, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configures for the selected ADC injected channel its corresponding rank in the sequencer and its sample time
  */
  sConfigInjected.InjectedChannel = ADC_CHANNEL_6;
  sConfigInjected.InjectedRank = ADC_INJECTED_RANK_2;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc3, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
static void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, TFT_DC_Pin|TFT_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, TFT_CSD14_Pin|TFT_BL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Joy_PWR_GPIO_Port, Joy_PWR_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : TFT_DC_Pin TFT_CS_Pin */
  GPIO_InitStruct.Pin = TFT_DC_Pin|TFT_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : SD_CS_Pin */
  GPIO_InitStruct.Pin = SD_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SD_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : TFT_CSD14_Pin TFT_BL_Pin */
  GPIO_InitStruct.Pin = TFT_CSD14_Pin|TFT_BL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Joy_PWR_Pin */
  GPIO_InitStruct.Pin = Joy_PWR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Joy_PWR_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
