V0.99
	首次发布版本
V0.99A
	所有例程使用内部IRC，去除部分函数。
V0.99B
	修正一个使用多个端点是出错的问题。
V0.99C
	增加挂起和唤醒以及远程唤醒的支持，如果接口在PC休眠时断开电源，那么不支持远程唤醒(测试发现ASMedia USB3.1仍然支持)
	兼容性修复--支持ASMedia USB3.0/USB3.1, NEC USB3.0
V0.99D
	支持USB3.0 HUB
V0.99E
	基础库更新到V1.1
V0.99F
	地址设置更符合协议，增强兼容性
V0.99G
	修复VCP例程对于特殊传输长度的错误
	修改VCP_DataTx函数
V1.00
	修复CDC_HID_Composite




1、HID：
	现象--鼠标不停的左右抖动，每ms上报一次
	PS--如果要求1秒钟1000个包全部上报成功，必须使用外部晶振
	
2、Custom HID：
	现象--每次上报64个字节
	
3、MSC：
	现象--生成一个8MB大小的U盘
	PS--开发板上可能不是8MB大小的SPI FLASH
	
4、Virtual_COM_Port:
	现象--PC产生一个串口
	PS--需要手动安装驱动MIC_CDC_Driver.inf
	
5、CDC_HID_Composite
	现象--综合了Custom HID和Virtual_COM_Port
	PS--需要手动安装驱动MIC_HID_CDC_Driver.inf 
	
	
	