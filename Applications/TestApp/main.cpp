#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

#include "Springboard/Devices/DeviceConfig.hpp"
#include "Springboard/Drivers/GPIO/GPIODriverConfig.hpp"
#include "Springboard/Drivers/GPIO/InternalGPIODriverConfig.hpp"
#include "Springboard/Devices/DeviceBootstrapper.hpp"
#include <array>

static portTASK_FUNCTION(taskTest, pvParameters)
{
    while (1) {
        GPIO_ToggleBits(GPIOH, GPIO_Pin_2);
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}

void* operator new(size_t size)
{
    return pvPortMalloc(size);
}

void operator delete(void *p)
{
    vPortFree(p);
}

void operator delete(void *p, size_t size)
{
    vPortFree(p);
}

int main(void)
{
    enum ProjectDeviceIds : Springboard::DeviceId_t {
        PortHDevice = 1,
    };

    static Springboard::Drivers::GPIO::InternalGPIODriverConfig_t portHDriverSpecificConfig {
        Springboard::Drivers::GPIO::InternalGPIODriverConfig_t::Port_t::H,
    };
    static Springboard::Drivers::GPIO::GPIODriverConfig_t portHDriverConfig {
        Springboard::Drivers::GPIO::GPIODriverConfig_t::Type_t::InternalGPIO,
        &portHDriverSpecificConfig,
    };
    static std::array<Springboard::Devices::DeviceConfig_t, 1> deviceConfigs {
        { ProjectDeviceIds::PortHDevice, Springboard::DeviceType_t::GPIO,
          "PortHDevice", &portHDriverConfig },
    };

    Springboard::Devices::DeviceBootstrapper deviceBootstrapper;
    deviceBootstrapper.GetDeviceRegistry().CreateDevices(deviceConfigs.data(), deviceConfigs.size());

    // Springboard::Drivers::GPIO::InternalGPIODriver portH;
    // portH.Configure(&portHDriverConfig);

    // GPIO_InitTypeDef led1;
    // led1.GPIO_Pin = GPIO_Pin_2;
    // led1.GPIO_Mode = GPIO_Mode_OUT;
    // led1.GPIO_OType = GPIO_OType_PP;
    // led1.GPIO_PuPd = GPIO_PuPd_NOPULL;
    // led1.GPIO_Speed = GPIO_Speed_2MHz;
    // GPIO_Init(portH.GetGPIO(), &led1);
    
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
