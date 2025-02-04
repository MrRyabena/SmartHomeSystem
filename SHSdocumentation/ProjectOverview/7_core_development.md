
# 7. Этап II. Проектирование ядра (бизнес-логики)

[SHScore](src/SHScore/) — логика работы системы, основанная на парадигме **ООП** и принципах **SOLID**. В ядре описаны абстрактные классы для оперируемых системой объектов и процессов, а также обработчики для них, протоколы связи и передачи данных. Ядро дискретизирует и описывает действия системы, что позволяет быстро и удобно создавать и изменять конфигурацию системы и последующие классы высокого уровня (библиотеки для конкретных задач).</br>

Конечно, парадигма ООП с длинными цепочками наследования, виртуальными функциями и указателями расходует гораздо больше памяти и вычислительных ресурсов, чем функциональная. Такой выбор сделан намерено, с учетом того, что система разбита на большое количество модулей и каждый микроконтроллер будет содержать небольшое количество оперируемых объектов. Зато ООП позволяет организовать систему очень удобно, быстро и без лишнего дублирования кода.

![SHScore-scheme](schemes/SHScore-scheme.png)

<a id="7-1_containers"></a>

## 7.1 Containers

<a id="7-1-1_ByteCollector"></a>

### 7.1.1 ByteCollector

Для удобной упаковки данных в массив байтов и дальнейшей их обработки разработан легкий класс: [SHSByteCollector.h](src/SHScore/SHSByteCollector.h).</br>

Класс используется в протоколах передачи данных и API.</br>

```c++
class shs::ByteCollector
{
public:
    uint8_t *buf{};      // array
    uint8_t *ptr{};      // current position
    uint8_t *readPtr{};  // read position

    explicit ByteCollector(uint8_t size);

    /*
      The bytes argument specifies how many bytes
      to write from the passed type.

      int value = 1000;
      bc.add(value, 2);  // will add 2 bytes
      bc.size();         // will return 2, not 4!

      bc.add(value);     // will add sizeof(value)
      bc.size();         // will return 6

    */
    // add to the end
    template <typename T>
    void add(const T &value, uint8_t bytes = sizeof(T));

    // add to the beginning
    template <typename T>
    void addBefore(const T &value, uint8_t bytes = sizeof(T));

    // unpack data
    template <typename T>
    void get(T &var, uint8_t bytes = sizeof(T))

    // reserve bytes for more size
    void reserve(uint8_t size);
    void reserveBefore(uint8_t size)

    uint16_t size();
};

```

<a id="7-1-2_Handlers"></a>

### 7.1.2 Handlers

Классы-контейнеры для обработчиков процессов. Они позволяют оперировать несколькими объектами как одним, что дает возможность легко масштабировать систему, без вмешательства в логику обработки данных.</br>

- [ProcessesKeeper](src/SHScore/SHSProcessesKeeper.h) — позволяет добавлять различные процессы, например, опросы датчиков, циклические вычисления, парсинг сайтов...</br>

  ```c++
  class shs::ProcessesKeeper : public shs::Process
  {
  public:
      explicit ProcessesKeeper();

      void attach(shs::Process *object);
      void detach(shs::Process*object);

      void begin();
      void tick();
      void end();

  protected:
      std::vector<shs::Process *> m_ptrs;
      uint8_t m_find(const shs::Process*object);
  };
  ```

- [CallbacksKeeper](src/SHScore/SHSCallbacksKeeper.h) — в него добавляются API датчиков и модулей, которые вызываются при поступлении новых данных.

  ```c++
  class shs::CallbacksKeeper
  {
  public:
      explicit CallbacksKeeper() {}

      void attach(shs::API *object);
      void detach(shs::API *object);

      uint8_t handler(shs::ByteCollector &data);

  protected:
      std::vector<shs::API *> m_ptrs;
      uint8_t m_find(shs::API *object);
  };
  ```

- [SensorsKeeper](src/SHScore/SHSSensorsKeeper.h) — хранит набор датчиков и позволяет вызывать методы конкретного датчика по ID.

  ```c++
  class shs::SensorsKeeper : public Sensor
  {
  public:
      explicit SensorsKeeper();
      void attach(shs::Sensor *object);
      void detach(shs::Sensor *object);

      void setup() override;

      uint8_t find(const shs::settings::shs_ID_t ID);

      int16_t getValueI(const shs::settings::shs_ID_t ID) override;
      shs::settings::shs_float_t getValueF(const shs::settings::shs_ID_t ID) override;
      shs::settings::shs_double_t getValueD(const shs::settings::shs_ID_t ID) override;

      int16_t getAverageI(const shs::settings::shs_ID_t ID) override;
      shs::settings::shs_float_t getAverageF(const shs::settings::shs_ID_t ID) override;
      shs::settings::shs_double_t getAverageD(const shs::settings::shs_ID_t ID) override;

  protected:
      std::vector<shs::Sensor *> m_ptrs;
      uint8_t m_find(const shs::Sensor *object);
  };
  ```

- [LoadKeeper](src/SHScore/SHSLoadKeeper.h) — аналогично SensorsKeeper управляет нагрузками.

  ```c++
   class shs::LoadKeeper : public shs::Load
  {
  public:
      explicit LoadKeeper();

      void attach(shs::Load *object);
      void detach(shs::Load *object);

      uint8_t find(shs::settings::shs_ID_t ID);

      void setup() override;

      void on(const uint8_t value = 255, const uint8_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;
      void on(const uint16_t value = UINT16_MAX, const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;

      void off(const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;


  protected:
      std::vector<shs::Load *> m_ptrs;
      uint8_t m_find(const shs::Load *object);
  };
  ```

<a id="7-2_protocols"></a>

## 7.2 Protocols

<a id="7-2-1_SHSDTP"></a>

### 7.2.1 SHSDTP

**Smart Home System Data Transmission Protocol** — единый протокол передачи данных, разработанный для передачи информации между всеми модулями. Идея взята из [GyverBus](https://github.com/GyverLibs/GyverBus).</br>

Для отправки данные нужно обработать, а потом распаковать обратно, для этого создан [SHSdtp.h](src/SHScore/SHSdtp.h). Он добавляет к пакету данные об отправителе и получателе, общее количество байт и CRC. Затем данные отправляются любым способом, основанным на классе `Stream`. Если не используется стандартная библиотека `<Arduino.h>`, то класс `Stream` необходимо реализовать отдельно, унаследовавшись от абстрактного класса [shs::Stream](src/SHScore/SHSStream.h):

```c++
class shs::Stream
{
public:
    virtual uint8_t write(const uint8_t *buf, uint16_t size) = 0;
    virtual uint8_t read() = 0;
    virtual uint8_t available() = 0;
};
```

В конструкторе `DTP` принимает указатель на объект `Stream`.

```c++
/*
  Smart Home System Data Transmission Protocol

  The idea is taken from https://github.com/GyverLibs/GyverBus
*/

/*
  WARNING! It is necessary to include Stream-class befor this file.
  If the <Arduino.h> is not used, you need to create your own class inherited from
  abstract class shs::Stream (SHSStream.h)
*/

namespace shs::settings
{
#ifndef SILENCE_TIMEOUT
#define SILENCE_TIMEOUT 120000
#endif

    inline const uint8_t DTP_OFFSETbeg = 5;
};

namespace shs
{
    namespace DTPcommands
    {
        enum DTPcommands : uint8_t;
    };

    namespace DTPhandlerStatus
    {
        enum DTPhandlerStatus : uint8_t;
    };

    struct DTPdata;
    class DTP;
    class DTPpacker;
    typedef void (*DTPhandler_t)(shs::DTPdata &);

};

enum shs::DTPcommands::DTPcommands : uint8_t
{
    answer = 252,
    error,
    request,
};

struct shs::DTPdata
{
    shs::settings::shs_ModuleID_t to{};
    shs::settings::shs_ModuleID_t from{};
    shs::settings::shs_ID_t apiID{};
    uint8_t datasize{};
};

/*
  ----------------------------------------
  DTPpacker
  ----------------------------------------
*/
class shs::DTPpacker
{
public:
    // uint8_t packDTP(shs::ByteCollector *bc, const uint8_t to, const int16_t apiID);
    uint8_t packDTP(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to, const shs::settings::shs_ID_t apiID, const shs::settings::shs_ModuleID_t from);
    uint8_t checkDTP(shs::ByteCollector *bc);
    uint8_t parseDTP(shs::ByteCollector *bc, shs::DTPdata &data);

protected:
    shs::CRC8 _crc;
};

/*
  ----------------------------------------
  DTP
  ----------------------------------------
*/
class shs::DTP : public shs::DTPpacker, public shs::CallbacksKeeper
{
public:
    explicit DTP(Stream *bus, const shs::settings::shs_ModuleID_t ID);
    ~DTP();

    uint8_t tick();
    uint8_t checkBus(uint8_t len = UINT8_MAX);

    uint8_t sendPacket(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to);
    uint8_t sendPacket(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to, const shs::settings::shs_ID_t api_ID, const shs::settings::shs_ModuleID_t from);
};
```

<a id=7-2-2_SHSF></a>

### 7.2.2 SHSF

_**Smart Home System File**_ — протокол записи данных в файл, а так же само расширение файла (.shsf). Содержит инструменты для записи, сжатия, чтения данных, сохранения настроек и конфигураций.</br>

_В данной версии проекта имеются наброски, но реализация еще не готова._

<a id="7-2-3_tcpip"></a>

### 7.2.3 TCP/IP

Для передачи данных по WiFi используется протокол TCP/IP. Для системы хватает стандартной реализации протокола в ядрах esp, однако для удобства добавлены расширения.</br>

[SHSTcpClient.h](src/SHScore/SHSTcpClient.h) и [SHSTcpServer.h](src/SHScore/SHSTcpServer.h) упрощают процессы подключения и опроса входящих потоков.

```c++
class shs::TcpServer
{
public:
    WiFiServer server;
    WiFiClient *clients;
    shs::DTP *dtp{};

    const uint8_t *IP{};
    uint8_t maxClients{};

    TcpServer(const uint8_t *IPaddress, uint16_t port = 50000, uint8_t max_clients = 6);
    ~TcpServer();

    void begin();
    void tick();

    uint8_t sendPacket(shs::ByteCollector *bc, const shs::settings::shs_ModuleID_t to,
                             const shs::settings::shs_ID_t api_ID);
};
```

<a id="7-3_system"></a>

## 7.3 System

<a id="7-3-1_Process"></a>

## 7.3.1 Process

[SHSProcess.h](src/SHScore/SHSProcess.h) — абстрактный класс, описывающий интерфейс процессов в системе:

- `begin()` — вызывается один раз во время конфигурации процесса (например, блок `setup`).
- `tick()` — постоянно вызывается в цикле программы.
- `end()` — вызывается для завершения процесса.

```c++
class shs::Process
{
public:
    virtual void begin() = 0;
    virtual void tick() = 0;
    virtual void end() = 0;
};
```

<a id="7-3-2_sensor"></a>

### 7.3.2 Sensor

- Класс `shs::Sensor` ([SHSSensor.h](src/SHScore/SHSSensor.h)) является абстрактным и описывает интерфейс для получения значений с датчиков. В `type` хранится тип датчика, которых с развитием поддерживаемых системой устройств может быть несколько десятков.</br>

- В классе `shs::SensorAnalog` ([SHSSensorAnalog.h](src/SHScore/SHSSensorAnalog.h)) реализованы методы считывания значений с аналоговых выводов микроконтроллера и подсчет среднего значения из выборки измерений.</br>

На основе этих классов в [SHSlibrary](src/SHSlibrary/) разрабатываются классы для конкретных моделей датчиков, расширяя набор поддерживаемых устройств.

```c++
// SHSsensor.h
enum shs::SensorType::SensorType : uint8_t
{
    unknown,
    analogPin,
    thermistor,
    photoresistor,
};

class shs::Sensor
{
public:
    shs::SensorType::SensorType type{};

public:
    explicit Sensor(const shs::settings::shs_ID_t ID = 0, const shs::SensorType::SensorType stype = shs::SensorType::unknown);

    void setID(const shs::settings::shs_ID_t ID);
    shs::settings::shs_ID_t getID() const;

    virtual void setup() = 0;

    virtual int16_t getValueI(const shs::settings::shs_ID_t ID = 0) = 0;
    virtual shs::settings::shs_float_t getValueF(const shs::settings::shs_ID_t ID = 0) = 0;
    virtual shs::settings::shs_double_t getValueD(const shs::settings::shs_ID_t ID = 0) = 0;

    virtual int16_t getAverageI(const shs::settings::shs_ID_t ID = 0) = 0;
    virtual shs::settings::shs_float_t getAverageF(const shs::settings::shs_ID_t ID = 0) = 0;
    virtual shs::settings::shs_double_t getAverageD(const shs::settings::shs_ID_t ID = 0) = 0;

protected:
    shs::settings::shs_ID_t m_sensorID{};
};

// SHSSensorAnalog.h
class shs::SensorAnalog : public shs::Sensor
{
public:
    explicit SensorAnalog(const shs::settings::shs_ID_t ID = 0, const shs::SensorType::SensorType stype = shs::SensorType::unknown, const uint8_t pin = A0);

    void setup() override;
    shs::settings::shs_float_t getValueF(const shs::settings::shs_ID_t ID = 0) override;
    shs::settings::shs_double_t getValueD(const shs::settings::shs_ID_t ID = 0) override;
    int16_t getValueI(const shs::settings::shs_ID_t ID = 0) override;

    shs::settings::shs_float_t getAverageF(const shs::settings::shs_ID_t ID = 0) override;
    shs::settings::shs_double_t getAverageD(const shs::settings::shs_ID_t ID = 0) override;
    int16_t getAverageI(const shs::settings::shs_ID_t ID = 0) override;

protected:
    uint8_t m_pin{};
    uint16_t m_getSamplesSum(const uint8_t count = shs::settings::SENSOR_AVERAGE_SAMPLES);
};
```

<a id="7-3-3_load"></a>

### 7.3.3 Load

[SHSLoad.h](src/SHScore/SHSLoad.h) — абстрактный класс, описывающий интерфейс взаимодействия с нагрузками.</br>

_**Smart Home System**_ предлагает на выбор 3 режима управления нагрузкой:

- `SWITCH` — нагрузку можно только полностью включить или полностью выключить.
- `PWM` — можно управлять мощностью нагрузки в сети постоянного тока с помощью ШИМ.
- `DIMMER` — аналог ШИМ для сети переменного тока.

Параметр `smothing` работает только для режимов `PWM` и `DIMMER`. Это коэффициент, устанавливающий скорость изменения управляющего сигнала, например, для плавного регулирования света. Коэффициент задает время, за которое значение `value` нагрузки будет увеличено на 1.</br>

Для работы `smoothing` необходимо передать в класс объект типа `shs::ProcessesKeeper*`. Когда потребуется выполнить сглаживание, класс сам добавится, а затем удалится из массива keeper'а.

```c++
enum shs::LoadType::LoadType : uint8_t
{
    UNKNOWN,
    SWITCH,
    PID,
    PWM,
    DIMMER,
};

class shs::Load
{
public:
    shs::LoadType::LoadType type;

public:
    explicit Load(shs::settings::shs_ID_t ID = 0, shs::LoadType::LoadType ltype = shs::LoadType::UNKNOWN);

    void setID(const shs::settings::shs_ID_t ID);
    shs::settings::shs_ID_t getID() const;

    virtual void setup() = 0;

    virtual void on(const uint8_t value = 255, const uint8_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) = 0;
    virtual void on(const uint16_t value = UINT16_MAX, const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) = 0;

    virtual void off(const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) = 0;

protected:
    shs::settings::shs_ID_t m_loadID{};
}
```

<a id="7-3-4_errorshandler"></a>

### 7.3.4 ErrorsHandler

В класс `shs::ErrorsHandler` ([SHSErrorsHandler](src/SHScore/SHSErrorsHandler.h)) передаются коды ошибок, которые обрабатываются подключенными обработчиками.</br>

Класс рассчитан на два обработчика: первый используется системой, второй — пользователем. Возможно, в будущем будет рассчитан на любое число обработчиков.</br>

Коды всех ошибок находятся в отдельном файле [SHSerrors.h](src/SHScore/SHSerrors.h). При необходимости, `enum shs::errors::Errors` может быть дополнено пользователем.

```c++
class shs::ErrorsHandler
{
public:
    ErrorsHandler(shs::errorsCallback_t system_callback = nullptr,
    shs::errorsCallback_t user_callback = nullptr);

    void attachFirstHandler(shs::errorsCallback_t callback);
    void attachSecondHandler(shs::errorsCallback_t callback);

    void error(const shs::errors::Errors error);

    [[nodiscard]] shs::errors::Errors getLastError();
    [[nodiscard]] uint8_t getCount();
};
```

<a id="7-3-5_settings"></a>

### 7.3.5 Settings

Все настройки обернуты в `namespace shs::settings`. Файл [SHSsettings.h](src/SHScore/SHSsettings.h) является пользовательским шаблоном настроек. Там можно разово задать общие параметры для всей системы. В файл [SHSsettings_private.h](src/SHScore/SHSsettings_private.h) рекомендуется не вносить изменения, во избежание некорректной работы системы.

<a id="7-4_algorithms"></a>

## 7.4 Algorithms

Для обработки информации в системе потребуется разработать много легких и эффективных алгоритмов: сортировка и сжатие данных, поиск и оптимизация хранения, собсвтенные аллокаторы для работы с памятью, хеш-функции и пр.

<a id="7-4-1_CRC"></a>

### 7.4.1 CRC

Циклическая контрольная сумма — очень важный алгоритм для проверки целостности данных при передаче или хранении в файле.</br>

Ядро предлагает реализацию самых удобных и востребованных для _**Smart Home System**_ типов на 8, 16 и 32-bit.</br>

_Ниже приведен класс для CRC-32, остальные организованы полностью аналогично, см. [SHSCRC.h](src/SHScore/SHSCRC.h)._

```c++
namespace shs
{
    class CRC8;
    class CRC16;
    class CRC32;

    const uint8_t CRC8_beg = 0x00;
    const uint16_t CRC16_beg = 0xFFFF;
    const uint32_t CRC32_beg = 0x00000000;
};

class shs::CRC32
{
public:
    uint32_t crc{};
    explicit CRC32() : crc(shs::CRC32_beg) {}

    void add(const uint8_t value);
    void clear();

    void update(uint32_t &crc, uint8_t data);
    uint32_t crcBuf(const uint8_t *ptr, uint16_t size);
};
```