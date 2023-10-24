# Learn ESP32

## 02 - Environment Setup

### Índice

- [Introduction](#introduction)
- [Installing ESP-IDF on Windows](#installing-esp-idf-on-windows)
- [Installing ESP-IDF on Ubuntu](#installing-esp-idf-on-ubuntu)
- [Installing and Configuring VSCode](#installing-and-configuring-vscode)
- [Project Walkthrough](#project-walkthrough)
- [Multiple IDF Versions](#multiple-idf-versions)

### Glosário

### Introduction

Instalação do ESP-IDF, configuração do VSCode (ferramenta de edição gratuita disponibilizada pela Microsoft).

### Installing ESP-IDF on Windows

A Espressif mantém uma [página](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/) onde ele disponibiliza diversas versões de download do ESP-IDF de acordo com o sistema operacional desejado. Recomenda-se realizar o download e instalá-lo antes de realizar a configuração dele no VSCode.

[Link de Download para o ESP-IDF no Windows](https://dl.espressif.com/dl/esp-idf/?idf=4.4)

Durante a instalação, o ESP-IDF solicitará a modificação:
- Long Paths Enabled (habilitar a expansão de endereços de 260 caracteres para 32767);
- A inclusão à lista de exceções no antivirus (aumentará a velocidade de compilação em até 30%).

Para aplicar essas modificações, clicar em `Apply Fixes`.

Recomenda-se realizar a instalação na raiz do Windows (como `C:`). Deve-se criar uma estrutura de pastas antes de realizar a instalação da ferramenta:

```
|—— C:
|    |—— Espressif
|        |—— esp-idf
|        |—— tools
```

Realizar a instalação das ferramentas nas respectivas pastas.

Quando a instalação for concluída, o ESP-IDF fornecerá o seu próprio Prompt de Comando com as variáveis de ambiente já configuradas automaticamente. Caso deseje testá-lo, pode-se navegar até a pasta `C:/Espressif/esp-idf/examples/get-started/hello_world` e realizar a compilação e gravação do binário no ESP32 utilizando o seguinte comando:

``` bash
idf.py build flash monitor
```

### Installing ESP-IDF on Ubuntu

Pré-requisitos:
- Instalação do Git (`apt-get install git`).
- Instalação de todos os pré-requisitos mencionados na página:

``` bash
sudo apt-get install git wget flex bison gperf python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
```

Criar um diretório na pasta raiz chamado `esp` e realizar o download do ESP-IDF via Git:

``` bash
mkdir -p ~/esp
cd ~/esp
git clone --recursive https://github.com/espressif/esp-idf.git
```

Realizar a instalação da ferramenta:

``` bash
cd ~/esp/esp-idf
./install.sh esp32
```

Configurando as variáveis de ambiente (este comando sempre deverá ser executado ao abrir o terminal):

``` bash
. $HOME/esp/esp-idf/export.sh
```

Atribuir permissão de acesso a porta `/dev/ttyUSB0` (ao utilizar esse comando, deve-se reiniciar a máquina para que as mudanças surtam efeito):

``` bash
sudo usermod -a -G dialout $USER
```

Para testar a ferramenta, copiar um dos códigos de exemplo disponibilizados pela Espressif:

``` bash
cd ~/esp
cp -r $IDF_PATH/examples/get-started/hello_world .
```

Acessar a pasta e realizar a compilação e gravação do código:

``` bash
cd ~/esp/hello_world
idf.py -p /dev/ttyUSB0 build flash monitor
```

**Obs:** Para verificar se realmente o ESP32 foi identificado na porta `/dev/ttyUSB0`, digitar:

``` bash
ls /dev/tty*
```

### Installing and Configuring VSCode

Para trabalhar com o VSCode, será necessário realizar o [download](https://code.visualstudio.com) dele no site. Em seguida, realizar a instalação da [extensão da Espressif](https://marketplace.visualstudio.com/items?itemName=espressif.esp-idf-extension) no VSCode.

Ao abrir a paleta de comandos, executar `ESP-IDF: Configure ESP-IDF Extension`, para poder configurar o VSCode. Utilizar a opção `Use Existing Setup` para utilizar as configurações da instalação do ESP-IDF realizado anteriormente. Apontar para as mesmas pastas da instalação, ou seja:

- **IDF_PATH**: `c:/esp/esp-idf`
- **IDF_TOOLS_PATH**: `c:/esp/tools`

Também é possível realizar a configuração através da opção `Express`, já a opção `Advanced` é desaconcelhável e algumas vezes não se comporta da maneira desejada.

Para criar um novo projeto, abrir a paleta de comandos e executar: `ESP-IDF: New Project`. Escolher um nome para o projeto e escolher o diretório (muita atenção aqui, pois nem o nome e nem o endereço poderão conter acentuação, espaço e alguns outros símbolos), selecionar qual ESP32 está sendo utilizado e a porta utilizada. 

Ao criar o projeto, será possível realizar a sua criação com base em `templates` (como o `hello_world`) ou em projetos já concluídos.

Um dos problemas que pode ocorrer ao criar um novo projeto é da ferramenta `IntelliSense` não funcionar corretamente. Para solucionar este problema, acessar a pasta `.vscode` dentro da pasta do projeto através do VSCode, e acessar o arquivo `c_cpp_properties.json` e alterar a respectiva linha:

``` json
// Linha antes da modificação (formato padrão)
"C_Cpp.intelliSenseEngine": "Tag Parser",

// Linha após a modificação
"C_Cpp.intelliSenseEngine": "Default",
```

Após realizar a modificação, o VSCode irá sugerir a reinicialização do ambiente (clicar em `Sim`).

Comandos:
- `Ctrl + Shift + P`, `F1` ou `View > Command Pallete`: Abre a paleta de comandos.

**OBS:** No final da aula, Mair Swartz explica como utilizar as ferramentas disponibilizadas na barra de status do VSCode, porém, ele prefere realizar as gravações do ESP32 através da linha de comando.

**OBS:** Caso esteja numa sessão de `monitor` com o ESP32, e deseja-se encerrar a comunicação, utilizar o comando `Ctrl + ]` + `Ctrl + [` várias vezes até encerrar a comunicação.

### Project Walkthrough

Sempre que um projeto for criado, a ferramenta irá criar a seguinte estrutura de pastas:

```
|—— .devcontainer
|    |—— devcontainer.json
|    |—— Dockerfile
|—— .vscode
|    |—— c_cpp_properties.json
|    |—— launch.json
|    |—— settings.json
|    |—— tasks.json
|—— .gitignore
|—— CMakeLists.txt
|—— main
|    |—— CMakeLists.txt
|    |—— main.c
|—— README.md
|—— sdkconfig
```

- `.devcontainer`: Armazena as configurações no caso de desejar trabalhar com um ambiente de trabalho virtual (denominado `Remote-Container` no VSCode), cuja as ferramentas já estão instaladas e configuradas corretamente;
- `.vscode`: Armazena as configurações do ambiente e das ferramentas que serão utilizadas no processo de desenvolvimento e compilação da aplicação;
- `main`: Pasta que conterá o software da aplicação.
- `sdkconfig`: Arquivo de personalização da compilação do ESP32. A modificação do sdkconfig é feito via `menuconfig` utilizando o seguinte comando: `idf.py menuconfig`.

### Multiple IDF Versions

Para se trabalhar com múltiplas versões do ESP-IDF, basta possuir um diretório que irá concentrar todas as instâncias das versões das ferramentas de compilação em pastas distintas (ou seja, a instalação por padrão foi feita no diretório `C:/Espressif`, porém, neste diretório, poderia-se criar uma pasta para cada versão desejada, e em seguida, criar locais para a instalação das ferramentas da respectiva versão):

```
|—— C:
|    |—— Espressif
|        |—— idf-v4.2
|            |—— esp-idf
|            |—— tools
|        |—— idf-v4.3
|            |—— esp-idf
|            |—— tools
|        |—— idf-v4.5
|            |—— esp-idf
|            |—— tools
|        |—— idf-v5.0
|            |—— esp-idf
|            |—— tools
```

Em seguida, executar o comando na `Command Pallete`: `ESP-IDF: Configure ESP-IDF extension`. Abrirá uma janela onde será possível indicar se a configuração do ESP-IDF será no `Workspace` (diretório atual) ou `Global` (para todos os projetos) e as seguintes opções:

- Express;
- Advanced;
- Use Existing Setup.

A instalação de novas instâncias do ESP-IDF recomenda-se serem feitas utilizando a opção **Express**, enquanto que para utilizar novas versões a opção **Use Existing Setup**. Recomenda-se também realizar as mudanças no **Workspace**, assim, não irá comprometer os outros projetos.<br>
Pode acontecer da compilação não funcionar em um primeiro momento pois as variáveis de ambiente da ferramenta não foram inicializadas corretamente ou realizaram a inicialização a partir das variáveis de ambiente global, portanto, basta reiniciar o VSCode para que as modificações tenham efeito.
