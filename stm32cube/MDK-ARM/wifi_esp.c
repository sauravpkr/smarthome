#include "main.h"
#include <stdio.h>
#include "Lcd.h"
#include"string.h"

/************************************/
unsigned char *Fetch ;
unsigned int temp=20,hum=40;
volatile unsigned char Rx_Buff[200];
volatile unsigned char Rx_Buff_Time[200];
volatile unsigned int  Rx_Count;
volatile int Count;
 extern int Rx_Flag;
 extern int f_ip;
int Loop_break_count;
int Time_Flag;
char data[3]="000";
/************************************/


extern UART_HandleTypeDef huart1;
//extern ADC_HandleTypeDef hadc1;




/************************************/
void AT_Cmd(void);
void At_Reset_Cmd(void);
void At_SetWifi_Mode(void);
void At_Connet_To_Wifi(void);
void At_Mux_Mode(void);
void At_Ap_Mode_Selection(void);
void Wifi_Loop_Send(void);
 void Wifi_Loop_on_Send(void);
  void Wifi_Loop_off_Send(void);
	void Wifi_Loop_not_Send(void);
//void At_start_Mode(void);          ////////////////-----
void cw_mode(void);             //////----------
 void cip_server(void);            /////////--------------
/*************;***********************/



/************************************/

void AT_Cmd(void)
	{

    HAL_UART_Transmit(&huart1, (uint8_t *)"AT\r\n",5,1000);
  HAL_Delay(300);
 while(!Rx_Flag)
 {
 HAL_UART_Transmit(&huart1, (uint8_t *)"AT\r\n",5,1000);
 HAL_Delay(500);
 }
  RM_LCD_Write_Str(3,0,"WI-FI Init");
 RM_LCD_Write_Str(3,1,"Connecting...");
   Rx_Flag=0;
 At_Reset_Cmd();

}
/************************************/




/************************************/
void At_Reset_Cmd(void)
	{
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+RST\r\n",9,1000);
HAL_Delay(300);
   At_SetWifi_Mode();

}
/************************************/



/************************************/
void At_SetWifi_Mode(void)
	{

 HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CWMODE=3\r\n",14,1000);
HAL_Delay(300); HAL_Delay(300);
 while(!Rx_Flag)
 {
   
    HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CWMODE=3\r\n",14,1000);
  HAL_Delay(300);
// RM_LCD_Clear();
//    RM_LCD_Write_Str(13,0,"2");
 }
//   RM_LCD_Clear();
//    RM_LCD_Write_Str(13,0,"2");
  Rx_Flag=0;
At_Connet_To_Wifi();
 

}
/************************************/





/************************************/
void At_Connet_To_Wifi(void)
	{
 HAL_UART_Transmit(&huart1,(uint8_t*)"AT+CWJAP=\"\",\"moto e5 plus 2627\"\r\n",49,1000);
HAL_Delay(300);
	HAL_Delay(300);
 while(!Rx_Flag)
{
  HAL_UART_Transmit(&huart1,(uint8_t*)"AT+CWJAP=\"moto e5 plus 2627\",\"sanat1234\"\r\n",49,1000);
  HAL_Delay(500);
//RM_LCD_Clear();
//    RM_LCD_Write_Str(13,0,"3");
 }
 
  Rx_Flag=0;
   
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIFSR\r\n",11,1000);             //get the ip address
HAL_Delay(300); HAL_Delay(300);
 /*
 while(!f_ip)
 {
 HAL_Delay(300);
 HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIFSR\r\n",11,1000); 
 
	 RM_LCD_Write_DATA(Rx_Buff_Time[4]);
 }
 HAL_Delay(1000);
 f_ip=0;
 RM_LCD_Clear();
 */
while(!Rx_Flag)
	{
  HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIFSR\r\n",11,1000);
  HAL_Delay(300);
 }
//RM_LCD_Clear();
//    RM_LCD_Write_Str(13,0,"3");
 Rx_Flag=0;
 
At_Mux_Mode();                     //////////////////////////
}

/*----------------------------------------mine start-----------------*/
/*
void At_start_Mode(void)
	{

 HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSTART="TCP","192.168.1.43",8080\r\n",14,1000);
HAL_Delay(300); HAL_Delay(300);
   while(!Rx_Flag){
   
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSTART="TCP","192.168.1.43",8080\r\n",14,1000);
  HAL_Delay(300);
RM_LCD_Clear();
    RM_LCD_Write_Str(13,0,"4");
 }
 RM_LCD_Clear();
    RM_LCD_Write_Str(13,0,"4");
    Rx_Flag=0;
At_Ap_Mode_Selection();
}
*/
/*-------------------------------------------mine end---------------*/



/************************************/



/************************************/
void At_Mux_Mode(void){

      HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPMUX=1\r\n",14,1000);
HAL_Delay(300); HAL_Delay(300);
   while(!Rx_Flag){
   
   HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPMUX=1\r\n",14,1000);
  HAL_Delay(300);
//RM_LCD_Clear();
//    RM_LCD_Write_Str(13,0,"4");
 }
// RM_LCD_Clear();
//    RM_LCD_Write_Str(13,0,"4");
    Rx_Flag=0;
//At_Ap_Mode_Selection();
 cw_mode();
}
/************************************/

/*-------------------------------*/
void cw_mode(void)
{
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CWMODE=3\r\n",14,1000);
HAL_Delay(300); HAL_Delay(300);
 
    while(!Rx_Flag){

     HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CWMODE=3\r\n",14,1000);
  HAL_Delay(300);
//RM_LCD_Clear();
//     RM_LCD_Write_Str(13,0,"5");
 }
     Rx_Flag=0;

 cip_server();
 }

 void cip_server(void)
{
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSERVER=1\r\n",17,1000);
HAL_Delay(300); HAL_Delay(300);
 
    while(!Rx_Flag){

     HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSERVER=1\r\n",17,1000);
  HAL_Delay(300);
//RM_LCD_Clear();
//     RM_LCD_Write_Str(13,0,"5");
 }
     Rx_Flag=0;
 RM_LCD_Clear();
RM_LCD_Write_Str(3,0,"Connected");
 HAL_Delay(1000);
  RM_LCD_Clear();
 }
/*-------------------------------*/
 
 
/************************************/
void At_Ap_Mode_Selection(void)
	{

 HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CWLAP\r\n",11,1000);
  HAL_Delay(300); HAL_Delay(300);

  while(!Rx_Flag){

    HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CWLAP\r\n",11,1000);
  HAL_Delay(300);
 }
    Rx_Flag=0;

   HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPMODE=0\r\n",15,1000);
HAL_Delay(300); HAL_Delay(300);
 
    while(!Rx_Flag){

     HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPMODE=0\r\n",15,1000);
  HAL_Delay(300);
RM_LCD_Clear();
     RM_LCD_Write_Str(13,0,"5");
 }
     Rx_Flag=0;
RM_LCD_Clear();
     RM_LCD_Write_Str(13,0,"5");
}
/************************************/




/************************************/
void Wifi_Init(void){

Rx_Count=0;
Rx_Flag=0;

    Loop_break_count=0;
   __HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
    AT_Cmd();


}
 
/************************************/


/************************************/
 void Rx_Time(void)
	 {
// int i,Hour,Minit,flag=0;
RM_LCD_Write_CMD(0x80);
//for(i=0;i<10;i++)
{
// if((Rx_Buff[i]==':')&&(flag==0)) //
{
	// RM_LCD_clear();                      	  
  //  flag=1;
      //if((flag==1)&&(Rx_Buff[i]!=' '))
     //RM_LCD_Write_DATA(Rx_Buff_Time[3]);
    // RM_LCD_Write_DATA(1);
	  // RM_LCD_Write_DATA(Rx_Buff_Time[4]);
    //
	RM_LCD_Write_DATA(Rx_Buff_Time[5]);
   data[0]=Rx_Buff_Time[3];
	 data[1]=Rx_Buff_Time[4];
	 data[2]=Rx_Buff_Time[5];
	
	/*
	if(strstr(data,"113"))       //load2 status
	{
	//(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2))
		Wifi_Loop_on_Send();
	// else
		//Wifi_Loop_off_Send();
	}
	*/
	
//	 data[0]=Rx_Buff_Time[6];
//	 data[1]=Rx_Buff_Time[7];
//	 data[2]=Rx_Buff_Time[8];
	
	
	
	
//       RM_LCD_Write_DATA(Rx_Buff_Time[8]);
//     RM_LCD_Write_DATA(Rx_Buff_Time[9]);
     //RM_LCD_Write_DATA(Rx_Buff_Time[10]);
}
 }
}
/************************************/
 
 
/************************************/
/*
 void Wifi_Loop(void)
	 {

   HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSTATUS\r\n",15,1000);
   // Rx_Time();
HAL_Delay(1000); HAL_Delay(1000);HAL_Delay(1000);
//HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSTART=\"TCP\",\"142.93.218.33\",80\r\n",43,1000);

HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n",43,1000);
 //Rx_Time();  
HAL_Delay(1000);HAL_Delay(1000);

    while(!Rx_Flag){

HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n",43,1000);
HAL_Delay(1000);HAL_Delay(1000);

 // RM_LCD_Clear();
      //RM_LCD_Write_Str(13,0,"5");
 }
Rx_Flag=0;



  //sprintf(Fetch,"GET /page.php?temp=99&hum=99&dev=17\r\n\r\n");
  HAL_Delay(1000);
    HAL_Delay(1000);
 Time_Flag=1;
//HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSEND=50\r\n",16,1000);
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSEND=83\r\n",16,1000);
  HAL_Delay(300);
//   while(!Rx_Flag){
// HAL_Delay(300);
// HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSEND=83\r\n",16,1000);
//
//  // RM_LCD_Clear();
//      //RM_LCD_Write_Str(13,0,"5");
// }
Rx_Flag=0;
// HAL_Delay(1000); HAL_Delay(1000); HAL_Delay(1000);
  //HAL_Delay(1000); HAL_Delay(1000); HAL_Delay(1000);
//HAL_Delay(1000); HAL_Delay(1000); HAL_Delay(1000);
HAL_Delay(1000); HAL_Delay(1000); HAL_Delay(1000);
 
// HAL_Delay(300); HAL_Delay(300);   HAL_Delay(300); HAL_Delay(300);   HAL_Delay(300); HAL_Delay(300);   HAL_Delay(300); HAL_Delay(300);
//HAL_UART_Transmit(&huart1,(uint8_t *)"GET /page.php?temp=99&hum=99&dev=17\r\n\r\n",49,1000);
HAL_UART_Transmit(&huart1,(uint8_t *)"GET /apps/thinghttp/send_request?api_key=FYK7MM0RIXBFL0H7\r\n",60,1000);
   

//    Rx_Time();
HAL_Delay(1000);
  Time_Flag=0;
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPCLOSE\r\n",15,1000);
Rx_Time();
  HAL_Delay(1000); HAL_Delay(1000); HAL_Delay(1000);

//HAL_UART_Transmit(&huart1,"AT+CIPMODE=0\r\n",15,1000);

//HAL_UART_Transmit(&huart1,"AT+CIPMODE=0\r\n",15,1000);

//HAL_UART_Transmit(&huart1,"AT+CIPMODE=0\r\n",15,1000);
 
 }
 */
/************************************/
 
 
 
 
 
 
 /************************************/
 /*
 void Wifi_Loop_Send(void)
	 {

   HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSTATUS\r\n",15,1000);

HAL_Delay(1000); HAL_Delay(1000);HAL_Delay(1000);

RM_LCD_Clear();
//RM_LCD_Write_Str(1,0,"CONNECT");                   //////////////////////////////////////


  //sprintf(Fetch,"GET /page.php?temp=99&hum=99&dev=17\r\n\r\n");
  HAL_Delay(1000);
    HAL_Delay(1000);
 Time_Flag=1;
//HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSEND=50\r\n",16,1000);
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSEND=0,10\r\n",17,1000);
//HAL_UART_Transmit(&huart1,(uint8_t *)"A0,4\r\n",15,1000);
  HAL_Delay(300);
 while(!Rx_Flag)
{
HAL_Delay(300);
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSEND=0,10\r\n",17,1000);
//RM_LCD_Clear();
//RM_LCD_Write_Str(14,0,"s");
}
Rx_Flag=0;
 

//HAL_UART_Transmit(&huart1,(uint8_t *)"GET /page.php?temp=60&hum=60&dev=9\r\n\r\n",49,1000);
HAL_UART_Transmit(&huart1,(uint8_t *)"ON\r\n",5,1000);               //smart home
//HAL_UART_Transmit(&huart1,(uint8_t *)"GET /apps/thinghttp/send_request?api_key=FYK7MM0RIXBFL0H7\r\n",60,1000);
   

//  Rx_Time();
  HAL_Delay(1000);
  Time_Flag=0;
//HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPCLOSE\r\n",15,1000);
//  Rx_Time();
  HAL_Delay(1000);
// HAL_Delay(1000); HAL_Delay(1000);
Rx_Time();
//HAL_UART_Transmit(&huart1,"AT+CIPMODE=0\r\n",15,1000);

//HAL_UART_Transmit(&huart1,"AT+CIPMODE=0\r\n",15,1000);

//HAL_UART_Transmit(&huart1,"AT+CIPMODE=0\r\n",15,1000);
 
 }
 */
 
 
 void Wifi_Loop_off_Send(void)
{

HAL_Delay(600);
Rx_Flag=0;
 //Time_Flag=1;          -----------------------------
//HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSEND=50\r\n",16,1000);
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSEND=0,10\r\n",17,600);
  HAL_Delay(300);
 while(!Rx_Flag)
{
HAL_Delay(300);
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSEND=0,10\r\n",17,600);
//RM_LCD_Clear();
//RM_LCD_Write_Str(14,0,"s");
}
Rx_Flag=0;
 
HAL_UART_Transmit(&huart1,(uint8_t *)"OFF\r\n",6,600);               //smart home

  HAL_Delay(600);
 // Time_Flag=0;
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPCLOSE\r\n",15,1000);
//  Rx_Time();
  HAL_Delay(1000);
Rx_Flag=0;

 
 }
 
 
 
 
void Wifi_Loop_on_Send(void)
{
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSTATUS\r\n",15,600);
 HAL_Delay(600);
Rx_Flag=0;	 
//HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSEND=50\r\n",16,1000);
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSEND=0,10\r\n",17,600);
//HAL_UART_Transmit(&huart1,(uint8_t *)"A0,4\r\n",15,1000);
  HAL_Delay(300);
 while(!Rx_Flag)
{
HAL_Delay(300);
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPSEND=0,10\r\n",17,600);
}
Rx_Flag=0;
//HAL_UART_Transmit(&huart1,(uint8_t *)"GET /page.php?temp=60&hum=60&dev=9\r\n\r\n",49,1000);
HAL_UART_Transmit(&huart1,(uint8_t *)"ON\r\n",6,600);               //smart home
//HAL_UART_Transmit(&huart1,(uint8_t *)"GET /apps/thinghttp/send_request?api_key=FYK7MM0RIXBFL0H7\r\n",60,1000);

  HAL_Delay(500);
 // Time_Flag=0;
HAL_UART_Transmit(&huart1,(uint8_t *)"AT+CIPCLOSE\r\n",15,1000);
//  Rx_Time();
HAL_Delay(500);
Rx_Flag=0;

}
 
 

 
 
 /************************************/
void Usart_Recv_Task( unsigned char Temp){

//if(Temp=='\n'){
//}
     Rx_Buff[Rx_Count++]=Temp;
  if(Rx_Count>199)
         Rx_Count=0;  

}
/************************************/

void Usart_Recv_Timecheck(void)
	{
int i;
for(i=0;i<200;i++){
if((Rx_Buff[i]=='+')&&(Rx_Buff[i+1]=='I')&&(Rx_Buff[i+2]=='P')&&(Rx_Buff[i+3]=='D')){

i=i+3;

}
}

}



int temp1;
char *Temp_Value;
/*
void Lm35_Loop(void)
	{
  HAL_ADC_Start(&hadc1);
 HAL_ADC_PollForConversion(&hadc1,10);
temp1=HAL_ADC_GetValue(&hadc1);
//temp1=(temp1*350.00);
//temp1=(temp1/4096);
temp1=(temp1/12);
sprintf(Temp_Value, "%d", temp1);
RM_LCD_Goto(2,1);
RM_LCD_PutStr("TEMP: ");
RM_LCD_PutStr(Temp_Value);
RM_LCD_Put_Char('C');
HAL_Delay(300);
HAL_Delay(1000);
}

*/

