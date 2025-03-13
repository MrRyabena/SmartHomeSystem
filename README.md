![logo](/SHSlogos/com.png)

[![Static Badge](https://img.shields.io/badge/Telegram-dev%20blog-blue)](https://t.me/SmartHomeSystem_dev)

---

<a id="versions"></a>

# Versions

<!---------------------------------- v2.0.0 ----------------------------------->

<details>
<summary>v2.0.0 — <b>[current]</b> global update.</summary>

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
- **Undebugged Components**:
  - `shs::StreamBus`: Not debugged, has bugs. Support and development expected in future versions.
  - `shs::EventTracker`: Has bugs and errors.
- **Unused Components**:
  - `shs::CreateProcess`: The class creates a process from function pointer templates.
  - `shs::MutexSafe`: Component of an unused OS module.
- **Underdeveloped Components**:
  - `shs::Time`: Unix time storage and parsing (not developed).

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

<!---------------------------------- v0.2.0 ----------------------------------->

<details>
<summary>v0.2.0 — development.</summary>
</details>

<!---------------------------------- v0.1.0 ----------------------------------->

<details>
<summary>v0.1.0 — private beta-version.</summary>
</details>

<!----------------------------------------------------------------------------->

---
> [!NOTE]
> Проект готовиться к релизу, код оптимизируется, документация переписывается...

> [!IMPORTANT]
>
> - Для краткого ознакомления с проектом можно посмотреть [презентацию](pitch/SmartHomeSystem.pdf).
> - Вся документация переехала в папку [SHSdocumentation](SHSdocumentation/). Огромная статья из прошлого релиза разделена на тематические файлы и папки и дополнена.
> - У **_SmartHomeSystem_** есть [блог разработки](https://t.me/SmartHomeSystem_dev), там можно наблюдать за развитием проекта.
>

---

## Структура репозитория

Проект выложен в репозитории на GitHub и доступен по ссылке: <https://github.com/MrRyabena/SmartHomeSystem>.</br>

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

**_SmartHomeSystem_** — это кроссплатформенный фреймворк, который упрощает создание автоматизированных систем для различных условий. Проект предлагает удобные инструменты для разработки модульных систем, которые могут быстро изменять свою конфигурацию. Вы можете как создавать полномасштабные автоматизированные системы, так и частично использовать алгоритмы и протоколы ядра в других проектах.

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

### Сферы применения

- Создание систем "Умный дом": автоматизация управления освещением, климатом и бытовыми приборами для повышения комфорта и энергоэффективности.
- Автоматизация производственных и бизнес-процессов: оптимизация работы оборудования и управление производственными линиями для повышения эффективности.
- Разработка специализированных решений для управления и мониторинга: использование в научных исследованиях для создания систем датчиков и мониторинга.
- Умные офисы: автоматизация управления освещением, климатом и системами безопасности для повышения комфорта и продуктивности сотрудников.
- Сценические эффекты и выставки: управление прожекторами, дымогенераторами и создание эффектов для уникальных визуальных представлений на мероприятиях и выставках.
- Фото и видеоиндустрия: управление системой источников света и эффектов во время съемок, что позволяет создавать профессиональные материалы.
- Образовательные учреждения: создание интерактивных учебных лабораторных проектов, создание наборов для проведения и мониторинга экспериментов.
- Сельское хозяйство: автоматизация процессов полива, контроля температуры и влажности воздуха и почвы для повышения урожайности.

## Contacts

Tg: <https://t.me/MrRyabena></br>
Mail: <daniilrazanov82349@gmail.com></br>
_**I will be glad to receive suggestions for improving the project, cooperation, and feedback.**_</br>
Daniil Ryazanov (Даниил Рязанов)</br>
_Saint-Petersburg, 2025_</br>
