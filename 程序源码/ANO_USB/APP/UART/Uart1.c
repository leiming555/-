#include "uart1.h"
#include "app/rc/rc.h"

void Uart_DataAnl(u8 buf_num)		//���ڻ������ݷ���
{
	if(Rx_Buf[buf_num][0]==0x8A)		//�����յ�������λ�������ɻ�������ADC1,ֱ��ת��
	{
		NRF_SendData_AP(Rx_Buf[buf_num]);
	}
}
void Uart_CheckEvent(void)
{
	if(Rx_Ok0)
	{
		Rx_Ok0 = 0;
		u8 sum = 0;
		for(int i=0;i<31;i++)
			sum += Rx_Buf[0][i];
		if(sum == Rx_Buf[0][31])		//��У��ͨ��
		{
			Uart_DataAnl(0);
		}
	}
	if(Rx_Ok1)
	{
		Rx_Ok1 = 0;
		u8 sum = 0;
		for(int i=0;i<31;i++)
			sum += Rx_Buf[1][i];
		if(sum == Rx_Buf[1][31])		//��У��ͨ��
		{
			Uart_DataAnl(1);
		}
	}
}

void Uart1_Send_Buf(u8 *buf,u8 len)		//����buf,����len,�����ֽں�sum
{
	while(len)
	{
		Uart1_Put_Char(*buf);
		buf++;
		len--;
	}
}
void Uart1_Send_RCdata(void)
{
	uint8_t sum = 0;
	sum += Uart1_Put_Char(0x88);
	sum += Uart1_Put_Char(0xAE);
	sum += Uart1_Put_Char(28);
	sum += Uart1_Put_Int16(Rc_Get.THROTTLE);
	sum += Uart1_Put_Int16(Rc_Get.YAW);
	sum += Uart1_Put_Int16(Rc_Get.ROLL);
	sum += Uart1_Put_Int16(Rc_Get.PITCH);
	sum += Uart1_Put_Int16(Rc_Get.AUX1);
	sum += Uart1_Put_Int16(Rc_Get.AUX2);
	sum += Uart1_Put_Int16(Rc_Get.AUX3);
	sum += Uart1_Put_Int16(Rc_Get.AUX4);
	sum += Uart1_Put_Int16(0);
	sum += Uart1_Put_Int16(0);
	sum += Uart1_Put_Int16(0);
	sum += Uart1_Put_Int16(0);
	sum += Uart1_Put_Int16(0);
	sum += Uart1_Put_Int16(0);
	Uart1_Put_Char(sum);
}

void PC_Debug_Show(u8 num,u16 sta)//sta=0 Ϩ�� sta=1 ����  >1 ȡ��
{
	static uint8_t led_s[6] = {0,0,0,0,0,0};
	uint8_t sum = 0;
	if(0<num && num<7)
	{
		sum += Uart1_Put_Char(0x88);
		sum += Uart1_Put_Char(0xAD);
		sum += Uart1_Put_Char(0x02);
		sum += Uart1_Put_Char(num);
		if(sta==0)
			sum += Uart1_Put_Char(0x00);
		else if(sta==1)
			sum += Uart1_Put_Char(0x01);
		else 
		{
			if(led_s[num])	led_s[num] = 0;
			else 			led_s[num] = 1;
			sum += Uart1_Put_Char(led_s[num]);
		}
		Uart1_Put_Char(sum);
	}
	else if(6<num && num<13)
	{
		sum += Uart1_Put_Char(0x88);
		sum += Uart1_Put_Char(0xAD);
		sum += Uart1_Put_Char(0x03);
		sum += Uart1_Put_Char(num);
		sum += Uart1_Put_Int16(sta);
		Uart1_Put_Char(sum);
	}
}
