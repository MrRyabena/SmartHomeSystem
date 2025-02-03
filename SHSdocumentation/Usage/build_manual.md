
# Build SmartHomeSystem

## Содержание

- [Сборка под Arduino IDE](#сборка-под-arduino-ide)
  - [Установка ПО](#установка-по)
  - [Установка проекта в библиотеки](#установка-проекта-в-библиотеки)
- [Сборка под Qt/VS](#сборка-под-qtvs)
- [CMake](#cmake)

## Сборка под Arduino IDE

### Установка ПО

Для работы с микроконтроллерами необходимо установить [Arduino IDE](https://www.arduino.cc/en/software) или [PlatformIO](https://platformio.org). Подробную инструкцию об установке, решении ошибок, дополнительных драйверах и зависимостях можно изучать в статьях AlexGyver'a:

- ["Гайд для новичков Arduino"](https://alexgyver.ru/arduino-first/)
- ["Начало работы с Arduino IDE"](https://alexgyver.ru/lessons/before-start/)
- ["Работа с Arduino IDE"](https://alexgyver.ru/lessons/arduino-ide/)
- ["PlatformIO — замена Arduino IDE"](https://alexgyver.ru/platformio-замена-arduino-ide/)

> [!IMPORTANT]
> Настоятельно рекомендуется внимательно прочитать вышеперечисленные статьи, если вы не имеете опыта работы с микроконтроллерами и данными средами разработки.

### Установка проекта в библиотеки

Теперь, чтобы проектом можно было пользоваться прямо из IDE, нужно переместить содержимое папок [SHScore](../../src/SHScore/) и [SHSlibrary](../../src/SHSlibrary/) в папку с библиотеками. Конечно, нет никакого смысла делать это вручную. Поэтому в проекте предусмотрено средство сборки.

> [!TIP]
> Чтобы запустить сборку проекта, понадобится терминал linux. Если вы используете ОС Windows, то вы можете разблокировать компонент WSL — для наших целей виртуальной linux будет достаточно. Инструкцию как это сделать можно найти в интернете.

Для начала необходимо создать копию файла [libraries_path_example](../../src/libraries_path_example). После чего ей следует сменить имя на _"libraries_path"_. В самом файле необходимо прописать путь к папкам с библиотеками вашей IDE.

После того, как файл подготовлен, можно запустить скрипт из файла [make.sh](../../src/make.sh) в терминале linux:

```shell
@:~/SHS/src$ ./make.sh --ard
```

> [!TIP]
> Для подробного вывода описания команд следует передать `--help`

## Сборка под Qt/VS

Интеграция проекта в QtCreator или Microsoft Visual Studio происходит аналогично. Сначала необходимо добавить путь, в который требуется скопировать исходники в файл [libraries_paths.sh](../../src/libraries_paths.sh). Затем запустить скрипт, передав соответствующие параметры (`--qt`/`--oth`):

```shell
@:~/SHS/src$ ./make.sh --qt
@:~/SHS/src$ ./make.sh --oth
```

## CMake

**_SmartHomeSystem_** поддерживает сборку средствами [CMake](https://cmake.org). `SHScore` и `SHSqt_core` содержат фалы `CmakeLists.txt` и собираются как статические библиотеки. Их подключение в проект выглядит примерно так:

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
