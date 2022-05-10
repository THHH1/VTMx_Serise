#include "config.h"
#include "USart.h"
#ifdef RT_USING_SERIAL


#if USART0_EN == 1
	uint8_t   g_USART0_RxBuf[USART0_RX_BUF_SIZE];//串口接收缓冲区
	uint16_t 	g_USART0_RecPos = 0;//存放当前串口接收数据存放的位置
#endif 

#if USART1_EN == 1
	uint8_t   g_USART1_RxBuf[USART1_RX_BUF_SIZE];//串口接收缓冲区
	uint16_t 	g_USART1_RecPos = 0;//存放当前串口接收数据存放的位置
#endif 
//----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void UsartInit(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
	
#ifdef	BSP_USING_UART0

	
    RCC_APBPeriphClockCmd(UART0_RCC,ENABLE);
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, 1);

    GPIO_InitStructure.GPIO_Pin = UART0_TX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(UART0_TX_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = UART0_RX_PIN;
    GPIO_Init(UART0_RX_GPIO, &GPIO_InitStructure);

    USART_DeInit(USART0);
    USART_StructInit(&USART_InitStructure);
    USART_Init(USART0, &USART_InitStructure);
    USART_Cmd(USART0, ENABLE);	
#if 0 //由于FinSH中rt_hw_console_getchar使用查询方式实现，故串口1中断初始化需注释掉
	//串口1中断初始化	
    /* Enable USART0 RX and Receive timeout irq */
	NVIC_EnableIRQ(USART0_IRQn);
    USART_ITConfig(USART0, USART_IT_RXIEN, ENABLE);
    USART_RXTOCountConfig(USART0, 20);
    USART_ITConfig(USART0, USART_IT_RXTOEN, ENABLE);
    USART_Cmd(USART0, ENABLE);
#endif

#endif

#ifdef	BSP_USING_UART1
	NVIC_EnableIRQ(USART1_IRQn);
	
    RCC_APBPeriphClockCmd(UART1_RCC,ENABLE);
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART1CLK, 1);

    GPIO_InitStructure.GPIO_Pin = UART1_TX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(UART1_TX_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = UART0_RX_PIN;
    GPIO_Init(UART1_RX_GPIO, &GPIO_InitStructure);

    USART_DeInit(USART1);
    USART_StructInit(&USART_InitStructure);
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);	
    /* Enable USART1 RX and Receive timeout irq */
    USART_ITConfig(USART1, USART_IT_RXIEN, ENABLE);
    USART_RXTOCountConfig(USART1, 20);
    USART_ITConfig(USART1, USART_IT_RXTOEN, ENABLE);
    USART_Cmd(USART1, ENABLE);
#endif	
}


void USART0_IRQHandler(void)
{
    int ch = -1;
//    rt_base_t level;
    /* enter interrupt */
    rt_interrupt_enter();          //在中断之前一定要调用此函数，进入中断

    if ((USART_GetITStatus(USART0, USART_IT_RXIS) == SET) || (USART_GetITStatus(USART0, USART_IT_RXTOIS) == SET))
    {
        USART_ClearITPendingBit(USART0, USART_IT_RXIS);
        USART_ClearITPendingBit(USART0, USART_IT_RXTOIS);

        while(USART_GetFlagStatus(USART0, USART_FLAG_RXFE) == RESET)
        {
            /* Receive data from PC */
            ch = (uint8_t)USART_ReceiveData(USART0);
            USART_SendData(USART1, ch);
            /* 读取到数据,将数据存入 ringbuffer */
        }
    }

    /* leave interrupt */
    rt_interrupt_leave();    //在中断中一定要调用此函数，离开中断
}


//USART1_IRQHandler,串口1中断回调函数
void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();          //在中断之前一定要调用此函数，进入中断
	#if USART1_EN == 1 
		//用户代码
	 uint8_t RecCh;
	#endif
	if ((USART_GetITStatus(USART1, USART_IT_RXIS) == SET) || (USART_GetITStatus(USART1, USART_IT_RXTOIS) == SET))				// 串口接收数据 
	{		
		USART_ClearITPendingBit(USART1, USART_IT_RXIS);
        USART_ClearITPendingBit(USART1, USART_IT_RXTOIS);
		#if USART1_EN == 1 
					 //用户代码
        while(USART_GetFlagStatus(USART1, USART_FLAG_RXFE) == RESET)
        {
            /* Receive data from PC */
			RecCh = (uint8_t)USART_ReceiveData(USART1);
			g_USART1_RxBuf[g_USART1_RecPos++] = RecCh;
        }		
		rt_sem_release(usart1_recv_sem);
		
		#endif

	}
    /* leave interrupt */
    rt_interrupt_leave();    //在中断中一定要调用此函数，离开中断
}


//***************************FINSH*********************************
void rt_hw_console_output(const char *str)
{
	rt_enter_critical();
	
    rt_size_t i = 0, size = 0;
    char a = '\r';

    size = rt_strlen(str);

    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
			USART_SendData(USART0, (uint8_t) a);
        }
		while (USART_GetFlagStatus(USART0, USART_FLAG_TXFE) == RESET);//很重要！
		USART_SendData(USART0, *(str + i));
    }	
	rt_exit_critical();	
}

char rt_hw_console_getchar(void)//使用Finsh组件三步骤：1.实现该函数及rt_hw_console_output函数；2.rtconfig.h中开启RT_USING_FINSH宏;3.添加Finsh组件(cmd.c、msh.c、shell.c)，
{  //查询方式实现，记得将Usart1初始化中的中断接收配置相关代码注释掉
    int ch = -1;

    if (USART_GetFlagStatus(USART0, USART_FLAG_RXFE) == RESET)
    {
        ch = (uint8_t)USART_ReceiveData(USART0);
    }
    else
    {
        USART_ClearITPendingBit(USART0, USART_IT_RXIS);
        USART_ClearITPendingBit(USART0, USART_IT_RXTOIS);
        rt_thread_mdelay(10);
    }
    return ch;
}


#endif /* RT_USING_SERIAL */


