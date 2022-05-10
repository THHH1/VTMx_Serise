#include "config.h"
#include "ChipInfo.h"


uint32_t ChipUniqueID[3];
void GetChipID(void)//��ȡCPU��ID������ÿ��оƬ����Ψһ�� 96_bit unique ID
{
	ChipUniqueID[0]=*(volatile uint32_t *)(0x1FFFF7F0);//ID�Ÿ�32λ
	ChipUniqueID[1]=*(volatile uint32_t *)(0x1FFFF7EC);
	ChipUniqueID[2]=*(volatile uint32_t *)(0x1FFFF7E8);//ID�ŵ��ֽ�
	rt_kprintf("\nChip ID is:0x%08X-%08X-%08X\n\n",ChipUniqueID[0],ChipUniqueID[1],ChipUniqueID[2]);
	
}
MSH_CMD_EXPORT(GetChipID, Get 96_bit unique Chip ID);

void GetFlashCapacity(void)
{
	rt_kprintf("\nChip Flash capacity is:%dK \n\n",*(volatile uint16_t *)(0x1FFFF7E0));
}
MSH_CMD_EXPORT(GetFlashCapacity, Get Chip Flash Capacity);

