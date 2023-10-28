#include <stdio.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define LED_BUILTIN		2

void app_main(void)
{
	char command[100] = {0};
	int index = 0;

	gpio_set_direction(LED_BUILTIN, GPIO_MODE_OUTPUT);
	gpio_set_level(LED_BUILTIN, 0);

	while (1)
	{
		char letter = (char)getchar();

		if (letter == (char)EOF)
			letter = '\0';

		if (letter != '\0' && index < (sizeof(command) - 2))
		{
			if (letter != '\n')
				printf("%c", letter);
			else
				printf("\r\n");

			if (letter != '\n')
				command[index] = letter;
			else
				command[index] = '\0';

			++index;
		}
		else if (index == (sizeof(command) - 1))
		{
			letter = '\n';
			command[index] = '\0';
		}

		if (letter == '\n')
		{
			if (strcmp(command, "ligar") == 0)
				gpio_set_level(LED_BUILTIN, 1);
			else if (strcmp(command, "desligar") == 0)
				gpio_set_level(LED_BUILTIN, 0);

			index = 0;
		}

		vTaskDelay(1);
	}
}
