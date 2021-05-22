/**
 * @file CUart.cpp
 *
 * @date: 27 џэт. 2021 у.
 * @author: r.sablin
 */

#include <Uart.h>

static const IRQn_Type g_UartIRQn[3] = {USART1_IRQn, USART2_IRQn, USART6_IRQn};
static CUart * g_UartObj[3] = {nullptr};
static uint32_t g_ClockRefs[3] = { 0, };

CUart::CUart(USART_TypeDef * _uart, int _baudrate)
	: m_Handler(nullptr)
	, m_IsDmaComplete(true)
//	, m_Dma(CDMA_USART1_TX_stream7)
	, mRxCallback(nullptr)
{
	int idx = GetIndex(_uart);
	g_UartObj[idx] = this;
	m_Huart.Instance = _uart;
	m_Huart.Init.BaudRate = _baudrate;
}

void CUart::SetIrqHandler(CHandler * _handler)
{
	m_Handler = _handler;
}

void CUart::SetBaudrate(const uint32_t _baudrate)
{
	m_Huart.Init.BaudRate = _baudrate;
}

void CUart::EnableClock()
{
	uint32_t idx = GetIndex(m_Huart.Instance);
	if (idx >= sizeof(g_ClockRefs) / sizeof(uint32_t))
		return;

	if (g_ClockRefs[idx] == 0)
	{
		switch (idx)
		{
		case 0:
			__HAL_RCC_USART1_CLK_ENABLE();
			break;
		case 1:
			__HAL_RCC_USART2_CLK_ENABLE();
			break;
		case 2:
			__HAL_RCC_USART6_CLK_ENABLE();
			break;
		}
	}
	++g_ClockRefs[idx];
}

void CUart::DisableClock()
{
}

void CUart::Init()
{
	EnableClock();
	m_Huart.Init.WordLength = UART_WORDLENGTH_8B;
	m_Huart.Init.StopBits = UART_STOPBITS_1;
	m_Huart.Init.Parity = UART_PARITY_NONE;
	m_Huart.Init.Mode = UART_MODE_TX_RX;
//	m_Huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//	m_Huart.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_USART_Init(&m_Huart) != HAL_OK)
	{
		while(1){}
	}

	// for all UART DMA channel equal DMA_CHANNEL_4 (Only USART6 = DMA_CHANNEL_5)
//	m_Dma.Init(CDma::Memory2Periph, CDma::PeriphIncDisable, CDma::MemIncEnable, CDma::Byte, CDma::ModeNormal, CDma::Low, DMA_CHANNEL_4, true);
//	m_Dma.LinkTx(&m_Huart);
//	m_Dma.Enable();
	uint32_t idx = GetIndex(m_Huart.Instance);
	HAL_NVIC_SetPriority(g_UartIRQn[idx], 15, 0);
    HAL_NVIC_EnableIRQ(g_UartIRQn[idx]);
}

bool CUart::IsDmaComplete()
{
	return m_IsDmaComplete;
}

void CUart::SetDmaComplete(bool _complete)
{
	m_IsDmaComplete = _complete;
}

void CUart::Send(const uint8_t _data)
{
    m_Huart.Instance->DR = ((uint16_t)_data & (uint16_t)0x01FF);
}

void CUart::Send(const uint8_t * _data, const uint16_t _size)
{
	while(!IsDmaComplete())
	{
//		CMisc::DelayMs(1);
	}
	SetDmaComplete(false);
//	if(m_Dma.GetHandler()->Instance != CDMA_NO_DMA_channel)
	if(_size > 1)
		HAL_USART_Transmit_DMA(&m_Huart, (uint8_t *)_data, _size);
	else
		HAL_USART_Transmit_IT(&m_Huart, (uint8_t *)_data, _size);
}

int CUart::GetIndex(USART_TypeDef * _usart)
{
	if((uint32_t)USART1 == (uint32_t)_usart)
		return 0;
	else if((uint32_t)USART2 == (uint32_t)_usart)
		return 1;
	else if((uint32_t)USART6 == (uint32_t)_usart)
		return 2;

	return -1;
}

void CUart::IRQHandler(int _idx)
{
	USART_HandleTypeDef * huart;
	huart = g_UartObj[_idx]->GetUartHandler();
	HAL_USART_IRQHandler( huart );
}

void CUart::RegisterRxCallback(RxCallbackT _callback)
{
	mRxCallback = _callback;
	HAL_USART_Receive_IT(&m_Huart, mRxData, 1);
}

void CUart::IRQRxHandle()
{
	if(mRxCallback != nullptr)
	{
		mRxCallback(mRxData[0]);
		HAL_USART_Receive_IT(&m_Huart, mRxData, 1);
	}
}

extern "C"
{

void USART1_IRQHandler(void) { CUart::IRQHandler(0); }
void USART2_IRQHandler(void) { CUart::IRQHandler(1); }
void USART6_IRQHandler(void) { CUart::IRQHandler(2); }

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == NULL)
		return;

	int idx = CUart::GetIndex(huart->Instance);

	CUart * uart = g_UartObj[idx];

	if(uart != nullptr)
	{
		uart->SetDmaComplete(true);

		if(uart->GetIrqHandler() != nullptr)
			uart->GetIrqHandler()->OnTransmitComplete();
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == NULL)
		return;

	int idx = CUart::GetIndex(huart->Instance);
	g_UartObj[idx]->IRQRxHandle();
}

static uint32_t errorCount = 0;
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	++errorCount;
	uint32_t error_code = HAL_UART_GetError(huart);

	if(huart->Instance == USART2)
	{
		errorCount++;
	}
}

}
