/**
 *
 * @file Board.cpp
 *
 *  Created on: 13 мар. 2021 г.
 *      @author: r.sablin
 *
 * @brief Description.
 *
 */

#include "Board.h"
#include "stm32f4xx_hal.h"

#include "thread.hpp"

CGpioOutput CBoard::mUserLed(GPIOC, GPIO_PIN_13);


extern "C"
{
void SystemClock_Config(void);

void Error_Handler()
{
	for(;;){}
}

void HAL_Delay(uint32_t Delay)
{
	vTaskDelay(Delay);
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
