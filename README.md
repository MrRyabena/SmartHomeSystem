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
