# Learn ESP32

## 01 - Course Introduction

### Índice

- [Course Introduction](#course-introduction-1)
- [Dev Boards](#dev-boards)

### Glosário
- IDF: Internet-of-Things Development Framework.
- PSRAM: Pseudo-Static RAM. É a capacidade de transformar parte da sua memória Flash (cujo tamanho começa a partir de 4MB) em memória RAM (que é mais limitada). O processador precisa possuir essa funcionalidade para poder ser explorada.

### Course Introduction

O quê o curso abordará:
- Configuração do ambiente de desenvolvimento;
- Debugging;
- C Avançado;
- FreeRTOS;
- Arquivos de Configuração (Kconfig e menuconfig);
- Memória;
- Armazenamento;
- GPIO;
- I2C;
- SPI;
- Sleeping;
- Internet;
- TCP Client/Server;
- Modos de operação do WiFi;
- MQTT;
- OTA;
- Bluetooth;
- etc.

O ESP32 é um dos mais populares microcontroladores para hobistas e profissionais, produzido pela **Espressif**. A versão `WROOM` tem como uma de suas principais características:

- 512kB de RAM;
- 4MB de Flash;
- Dual Core (apresenta dois processadores);
- Possui integrado WiFi e Bluetooth;
- Preço muito competitivo;
- Permite ser programado utilizando `Javascript`, `Python`, `C/C++ (Arduino)`, `C/C++ (IDF)`;
- O IDF utiliza o sistema operacional `FreeRTOS` para o gerenciamento de tarefas complexas;
- O IDF possui a capacidade de configurar o hardware com bastante facilidade;
- O IDF permite gerenciar a memória da melhor forma de acordo com a aplicação;
- O IDF permite criar um sistema de customização;

O objetivo do curso é apresentar rapidamente os conceitos que podem ser utilizados imediatamente ao se optar pelo IDF em seus projetos.

Materiais que devem ser adquiridos para realizar o curso:
- LEDs e resistores;
- Botões;
- Módulo Bluetooth (como JDY-31 ou **HC-05**);
- LM75AA (sensor de temperatura I2C) (pode ser outro dispositivo I2C);
- Display LCD OLED com SPI (como SSD1306);
- Opcional: ESP32 WROVER, para utilizar a PSRAM;

### Dev Boards

Apresentação de alguns modelos da Espressif como:

- ESP8266 (muito utilizado com Arduino para conexão WiFi através de comandos AT, e que posteriormente, substitui o próprio Arduino ao se darem conta que ele era inclusive mais poderoso do que quem o controlava). Este modelo não possui Bluetooth;
- ESP32 (sucessor do ESP8266, um pouco maior, o modelo mais conhecido é o WROOM que possui 4MB de memória Flash). Possui alguns modelos como DOIT ESP32 e ESP32 Wemos Lolin.

O ESP32 não possui memória Flash interna, sendo necessária a utilização de uma memória Flash externa (geralmente é utilizada uma memória Flash SPI de 4MB).

Sugestão de montagem do ESP32 em protoboard:

![Montagem do ESP32 em Protoboard](Assets/Montagem%20do%20ESP32%20em%20Protoboard.png)
