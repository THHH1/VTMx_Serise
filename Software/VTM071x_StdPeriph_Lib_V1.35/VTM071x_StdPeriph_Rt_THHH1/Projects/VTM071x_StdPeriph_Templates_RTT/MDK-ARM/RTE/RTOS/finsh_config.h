/* FinSH config file */

#ifndef __MSH_CFG_H__
#define __MSH_CFG_H__

// <<< Use Configuration Wizard in Context Menu >>>
#define RT_USING_FINSH						//打开 FinSH 组件 
#define FINSH_USING_MSH						//使用 MSH 模式
#define FINSH_USING_MSH_ONLY
// <h>FinSH Configuration
// <o>the priority of finsh thread <1-30>
//  <i>the priority of finsh thread
//  <i>Default: 21
#define FINSH_THREAD_PRIORITY       21		// 请检查系统最大优先级的值，该值必须在系统支持的优先级范围之内
// <o>the stack of finsh thread <1-4096>
//  <i>the stack of finsh thread
//  <i>Default: 4096  (4096Byte)
#define FINSH_THREAD_STACK_SIZE     1024
//使用符号表，使用命令描述
#define FINSH_USING_SYMTAB
// <c1>Enable command description
//  <i>Enable command description
#define FINSH_USING_DESCRIPTION
//  </c>
// </h>

// <<< end of configuration section >>>
#endif

