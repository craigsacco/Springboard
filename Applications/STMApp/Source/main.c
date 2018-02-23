#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "FreeRTOS.h"
#include "task.h"

static portTASK_FUNCTION(taskTest, pvParameters)
{
    (void) pvParameters;

    uint8_t i = 0;

    while (1)
    {
        switch (i)
        {
        case 0:
            GPIOI->BSRRH = GPIO_Pin_10;
            GPIOH->BSRRL = GPIO_Pin_2;
            i++;
            break;
        case 1:
            GPIOH->BSRRH = GPIO_Pin_2;
            GPIOH->BSRRL = GPIO_Pin_3;
            i++;
            break;
        case 2:
            GPIOH->BSRRH = GPIO_Pin_3;
            GPIOI->BSRRL = GPIO_Pin_8;
            i++;
            break;
        case 3:
            GPIOI->BSRRH = GPIO_Pin_8;
            GPIOI->BSRRL = GPIO_Pin_10;
            i = 0;
            break;
        }

        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}

int main(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);

    // configure PH2 and PH3 as outputs
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOH, &GPIO_InitStructure);

    // configure PI8 and PI10 as outputs
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOI, &GPIO_InitStructure);

    // create new task
    xTaskCreate(taskTest, "TaskTest", configMINIMAL_STACK_SIZE,
                NULL, tskIDLE_PRIORITY + 1UL,
                (TaskHandle_t*)NULL);

    vTaskStartScheduler();

    // should never get here
	for( ;; );
	return 0;
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

void vApplicationTickHook( void )
{
}

void vApplicationIdleHook( void )
{
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	taskDISABLE_INTERRUPTS();
	for( ;; );
}

void vApplicationMallocFailedHook( void )
{
	taskDISABLE_INTERRUPTS();
	for( ;; );
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
