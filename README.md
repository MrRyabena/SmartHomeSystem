![logo](/SHSlogos/com.png)

[![Static Badge](https://img.shields.io/badge/Telegram-dev%20blog-blue)](https://t.me/SmartHomeSystem_dev)

---

<a id="versions"></a>

# Versions

<details>
<summary>v0.1.0 — private beta-version.</summary>
</details>

<details>
<summary>v0.2.0 — development.</summary>
</details>

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

<details>
<summary>v2.0.0 — <b>[current]</b> intermediate version.</summary>

- Completed full-fledged project build system using CMake and Shell.
- Algorithms and containers for working with ordered data have been added.
  - Created

- Разработана система сборки, использующая CMake и sheel.
- Добавлены алгоритмы и контейнеры для работы с упорядоченными данными:
  - shs::SortedBuf — контейнер для работы с упорядоченным std::vector.
  - shs_algorithms — шаблонные функции для поиска, вставки и удаления элементов в контейнерах.
- Добавлена семантика перемещений, улучшена работа с памятью
- Global changes in SHSDTP: divided into components and expanded.
      - Divided into component classes:
        - shs::DTP — container class for linking data buses and API handlers.
        - shs::DTPbus — abstract class of a data bus that accepts and sends messages.
        - shs::DTPdiscover — class for searching for devices on a local network.
        - shs::DTPless — comparison operators (for search and sorting algorithms).
        - shs::DTPpacket — a class for creating, encrypting, and decrypting messages.
      - Tested.
- shs::ProgramTime — function names have been changed, optimized, fixed bugs, tested.
- Создан shs::SimpleFixed — a temporary implementation of fixed-point numbers for convenience.
- Network
  - Обновлен и отлажен shs::ControlWiFi.
  - Добавлен класс shs::IP для хранения и работы с IP-адресами.
  - Созданы и протестированы классы для работы с сокетами Qt:
    - shs::qt::TcpSocket
    - shs::qt::UdpSocket
  - shs::TcpServer — updated functionality, debugged, tested.
    - Automatically attach clients to shs::DTP.
    - Configure clients to delete when the connection is closed.
  shs::TcpSocket — updated functionality, debugged, tested.
    - It is based on shs::DTPbus.
    - Automatic reconnection in case of loss of connection.
    - Qt support.
  - Поддержка UDP
    - Создан класс shs::UDP, предоставляющий интерфейс для работы с UPD
    - shs::UdpBus — работа с UDP как с shs::DTPbus.
    - shs::UdpBroadcastBus — отправка и прием широковещательных сообщений.
    - shs::UdpMulticastBus — отправки и прием сообщений в группе.

- Load components — redesigned, debugged and tested.

- shs_types — developed from shs_settings_private.h.

- Sensor
  - Redesigned, debugged and tested.
    - The functionality has been changed
    - update() must be called before getting the value.
    - updateFast(), if supported by the sensor, measures less accurately, but faster.
    - Added error status.
    - Support for multiple metrics.

- Неотлаженные компоненты:
  - shs::StreamBus — it is not debugged, has bugs. Support and development is expected in the following versions.
  - shs::EventTracker — has bugs and errors.
- Неиспользуемые компоненты:
  - shs::CreateProcess — the class creates a process from function pointer templates.
  - shs::MutexSafe — component of an unused OS module.
- Недоразработанные компоненты
  - shs::Time — Unix time storage and parsing (not developed).

</details>

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

## Структура проекта

Проект выложен в репозитории на GitHub и доступен по ссылке: <https://github.com/MrRyabena/SmartHomeSystem>.</br>

<details>
<summary>See structure</summary>

- [SHSdocumentation](SHSdocumentation/) — документация к проекту.
  - [Code](SHSdocumentation/Code/) — документация к программному коду.
  - [Hardware](SHSdocumentation/Hardware/) — документация к компонентам, микроконтроллерам, техническим устройствам, а также схемы, чертежи и модели.
  - [ProjectOverview](SHSdocumentation/ProjectOverview/) — обзор проекта, особенности разработки, методы и подходы.
  - [Usage](SHSdocumentation/Usage/) — инструкции по сборке и использованию проекта.
- [libraries](libraries/) — сторонние библиотеки, используемые в проекте.
- [pitch](pitch/) — презентации проекта и вспомогательные файлы.
- [schemes](schemes/) — картинки, схемы, чертежи...
- [SHSlogos](SHSlogos/) — логотипы и символика проекта.
- [src](src/) — ПО проекта.
  - [debugging_sketches](src/debugging_sketches/) — наброски отладочных прошивок.
  - [demo_version](src/demo_version/) — демонстрационная версия проекта.
    - [app](/src/demo_version/app/) — приложение под Windows.
    - [SmartModules](/src/demo_version/SmartModules/) — прошивки модулей.
  - [SHSapp](src/SHSapp/) — приложение под windows.
  - [SHScore](src/SHScore/) — ядро (бизнес-логика), основная разработка.
  - [SHSlibrary](src/SHSlibrary/) — библиотека с удобными инструментами, основанная на ядре.
  - [SmartModules](src/SmartModules/) — [beta] устройства и модули.
  - [SmartModulesAPI](src/SmartModulesAPI/) — [beta] команды устройств и модулей.
  - [synchronizer](synchronizer/) — быстро перекидывает файлы из SHSlibrary в папку с библиотеками (для удобства разработки).

</details>

## Краткий обзор

## Благодарность

## Contacts

Tg: <https://t.me/MrRyabena></br>
Mail: <daniilrazanov82349@gmail.com></br>
_**I will be glad to receive suggestions for improving the project, cooperation, and feedback.**_</br>
Daniil Ryazanov (Даниил Рязанов)</br>
_Saint-Petersburg, 2025_</br>

# Заключение

_**Smart Home System**_ — масштабный проект, предлагающий удобные решения и инструменты в современной реализации. В скором времени пользоваться разработками будет удобно и легко даже пользователю, не владеющему навыками программирования и проектирования.</br>

У проекта большой простор для развития и расширения. Впереди полно работы и многие инструменты недоработаны, но уже сейчас на базе _**Smart Home System**_ можно создавать автоматизированные системы.</br>

Подготовив линейку модулей и пользовательские интерфейсы, можно наладить коммерческое производство модульных систем.</br>

Многие инструменты в проекте поддерживают индивидуальную работу, поэтому _**Smart Home System**_ можно использовать в отдельных проектах и устройствах, ускорив процесс их создания.
