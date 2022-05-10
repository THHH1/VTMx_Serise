/*
*****************************************************************************
    ���ܣ�USART
    ʱ�䣺2022.03.01
    ��Ա��th
    �޸ļ�¼��
        th 2022.03.01  �޸�
*****************************************************************************
*/

#ifndef __DRV_USART_H__
#define __DRV_USART_H__


#define RT_USING_SERIAL


#define BSP_USING_GPIO
#define BSP_USING_UART0
#define BSP_USING_UART1

#define  USART0_EN 1
#define  USART1_EN 0

#if USART0_EN == 1
	#define USART0_BAUD         115200
	#define USART0_RX_BUF_SIZE  256
#endif 

#if USART1_EN == 1
	#define USART1_BAUD         115200
	#define USART1_RX_BUF_SIZE  256
#endif 

#ifdef	BSP_USING_UART0 

	#define	UART0_RCC			RCC_AHBCLKCTRL_USART0
	/*Tx*/
	#define	UART0_TX_PIN		GPIO_Pin_1
	#define	UART0_TX_GPIO		GPIO1
	/*Tx*/
	#define	UART0_RX_PIN		GPIO_Pin_2
	#define	UART0_RX_GPIO		GPIO1
	
#endif	


#ifdef	BSP_USING_UART1 

	#define	UART1_RCC			RCC_AHBCLKCTRL_USART1
	/*Tx*/
	#define	UART1_TX_PIN		GPIO_Pin_2
	#define	UART1_TX_GPIO		GPIO0
	/*Tx*/
	#define	UART1_RX_PIN		GPIO_Pin_3
	#define	UART1_RX_GPIO		GPIO0
	
#endif	

#if USART0_EN == 1
	extern uint8_t   	g_USART0_RxBuf[USART0_RX_BUF_SIZE];//���ڽ��ջ�����
	extern uint16_t 	g_USART0_RecPos;//��ŵ�ǰ���ڽ������ݴ�ŵ�λ��
#endif 

#if USART1_EN == 1
	extern uint8_t   	g_USART1_RxBuf[USART1_RX_BUF_SIZE];//���ڽ��ջ�����
	extern uint16_t 	g_USART1_RecPos;//��ŵ�ǰ���ڽ������ݴ�ŵ�λ��
#endif 


//void UsartSendString(USART_TypeDef* USARTx,uint8 *str);//�����ַ���
//unsigned char Usart0_RecProcess(void);//����1������
//unsigned char Usart1_RecProcess(void);


void  UsartInit(void);
void UsartSendString(USART_TypeDef* USARTx,uint8 *str);//�����ַ���
void UsartSendByte(USART_TypeDef* USARTx,uint8 ch);
void USART_printf ( USART_TypeDef * USARTx, char * Data, ... );
#endif  /* __DRV_USART_H__ */



