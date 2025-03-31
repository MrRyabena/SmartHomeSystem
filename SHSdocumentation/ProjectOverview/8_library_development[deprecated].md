# 8. Этап III. Разработка библиотеки

[SHSlibrary](src/SHSlibrary/) — следующий уровень программной архитектуры _**Smart Home System**_. Библиотека реализует более функциональные и направленные решения, API к устройствам и библиотекам.</br>

Пока что большая часть библиотеки находится в разработке. Сейчас в ней представлен класс [SHSAutoProcesses](src/SHSlibrary/SHSAutoProcesses.h), позволяющий выполнять автоматическую конфигурацию и управление модулем.</br>

Позже в библиотеку будут добавлены классы для работы с датчиками, более продвинутые модели API, инструменты конфигурации и сохранения системы, обработки с файлов и данных.

```c++
class shs::AutoProcesses : public shs::Process
{
public:
    WiFiClient tcp;
    shs::DTP dtp;
    shs::LoadAPIhandler loadAPI;
    shs::SensorAPIhandler sensorsAPI;

    explicit AutoProcesses();

    void begin() override;
    void tick() override;
    void end() override;
};
```
