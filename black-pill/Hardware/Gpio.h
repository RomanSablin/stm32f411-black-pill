#pragma once

#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_gpio.h>

class CGpio
{
public:
	enum SpeedT
	{
		SpeedLow    = GPIO_SPEED_FREQ_LOW,
		SpeedMedium = GPIO_SPEED_FREQ_MEDIUM,
		SpeedHigh   = GPIO_SPEED_FREQ_HIGH,
		SpeedVeryHigh = GPIO_SPEED_FREQ_VERY_HIGH
	};

	enum PullT
	{
		NoPull   = GPIO_NOPULL,
		PullUp   = GPIO_PULLUP,
		PullDown = GPIO_PULLDOWN
	};

	CGpio(GPIO_TypeDef * _port, uint32_t _pin,PullT _pull = NoPull, SpeedT _speed = SpeedHigh);

	static const int PORTS_NUMBER = 9;

	void Enable();
	void Disable();
	bool IsEnabled() const;

	bool IsHigh() const;
	bool IsLow() const;

private:
	void ClockEnable();
	void ClockDisable();

protected:
	GPIO_TypeDef * m_Port;
	GPIO_InitTypeDef m_InitStructure;

private:
	bool m_Enabled;
};
