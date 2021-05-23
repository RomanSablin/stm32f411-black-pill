/**
 *
 * @file Board.h
 *
 *  Created on: 13 ���. 2021 �.
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

