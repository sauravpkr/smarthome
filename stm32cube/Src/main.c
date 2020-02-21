/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lcd.h"
#include<string.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
int Rx_Flag=0;

int i;
extern char x[];
extern char data[];
extern char Rx_Buff_Time[];
extern int f_ip;
int st=0;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */
void RM_LCD_Init(void);
void Wifi_Init(void);
 void Wifi_Loop_on_Send(void);
  void Wifi_Loop_off_Send(void);
	void Wifi_Loop_not_Send(void);
	void Rx_Time(void);
//void start_wifi_init_function(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
 	char str[]="WELCOME TO";
	char str1[]="SMART HOME";
	char r[4];
	st=0;
	static int a1=0x01;
	/*
	Fetch[0]='s';
	Fetch[1]='a';
	Fetch[2]='u';
	Fetch[3]='a';
	Fetch[4]='v';
	*/
i=0;
	Rx_Flag=0;
	int v;
	f_ip=0;
	
char load0[8]={0x7e,0xff,0x06,0x12,0x00,0x00,0x01,0xef};
char load1[8]={0x7e,0xff,0x06,0x12,0x00,0x00,0x02,0xef};
char party[8]={0x7e,0xff,0x06,0x12,0x00,0x00,0x03,0xef};



char sd[8]={0x7e,0xff,0x06,0x09,0x00,0x00,0x02,0xef};
char vol[8]={0x7e,0xff,0x06,0x06,0x00,0x00,0x0f,0xef};
char vol_dcr[8]={0x7e,0xff,0x06,0x05,0x00,0x00,0x00,0xef};
char vol_inr[8]={0x7e,0xff,0x06,0x04,0x00,0x00,0x00,0xef};

char play_back[8]={0x7e,0xff,0x06,0x11,0x00,0x00,a1,0xef};
char play[8]={0x7e,0xff,0x06,0x0d,0x00,0x00,0x00,0xef};
char pause[8]={0x7e,0xff,0x06,0x0e,0x00,0x00,0x00,0xef};
char stop[8]={0x7e,0xff,0x06,0x09,0x00,0x00,0x00,0xef};
char nxt[8]={0x7e,0xff,0x06,0x01,0x00,0x00,0x00,0xef};
char prv[8]={0x7e,0xff,0x06,0x02,0x00,0x00,0x00,0xef};
int mc=0;
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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART6_UART_Init();
  MX_RTC_Init();
	 RM_LCD_Init();
	 
  /* USER CODE BEGIN 2 */

HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);

HAL_UART_Transmit(&huart2,(uint8_t *)sd,8,500);               //SD card init
HAL_Delay(100);
for(v=0;v<10;v++)                                             //volume decrease
{
HAL_UART_Transmit(&huart2,(uint8_t *)vol_dcr,8,500);
HAL_Delay(50);
}

  RM_LCD_Write_Str(3,0, str);
	HAL_Delay(100);
	RM_LCD_Write_Str(3,1, str1);
  HAL_Delay(2000);
	RM_LCD_clear();
	
		__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
		//start_wifi_init_function();
		Wifi_Init();
  //HAL_UART_Receive_IT(&huart1, (uint8_t*)r,2);
	//HAL_UART_Transmit(&huart1,(uint8_t*)cmd1, sizeof(cmd), 200);
HAL_Delay(1000);
RM_LCD_Write_Str(3,0,"L1:OFF");
RM_LCD_Write_Str(10,0,"L2:OFF");
RM_LCD_Write_Str(3,1,"L3:OFF");
RM_LCD_Write_Str(10,1,"L4:OFF");
///////////////wait fot ok
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    //HAL_UART_Transmit(&huart1,(uint8_t*)c,3,20);
	HAL_Delay(500);
	Rx_Time();

		/*---------------------if data is received --------------*/
		if(strstr(data,"111"))                  //load1 on (kitchen light)
	{
	HAL_GPIO_WritePin(USER_LED_1_GPIO_Port, USER_LED_1_Pin, GPIO_PIN_RESET);
	HAL_Delay(50);	
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
//	HAL_UART_Transmit(&huart2,(uint8_t *)pause,8,500);
//	HAL_Delay(100);	
	HAL_UART_Transmit(&huart2,(uint8_t *)load1,8,500);
	HAL_Delay(500);	
		mc=0;
		RM_LCD_Write_Str(3,0,"L1:ON ");
		HAL_Delay(50);
		Rx_Buff_Time[3]=0;
		//data[0]=0;
	}
	else if(strstr(data,"112"))         //load1 off   (kitchen light)
	{
	HAL_GPIO_WritePin(USER_LED_1_GPIO_Port, USER_LED_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
//	HAL_UART_Transmit(&huart2,(uint8_t *)pause,8,500);
//	HAL_Delay(100);
	HAL_UART_Transmit(&huart2,(uint8_t *)load0,8,500);
	HAL_Delay(500);	
   mc=0;		
		RM_LCD_Write_Str(3,0,"L1:OFF");
		Rx_Buff_Time[3]=0;
		//data[0]=0;
	}
	
	else if(strstr(data,"121"))        //load2 on    (bathroom light)
	{
	HAL_GPIO_WritePin(USER_LED_2_GPIO_Port, USER_LED_2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
//	HAL_UART_Transmit(&huart2,(uint8_t *)pause,8,500);
//	HAL_Delay(100);
	HAL_UART_Transmit(&huart2,(uint8_t *)load1,8,500);
		HAL_Delay(500);	
		mc=0;
		RM_LCD_Write_Str(10,0,"L2:ON ");
		Rx_Buff_Time[3]=0;
		//data[0]=0;
	}
	else if(strstr(data,"122"))         // load2 off   (bathroom light)
	{
	HAL_GPIO_WritePin(USER_LED_2_GPIO_Port, USER_LED_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
//	HAL_UART_Transmit(&huart2,(uint8_t *)pause,8,500);
//	HAL_Delay(100);
  HAL_UART_Transmit(&huart2,(uint8_t *)load0,8,500);
		HAL_Delay(500);	
		mc=0;
		RM_LCD_Write_Str(10,0,"L2:OFF");
		Rx_Buff_Time[3]=0;
		//data[0]=0;
	}
	
	else if(strstr(data,"131"))           //load3 on  (bed room AC)
	{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
//	HAL_UART_Transmit(&huart2,(uint8_t *)pause,8,500);
//	HAL_Delay(100);
HAL_UART_Transmit(&huart2,(uint8_t *)load1,8,500);
		HAL_Delay(500);	
		mc=0;
		RM_LCD_Write_Str(3,1,"L3:ON ");
		Rx_Buff_Time[3]=0;
		//data[0]=0;
	}
	else if(strstr(data,"132"))           //load3 off   (bed room AC)
	{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
//	HAL_UART_Transmit(&huart2,(uint8_t *)pause,8,500);
//	HAL_Delay(100);	
	HAL_UART_Transmit(&huart2,(uint8_t *)load0,8,500);
		HAL_Delay(500);	
		mc=0;
		RM_LCD_Write_Str(3,1,"L3:OFF");
		Rx_Buff_Time[3]=0;
		//data[0]=0;
	}
	
	else if(strstr(data,"141"))       //load4 on   (living room light)
	{	
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
//	HAL_UART_Transmit(&huart2,(uint8_t *)pause,8,500);
//	HAL_Delay(100);
		HAL_UART_Transmit(&huart2,(uint8_t *)load1,8,500);
		HAL_Delay(500);	
		mc=0;
		RM_LCD_Write_Str(10,1,"L4:ON ");
		Rx_Buff_Time[3]=0;
		//data[0]=0;
	}
	
	else if(strstr(data,"142"))       //load4 off       (living room light)
	{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
//	HAL_UART_Transmit(&huart2,(uint8_t *)pause,8,500);
//	HAL_Delay(100);
		HAL_UART_Transmit(&huart2,(uint8_t *)load0,8,500);
		HAL_Delay(500);	
		mc=0;
		RM_LCD_Write_Str(10,1,"L4:OFF");
		Rx_Buff_Time[3]=0;
		//data[0]=0;
	}
	/*------------------status---------------*/
	
	
	else if(strstr(data,"113"))       //load1 status
	{

		{
	 if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1))
		Wifi_Loop_on_Send();
	  else
		Wifi_Loop_off_Send();
	}
	Rx_Buff_Time[3]=0;	
	//data[0]=0;	
}
		
  else if(strstr(data,"123"))       //load2 status
	{
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2))
		Wifi_Loop_on_Send();
	 else
		Wifi_Loop_off_Send();
	 Rx_Buff_Time[3]=0;
	 //data[0]=0;
	}
	else if(strstr(data,"133"))       //load3 status
	{
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3))
		Wifi_Loop_on_Send();
	 else
		Wifi_Loop_off_Send();
	 Rx_Buff_Time[3]=0;
	 //data[0]=0;
	}
	else if(strstr(data,"143"))       //load4 status
	{
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4))
		Wifi_Loop_on_Send();
	 else
		Wifi_Loop_off_Send();
	 Rx_Buff_Time[3]=0;
	 //data[0]=0;
	}
	/*------------------mp3 player---------------*/
else if(strstr(data,"151"))       //play
{	

	if(mc==0)
	{
  HAL_UART_Transmit(&huart2,(uint8_t *)play_back,8,500);
	HAL_Delay(300);
		mc=1;
	}
	else
	{
	HAL_UART_Transmit(&huart2,(uint8_t *)play,8,500);
	HAL_Delay(300);
	}	
		Rx_Buff_Time[3]=0;
}
else if(strstr(data,"152"))       //pause/stop
{	
HAL_UART_Transmit(&huart2,(uint8_t *)pause,8,500);
		HAL_Delay(300);	
		Rx_Buff_Time[3]=0;
}
else if(strstr(data,"154"))       //next
{	
	if(a1<=7)
	{
HAL_UART_Transmit(&huart2,(uint8_t *)nxt,8,500);
		HAL_Delay(300);
		if(a1<7)
			a1++;
		else
			a1=0x01;
	}
		Rx_Buff_Time[3]=0;
}
else if(strstr(data,"155"))       //previous
{	
HAL_UART_Transmit(&huart2,(uint8_t *)prv,8,500);
HAL_Delay(300);	
Rx_Buff_Time[3]=0;
}
/*------------------party mode---------------*/
else if(strstr(data,"162"))       //party mode on
{	
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);
HAL_Delay(300);	
Rx_Buff_Time[3]=0;
RM_LCD_Write_Str(3,0,"L1:OFF");
RM_LCD_Write_Str(10,0,"L2:OFF");
RM_LCD_Write_Str(3,1,"L3:OFF");
RM_LCD_Write_Str(10,1,"L4:OFF");
}
else if(strstr(data,"161"))       //previous
{	
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);
HAL_Delay(500);	
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);
HAL_Delay(500);	
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_3, GPIO_PIN_RESET);
HAL_Delay(500);	
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);
HAL_Delay(500);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_2, GPIO_PIN_RESET);
HAL_Delay(500);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_SET);	
HAL_Delay(500);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3|GPIO_PIN_2, GPIO_PIN_SET);	
HAL_Delay(500);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_2, GPIO_PIN_RESET);	
HAL_Delay(500);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_2, GPIO_PIN_SET);
HAL_Delay(500);
}

/*---------------------volume control--------------------*/
else if(!(HAL_GPIO_ReadPin(GPIOC, USER_SW2_Pin)))       //if wakeup switch is pressed
{	
for(v=0;v<5;v++)                                             //volume decrease
{
HAL_UART_Transmit(&huart2,(uint8_t *)vol_dcr,8,500);
HAL_Delay(50);		
}
}
else if(!(HAL_GPIO_ReadPin(GPIOC, USER_SW1_Pin)))       //if wakeup switch is pressed
{	
for(v=0;v<5;v++)                                             //volume increase
{
HAL_UART_Transmit(&huart2,(uint8_t *)vol_inr,8,500);
HAL_Delay(50);		
}
}
}
}

/*
void start_wifi_init_function(void)
{

HAL_Delay(4000);
//////////////////////////
HAL_UART_Transmit(&huart1,(uint8_t*)cmd1, sizeof(cmd1), 1000);
HAL_Delay(1000);
//r_flag=0;	
//////////////////wait for ready
HAL_UART_Transmit(&huart1,(uint8_t*)cmd2, sizeof(cmd2), 1000);
while(1)
{
	if(Rx_Flag==1)
		{
		if(strstr(x,"OK"))
		{
		HAL_Delay(100);
		RM_LCD_Write_Str(0,1,"1");	
		Rx_Flag=0;
		break;
		}
		}
}
///////////////wait fot ok
HAL_UART_Transmit(&huart1,(uint8_t*)cmd3, sizeof(cmd3), 1000);
while(1)
{
	if(Rx_Flag==1)
		{
		if(strstr(x,"OK"))
		{
		HAL_Delay(100);
		RM_LCD_Write_Str(0,1,"2");
			Rx_Flag=0;
break;			
		}
	}
}
///////////////wait fot ok
HAL_UART_Transmit(&huart1,(uint8_t*)cmd4, sizeof(cmd4), 1000);
while(1)
{
	if(Rx_Flag==1)
		{
		if(strstr(x,"OK"))
		{
		HAL_Delay(100);
		RM_LCD_Write_Str(0,1,"3");
			Rx_Flag=0;
break;			
		}
	}
}
///////////////wait fot ok
HAL_UART_Transmit(&huart1,(uint8_t*)cmd5, sizeof(cmd5), 1000);
while(1)
{
	if(Rx_Flag==1)
		{
		if(strstr(x,"OK"))
		{
		HAL_Delay(100);
		RM_LCD_Write_Str(0,1,"4");
			Rx_Flag=0;
break;			
		}
	}
}
///////////////wait fot ok
HAL_UART_Transmit(&huart1,(uint8_t*)cmd6, sizeof(cmd6), 1000);
while(1)
{
	if(Rx_Flag==1)
		{
		if(strstr(x,"OK"))
		{
		HAL_Delay(100);
		RM_LCD_Write_Str(0,1,"5");
			Rx_Flag=0;
break;			
		}
	}
}
///////////////wait fot ok
HAL_UART_Transmit(&huart1,(uint8_t*)cmd7, sizeof(cmd7), 1000);
while(1)
{
	if(Rx_Flag==1)
		{
		if(strstr(x,"OK"))
		{
		HAL_Delay(100);
		RM_LCD_Write_Str(0,1,"connected");
			Rx_Flag=0;
break;			
		}
	}
}
///////////////wait fot ok
}
*/

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
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
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 9600;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USER_LED_2_GPIO_Port, USER_LED_2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|Buzzer_Pin 
                          |LCD_D7_Pin|LCD_RS_Pin|LCD_RW_Pin|LCD_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USER_LED_1_GPIO_Port, USER_LED_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC1 PC2 PC3 PC4 
                           USER_LED_2_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4 
                          |USER_LED_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : WAKEUP_Pin */
  GPIO_InitStruct.Pin = WAKEUP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(WAKEUP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_D4_Pin LCD_D5_Pin LCD_D6_Pin Buzzer_Pin 
                           LCD_D7_Pin LCD_RS_Pin LCD_RW_Pin LCD_EN_Pin */
  GPIO_InitStruct.Pin = LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|Buzzer_Pin 
                          |LCD_D7_Pin|LCD_RS_Pin|LCD_RW_Pin|LCD_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : USER_SW2_Pin USER_SW1_Pin */
  GPIO_InitStruct.Pin = USER_SW2_Pin|USER_SW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : USER_LED_1_Pin */
  GPIO_InitStruct.Pin = USER_LED_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USER_LED_1_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
