
# Build SmartHomeSystem

## Содержание

- [Рекомендуемое ПО](#рекомендуемое-по)
- [Сборка под Arduino IDE](#сборка-под-arduino-ide)
  - [Установка ПО](#установка-по)
  - [Установка проекта](#установка-проекта)
- [Сборка под Qt/VS](#сборка-под-qtvs)
- [CMake](#cmake)

## Рекомендуемое ПО

Ниже представлен список рекомендуемого программного обеспечения для работы с проектом:

- IDEs
  - [Cursor](https://www.cursor.com) ([Visual Studio Code](https://code.visualstudio.com))
  - [Microsoft Visual Studio](https://visualstudio.microsoft.com/ru/)
  - [QtCreator](https://www.qt.io/product/development-tools)
  - [Arduino IDE](https://www.arduino.cc/en/software) / [PlatformIO](https://platformio.org)
    - ESP8266, ESP32 and AVR boards
    - [ESP Exception Decoder](https://github.com/dankeboy36/esp-exception-decoder)
- Tools
  - linux (WSL)
  - shell
  - [Git](https://git-scm.com)
  - [CMake](https://cmake.org)
- Drivers (see AlexGyver's guide)
  - CH341
  - CP2102

## Сборка под Arduino IDE

### Установка ПО

Для работы с микроконтроллерами необходимо установить [Arduino IDE](https://www.arduino.cc/en/software) или [PlatformIO](https://platformio.org). Подробную инструкцию об установке, решении ошибок, дополнительных драйверах и зависимостях можно изучать в статьях AlexGyver'a:

- ["Гайд для новичков Arduino"](https://alexgyver.ru/arduino-first/)
- ["Начало работы с Arduino IDE"](https://alexgyver.ru/lessons/before-start/)
- ["Работа с Arduino IDE"](https://alexgyver.ru/lessons/arduino-ide/)
- ["PlatformIO — замена Arduino IDE"](https://alexgyver.ru/platformio-замена-arduino-ide/)
- ["ESP8266. Начало работы, особенности"](https://alexgyver.ru/lessons/esp8266/)

> [!IMPORTANT]
> Настоятельно рекомендуется внимательно прочитать вышеперечисленные статьи, если вы не имеете опыта работы с микроконтроллерами и данными средами разработки.

### Установка проекта

Теперь, чтобы проектом можно было пользоваться прямо из IDE, нужно переместить содержимое папок [SHScore](../../src/SHScore/) и [SHSlibrary](../../src/SHSlibrary/) в папку с библиотеками IDE. Конечно, нет никакого смысла делать это вручную. Поэтому в проекте предусмотрено средство сборки.

> [!TIP]
> Чтобы запустить сборку проекта, понадобится терминал linux. Если вы используете ОС Windows, то вы можете разблокировать компонент WSL — для наших целей виртуальной linux будет достаточно. Инструкцию как это сделать можно найти в интернете.

Для начала необходимо создать копию файла [libraries_path_example.sh](../../src/libraries_path_example.sh). После чего следует сменить ее имя на _"libraries_path"_. В самом файле необходимо прописать путь к папкам с библиотеками вашей IDE.

После того, как файл подготовлен, можно запустить скрипт из файла [make.sh](../../src/make.sh) в терминале linux:

```shell
./make.sh --ard
```

> [!TIP]
> Для подробного вывода описания команд следует передать `--help`

## Сборка под Qt/VS

Интеграция проекта в QtCreator или Microsoft Visual Studio происходит аналогично. Сначала необходимо добавить путь, в который требуется скопировать исходники в файл [libraries_paths.sh](../../src/libraries_paths.sh). Затем запустить скрипт, передав соответствующие параметры (`--qt`/`--oth`):

```shell
./make.sh --qt
./make.sh --oth
```

## CMake

**_SmartHomeSystem_** поддерживает сборку средствами [CMake](https://cmake.org). `SHScore` и `SHSqt_core` содержат файлы `CmakeLists.txt` и собираются как статические библиотеки. Их подключение в проект выглядит примерно так:

```cmake
add_subdirectory(path/to/SHScore)
target_link_libraries(TARGET PRIVATE SHScore)
target_include_directories(TARGET PRIVATE path/to/SHScore)
```

> [!IMPORTANT]
> Если используется Qt, то для подключения в сборку его файлов необходимо установить флаги:
>
> ```cmake
> set(SHS_CMF_QT ON CACHE BOOL "Enable Qt")
> add_definitions(-DSHS_QT_FLAG)
>```

Сборка `SHSlibrary` может происходить как по отдельным компонентам, так и целиком.
