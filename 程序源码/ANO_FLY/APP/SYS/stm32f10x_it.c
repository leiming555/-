/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp/bsp.h"
#include "app/uart/uart1.h"
#include "app/rc/rc.h"
#include "app/imu/imu.h"
#include "app/control/control.h"
#include "stdio.h"//app/control/control.h"
//#include "BSP/ultrasonic.H"


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
/*=====================================================================================================*/
/*=====================================================================================================*/
void USART1_IRQHandler(void)  //�����жϺ���
{
    Uart1_IRQ();
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void I2C1_EV_IRQHandler( void )
{
    //ANO_Tech_I2C1_EV_IRQ();
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void I2C1_ER_IRQHandler( void )
{
    //ANO_Tech_I2C1_ER_IRQ();
}
/*=====================================================================================================*/
////void TIM8_IRQHandler(void)      //0.5ms�ж�һ��
////{
////}
void TIM3_IRQHandler(void)      //0.5ms�ж�һ��
{
    static u8 ms1 = 0, ms2 = 0, ms5 = 0, ms10 = 0, ms100 = 0;//,ms1000 = 0;           //�жϴ���������
    if (TIM3->SR & TIM_IT_Update)       //if ( TIM_GetITStatus(TIM3 , TIM_IT_Update) != RESET )
    {
        TIM3->SR = ~TIM_FLAG_Update;//TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);   //����жϱ�־
        TIM3_IRQCNT ++;
        //Uart1_Put_String("3\r\n");

        if (!SYS_INIT_OK)
            return;
        //ÿ���ж϶�ִ��,0.5ms
        ms1++;
        ms2++;
        ms5++;
        ms10++;
				ms100++;
        Nrf_Check_Event();
        if (ms1 == 2)           //ÿ�����ж�ִ��һ��,1ms
        {
            ms1 = 0;
            Prepare_Data();
        }
        if (ms2 == 4)           //ÿ�Ĵ��ж�ִ��һ��,2ms
        {
            ms2 = 0;
            Get_Attitude();     //��̬����
            CONTROL(Q_ANGLE.X, Q_ANGLE.Y, Q_ANGLE.Z, RC_Target_ROL, RC_Target_PIT, RC_Target_YAW);
            NRF_Send_AF();      //���ʹ���������̬����
//            if (ARMED)       LED4_ON;
//            else             LED4_OFF;
        }
        if (ms5 == 10)
        {
            ms5 = 0;                //ÿʮ���ж�ִ��һ��,5ms
        }
        if (ms10 == 20)
        {
            ms10 = 0;               //û��ʮ���ж�ִ��һ��,10ms
						//NRF_SEND_test();
				}
        if (ms100 == 70)
        {
            ms100 = 0;
            NRF_Send_AE();      //����ң���Լ����ת�ٵ�ѹ����
        }
//            if (ms1000 == 100)
//            {
//              ms1000 = 0;
//							Ultrasonic_ECHO();
//              Ultrasonic_TRIG();
//            }
    }
}

//void TIM7_IRQHandler(void)      //0.5ms�ж�һ��
//{
//    static u8 ms1 = 0, ms2 = 0, ms5 = 0, ms10 = 0, ms100 = 0;//,ms1000 = 0;//�жϴ���������
//    if (TIM7->SR & TIM_IT_Update)       
//    {
//        TIM7->SR = ~TIM_FLAG_Update;//����жϱ�־
//        TIM7_IRQCNT ++;
//        if (!SYS_INIT_OK)
//            return;
//        //ÿ���ж϶�ִ��,0.5ms
//        ms1++;
//        ms2++;
//        ms5++;
//        ms10++;
//        Nrf_Check_Event();
//				        if (ms10 == 20)
//        {
//            ms10 = 0;               //û��ʮ���ж�ִ��һ��,10ms
//            ms100 ++;
////            ms1000 ++;
//            //NRF_SEND_test();
//            if (ms100 == 10)
//            {
//                ms100 = 0;
//                NRF_Send_AE();      //����ң���Լ����ת�ٵ�ѹ����
//            }
////            if (ms1000 == 100)
////            {
////              ms1000 = 0;
////							Ultrasonic_ECHO();
////              Ultrasonic_TRIG();
////            }
//        }
//        if (ms1 == 2)           //ÿ�����ж�ִ��һ��,1ms
//        {
//            ms1 = 0;
//            Prepare_Data();// ����������
//        }
//        if (ms2 == 4)           //ÿ�Ĵ��ж�ִ��һ��,2ms
//        {
//            ms2 = 0;
//            Get_Attitude();     //��̬����
//            CONTROL(Q_ANGLE.X, Q_ANGLE.Y, Q_ANGLE.Z, RC_Target_ROL, RC_Target_PIT, RC_Target_YAW);

//            NRF_Send_AF();      //���ʹ���������̬����
//            if (ARMED)       LED4_ON;
//           else             LED4_OFF;
//        }
//        if (ms5 == 10)
//        {
//            ms5 = 0;                //ÿʮ���ж�ִ��һ��,5ms
//        }

//    }
//}

/*=====================================================================================================*/
/*=====================================================================================================*/
// void EXTI1_IRQHandler(void)
// {
//  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
//  {
//      EXTI_ClearITPendingBit(EXTI_Line1);
//  }
// }
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{

}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
