# Learn ESP32

## 04 - A First Look - Introduction

### Índice

- [A First Look - Introduction](#a-first-look---introduction)
- [Logging](#logging)
- [Delays](#delays)
- [Random Number](#random-number)
- [Blinkey](#blinkey)
- [Keyboard Input](#k)
- [Using Examples]()

### Glosário

### A First Look - Introduction

Introdução a alguns exemplos utilizando o ESP-IDF, como:

- Logging;
- Delays;
- Geração de Números Aleatórios;
- Blink;
- Leitura do Teclado;
- etc.

### Logging

Biblioteca: `esp_log.h`

A ferramenta de **Logging** é uma ótima forma de exibir notificações no terminal. Existem 6 níveis de log (da maior prioridade a menor prioridade):

- No Output;
- Error;
- Warning;
- Info;
- Debug;
- Verbose.

Mesmo que no programa seja explorado o 6 tipos, é possível habilitar/desabilitar quais logs serão exibidas no terminal. A configuração dos logs que serão exibidos no terminal são configurados via `Menuconfig` em `Component Config/Log Output/Default Log Verbosity`. Ao habilitar um dos tipos de Log a ser exibido no terminal, todos os outros tipos de Log cuja prioridade seja superior a escolhida serão exibidas também, e as inferiores desabilitadas. Também pode-se configurar o tipo de Log a ser exibido no terminal através da função `esp_log_level_set()`, porém, essa função apenas consegue diminuir o nível de prioridade até o nivel configurado via `menuconfig`.

Código exemplo:

``` c++
#include <stdio.h>
#include "esp_log.h"

void app_main(void)
{
  esp_log_level_set("LOG", ESP_LOG_INFO);
  ESP_LOGE("LOG", "This is an error");
  ESP_LOGW("LOG", "This is a warning");
  ESP_LOGI("LOG", "This is an info");
  ESP_LOGD("LOG", "This is a Debug");
  ESP_LOGV("LOG", "This is Verbose");

  int number = 0;
  ESP_LOGE("TAG 2", "This is an error %d", number++);
  ESP_LOGW("TAG 2", "This is a warning %d", number++);
  ESP_LOGI("TAG 2", "This is an info %d", number++);
  ESP_LOGD("TAG 2", "This is a Debug %d", number++);
  ESP_LOGV("TAG 2", "This is Verbose %d", number++);
}
```

### Delays

Bibliotecas:
- `freertos/FreeRTOS.h`
- `freertos/task.h`

A temporização pode ser feita primariamente utilizando funções proveniente das APIs do FreeRTOS, como o `vTaskDelay`. O benefício dessa abordagem é que o programa "não trava" com as chamadas de delays como em outros microcontroladores (já que está sendo utilzado um sistema operacional para gerir o funcionamento do processador).

Código exemplo:

``` c++
#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "DELAY"

void app_main(void)
{
  int i = 0;
  while (1)
  {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    ESP_LOGI(TAG, "in loop %d", i++);
  }
}
```

### Random Number

Biblioteca: `esp_random.h` (ESP-IDF 5.x) ou `esp_system.h` (ESP-IDF 4.x)

A função `esp_random()` é capaz de retornar um número aleatório dentro do intervalo de um `uint_32t`. A geração de números aleatórios é realizado via hardware, garantindo que os números sejam sempre aleatórios.

Segundo a documentação do ESP-IDF ([Random Number Generation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/random.html)), para obter números verdadeiramente randomicos, o sistema de Wi-Fi ou Bluetooth devem estar habilitados (pois amostras do ruído físico são continuamente misturados ao hardware de RNG). Caso não estejam, utilizar as funções `bootloader_random_enable()` e `bootloader_random_disable()` durante a inicialização.

Código exemplo:

``` c++
#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// for idf version 4.x use #include "esp_system.h"
#include "esp_random.h"
#include "math.h"

#define TAG "DICE"

int dice_role()
{
  int random = esp_random();
  int positiveNumber = abs(random);
  int diceNumber = (positiveNumber % 6) + 1;
  return diceNumber;
}

void app_main(void)
{
  while (1)
  {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    ESP_LOGI(TAG, "random number %d", dice_role());
  }
}
```

### Blinkey

Código exemplo:

Biblioteca: `driver/gpio.h`

Através da biblioteca `gpio.h`, será possível configurar os pinos do ESP32 individualmente, utilizando a função `gpio_set_direction()`. Para atribuir um valor ao pino, utilizar a função `gpio_set_level()`.

``` c++
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define PIN 2

void app_main(void)
{
  gpio_set_direction(PIN, GPIO_MODE_OUTPUT);
  uint32_t isOn = 0;
  while (true)
  {
    isOn = !isOn;
    gpio_set_level(PIN, isOn);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
```

### Keyboard Input

Ao ler o teclado, a solução adotada aqui é o uso da função `getchar()`, porém, o cuidado que deve-se ter é que ela é uma função não-bloqueante (diferente da função `getchar()` para computador que é uma função bloqueante), portanto, caso não haja nenhum valor recebido pelo seu buffer via serial, retornará logo em seguida o valor `EOF` (-1). Ao comparar o valor retornado pela função `getchar()`, deve-se realizar um *cast* para *char* em `EOF` (ou seja, `(char)EOF`).

Outro detalhe é que o terminal não exibirá as informações enviadas para o ESP32, portanto, para cada tecla enviada, recomenda-se *"printar"* o valor recebido na tela caso o valor recebido seja diferente de `EOF` para poder visualizar o que se escreve.

Para pular de linha no terminal, enviar `\r\n`.

Código exemplo:

``` c++
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
  char c = 0;
  char str[100];
  memset(str, 0, sizeof(str));
  while (c != '\n')
  {
    c = getchar();
    if (c != 0xff)
    {
      str[strlen(str)] = c;
      printf("%c", c);
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }

  printf("you typed: %s\n", str);
}
```

### Using Examples

Bibliotecas:
- `esp_chip_info.h`
- `esp_system.h`
- `esp_spi_flash.h`

Código exemplo (Hello World). Utilizando a biblioteca `esp_chip_info.h`, é possível extrair características do modelo de ESP32 como:
- Modelo;
- Quantidade de núcleos;
- Features;
- Versão do Chip (Major e Minor Revision);
- Tipo de Flash (interna ou externa);
- Presença ou não de PSRAM.

Utilizando a biblioteca `esp_spi_flash.h`, através da função `spi_flash_get_chip_size()`, é possível determinar o tamanho da memória Flash (é possível ajustar esse tamanho via `menuconfig` desde que o ajuste esteja dentro do tamanho disponível de Flash).

Utilizando a bibioteca `esp_system.h`, através da função `esp_restart()`, é possível reiniciar o ESP32 (reset via software).

``` c++
#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

void app_main(void)
{
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
           (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}
```
