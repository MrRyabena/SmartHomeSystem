# Project Overview

> [!NOTE]
> Часть документации в этом разделе, помеченная `[deprecated]` является устаревший. В основном это касается программной части. Подробная документация по ядру (`SHScore`) и другим компонентам кода находится в разделе [Code](../Code/).

> [!IMPORTANT]
> Вместо устаревшей (`[deprecated]`) документации следует ознакомиться с работой [SmartHomeSystem_conference_report.docx](../docs/SmartHomeSystem_conference_report.docx). В ней представлен полный обзор проекта с актуальной информацией. Частично повторяет некоторые разделы документации.

# Содержание

- [1. Введение](1_introduction.md)
  - 1.1 Микроэлектроника уже повсюду
  - 1.2 Актуальность и обоснование проекта
  - 1.3 Цели и задачи
- [2. Обзор литературы](2_literature.md)
  - 2.1 Alex Gyver
  - 2.2 Виктор Петин
  - 2.3 Нил Кэмерон
  - 2.4 Макс Шлее
  - 2.5 Яцек Галовиц
- [3. Структура проекта]()
- [4. Методы и этапы проектирования](4_development_methods.md)
  - 4.1 Принцип работы
  - 4.2 Этапы разработки
  - 4.3 Подход к проектированию
  - 4.4 Функции
  - 4.5 Структура Smart Home System
- [5. Выбор компонентов](../Hardware/) (в разделе [Hardware]())
  - [5.1 Микроконтроллеры](../Hardware/microcontrollers.md)
    - 5.1.1 Atmega328P
    - 5.1.2 ESP8266
    - 5.1.3 ESP32
  - [5.2 Датчики](../Hardware/sensors.md)
    - 5.2.1 Temperature
    - 5.2.2 Humidity
    - 5.2.3 Pressure
    - 5.2.4 Carbon dioxide
    - 5.2.5 Illumination
    - 5.2.6 Other
  - [5.3 Силовые компоненты](../Hardware/power_components.md)
    - 5.3.1 Транзисторы
    - 5.3.2 Симисторы
  - [5.4 Обвязка](../Hardware/electronic_components.md)
    - 5.4.1 Резисторы
    - 5.4.2 Конденсаторы
    - 5.4.3 Диоды
    - 5.4.4 Стабилитроны
    - 5.4.5 Стабилизаторы напряжения
    - 5.4.6 Оптопары (оптроны)
    - 5.4.7 Регистры
- [6. Этап I. Проектирование автоматических модулей `[deprecated]`]()
  - 6.1 Module `[deprecated]`
  - 6.2 Server `[deprecated]`
    - 6.2.1 Основные требования к серверу(#6-2-1_server_requirements)
  - 6.3 Управление нагрузкой `[deprecated]`
    - 6.3.1 Силовые схемы `[deprecated]`
    - 6.3.2 Режим `SWITCH` `[deprecated]`
    - 6.3.3 Режим `PWM` `[deprecated]`
    - 6.3.4 Режим `DIMMER` `[deprecated]`
    - 6.3.5 Режим `PID` `[deprecated]`
  - 6.4 Датчики `[deprecated]`
    - 6.4.1 Кнопка, энкодер, потенциометр `[deprecated]`
    - 6.4.2 Термистор и фоторезистор `[deprecated]`
    - 6.4.3 Термопара `[deprecated]`
    - 6.4.4 DS18B20 `[deprecated]`
    - 6.4.5 HTU21D `[deprecated]`
    - 6.4.6 BME280/BMP280 `[deprecated]`
    - 6.4.7 MH-Z19b `[deprecated]`
    - 6.4.8 HX711 `[deprecated]`
- [7. Этап II. Проектирование ядра (бизнес-логики)`[deprecated]`]()
  - 7.1 Containers `[deprecated]`
    - 7.1.1 ByteCollector `[deprecated]`
    - 7.1.2 Handlers `[deprecated]`
  - 7.2 Protocols `[deprecated]`
    - 7.2.1 SHSDTP `[deprecated]`
    - 7.2.2 SHSF `[deprecated]`
    - 7.2.3 TCP/IP `[deprecated]`
  - 7.3 System `[deprecated]`
    - 7.3.1 Process `[deprecated]`
    - 7.3.2 Sensor `[deprecated]`
    - 7.3.3 Load `[deprecated]`
    - 7.3.4 ErrorsHandler `[deprecated]`
    - 7.3.5 Settings `[deprecated]`
  - 7.4 Algorithms `[deprecated]`
    - 7.4.1 CRC `[deprecated]`
- [8. Этап III. Разработка библиотеки `[deprecated]`]()
- [9. Этап IV. Объединение модулей в единую систему `[deprecated]`]()
  - 9.1 Организация соединения `[deprecated]`
  - 9.1.2 Подключение модулей `[deprecated]`
  - 9.1.3 TCP/IP `[deprecated]`
  - 9.2 API `[deprecated]`
- [10. Этап V. Взаимодействие с пользователем `[deprecated]`]()
  - 10.1 Кнопки и датчики `[deprecated]`
  - 10.2 Telegram bot `[deprecated]`
  - 10.3 Приложение `[deprecated]`
  - 10.4 Голосовое управление `[deprecated]`
- [11. Этап VI. Обучение системы саморегулированию `[deprecated]`]()
  - 11.1 Алгоритмы поведения системы `[deprecated]`
    - 11.1.1 Автоматизация на основе датчиков `[deprecated]`
    - 11.1.2 Модели и режимы поведения `[deprecated]`
    - 11.1.3 Автоматический выбор режима `[deprecated]`
  - 11.2 SHSNeuralNet `[deprecated]`
    - 11.2.1 Оригинальное устройство SHSNeuralNet `[deprecated]`
    - 11.2.2 Реализация в Smart Home System `[deprecated]`
    - 11.2.3 Управление системой `[deprecated]`
    - 11.2.4 Предсказание событий `[deprecated]`
  - 11.3 AdvancedNeuralNet `[deprecated]`
- [12. Этап VII. Настройка системы `[deprecated]`]()
  - 12.1 Настройка на уровне ядра `[deprecated]`
    - 12.1.1 SHSsettings.h `[deprecated]`
    - 12.1.2 SHSsettings_private.h `[deprecated]`
    - 12.2 Конфигурация системы `[deprecated]`
- [13. Resources `[deprecated]`]()
  - 13.1 Уроки и гайды `[deprecated]`
  - 13.2 Документация и библиотеки `[deprecated]`
  - 13.3 Поиск компонентов `[deprecated]`


