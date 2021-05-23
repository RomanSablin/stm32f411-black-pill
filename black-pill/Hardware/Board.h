/**
 *
 * @file Board.h
 *
 *  Created on: 13 мар. 2021 г.
 *      @author: r.sablin
 *
 * @brief Description.
 *
 */

#pragma once

#include <stdint.h>
#include "GpioOutput.h"

class CBoard
{
public:
	static void Init();
	static CGpioOutput mUserLed;
private:
	CBoard();
};

