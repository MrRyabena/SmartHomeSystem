#pragma once

#include <memory>

#include <QObject>
#include <QDebug>
#include <QHostAddress>
#include <QHostInfo>

#include <shs_settings_private.h>
#include <shs_types.h>

#include <shs_APIids.h>
#include <shs_Network>
#include <shs_DTP>
#include <shs_Load>
#include <shs_Sensor>
#include <gs_config.h>


class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject* parent = nullptr) : QObject(parent), m_dtp(THIS_ID), m_discover(THIS_ID), m_load(THIS_ID, LOAD_ID, m_dtp), m_sensor(THIS_ID, SENSOR_ID, m_dtp)
    {
        start();
    }

    ~Engine() = default;

    void start();
    void tick();
    void stop() {}


    Q_INVOKABLE double   getSensorValue() { return m_sensor.getValueD(); }
    Q_INVOKABLE bool getSensorConnected() { return m_sensor_connected; }
    Q_INVOKABLE bool   getLoadConnected() { return m_load_connected; }


signals:
    void sensorUpdated();
    void sensorConnectionSignal();
    void loadConnectionSignal();


public slots:
    void onSwitchToggled(bool checked) { checked ? m_load.on() : m_load.off(); }
    void timerEvent([[maybe_unused]] QTimerEvent* event) override { tick(); }


private:
    Q_PROPERTY(double sensorValue READ getSensorValue NOTIFY sensorUpdated);
    Q_PROPERTY(bool sensorConnected READ getSensorConnected NOTIFY sensorConnectionSignal);
    Q_PROPERTY(bool loadConnected READ getLoadConnected NOTIFY loadConnectionSignal);

    bool m_checkModuleConnection(const shs::t::shs_ID_t moduleID);

    static constexpr auto THIS_ID = shs::config::Module_3::MODULE_ID;
    static constexpr auto LOAD_ID = shs::t::shs_ID_t(shs::config::Module_2::MODULE_ID, shs::config::Module_2::LOAD);
    static constexpr auto SENSOR_ID = shs::t::shs_ID_t(shs::config::Module_1::MODULE_ID, shs::config::Module_1::THERM_SENSOR);
    static constexpr shs::t::shs_port_t PORT = shs::settings::DEFAULT_TCP_PORT;

    shs::DTP m_dtp;
    shs::DTPdiscover m_discover;

    shs::LoadVirtual m_load;
    bool m_load_connected{};

    shs::SensorVirtual m_sensor;
    bool m_sensor_connected{};

    shs::ProgramTime m_check_connection_timer;
    shs::ProgramTime m_sens_timer;
    bool m_sens_update{};
};
