/*
*****************************************************************************
    功能：内存池例程
    时间：2022.02.17
    人员：th
    修改记录：
        th 2022.02.17  修改
*****************************************************************************
*/
/*
 * 程序清单：
 * 这个程序会创建一个静态的内存池对象，2个动态线程。
 * 一个线程会试图从内存池中获得内存块，另一个线程释放内存块
 * 内存块
 */
 
#include "config.h"


static rt_uint8_t *ptr[60];
static rt_uint8_t mempool[1024];
static struct rt_mempool mp;
#define THREAD_PRIORITY      25
#define THREAD_STACK_SIZE    512
#define THREAD_TIMESLICE     5
/* 指向线程控制块的指针 */
static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid2 = RT_NULL;
/* 线程1入口 */
static void thread1_mp_alloc(void *parameter)
{
    int i;
    for (i = 0 ; i < 60 ; i++)
    {
        if (ptr[i] == RT_NULL)
        {
            /* 试图申请内存块50次，当申请不到内存块时，
               线程1挂起，转至线程2运行 */
            ptr[i] = rt_mp_alloc(&mp, RT_WAITING_FOREVER);
            if (ptr[i] != RT_NULL)
                rt_kprintf("allocate No.%d\n", i);
        }
    }
}
/* 线程2入口，线程2的优先级比线程1低，应该线程1先获得执行。*/
static void thread2_mp_release(void *parameter)
{
    int i;
    rt_kprintf("thread2 try to release block\n");
    for (i = 0; i < 60 ; i++)
    {
        /* 释放所有分配成功的内存块 */
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
    /* 初始化内存池对象 */
    rt_mp_init(&mp, "mp1", &mempool[0], sizeof(mempool), 16);
    /* 创建线程1：申请内存池 */
    tid1 = rt_thread_create("thread1", thread1_mp_alloc, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);
    /* 创建线程2：释放内存池*/
    tid2 = rt_thread_create("thread2", thread2_mp_release, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY + 1, THREAD_TIMESLICE);
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);
    return 0;
}

#if USING_MEMPOOL
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(mempool_sample, mempool sample);

#endif


/*
本例程在初始化内存池对象时，初始化了 1024 /(16+4) = 51 个内存块。

①线程 1 申请了 51 个内存块之后，此时内存块已经被用完，需要其他地方释放才能再次申请；但此时，线程 1 以一直等待的方式又申请了 1 个，由于无法分配，所以线程 1 挂起；

②线程 2 开始执行释放内存的操作；当线程 2 释放一个内存块的时候，就有一个内存块空闲出来，唤醒线程 1 申请内存，申请成功后再申请，线程 1 又挂起，再循环一次②；

③线程 2 继续释放剩余的内存块，释放完毕。


*/
