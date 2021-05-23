#include <GpioOutput.h>

CGpioOutput::CGpioOutput(CGpio &_digital_pin, CGpioOutput::ModeT _mode)
	: CGpio(_digital_pin)
{
	m_InitStructure.Mode = _mode;
}

CGpioOutput::CGpioOutput(GPIO_TypeDef * _port, uint32_t _pin, CGpioOutput::ModeT _mode, CGpio::PullT _pull, CGpio::SpeedT _speed)
	: CGpio(_port, _pin, _pull, _speed)
{
	m_InitStructure.Mode = _mode;
}

void CGpioOutput::Set(bool _high)
{
	HAL_GPIO_WritePin(m_Port, m_InitStructure.Pin, _high ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void CGpioOutput::SetHigh()
{
	HAL_GPIO_WritePin(m_Port, m_InitStructure.Pin, GPIO_PIN_SET);
}

void CGpioOutput::SetLow()
{
	HAL_GPIO_WritePin(m_Port, m_InitStructure.Pin, GPIO_PIN_RESET);
}

void CGpioOutput::Toggle()
{
	HAL_GPIO_TogglePin(m_Port, m_InitStructure.Pin);
}

