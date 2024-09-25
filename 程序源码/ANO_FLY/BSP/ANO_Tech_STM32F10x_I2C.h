#ifndef __STM32_I2C_H
#define __STM32_I2C_H
/*====================================================================================================*/
/*====================================================================================================*/

uint8_t ANO_Tech_I2C1_Write_Int(uint8_t DevAddr, uint8_t RegAddr, uint8_t WriteNum, uint8_t * WriteTemp);
								//I2Cд���ֽڣ���������1
uint8_t ANO_Tech_I2C1_Write_1Byte(uint8_t DevAddr, uint8_t RegAddr, uint8_t WriteData);
								//I2Cд���ֽڣ�д��󷵻�1
uint8_t ANO_Tech_I2C1_Write_Buf(uint8_t DevAddr, uint8_t RegAddr, uint8_t WriteNum, uint8_t * WriteTemp);
								//I2Cд���ֽڣ�д��󷵻�1
uint8_t ANO_Tech_I2C1_Read_Int(uint8_t DevAddr, uint8_t RegAddr, uint8_t ReadNum, uint8_t * ReadTemp);
								//I2C�����ֽڻ���ֽڣ���������1������ʱ��ȡ�����ܿ��ܻ�δ��ɣ�
uint8_t ANO_Tech_I2C1_Read_Buf(uint8_t DevAddr, uint8_t RegAddr, uint8_t ReadNum, uint8_t * ReadTemp);
								//I2C�����ֽڻ���ֽڣ���ȡ��ɺ󷵻�1
void ANOTech_taobao_com_I2C1_INIT(u8 ownadd, u32 speed, u8 nvic_g, u8 nvic_er_p, u8 nvic_er_s, u8 nvic_ev_p, u8 nvic_ev_s);
								//I2C1��ʼ��
void ANO_Tech_I2C1_RESET(void);
								//I2C1��λ
void ANO_Tech_I2C1_EV_IRQ( void );
								//I2C1�¼��ж�,��I2C1_EV_IRQHandler�ж��е��ñ�����
void ANO_Tech_I2C1_ER_IRQ( void );
								//I2C1�����ж�,��I2C1_ER_IRQHandler�ж��е��ñ�����
/*====================================================================================================*/
/*====================================================================================================*/
#endif
