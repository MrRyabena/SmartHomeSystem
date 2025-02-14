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
#include "gs_config.h"

class SHS : public QObject
{
    Q_OBJECT
public:
    explicit SHS(QObject* parent = nullptr) : QObject(parent), m_dtp(THIS_ID),  m_discover(THIS_ID), m_load(THIS_ID, LOAD_ID, m_dtp), m_sensor(THIS_ID, SENSOR_ID, m_dtp)
    {
         start();
    }

    ~SHS() = default;

    void start();
    void tick();
    void stop()  {} // m_dtp.stop(); }


    Q_INVOKABLE double getSensorValue() { return m_sensor.getValueD(); }


signals:
    void sensorUpdated();

public slots:
    void onSwitchToggled(bool checked) {
        if (checked) {
            m_load.on();
        } else {
            m_load.off();
       }
    }
    void timerEvent(QTimerEvent *event) override { tick(); }


private:
    Q_PROPERTY(double sensorValue READ getSensorValue NOTIFY sensorUpdated)

    static constexpr auto THIS_ID = shs::config::Module_3::MODULE_ID;
    static constexpr auto LOAD_ID = shs::t::shs_ID_t(shs::config::Module_2::MODULE_ID, shs::config::Module_2::LOAD);
    static constexpr auto SENSOR_ID = shs::t::shs_ID_t(shs::config::Module_1::MODULE_ID, shs::config::Module_1::THERM_SENSOR);

    shs::t::shs_IP_t HOST_IP;
    static constexpr shs::t::shs_port_t PORT = shs::settings::DEFAULT_TCP_PORT;

   shs::DTP m_dtp;
   shs::DTPdiscover m_discover;
   shs::LoadVirtual m_load;
   shs::SensorVirtual m_sensor;
   shs::ProgramTime m_sens_timer;
   bool m_sens_update;

};
