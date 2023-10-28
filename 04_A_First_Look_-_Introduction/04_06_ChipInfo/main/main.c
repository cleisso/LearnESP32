#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <esp_chip_info.h>
#include <esp_system.h>

#include <esp_spi_flash.h>
#include <esp_heap_caps.h>

void app_main(void)
{
	esp_chip_info_t chipInfo;
	esp_chip_info(&chipInfo);

	uint32_t flashSize = spi_flash_get_chip_size();

	printf("Caracteristicas do %s%s%s%s%s:\n",
			(chipInfo.model == CHIP_ESP32) ? "ESP32" : "",
			(chipInfo.model == CHIP_ESP32C3) ? "ESP32C3" : "",
			(chipInfo.model == CHIP_ESP32H2) ? "ESP32H2" : "",
			(chipInfo.model == CHIP_ESP32S2) ? "ESP32S2" : "",
			(chipInfo.model == CHIP_ESP32S3) ? "ESP32S3" : ""
	);
	printf("\t- Cores: %d\n", chipInfo.cores);
	printf("\t- Features: %s%s%s%s\n",
			(chipInfo.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi" : "",
			(chipInfo.features & CHIP_FEATURE_BT) ? "/Bluetooth" : "",
			(chipInfo.features & CHIP_FEATURE_BLE) ? "/BLE" : "",
			(chipInfo.features & CHIP_FEATURE_IEEE802154) ? "/802.15.4 (Zigbee/Thread)" : ""
	);
	printf("\t- Wafer Revision: v%d.%d\n", chipInfo.full_revision/100, chipInfo.full_revision%100);
//	printf("\t- Chip Revision: v%d\n", chipInfo.revision);		// Major Revision Only
	printf("\t- Flash Size %uMB\n", flashSize/(1024*1024));
	printf("\t- Flash Type: %s\n", (chipInfo.features & CHIP_FEATURE_EMB_FLASH) ? "Embedded" : "External");
	printf("\t- PSRAM: %s\n", (chipInfo.features & CHIP_FEATURE_EMB_PSRAM) ? "Yes" : "No");
//	printf("\t- Minimum Heap Size (1): %d bytes\n", heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT));
	printf("\t- Minimum Heap Size (2): %d bytes\n", esp_get_minimum_free_heap_size());
	printf("\n");

	for (int i = 10; i >= 0; --i)
	{
		printf("Reiniciando o ESP32 em %d segundos...\n", i);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}

	esp_restart();
}
