////////所有示例仅在VTM071x LQFP64 EVK上验证，不保证在其他硬件上有相同的结果/////////

示例功能：WWDG_Reset
使用方法：1、将示例文件夹中所有源码复制到VTM071x _StdPeriph_Lib\Projects\VTM071x _StdPeriph_Templates
                文件夹下，覆盖原文件，重新编译。
                 2、使用串口线将开发板和PC相连，打开PC端的串口工具，设置为115200，8，n，1，无流控。
硬件连接：
VCC
GND
UART0(RXD)----GPIO  1_2
UART0(TXD)----GPIO  1_1
SWD----IO-----GPIO  1_6
SWD----TCK---GPIO  1_5

示例现象：当64<计数值<80时，窗口看门狗的计数值会被更新，否则将产生复位；蓝色LED200以160ms为一周期闪烁（明暗各80ms），每80ms更新一次计数器。