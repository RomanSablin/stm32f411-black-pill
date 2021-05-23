/**
 *
 * @file Board.cpp
 *
 *  Created on: 13 ���. 2021 �.
 *      @author: r.sablin
 *
 * @brief Description.
 *
 */

#include "Board.h"
#include "stm32f4xx_hal.h"

CGpioOutput CBoard::mUserLed(GPIOC, GPIO_PIN_13);


extern "C"
{
void SystemClock_Config(void);

void Error_Handler()
{
	for(;;){}
}

}

CBoard::CBoard()
{
}

void CBoard::Init()
{
	HAL_Init();
	SystemClock_Config();
	SystemCoreClockUpdate();
	mUserLed.Enable();
}
