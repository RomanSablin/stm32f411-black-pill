#pragma once

#include "Gpio.h"

class CGpioOutput : public CGpio
{
public:
	enum ModeT
	{
		ModePushPull = GPIO_MODE_OUTPUT_PP,
		ModeOpenDrain = GPIO_MODE_OUTPUT_OD
	};

	CGpioOutput(CGpio &_digital_pin, ModeT _mode = ModePushPull);
	CGpioOutput(GPIO_TypeDef * _port, uint32_t _pin, ModeT _mode = ModePushPull, CGpio::PullT _pull = NoPull, CGpio::SpeedT _speed = SpeedHigh);

	void Set(bool _high);
	void SetHigh();
	void SetLow();
	void Toggle();
};
