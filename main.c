/*
 * main.c
 *
 *     Author: RYZEN
 */

#include<avr/io.h>
#include<avr/interrupt.h>
#include "poller.h"
#include "gpio.h"
#include "TimerCompareMode.h"
#include "lcd.h"
#include "Timer1_PWM.h"
#include "device.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "common_macros.h"
#include "PollingDataClient.h"

long timeCounter = 0;
unsigned char DeviceFlag = 0;
unsigned char HandlerFlag = 0;
States_GroupType ButtonStateTest = {0,0,0,0};

void Task1_Func(void);
TaskHandle_t task1ptr;

void Task2_Func(void);
TaskHandle_t task2ptr;

void Task3_Func(void);
TaskHandle_t task3ptr;

int main(void)
{
	DIO_init();
	LCD_init();
//	timer1_PWM_Init();

	SREG |=(1<<7);			// I bit Enabled

	xTaskCreate(Task1_Func,"first",configMINIMAL_STACK_SIZE,NULL,1,&task1ptr);
	xTaskCreate(Task2_Func,"second",configMINIMAL_STACK_SIZE,NULL,1,&task2ptr);
	xTaskCreate(Task3_Func,"third",configMINIMAL_STACK_SIZE,NULL,0,&task3ptr);

//	TimerHandle_t xTimer1 = xTimerCreate("timer1",100/portTICK_PERIOD_MS,pdTRUE,0,Task1_Func);
//	TimerHandle_t xTimer2 = xTimerCreate("timer2",10/portTICK_PERIOD_MS,pdTRUE,0,Task2_Func);
//	xTimerStart(xTimer1, 1);
//	xTimerStart(xTimer2, 10);



	vTaskStartScheduler();
	//	SetPollingTime(100);
	//	Timer2_Init_CTC_Mode(50);
	while(1){

	}
}
//
//ISR(TIMER2_COMP_vect)
//{
//	Poll();
//}


void Task1_Func(void)
{
	while(1)
	{
//		SET_BIT(PORTB,5);
		DeviceFlag = 1;
		vTaskDelay(100/portTICK_PERIOD_MS);
	}

}

void Task2_Func(void)
{
	while(1)
	{
//		CLEAR_BIT(PORTB,5);
		if(DeviceFlag == 1)
		{
		DeviceFlag = 0;
		ButtonStateTest = Get_Data();
		HandlerFlag = 1;
		TOGGLE_BIT(PORTB,5);
//		if(ButtonStateTest.rightIndicator == LOGIC_HIGH)
//		{
//			SET_BIT(PORTB,6);
//		}
//		else
//		{
//			CLEAR_BIT(PORTB,6);
//		}
		//				CLEAR_BIT(PORTB,6);

		//		CLEAR_BIT(PORTB,6);
		//		vTaskDelay(pdMS_TO_TICKS( 25 ));

		}
	}
}
/*******************************Some unworking tests**************************************************************************/
void Task3_Func(void){
	//	TickType_t xLastWakeTime2;
	//	const TickType_t xPeriod2 = pdMS_TO_TICKS( 2000 );
	//	xLastWakeTime2 = xTaskGetTickCount();
	while(1)
	{
		if(HandlerFlag == 1)
		{
			HandlerFlag = 0;
			TOGGLE_BIT(PORTB,6);

//			Handle_data(&ButtonStateTest);
//			timer1_SetPWM_A(0);
//			if(ButtonStateTest.rightIndicator){
//				//				SET_BIT(PORTB,5);
//				timer1_SetPWM_B((255));
//				//				vTaskDelayUntil( &xLastWakeTime2, xPeriod2 );
//				//				timer1_SetPWM_B((0));
//			}
//			else{
//				timer1_SetPWM_B((0));
				//				CLEAR_BIT(PORTB,5);
		}
			//			Handle_data(&ButtonStateTest);
	}
}
//
//
//void Task3_Func(void){
//	while(1){
//		int i;
//		if(ButtonStateTest.ignition_key && ButtonStateTest.rightIndicator){
//			//				timer1_SetPWM_A(0);
//			for(i = 2 ; i < 17 ; i++){
//				SET_BIT(PORTB,6);
//				//					timer1_SetPWM_B((i*5));
//				vTaskDelay(pdMS_TO_TICKS( 30 ));
//			}
//			for(i = 16 ; i > 1 ; i--){
//				CLEAR_BIT(PORTB,6);
//				//					timer1_SetPWM_B((i*5));
//				vTaskDelay(pdMS_TO_TICKS( 30 ));
//			}
//		}
//
//
//	}
//}
/***********************************************************************************************************************************/
