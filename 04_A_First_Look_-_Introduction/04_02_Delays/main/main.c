#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void app_main(void)
{
	int count = 0;

	while (1)
	{
		// No IDF 5.x, utilizar %ld ao invés de %d
		printf("Count Value: %d\n", count++);
		vTaskDelay(pdMS_TO_TICKS(250));
	}
}