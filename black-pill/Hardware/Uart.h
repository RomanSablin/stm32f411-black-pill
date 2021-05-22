/**
 * @file CUart.h
 *
 * @date: 27 џэт. 2021 у.
 * @author: r.sablin
 */

#pragma once

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_usart.h"

#include <functional>

class CUart {
public:
	class CHandler {
	public:
		virtual ~CHandler() = default;
		virtual void OnTransmitComplete() = 0;
	};
	typedef std::function<void(const uint8_t _data)> RxCallbackT;

	CUart(USART_TypeDef * _uart, int _baudrate = 9600);

	void SetIrqHandler(CHandler * _handler);
	void SetBaudrate(const uint32_t _baudrate);
	void Init();
	void Send(const uint8_t * _data, const uint16_t _size);
	void Send(const uint8_t _data);

	void RegisterRxCallback(RxCallbackT _callback);

	void EnableClock();
	void DisableClock();

	bool IsDmaComplete();
	void SetDmaComplete(bool _complete);
	void IRQRxHandle();
	static void IRQHandler(int _idx);
	USART_HandleTypeDef * GetUartHandler() {return &m_Huart;};
	CHandler * GetIrqHandler() { return m_Handler; };

	static int GetIndex(USART_TypeDef * _usart);

private:
	CHandler * m_Handler;
	USART_HandleTypeDef m_Huart;
	bool m_IsDmaComplete;
//	CDma m_Dma;
	RxCallbackT mRxCallback;
	uint8_t mRxData[1];
};
