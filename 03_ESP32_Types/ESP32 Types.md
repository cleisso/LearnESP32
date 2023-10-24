# Learn ESP32

## 03 - ESP32 Types

### Índice

- [Introduction](#introduction)
- [Comparing ESP Types](#comparing-esp-types)
- [VSCode ESP32 Target](#vscode-esp32-target)

### Glosário

### Introduction

Apresentação de diversas placas que contém ESP32.

Observação:

- O ESP32-C3-Mini é pino-a-pino compatível com o ESP8266, tornando ideal para substituição de projetos que continham a versão anterior.

### Comparing ESP Types

![Comparativo entre os Diversos Modelos de ESP32](Assets/Comparativo%20entre%20os%20Diversos%20Modelos%20de%20ESP32.PNG)

A Espressif possui pelo menos 4 séries de chips:

- ESP32-S*: Essas placas podem ter conectividade Bluetooth ou não. A versão S3 é utilizada para trabalhar com *Computação de Borda (Edge AI)*. Aparentemente também são as versões que possuem PSRAM (pelo menos a versão S3);
- ESP32-C*: São versões Low-Power (a letra C pode indicar *Consuption*);
- ESP32-H*: São versões que trazem algum tipo de conectividade, como a versão H2 que possui o protocolo ZigBee;
- ESP32-P*: São placas de alta performance (a letra P pode indicar *Performance*).

Observação:

- O protocolo `Thread` foi desenvolvido pelos mesmos criadores do `ZigBee`.

### VSCode ESP32 Target

Apresenta como realizar a troca da série do ESP32 via VSCode. Recomenda-se que após a alteração do microcontrolador alvo, seja feita uma limpeza na compilação antes de compilar novamente.
