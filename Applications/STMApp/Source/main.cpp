#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

#include <Springboard/InternalHAL/GPIOPort.hpp>
#include <Springboard/InternalHAL/DigitalOutput.hpp>

using Springboard::InternalHAL::GPIOPort;
using Springboard::InternalHAL::GPIOPortConfiguration;
using Springboard::InternalHAL::DigitalOutput;
using Springboard::InternalHAL::DigitalOutputConfiguration;

GPIOPort porth;
GPIOPort porti;

DigitalOutput led1;
DigitalOutput led2;
DigitalOutput led3;
DigitalOutput led4;

GPIOPortConfiguration porth_config {
    0, Springboard::Configuration::ConfigurationTypes::GPIOPort, GPIOH };
GPIOPortConfiguration porti_config {
    0, Springboard::Configuration::ConfigurationTypes::GPIOPort, GPIOI };

DigitalOutputConfiguration led1_config {
    0, Springboard::Configuration::ConfigurationTypes::DigitalOutput, &porth_config, 2 };
DigitalOutputConfiguration led2_config {
    0, Springboard::Configuration::ConfigurationTypes::DigitalOutput, &porth_config, 3 };
DigitalOutputConfiguration led3_config {
    0, Springboard::Configuration::ConfigurationTypes::DigitalOutput, &porti_config, 8 };
DigitalOutputConfiguration led4_config {
    0, Springboard::Configuration::ConfigurationTypes::DigitalOutput, &porti_config, 10 };

static portTASK_FUNCTION(taskTest, pvParameters)
{
    (void) pvParameters;

    uint8_t i = 0;

    while (1)
    {
        switch (i)
        {
        case 0:
            led4.Clear();
            led1.Set();
            i++;
            break;
        case 1:
            led1.Clear();
            led2.Set();
            i++;
            break;
        case 2:
            led2.Clear();
            led3.Set();
            i++;
            break;
        case 3:
            led3.Clear();
            led4.Set();
            i = 0;
            break;
        }

        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}

void* operator new(size_t size) noexcept
{
    return pvPortMalloc(size);
}

void operator delete(void *p) noexcept
{
    vPortFree(p);
}

void operator delete(void *p, size_t size) noexcept
{
    vPortFree(p);
}

int main(void)
{
    porth.Configure(&porth_config);
    porti.Configure(&porti_config);

    led1.Configure(&led1_config);
    led2.Configure(&led2_config);
    led3.Configure(&led3_config);
    led4.Configure(&led4_config);

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

extern "C" {

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

}

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
