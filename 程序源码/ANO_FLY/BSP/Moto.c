#include "moto.h"

int16_t MOTO1_PWM = 0;
int16_t MOTO2_PWM = 0;
int16_t MOTO3_PWM = 0;
int16_t MOTO4_PWM = 0;

void Moto_PwmRflash(int16_t MOTO1_PWM,int16_t MOTO2_PWM,int16_t MOTO3_PWM,int16_t MOTO4_PWM)
{		
	if(MOTO1_PWM>Moto_PwmMax)	MOTO1_PWM = Moto_PwmMax;
	if(MOTO2_PWM>Moto_PwmMax)	MOTO2_PWM = Moto_PwmMax;
	if(MOTO3_PWM>Moto_PwmMax)	MOTO3_PWM = Moto_PwmMax;
	if(MOTO4_PWM>Moto_PwmMax)	MOTO4_PWM = Moto_PwmMax;
	if(MOTO1_PWM<0)	MOTO1_PWM = 0;
	if(MOTO2_PWM<0)	MOTO2_PWM = 0;
	if(MOTO3_PWM<0)	MOTO3_PWM = 0;
	if(MOTO4_PWM<0)	MOTO4_PWM = 0;
	

	TIM2->CCR1 = MOTO1_PWM; //
	TIM2->CCR2 = MOTO2_PWM;
	TIM8->CCR1 = MOTO3_PWM; //
	TIM8->CCR2 = MOTO4_PWM;
}
static TIM_TimeBaseInitTypeDef  TIM2_TimeBaseStructure,TIM8_TimeBaseStructure;
static TIM_OCInitTypeDef TIM2_OCInitStructure,TIM8_OCInitStructure;

void Tim2_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
		TIM_DeInit(TIM2);												 //��λ��ʱ��8���мĴ���

    /* Time Base configuration */
    TIM2_TimeBaseStructure.TIM_Prescaler = 35;				 //Ԥ��Ƶ��Ϊ0,����Ƶ
    TIM2_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 //��¦��ʽΪ˳�����ģʽ��������
    TIM2_TimeBaseStructure.TIM_Period = 1000-1;					 //���ü��������������س�ֵ
    TIM2_TimeBaseStructure.TIM_ClockDivision =  0x00;				 //����ʱ�ӷָ�ֵ
    TIM2_TimeBaseStructure.TIM_RepetitionCounter = 0x0;			     //ѭ����������ֵ

    TIM_TimeBaseInit(TIM2,&TIM2_TimeBaseStructure);				     //�����ϲ�����ʼ����ʱ��ʱ�����ģ��
  
    /* Channel 1 Configuration in PWM mode */
    TIM2_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 			     //�����ʽΪPWMģʽ1
 
    TIM2_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ������Ƚ�״̬
    TIM2_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //ʹ�ܶ�ʱ���������               
    //TIM2_OCInitStructure.TIM_Pulse = 2000; 						 //��������
    TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   	 //����Ƚϼ���Ϊ��
    TIM2_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;	     //�򿪿���״̬ѡ��ر�
	
	TIM_OC1Init(TIM2,&TIM2_OCInitStructure); 		         //�����ϲ�����ʼ��TIM8��ͨ��1
	TIM_OC2Init(TIM2,&TIM2_OCInitStructure); 		         //�����ϲ�����ʼ��TIM8��ͨ��2

    TIM_Cmd(TIM2,ENABLE);							   				 //ʹ�ܶ�ʱ��8
    TIM_CtrlPWMOutputs(TIM2,ENABLE);				   				 //ʹ�ܶ�ʱ��8��PWM���	 Ƶ�� 
}

void Tim8_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
		TIM_DeInit(TIM8);												 //��λ��ʱ��8���мĴ���
    /* Time Base configuration */
    TIM8_TimeBaseStructure.TIM_Prescaler = 35;				 //Ԥ��Ƶ��Ϊ0,����Ƶ
    TIM8_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 //��¦��ʽΪ˳�����ģʽ��������
    TIM8_TimeBaseStructure.TIM_Period = 1000-1;					 //���ü��������������س�ֵ
    TIM8_TimeBaseStructure.TIM_ClockDivision =  0x00;				 //����ʱ�ӷָ�ֵ
    TIM8_TimeBaseStructure.TIM_RepetitionCounter = 0x0;			     //ѭ����������ֵ

    TIM_TimeBaseInit(TIM8,&TIM8_TimeBaseStructure);				     //�����ϲ�����ʼ����ʱ��ʱ�����ģ��

    /* Channel 1 Configuration in PWM mode */
    TIM8_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 			     //�����ʽΪPWMģʽ1
 
    TIM8_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ������Ƚ�״̬
    TIM8_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //ʹ�ܶ�ʱ���������               
   // TIM8_OCInitStructure.TIM_Pulse =2000; 						 							//��������
    TIM8_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   	 //����Ƚϼ���Ϊ��
    TIM8_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;	     //�򿪿���״̬ѡ��ر�
	
		TIM_OC1Init(TIM8,&TIM8_OCInitStructure); 		         //�����ϲ�����ʼ��TIM8��ͨ��1
		TIM_OC2Init(TIM8,&TIM8_OCInitStructure); 		         //�����ϲ�����ʼ��TIM8��ͨ��2

    TIM_Cmd(TIM8,ENABLE);							   				 //ʹ�ܶ�ʱ��8
    TIM_CtrlPWMOutputs(TIM8,ENABLE);				   	 //ʹ�ܶ�ʱ��8��PWM���	 Ƶ��
}

void Moto_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//ʹ�ܵ���õ�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); 
	
	//���õ��ʹ�õ��ùܽ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;// | GPIO_Pin_2 | GPIO_Pin_3 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	Tim2_init();
	Tim8_init();
}

