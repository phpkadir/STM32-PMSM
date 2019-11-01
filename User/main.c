/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
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
#include "stm32f10x.h"
#include "gw_fifo.h"
#include "svpwm_module.h"
#include "svpwm_math.h"
#include "usart_driver.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

static __IO uint32_t TimingDelay;
int32_t wUalpha_g;
int32_t wUbeta_g;
struct svpwm_module ssvpwm;
volatile Trig_Components strig_math;
void Delay(__IO uint32_t nTime);
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
  
void delay(int32_t time){
	int i = 0;
	while(i<=time){
		i++;
	}
}
#define USE_TASK_ARCH 1
int main(void)
{	
#if USE_TASK_ARCH
	gw_event_fifo_init();

#else
	//static uint16_t i = 0;	
	
	//int16_t UAlpha;
    //int16_t UBeta;
	//int8_t a = 0;
#endif
	while (1)
	{				
#if USE_TASK_ARCH	
		gw_execute_event_task();
#else	
		strig_math = trig_functions(i);
		UAlpha = strig_math.hSin;
		UBeta = strig_math.hCos;	
		
		wUalpha_g = UAlpha * (int32_t)(8660);
		wUbeta_g = UBeta * (int32_t)(5000);
	/*	
		if((wUbeta & 0xF0000000) == 0xB0000000){
			a=0;
		}
		if((wUalpha & 0xF0000000) == 0xB0000000){
			a=0;
		}
		*/
		
		//svpwm_get_sector_2(UAlpha, UBeta);
		usart_printf("%d,",svpwm_get_sector_2(UAlpha, UBeta)); 
				

		i+=32;		
		//Delay(100);
		delay(100000);
#endif
	}
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
