#include <stdio.h>
#include <esp_random.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void app_main(void)
{
	while (1)
	{
		uint32_t dice = esp_random() % 6 + 1;

		printf("Dice Number: %d\n", dice);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
