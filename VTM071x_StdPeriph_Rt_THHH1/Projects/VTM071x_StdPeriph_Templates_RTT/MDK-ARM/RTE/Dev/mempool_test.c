/*
*****************************************************************************
    ���ܣ��ڴ������
    ʱ�䣺2022.02.17
    ��Ա��th
    �޸ļ�¼��
        th 2022.02.17  �޸�
*****************************************************************************
*/
/*
 * �����嵥��
 * �������ᴴ��һ����̬���ڴ�ض���2����̬�̡߳�
 * һ���̻߳���ͼ���ڴ���л���ڴ�飬��һ���߳��ͷ��ڴ��
 * �ڴ��
 */
 
#include "config.h"


static rt_uint8_t *ptr[60];
static rt_uint8_t mempool[1024];
static struct rt_mempool mp;
#define THREAD_PRIORITY      25
#define THREAD_STACK_SIZE    512
#define THREAD_TIMESLICE     5
/* ָ���߳̿��ƿ��ָ�� */
static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid2 = RT_NULL;
/* �߳�1��� */
static void thread1_mp_alloc(void *parameter)
{
    int i;
    for (i = 0 ; i < 60 ; i++)
    {
        if (ptr[i] == RT_NULL)
        {
            /* ��ͼ�����ڴ��50�Σ������벻���ڴ��ʱ��
               �߳�1����ת���߳�2���� */
            ptr[i] = rt_mp_alloc(&mp, RT_WAITING_FOREVER);
            if (ptr[i] != RT_NULL)
                rt_kprintf("allocate No.%d\n", i);
        }
    }
}
/* �߳�2��ڣ��߳�2�����ȼ����߳�1�ͣ�Ӧ���߳�1�Ȼ��ִ�С�*/
static void thread2_mp_release(void *parameter)
{
    int i;
    rt_kprintf("thread2 try to release block\n");
    for (i = 0; i < 60 ; i++)
    {
        /* �ͷ����з���ɹ����ڴ�� */
        if (ptr[i] != RT_NULL)
        {
            rt_kprintf("release block %d\n", i);
            rt_mp_free(ptr[i]);
            ptr[i] = RT_NULL;
        }
    }
}
int mempool_sample(void)
{
    int i;
    for (i = 0; i < 60; i ++) ptr[i] = RT_NULL;
    /* ��ʼ���ڴ�ض��� */
    rt_mp_init(&mp, "mp1", &mempool[0], sizeof(mempool), 16);
    /* �����߳�1�������ڴ�� */
    tid1 = rt_thread_create("thread1", thread1_mp_alloc, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);
    /* �����߳�2���ͷ��ڴ��*/
    tid2 = rt_thread_create("thread2", thread2_mp_release, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY + 1, THREAD_TIMESLICE);
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);
    return 0;
}

#if USING_MEMPOOL
/* ������ msh �����б��� */
MSH_CMD_EXPORT(mempool_sample, mempool sample);

#endif


/*
�������ڳ�ʼ���ڴ�ض���ʱ����ʼ���� 1024 /(16+4) = 51 ���ڴ�顣

���߳� 1 ������ 51 ���ڴ��֮�󣬴�ʱ�ڴ���Ѿ������꣬��Ҫ�����ط��ͷŲ����ٴ����룻����ʱ���߳� 1 ��һֱ�ȴ��ķ�ʽ�������� 1 ���������޷����䣬�����߳� 1 ����

���߳� 2 ��ʼִ���ͷ��ڴ�Ĳ��������߳� 2 �ͷ�һ���ڴ���ʱ�򣬾���һ���ڴ����г����������߳� 1 �����ڴ棬����ɹ��������룬�߳� 1 �ֹ�����ѭ��һ�΢ڣ�

���߳� 2 �����ͷ�ʣ����ڴ�飬�ͷ���ϡ�


*/
