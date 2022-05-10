#include "config.h"
#include "USart.h"
#ifdef RT_USING_SERIAL
/*
*****************************************************************************
    ���ܣ����ڳ�ʼ������
    ʱ�䣺2022.02.10
    ��Ա��th
    �޸ļ�¼��
        th 2022.02.10  �޸�
*****************************************************************************
*/

#if USART0_EN == 1
	uint8_t   g_USART0_RxBuf[USART0_RX_BUF_SIZE];//���ڽ��ջ�����
	uint16_t 	g_USART0_RecPos = 0;//��ŵ�ǰ���ڽ������ݴ�ŵ�λ��
#endif 

#if USART1_EN == 1
	uint8_t   g_USART1_RxBuf[USART1_RX_BUF_SIZE];//���ڽ��ջ�����
	uint16_t 	g_USART1_RecPos = 0;//��ŵ�ǰ���ڽ������ݴ�ŵ�λ��
#endif 
//----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void UsartInit(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
	
#if USART0_EN == 1

	
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
#if 0 //����FinSH��rt_hw_console_getcharʹ�ò�ѯ��ʽʵ�֣��ʴ���1�жϳ�ʼ����ע�͵�
	//����1�жϳ�ʼ��	
    /* Enable USART0 RX and Receive timeout irq */
	NVIC_EnableIRQ(USART0_IRQn);
    USART_ITConfig(USART0, USART_IT_RXIEN, ENABLE);
    USART_RXTOCountConfig(USART0, 20);
    USART_ITConfig(USART0, USART_IT_RXTOEN, ENABLE);
    USART_Cmd(USART0, ENABLE);
#endif

#endif

#if USART1_EN == 1
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





void UsartSendByte(USART_TypeDef* USARTx,uint8_t ch)
{
	
	USART_SendData(USARTx, (uint8_t)ch);
	
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXFE)== RESET);
}


void UsartSendString(USART_TypeDef* USARTx,uint8_t *str)
{
	uint32_t pos = 0;
	while(*(str+pos)!='\0')
	{
		UsartSendByte(USARTx,*(str+pos));
		pos ++;
		
	}

}

/*
 * ��������itoa
 * ����  ������������ת�����ַ���
 * ����  ��-radix =10 ��ʾ10���ƣ��������Ϊ0
 *         -value Ҫת����������
 *         -buf ת������ַ���
 *         -radix = 10
 * ���  ����
 * ����  ����
 * ����  ����USART2_printf()����
 */
static char * itoa( int value, char *string, int radix )
{
	int     i, d;
	int     flag = 0;
	char    *ptr = string;

	/* This implementation only works for decimal numbers. */
	if (radix != 10)
	{
		*ptr = 0;
		return string;
	}

	if (!value)
	{
		*ptr++ = 0x30;
		*ptr = 0;
		return string;
	}

	/* if this is a negative value insert the minus sign. */
	if (value < 0)
	{
		*ptr++ = '-';

		/* Make the value positive. */
		value *= -1;
		
	}

	for (i = 10000; i > 0; i /= 10)
	{
		d = value / i;

		if (d || flag)
		{
			*ptr++ = (char)(d + 0x30);
			value -= (d * i);
			flag = 1;
		}
	}

	/* Null terminate the string. */
	*ptr = 0;

	return string;

} /* NCL_Itoa */



/*
 * ��������USART_printf
 * ����  ����ʽ�������������C���е�printf��������û���õ�C��
 * ����  ��-USARTx ����ͨ����
 *		     -Data   Ҫ���͵����ڵ����ݵ�ָ��
 *			   -...    ��������
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ����
 *         ����Ӧ��USART1_printf( USART1, "\r\n this is a demo \r\n" );
 *            		 USART1_printf( USART1, "\r\n %d \r\n", i );
 *            		 USART1_printf( USART1, "\r\n %s \r\n", j );
 */
void USART_printf ( USART_TypeDef * USARTx, char * Data, ... )
{
	const char *s;
	int d;   
	char buf[16];

	
	va_list ap;
	va_start(ap, Data);

	while ( * Data != 0 )     // �ж��Ƿ񵽴��ַ���������
	{				                          
		if ( * Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //�س���
				USART_SendData(USARTx, 0x0d);
				Data ++;
				break;

				case 'n':							          //���з�
				USART_SendData(USARTx, 0x0a);	
				Data ++;
				break;

				default:
				Data ++;
				break;
			}			 
		}
		
		else if ( * Data == '%')
		{									  //
			switch ( *++Data )
			{				
				case 's':										  //�ַ���
				s = va_arg(ap, const char *);
				
				for ( ; *s; s++) 
				{
					USART_SendData(USARTx,*s);
					while( USART_GetFlagStatus(USARTx, USART_FLAG_TXFE) == RESET );
				}
				
				Data++;
				
				break;

				case 'd':			
					//ʮ����
				d = va_arg(ap, int);
				
				itoa(d, buf, 10);
				
				for (s = buf; *s; s++) 
				{
					USART_SendData(USARTx,*s);
					while( USART_GetFlagStatus(USARTx, USART_FLAG_TXFE) == RESET );
				}
				
				Data++;
				
				break;
				
				default:
				Data++;
				
				break;
				
			}		 
		}
		
		else USART_SendData(USARTx, *Data++);
		
		while ( USART_GetFlagStatus ( USARTx, USART_FLAG_TXFE ) == RESET );
		
	}
}



void USART0_IRQHandler(void)
{
    int ch = -1;
//    rt_base_t level;
    /* enter interrupt */
    rt_interrupt_enter();          //���ж�֮ǰһ��Ҫ���ô˺����������ж�

    if ((USART_GetITStatus(USART0, USART_IT_RXIS) == SET) || (USART_GetITStatus(USART0, USART_IT_RXTOIS) == SET))
    {
        USART_ClearITPendingBit(USART0, USART_IT_RXIS);
        USART_ClearITPendingBit(USART0, USART_IT_RXTOIS);

        while(USART_GetFlagStatus(USART0, USART_FLAG_RXFE) == RESET)
        {
            /* Receive data from PC */
            ch = (uint8_t)USART_ReceiveData(USART0);
            USART_SendData(USART1, ch);
            /* ��ȡ������,�����ݴ��� ringbuffer */
        }
    }

    /* leave interrupt */
    rt_interrupt_leave();    //���ж���һ��Ҫ���ô˺������뿪�ж�
}

#if 0	//�жϺ�����ESP8266������
//USART1_IRQHandler,����1�жϻص�����
void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();          //���ж�֮ǰһ��Ҫ���ô˺����������ж�
	#if USART1_EN == 1 
		//�û�����
	 uint8_t RecCh;
	#endif
	if ((USART_GetITStatus(USART1, USART_IT_RXIS) == SET) || (USART_GetITStatus(USART1, USART_IT_RXTOIS) == SET))				// ���ڽ������� 
	{		
		USART_ClearITPendingBit(USART1, USART_IT_RXIS);
        USART_ClearITPendingBit(USART1, USART_IT_RXTOIS);
		#if USART1_EN == 1 
					 //�û�����
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
    rt_interrupt_leave();    //���ж���һ��Ҫ���ô˺������뿪�ж�
}

#endif

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
		while (USART_GetFlagStatus(USART0, USART_FLAG_TXFE) == RESET);//����Ҫ��
		USART_SendData(USART0, *(str + i));
    }	
	rt_exit_critical();	
}

char rt_hw_console_getchar(void)//ʹ��Finsh��������裺1.ʵ�ָú�����rt_hw_console_output������2.rtconfig.h�п���RT_USING_FINSH��;3.���Finsh���(cmd.c��msh.c��shell.c)��
{  //��ѯ��ʽʵ�֣��ǵý�Usart1��ʼ���е��жϽ���������ش���ע�͵�
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


