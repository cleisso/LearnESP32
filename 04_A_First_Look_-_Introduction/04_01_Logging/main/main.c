#include <stdio.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define TAG1	"TAG1"
#define TAG2	"TAG2"

void app_main(void)
{
	esp_log_level_set(TAG1, ESP_LOG_INFO);
	ESP_LOGE(TAG1, "Mensagem de Error da %s", TAG1);
	ESP_LOGW(TAG1, "Mensagem de Warning da %s", TAG1);
	ESP_LOGI(TAG1, "Mensagem de Info da %s\n", TAG1);
	ESP_LOGD(TAG1, "Mensagem de Debug da %s", TAG1);
	ESP_LOGV(TAG1, "Mensagem de Verbose da %s", TAG1);

	esp_log_level_set(TAG2, ESP_LOG_VERBOSE);
	ESP_LOGE(TAG2, "Mensagem de Error da %s", TAG2);
	ESP_LOGW(TAG2, "Mensagem de Warning da %s", TAG2);
	ESP_LOGI(TAG2, "Mensagem de Info da %s", TAG2);
	ESP_LOGD(TAG2, "Mensagem de Debug da %s", TAG2);
	ESP_LOGV(TAG2, "Mensagem de Verbose da %s", TAG2);
	
	while (1)
	{
		vTaskDelay(pdMS_TO_TICKS(portMAX_DELAY));
	}
}