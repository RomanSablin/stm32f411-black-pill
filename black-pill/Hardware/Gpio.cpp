#include "Gpio.h"

CGpio::CGpio(GPIO_TypeDef * _port, uint32_t _pin, PullT _pull, SpeedT _speed)
	: m_Port(_port)
	, m_Enabled(false)
{
	m_InitStructure.Pin = _pin;
	m_InitStructure.Speed = _speed;
	m_InitStructure.Pull = _pull;
}

void CGpio::Enable()
{
	ClockEnable();
	HAL_GPIO_Init(m_Port, &m_InitStructure);
	m_Enabled = true;
}

void CGpio::Disable()
{
	m_Enabled = false;
	HAL_GPIO_DeInit(m_Port, m_InitStructure.Pin);
	ClockDisable();
}

bool CGpio::IsEnabled() const
{
	return m_Enabled;
}

bool CGpio::IsHigh() const
{
	return (HAL_GPIO_ReadPin(m_Port, m_InitStructure.Pin) != GPIO_PIN_RESET);
}

bool CGpio::IsLow() const
{
	return (HAL_GPIO_ReadPin(m_Port, m_InitStructure.Pin) != GPIO_PIN_SET);
}

static int g_ClockRefs[CGpio::PORTS_NUMBER] = { 0, };

void CGpio::ClockEnable()
{
	uint32_t index = (uint32_t(m_Port) - uint32_t(GPIOA_BASE)) / (uint32_t(GPIOB_BASE)-uint32_t(GPIOA_BASE));
	if (index >= sizeof(g_ClockRefs) / sizeof(uint32_t))
		return;

	if (g_ClockRefs[index] == 0)
	{
		switch (index)
		{
		case 0:
			__HAL_RCC_GPIOA_CLK_ENABLE();
			break;
		case 1:
			__HAL_RCC_GPIOB_CLK_ENABLE();
			break;
		case 2:
			__HAL_RCC_GPIOC_CLK_ENABLE();
			break;
		case 3:
			__HAL_RCC_GPIOD_CLK_ENABLE();
			break;
		case 4:
			__HAL_RCC_GPIOE_CLK_ENABLE();
			break;
		case 5:
			__HAL_RCC_GPIOH_CLK_ENABLE();
			break;
		}
	}
	++g_ClockRefs[index];
}

void CGpio::ClockDisable()
{
	uint32_t index = (uint32_t(m_Port) - uint32_t(GPIOA_BASE)) / (uint32_t(GPIOB_BASE)-uint32_t(GPIOA_BASE));
	if (index >= sizeof(g_ClockRefs) / sizeof(uint32_t))
		return;

	if (index > 0)
	{
		--g_ClockRefs[index];
		if (g_ClockRefs[index] == 0)
		{
			switch (index)
			{
			case 0:
				__HAL_RCC_GPIOA_CLK_DISABLE();
				break;
			case 1:
				__HAL_RCC_GPIOB_CLK_DISABLE();
				break;
			case 2:
				__HAL_RCC_GPIOC_CLK_DISABLE();
				break;
			case 3:
				__HAL_RCC_GPIOD_CLK_DISABLE();
				break;
			case 4:
				__HAL_RCC_GPIOE_CLK_DISABLE();
				break;
			case 5:
				__HAL_RCC_GPIOH_CLK_DISABLE();
				break;
			}
		}
	}
}


