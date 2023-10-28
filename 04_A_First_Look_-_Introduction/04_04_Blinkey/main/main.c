#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define LED_BUILTIN		2

void app_main(void)
{
	gpio_set_direction(LED_BUILTIN, GPIO_MODE_INPUT_OUTPUT);

	while (1)
	{
		gpio_set_level(LED_BUILTIN, !gpio_get_level(LED_BUILTIN));
		printf("Output(current/!current): %d, %d\n", gpio_get_level(LED_BUILTIN), !gpio_get_level(LED_BUILTIN));	// Correto
		printf("Output(current/~current): %d, %d\n", gpio_get_level(LED_BUILTIN), ~gpio_get_level(LED_BUILTIN));	// Errado
		printf("Output(current/1 ^ current): %d, %d\n", gpio_get_level(LED_BUILTIN), 1 ^ gpio_get_level(LED_BUILTIN));	// Correto
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}