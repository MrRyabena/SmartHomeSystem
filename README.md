![logo](/SHSlogos/PNG/SHS_com-mint.png)

[![Static Badge](https://img.shields.io/badge/Telegram-dev%20blog-blue)](https://t.me/SmartHomeSystem_dev)

---

<a id="versions"></a>

# Versions

<!---------------------------------- v0.1.0 ----------------------------------->

<details>
<summary>v0.1.0 — private beta-version.</summary>
</details>

<!---------------------------------- v0.2.0 ----------------------------------->

<details>
<summary>v0.2.0 — development.</summary>
</details>

<!---------------------------------- v1.0.0 ----------------------------------->

<details>
<summary>v1.0.0 — release.</summary>

- [See release](https://github.com/MrRyabena/SmartHomeSystem/releases/tag/v1.x.x)
- New core architecture.
- New library.
- The documentation has been completed.
- The SHScore has not been tested.
- The demo version is incomplete.
- Tests and additions are expected.

</details>

<!---------------------------------- v1.1.0 ----------------------------------->

<details>
<summary>v1.1.0 — added tests.</summary>

- Tests have been written and conducted, created the library SHStests.
- A random number generator (shs::Random) has been created.
- Development of a project assembly system.
- shs::ByteCollecor: fixed a critical error in functions get() and reserve().
- shs::CRC: now the function crcBuf(..) writes the result to a variable crc.
- The synchronizer has been replaced with a make.sh.

![SHScore-changes-v1_1_0](/schemes/SHScore-changes/SHScore-changes-v1_1_0.png)

</details>

<!---------------------------------- v1.2.0 ----------------------------------->

<details>
<summary>v1.2.0 — intermediate version.</summary>

- A file system has been developed [beta]:
  - shs::FSAbstract and shs::FileAbstract — interface classes.
  - shs::FS — file system class.
  - shs::File — file class.
  - shs::SHSF — [beta] Smart Home System File (.shsf). It has errors now.</br>
    _*note: The File System is poorly tested and isn't fully developed.*_
- Developed a new ID-type SHSID.
- Added SHSversion.h.
- An important version for the further development of the project.

![SHScore-changes-v1_2_0](/schemes/SHScore-changes/SHScore-changes-v1_2_0.png)

</details>

<!---------------------------------- v2.0.0 ----------------------------------->

<details>
<summary>v2.0.0 — global update.</summary>

<!-- # SmartHomeSystem v2.0.0 Release Notes -->

- **Build System**: Completed a comprehensive project build system using CMake and Shell.
- **Data Structures and Algorithms**: Added algorithms and containers for working with ordered data:
  - `shs::SortedBuf`: A container for working with ordered `std::vector`.
  - `shs_algorithms`: Template functions for searching, inserting, and deleting elements in containers.
- **Memory Management**: Improved memory handling with added move semantics.
- **SHSDTP Module**: Major changes, divided into components and expanded:
  - Component classes:
    - `shs::DTP`: A container class for linking data buses and API handlers.
    - `shs::DTPbus`: An abstract class for a data bus that accepts and sends messages.
    - `shs::DTPdiscover`: A class for discovering devices on a local network.
    - `shs::DTPless`: Comparison operators for search and sorting algorithms.
    - `shs::DTPpacket`: A class for creating, encrypting, and decrypting messages.
  - Fully tested.
- **Program Time**: Function names have been changed, optimized, bugs fixed, and tested.
- **Fixed-Point Numbers**: Created `shs::SimpleFixed`, a temporary implementation for convenience.
- **Network Module**:
  - Updated and debugged `shs::ControlWiFi`.
  - Added `shs::IP` class for storing and working with IP addresses.
  - Created and tested classes for working with Qt sockets:
    - `shs::qt::TcpSocket`
    - `shs::qt::UdpSocket`
  - `shs::TcpServer`: Updated functionality, debugged, and tested.
    - Automatically attaches clients to `shs::DTP`.
    - Configures clients to delete when the connection is closed.
  - `shs::TcpSocket`: Updated functionality, debugged, and tested.
    - Based on `shs::DTPbus`.
    - Automatic reconnection in case of connection loss.
    - Qt support.
  - **UDP Support**:
    - Created `shs::UDP`, providing an interface for working with UDP.
    - `shs::UdpBus`: Works with UDP as with `shs::DTPbus`.
    - `shs::UdpBroadcastBus`: Sending and receiving broadcast messages.
    - `shs::UdpMulticastBus`: Sending and receiving messages in a group.
- **Load Components**: Redesigned, debugged, and tested.
- **Types Module**: Developed from `shs_settings_private.h`.
- **Sensor Module**:
  - Redesigned, debugged, and tested.
  - Functionality changes:
    - `update()` must be called before getting the value.
    - `updateFast()`, if supported by the sensor, measures less accurately but faster.
    - Added error status.
    - Support for multiple metrics.
- **Library Updates**:
  - The library has been expanded and now includes new components:
    - **GRGB API**: An API for working with GRGB (from AlexGyver's library).
    - **RGB Color Music Library**: A library for managing RGB color music effects.
    - **Sensor Support**: Added support for various sensor types:
      - `BME280`
      - `DHT`
      - `DS18`
      - `MHZ19`
      - `Thermistor`
      - `SensorTypes`: An enumeration for different sensor types.
- **Undebugged Components**:
  - `shs::StreamBus`: Not debugged, has bugs. Support and development expected in future versions.
  - `shs::EventTracker`: Has bugs and errors.
- **Unused Components**:
  - `shs::CreateProcess`: The class creates a process from function pointer templates.
  - `shs::MutexSafe`: Component of an unused OS module.
- **Underdeveloped Components**:
  - `shs::Time`: Unix time storage and parsing (not developed).

Changes ([see also here](./schemes/SHScore-changes/SHScore-changes-v1_2_0.png))

![SHScore-changes-v2_0_0.png](./schemes/SHScore-changes/SHScore-changes-v2_0_0.png)
![SHScore-scheme](./schemes/SHScore-scheme.png)
![SHSlibrary-scheme](./schemes/SHSlibrary-scheme.png)

</details>

<!---------------------------------- v2.0.0 ----------------------------------->
<details>
<summary>v2.1.0 — <b>[current]</b> The core functionality has been expanded; sensor libraries have been debugged and tested; added a new device <i>ClimateStation</i>.</summary>
<!-- # SmartHomeSystem v2.1.0 Release Notes -->
- **SHScore:**
  - **Changes:**
    - `shs::ByteCollector`: Optimization and bugs fix.
    - `shs::ID`: Fixed a bug during the assignment of ID components.
  - **New functional:**
    - `shs::LoadPWM`: Returned to development, redesigned, debugged and tested.
    - `shs::ProgramTimer`: A class has been created for timers inside the program code.
  - **Bugs:**
    - `shs::DTP_API`: Critical error found.
      > [!WARNING]
      > The error has not been fixed, the use of this class is unsafe!

</details>

<!----------------------------------------------------------------------------->

---
> [!IMPORTANT]
>
> - Для краткого ознакомления с проектом можно посмотреть [презентацию](pitch/SmartHomeSystem.pdf).
> - Вся документация переехала в папку [SHSdocumentation](SHSdocumentation/). Огромная статья из прошлого релиза разделена на тематические файлы и папки и дополнена.
> - У **_SmartHomeSystem_** есть [блог разработки](https://t.me/SmartHomeSystem_dev), там можно наблюдать за развитием проекта.
> - Пример создания автоматизированной системы, используя фреймворк SmartHomeSystem можно посмотреть в [system_creation_guide](/SHSdocumentation/Usage/system_creation_guide.md).

---

## Содержание

- [Структура репозитория](#структура-репозитория)
- [Краткий обзор](#краткий-обзор)
- [SmartHomeSystem Projects](#smarthomesystem-projects)
- [Награды проекта](#награды-проекта)
- [Contacts](#contacts)

## Структура репозитория

Проект выложен в репозитории на GitHub и доступен по ссылке: <https://github.com/MrRyabena/SmartHomeSystem>.</br>

- [awards](./awards/) — награды проекта (дипломы, документы, фотографии).
- [SHSdocumentation](SHSdocumentation/) — документация к проекту.
  - [Code](SHSdocumentation/Code/) — документация к программному коду.
  - [Hardware](SHSdocumentation/Hardware/) — документация к компонентам, микроконтроллерам, техническим устройствам.
  - [ProjectOverview](SHSdocumentation/ProjectOverview/) — обзор проекта, особенности разработки, методы и подходы.
  - [Usage](SHSdocumentation/Usage/) — руководства по сборке библиотек и использованию Smart HomeSystem, информация для пользователей и разработчиков.
- [libraries](libraries/) — сторонние библиотеки, используемые в проекте.
- [pitch](pitch/) — презентации проекта и вспомогательные файлы.
- [schemes](schemes/) — картинки, схемы, чертежи...
- [SHSlogos](SHSlogos/) — логотипы и символика проекта.
- [src](src/) — исходный код.
  - [debugging_sketches](src/debugging_sketches/) — наброски отладочных прошивок.
  - [examples](src/examples/) — примеры использования программного кода.
  - [SHSapp](src/SHSapp/) — разработки графических приложений.
  - [SHScore](src/SHScore/) — ядро (бизнес-логика), основная разработка.
  - [SHSdevice](src/SHSdevice/) — устройства, которые можно добавлять в модули системы.
  - [SHSlibrary](src/SHSlibrary/) — библиотека с удобными инструментами, интерфейсами датчиков и нагрузок, вычислительными алгоритмами, основанная на ядре.
  - [SmartModules](src/SmartModules/) — [beta] устройства и модули.
  - [SmartModulesAPI](src/SmartModulesAPI/) — [beta] команды устройств и модулей.
  - [make.sh](src/make.sh) — Shell-скрипт для сборки всех исходников проекта (см. документацию по использованию: [build_manual](./SHSdocumentation/Usage/build_manual.md)).

## Краткий обзор

**_SmartHomeSystem_** — кроссплатформенный фреймворк, который упрощает создание автоматизированных систем для различных условий. Проект предлагает удобные инструменты для разработки модульных систем, которые могут быстро изменять свою конфигурацию. Вы можете как создавать полномасштабные автоматизированные системы, так и частично использовать алгоритмы и протоколы ядра в других проектах.

### В проект <b><i>SmartHomeSystem</b></i> входят

- **Аппаратные разработки**
  - Компонентная база
  - Схемы, платы, чертежи
  - 3D-модели
- **Программные разработки**
  - Универсальное кроссплатформенное ядро
  - Прошивки для микроконтроллеров
  - GUI приложения
- **Документация**
  - Рекомендации по разработке аппаратной части
  - Документация к коду
  - Инструкция по сборке и использованию программной части
  - Руководства по проектированию собственных устройств

---

#### SHScore

Разработанное ядро **_SmartHomeSystem_** даёт проекту его основные преимущества и на данный момент включает в себя следующие ключевые технологии:

- контейнеры для хранения и представления данных
- инструменты для работы с сетью и временем
- протоколы передачи данных
- абстракции датчиков и нагрузок
- утилиты для алгоритмов автоматизации

Схема ядра ([see also here](./schemes/SHScore-scheme.pdf)):
![SHScore-scheme](./schemes/SHScore-scheme.png)

---

#### SHSlibrary

Схема библиотеки ([see also here](./schemes/SHSlibrary-scheme.pdf)):

![SHSlibrary-scheme](./schemes/SHSlibrary-scheme.png)

---

### Сборка, использование, документация

Инструкции по сборке проекта находятся в папке документации в разделе [Usage](/SHSdocumentation/Usage/). Там же есть гайд по созданию систем, используя фреймворк **_SmartHomeSystem_**.

Рекомендуется внимательно ознакомиться со всей [документацией](/SHSdocumentation/). В её папке в соответствующем [README](/SHSdocumentation/README.md) описан порядок чтения разделов документации.

### Сферы применения

- Создание систем "Умный дом": автоматизация управления освещением, климатом и бытовыми приборами для повышения комфорта и энергоэффективности.
- Автоматизация производственных и бизнес-процессов: оптимизация работы оборудования и управление производственными линиями для повышения эффективности.
- Разработка специализированных решений для управления и мониторинга: использование в научных исследованиях для создания систем датчиков и мониторинга.
- Умные офисы: автоматизация управления освещением, климатом и системами безопасности для повышения комфорта и продуктивности сотрудников.
- Сценические эффекты и выставки: управление прожекторами, дымогенераторами и создание эффектов для уникальных визуальных представлений на мероприятиях и выставках.
- Фото и видеоиндустрия: управление системой источников света и эффектов во время съемок, что позволяет создавать профессиональные материалы.
- Образовательные учреждения: создание интерактивных учебных лабораторных проектов, создание наборов для проведения и мониторинга экспериментов.
- Сельское хозяйство: автоматизация процессов полива, контроля температуры и влажности воздуха и почвы для повышения урожайности.

## SmartHomeSystem Projects

Далее перечислены несколько проектов, которые тоже являются частью SmartHomeSystem, но для удобства разработки вынесены в отдельные репозитории.

- [SmartSpot](https://github.com/MrRyabena/SmartSpot) — мощный светодиодный RGB-светильник, управляющийся по WiFi через специальное приложение. Светильник поддерживает различные эффекты. Есть возможность объединить несколько светильников в группу, для мощного освещения сцены, фотозоны или других объектов. Таким образом, несколько созданных светильников успешно применяются в качестве сценического света, для проведения дискотек (имеется встроенная цветомузыка) и разработки тематических игр (в отдельной ветке проекта реализована игра Мафия, с тематической озвучкой и светоэффектами). Проект получил большую популярность среди аудитории SmartHomeSystem.

- [SmartBank](https://github.com/MrRyabena/SmartBank) — умная копилка, которая станет уникальным украшением в доме. Была создана на хакатоне "Умный Петербург 2025" и заняла 1 место. Устройство имеет возможность интеграции в систему, работающую по алгоритмам **_SmartHomeSystem_**, умеет распознавать номиналы монет, подсчитывать сумму, собирать статистику и выводить данные на экране и в Telegram чат.

- [ClimateStation](https://github.com/MrRyabena/ClimateStation) — метеостанция в специально разработанном для 3D-печати корпусе с сенсорным дисплеем. Собирает информацию с внутренних и внешних (для улицы) датчиков об атмосферном давлении, уровне CO2 (углекислого газа) в помещении, влажности и температуре воздуха. Станция составит прогноз погоды, подскажет когда необходимо проветрить помещение и выведет показания и графики их изменения. Сенсорный экран позволят изменять настройки, переключать режимы работы и смотреть датчики. Устройство имеет возможность полной интеграции с системами SmartHomeSystem. Таким образом, оно может стать средством обратной связи в системах климат-контроля.

## Награды проекта

Дипломы, грамоты, фотографии и другие документы находятся в соответствующей папке [awards](./awards).

### 1 место в хакатоне "Умный Петербург 2025"

[SmartBank](https://github.com/MrRyabena/SmartBank), созданная на хакатоне "Умный Петербург 2025" как решение кейса от Санкт-Петербургского политехнического университета Петра Великого, заняла первое место в треке "Интернет вещей". За 2 дня были смоделирован и напечатан корпус, собрана электроника, написан программный код и отлажен механизм распознавания монет.

<img src="./awards/hackathon_Smart_Petersburg_2025.jpg" alt="diploma" width="250"/>

### 1 место в районной научно-практической конференции "Шаг в будущее"

Проект **_SmartHomeSystem_**, по итогам конференции, был награжден грамотой за 1 место.

<img src="./awards/conference_Step_into_the_future_2025.jpg" alt="diploma" width="250"/>

---

## Источники информации и литература

См.: [/SHSdocumentation/ProjectOverview/2_literature.md](/SHSdocumentation/ProjectOverview/2_literature.md)

---

## Багодарности

Автор выражает благодарность:

- [AlexGyver'у](https://github.com/AlexGyver) (блогер и open source DIY разработчик), проекты которого послужили источником знаний и вдохновения для создания **_SmartHomeSystem_**.
- [Ивану Макарову](https://github.com/i-s-m-mipt) (преподаватель и ведущий программист-разработчик лаборатории МФТИ), лекции которого дали много полезных и глубоких знаний в области языка программирования C++.

---

## Contacts

Tg: <https://t.me/MrRyabena></br>
Mail: <daniilrazanov82349@gmail.com></br>
Development blog: <https://t.me/SmartHomeSystem_dev></br>
</br>
_**I will be glad to receive suggestions for improving the project, cooperation, and feedback.**_</br>
</br>
Daniil Ryazanov (Даниил Рязанов)</br>
_Saint-Petersburg, 2025_</br>
