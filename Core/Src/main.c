/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
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
#include "LiquidCrystal.h"
#include "string.h"
#include <stdbool.h>
#include <time.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CHAR_PADDLE 1
#define CHAR_BALL   2
#define CHAR_HEART  3
#define BLOCK_ROWS 4
#define BLOCK_COLS 6

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc3;

I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;

PCD_HandleTypeDef hpcd_USB_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_USB_PCD_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM3_Init(void);
static void MX_ADC3_Init(void);
/* USER CODE BEGIN PFP */
typedef unsigned char byte;
RTC_TimeTypeDef nowTime;
RTC_DateTypeDef nowDate;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void off() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, RESET);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);

}

void show_0() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);

}
void show_1() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
}
void show_2() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
}
void show_3() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);

}
void show_4() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
}
void show_5() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
}
void show_6() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
}
void show_7() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
}
void show_8() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, SET);
}
void show_9() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, SET);
}
void reset() {
	off();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET);
	show_0();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET);
	show_0();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, RESET);
	show_0();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, RESET);
	show_0();
}

typedef void (*func_ptr)();
func_ptr functionArray[10] = { show_0, show_1, show_2, show_3, show_4, show_5,
		show_6, show_7, show_8, show_9 };

byte circle[] = { 0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E };
byte heart[] = { 0x0C, 0x1E, 0x1F, 0x0F, 0x1F, 0x1F, 0x1E, 0x0C };
byte square[] = { 0x00, 0x00, 0x0E, 0x0E, 0x0E, 0x0E, 0x00, 0x00 };
byte padle[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

typedef struct {
	uint16_t freq;
	uint16_t dur;
} Note;

Note game_song[] = { { 262, 300 }, // DO
		{ 294, 300 }, // RE
		{ 330, 300 }, // MI
		{ 349, 300 }, // FA
		{ 392, 300 }, // SOL
		};

uint32_t player_health = 5;
uint32_t player_Hscore = 0;
uint32_t player_score = 0;
char player_name[6];

uint32_t ball_move = 0;
int menu_key = 0;
int start = 0;
int score = 0;
int blocks[BLOCK_ROWS][BLOCK_COLS];
int elements_num = 1 ;

int paddle_x = 0;
int paddle_flag = 3;
int PADDLE_WIDTH = 1;
int change_paddle = 1 ; // 1 = keypad  2 = potensiometr

int ballX = 12;
int ballY = 2;
int ballDX = 1;
int ballDY = 1;
int ball_num = 1 ;

int menu_flag = 3;
int ok_flag = 3;
int setting_flag = 3;
int stop_flag = 3 ;
int end_flag = 3 ;
int end_key = 1 ;


char gameMap[4][20];
int menu_mode = 0;
int mode = 0;

int clear_menu = 0;

char menuItems[5][16] = { "User ", "Start", "Continue", "Settings", "About" };

struct Ball {
	int x, y;
	int dx, dy;
};

struct Ball ball;

void first_page() {
	setCursor(4, 0);
	print("Block Breaker");
	setCursor(9, 3);
	print("_");
}

void menu() {
	if (clear_menu == 1) {
		clear();
		clear_menu = 0;
	}

	int j = 0;
	for (int i = 0; i < 4; i++) {
		j++;

		if (menu_key < 4) {
			setCursor(0, i);
			print(menuItems[i]);
		} else if (menu_key == 4) {
			setCursor(0, i);
			print(menuItems[j]);

		}

	}

}
void update_menu() {
	int col = strlen(menuItems[menu_key]);
	setCursor(col + 1, menu_key);
	print(" ");

	if (menu_flag == 1) {
		menu_key++;
		menu_flag = 3;
	} else if (menu_flag == 0) {
		menu_key--;
		menu_flag = 3;
	}
	col = strlen(menuItems[menu_key]);
	setCursor(col + 1, menu_key);
	print("<");

}

void setting() {
	if (clear_menu == 1) {
		clear();
		clear_menu = 0;
	}
	char buffer[20];
	char B_buffer[30];
	char health ;
	char b_num ;
	sprintf(buffer, "health : %d", player_health);
	sprintf(B_buffer, "elements  : %d", elements_num);
	setCursor(0, 0);
	print(buffer);
	setCursor(0, 1);
	print(B_buffer);


}
void user_info() {
	if (clear_menu == 1) {
		clear();
		clear_menu = 0;
	}
	char buffer2[30];

	sprintf(buffer2, "score : %d", player_score);
	setCursor(0, 0);
	print(player_name);
	setCursor(0, 1);
	print(buffer2);

}
void get_info() {
	HAL_UART_Transmit(&huart1, "enter your name : ",
			strlen("enter your name : "), HAL_MAX_DELAY);
	HAL_UART_Receive(&huart1, &player_name, 6, HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart1, player_name, strlen(player_name), HAL_MAX_DELAY);
	clear();
	mode = 1 ;

}

void check_lose() {
	char game_over[8] = "GAMEOVER";
	if (player_health == 0) {
		mode = 0;
		int k = 0;
		for (int i = 10; i < 12; i++) {
			for (int j = 0; j < 4; j++) {
				setCursor(i, j);
				write(game_over[k]);
				k++;

			}
		}
	clear();
	mode = 4 ;
	}
	if (player_score > player_Hscore){
		player_Hscore = player_score ;
	}

}
void end(){
	char buffer[30];
	sprintf(buffer, "score : %d", player_score);
	setCursor(0, 0);
	print(buffer);
	setCursor(0, 1);
	print("restart");
	setCursor(0, 2);
	print("exit");

}
void end_menu() {
	setCursor(10, end_key);
	print(" ");

	if (end_flag == 1) {
		end_key++;
		end_flag = 3;
	} else if (end_flag == 0) {
		end_key--;
		menu_flag = 3;
	}
	setCursor(10 , end_key);
	print("<");
	if (ok_flag == 1){
		if(end_key == 1){
			mode = 2 ;
			ok_flag = 3 ;
		}
		else if (end_key == 2){
			mode = 1 ;
			ok_flag = 3 ;
		}
	}

}

void about() {
	if (clear_menu == 1) {
		clear();
		clear_menu = 0;
	}

	HAL_RTC_GetTime(&hrtc, &nowTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &nowDate, RTC_FORMAT_BIN);
	char line1[21], line2[21];
	sprintf(line1, "Time: %02d:%02d:%02d", nowTime.Hours, nowTime.Minutes,
			nowTime.Seconds);
	sprintf(line2, "Date: %02d/%02d/20%02d", nowDate.Date, nowDate.Month,
			nowDate.Year);
	setCursor(0, 0);
	print("new player");
	setCursor(0, 1);
	print(line1);
	setCursor(0, 2);
	print(line2);

}
void creat_ranom(){
	srand(HAL_GetTick());
	int r = rand() % 10;

}

void countdown(){
	setCursor(11, 1);
	print("3");
	HAL_Delay(500);
	setCursor(11, 1);
	print("2");
	HAL_Delay(500);
	setCursor(11, 1);
	print("1");
	HAL_Delay(500);
	setCursor(11, 1);
	print(" ");

}
void board_game() {
	if (clear_menu == 1) {
		clear();
		clear_menu = 0;
	}
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, SET);


	for (int i = 0; i < BLOCK_ROWS; i++) {
		for (int j = 0; j < BLOCK_COLS; j++) {
			blocks[i][j] = 1;
			setCursor(j, i);
			print("o");
		}
	}

	srand(HAL_GetTick());
	int r = rand() % 10;

	setCursor(4, 2);
	write(CHAR_HEART);
	blocks[2][4] = 3;

	setCursor(5, 2);
	write(CHAR_BALL);
	blocks[2][5] = 2;

	setCursor(3, 1);
	print("*");
	blocks[1][3] = 4;



	ballX = 14;
	ballY = 2;
	setCursor(ballX, ballY);
	write(CHAR_BALL);

	setCursor(17, paddle_x);
	write(CHAR_PADDLE);
}

void updateBall() {

	setCursor(ballX, ballY);
	print(" ");

	ballX += ballDX;
	ballY += ballDY;


	if (ballY < BLOCK_ROWS && ballX < BLOCK_COLS && blocks[ballY][ballX] > 0) {
		play_hit_sound();

		if (blocks[ballY][ballX] == 1)
			player_score++;
		else if (blocks[ballY][ballX] == 2) {
				ball_num++;
		}
		else if (blocks[ballY][ballX] == 3) {
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, SET);
			player_health++;
		}
		else if (blocks[ballY][ballX] == 4) {
				player_score--;
		}

		blocks[ballY][ballX] = 0;
		setCursor(ballX, ballY);
		print(" ");

		if (ballDX != 0)
			ballDX *= -1;
		if (ballDY != 0)
			ballDY *= -1;
	}

	else if (ballDX > 0 && ballX == 17 && ballY == paddle_x) {
		ballDX = -1;
	}

	else {
		if (ballX <= 0 || ballX >= 19)
			ballDX *= -1;

		if (ballY <= 0 || ballY >= 3)
			ballDY *= -1;
	}

	if (ballX >= 19) {
		player_health--;
		check_lose();
		ballX = 10;
		ballY = 2;
		ballDX = -1;
		ballDY = 1;

	}

	setCursor(ballX, ballY);
	write(CHAR_BALL);
}

void update_paddle() {
	if (paddle_flag != 3) {
		setCursor(17, paddle_x);
		print(" ");
	}
	if (paddle_flag == 1 && paddle_x < 4) {
		paddle_x++;
		paddle_flag = 3;
	}
	if (paddle_flag == 0 && paddle_x > 0) {
		paddle_x--;
		paddle_flag = 3;
	}
	setCursor(17, paddle_x);
	write(CHAR_PADDLE);

}

uint32_t read_pot() {
    HAL_ADC_Start(&hadc3);
    HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY);
    return HAL_ADC_GetValue(&hadc3);
}

int map_adc_to_paddle(uint32_t adc_value) {
    return (adc_value * 4) / 4096;
}

void update_potansiometr() {
    static int last_paddle_x = -1;

    uint32_t adc_val = read_pot();
    int new_paddle_x = map_adc_to_paddle(adc_val);

    if (new_paddle_x != last_paddle_x) {

        if (last_paddle_x >= 0 && last_paddle_x <= 3) {
            setCursor(17, last_paddle_x);
            print(" ");
        }


        paddle_x = new_paddle_x;
        setCursor(17, paddle_x);
        write(CHAR_PADDLE);

        last_paddle_x = new_paddle_x;
    }
}




void show_health() {
	off();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, SET);
	functionArray[player_score / 100]();
	HAL_Delay(2);

	off();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, SET);
	functionArray[(player_score % 100) / 10]();
	HAL_Delay(2);

	off();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, SET);
	functionArray[player_score % 10]();
	HAL_Delay(2);

	off();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, SET);
	functionArray[player_health]();
	HAL_Delay(2);
//		off();

}

void buzzer_play_tone(uint16_t freq, uint16_t duration_ms) {

	__HAL_TIM_SET_AUTORELOAD(&htim3, (1000000 / freq) - 1);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, (500000 / freq)); // 50% duty
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_Delay(duration_ms);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
}

int length_ckecker = 0 ;
uint32_t last_song = 0 ;
void play_song(Note *song, int length) {
	if(HAL_GetTick() - last_song > 50 ){
		buzzer_play_tone(song[length_ckecker].freq, song[length_ckecker].dur);
		length_ckecker++;
		last_song = HAL_GetTick();

	}
	if (length_ckecker == 4 ){
		length_ckecker = 0;
	}
}

void play_hit_sound() {
	buzzer_play_tone(800, 80);
	buzzer_play_tone(600, 80);
}


// Row1 PD0, Row2 PD1, Row3 PD2, Row4 PD3
GPIO_TypeDef *const Row_ports[] = { GPIOD, GPIOD, GPIOD, GPIOD };
const uint16_t Row_pins[] = { GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3 };
// Output pins: Column1 PC6, Column2 PC7, Column3 PC8, Column4 PC9
GPIO_TypeDef *const Column_ports[] = { GPIOC, GPIOC, GPIOC, GPIOC };
const uint16_t Column_pins[] =
		{ GPIO_PIN_9, GPIO_PIN_8, GPIO_PIN_7, GPIO_PIN_6 };
volatile uint32_t last_gpio_exti = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (last_gpio_exti + 200 > HAL_GetTick()) // Simple button debouncing
			{
		return;
	}
	last_gpio_exti = HAL_GetTick();

	int8_t row_number = -1;
	int8_t column_number = -1;


	for (uint8_t row = 0; row < 4; row++) // Loop through Rows
			{
		if (GPIO_Pin == Row_pins[row]) {
			row_number = row;
		}
	}
	HAL_GPIO_WritePin(Column_ports[0], Column_pins[0], 0);
	HAL_GPIO_WritePin(Column_ports[1], Column_pins[1], 0);
	HAL_GPIO_WritePin(Column_ports[2], Column_pins[2], 0);
	HAL_GPIO_WritePin(Column_ports[3], Column_pins[3], 0);

	for (uint8_t col = 0; col < 4; col++) // Loop through Columns
			{
		HAL_GPIO_WritePin(Column_ports[col], Column_pins[col], 1);
		if (HAL_GPIO_ReadPin(Row_ports[row_number], Row_pins[row_number])) {
			column_number = col;
		}
		HAL_GPIO_WritePin(Column_ports[col], Column_pins[col], 0);
	}

	HAL_GPIO_WritePin(Column_ports[0], Column_pins[0], 1);
	HAL_GPIO_WritePin(Column_ports[1], Column_pins[1], 1);
	HAL_GPIO_WritePin(Column_ports[2], Column_pins[2], 1);
	HAL_GPIO_WritePin(Column_ports[3], Column_pins[3], 1);

	if (row_number == -1 || column_number == -1) {
		return; // Reject invalid scan
	}
	const uint8_t button_number = row_number * 4 + column_number + 1;
	switch (button_number) {
	case 1:
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);

		/* code */
		break;
	case 2:
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
		if (mode == 1) {
			menu_flag = 0;
		} else if (mode == 2) {
			setting_flag = 0;
		}
		if(mode == 4){
			end_flag = 0 ;
		}

		/* code */
		break;
	case 3:

		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
//		menu_key++;
		/* code */
		break;
	case 4:

		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11);
		if (mode == 1) {
			ok_flag = 3;
		}
		clear_menu = 1;

		/* code */
		break;
	case 5:
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
		paddle_flag = 0;

		/* code */
		break;
	case 6:
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
		if (ok_flag != 1)
			ok_flag = 1;
		else if (ok_flag == 1)
			ok_flag = 2;
		if(mode == 4){
			ok_flag = 1 ;
		}
//		ok_flag = 1;
		clear_menu = 1;


		/* code */
		break;
	case 7:
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_14);
		paddle_flag = 1;

		/* code */
		break;
	case 8:


		/* code */
		break;
	case 9:
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
		if (change_paddle !=  1) change_paddle = 1 ;
		else if (change_paddle == 1) change_paddle = 2;


		/* code */
		break;
	case 10:
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
		if (mode == 1) {
			menu_flag = 1;
		} else if (mode == 2) {
			setting_flag = 1;
		}
		if (mode == 4){
			end_flag = 1 ;
		}
//		menu_flag = 1;

		/* code */
		break;

	default:
		break;
	}
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
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USB_PCD_Init();
  MX_USART1_UART_Init();
  MX_RTC_Init();
  MX_TIM3_Init();
  MX_ADC3_Init();
  /* USER CODE BEGIN 2 */

	LiquidCrystal(GPIOD, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10,
	GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14);

	HAL_Delay(50);
	begin(20, 4);
	createChar(CHAR_PADDLE, padle);
	createChar(CHAR_HEART, heart);
	createChar(CHAR_BALL, square);

	first_page();

	get_info();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
//		play_song(game_song, sizeof(game_song)/sizeof(game_song[0]));
		if (mode == 1) {
			if (ok_flag != 1) {
				menu();
				update_menu();
			} else if (ok_flag == 1) {
				switch (menu_key) {
				case 0:
					user_info();
					break;
				case 1:
					mode = 2;
					break;
				case 2:
					mode = 3;
					break;
				case 3:
					setting();
					break;
				case 4:
					about();
					break;
				default:
					break;
				}
			}
		}
		if (mode == 2) {
			board_game();
			countdown();
			mode = 3;
		}

		if (mode == 3) {
			show_health();
			play_song(game_song, sizeof(game_song)/sizeof(game_song[0]));
			if (change_paddle == 1){
			update_paddle();
			}
			else if ( change_paddle == 2){
				update_potansiometr();
			}
			if (HAL_GetTick() - ball_move > 500) {
				updateBall();
				ball_move = HAL_GetTick();
			}
		}
		if(mode == 4){
			end();
			end_menu();
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_USART1
                              |RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_RTC
                              |RCC_PERIPHCLK_ADC34;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Adc34ClockSelection = RCC_ADC34PLLCLK_DIV1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Common config
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DMAContinuousRequests = DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc3.Init.LowPowerAutoWait = DISABLE;
  hadc3.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc3, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

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
  hspi1.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
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
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 71;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USB Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_PCD_Init(void)
{

  /* USER CODE BEGIN USB_Init 0 */

  /* USER CODE END USB_Init 0 */

  /* USER CODE BEGIN USB_Init 1 */

  /* USER CODE END USB_Init 1 */
  hpcd_USB_FS.Instance = USB;
  hpcd_USB_FS.Init.dev_endpoints = 8;
  hpcd_USB_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_FS.Init.battery_charging_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Init 2 */

  /* USER CODE END USB_Init 2 */

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pins : CS_I2C_SPI_Pin LD4_Pin LD3_Pin LD5_Pin
                           LD7_Pin LD9_Pin LD10_Pin LD8_Pin
                           LD6_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : MEMS_INT3_Pin MEMS_INT4_Pin */
  GPIO_InitStruct.Pin = MEMS_INT3_Pin|MEMS_INT4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3
                           PC6 PC7 PC8 PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD8 PD9 PD10 PD11
                           PD12 PD13 PD14 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PD0 PD1 PD2 PD3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_TSC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_TSC_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

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
	while (1) {
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
