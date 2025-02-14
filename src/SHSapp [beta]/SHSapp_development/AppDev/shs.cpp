#include "shs.h"


void SHS::start()
{

    m_discover.start();
    m_discover.discover(LOAD_ID.getModuleID());
    m_discover.discover(SENSOR_ID.getModuleID());

    auto load_IP = m_discover.discoverWait(LOAD_ID.getModuleID(), 2000);
    qDebug() << "load ip:    " << QHostAddress(static_cast<uint32_t>(load_IP)).toString();
    auto sensor_IP = m_discover.discoverWait(SENSOR_ID.getModuleID(), 5000);
    qDebug() << "sensor ip:  " << QHostAddress(static_cast<uint32_t>(sensor_IP)).toString();

    auto tcp_bus = std::make_unique<shs::TcpSocket>(load_IP, shs::settings::DEFAULT_TCP_PORT, m_dtp.getUniqueBusID());
    tcp_bus->connected_modules.attach(LOAD_ID.getModuleID());
    m_dtp.attachBus(std::move(tcp_bus));

    tcp_bus = std::make_unique<shs::TcpSocket>(sensor_IP, shs::settings::DEFAULT_TCP_PORT, m_dtp.getUniqueBusID());
    tcp_bus->connected_modules.attach(SENSOR_ID.getModuleID());
    m_dtp.attachBus(std::move(tcp_bus));

    m_dtp.attachAPI(&m_sensor);

    qDebug() << SENSOR_ID.getModuleID() << SENSOR_ID.getDeviceID();


    m_dtp.start();

    startTimer(50);
}


void SHS::tick()
{
    m_dtp.tick();

    if (m_sens_timer.seconds() >= 5)
    {
        m_sensor.update();
        m_sens_update = true;
        m_sens_timer.reset();
       // qDebug() << "tick";
    }

    if (m_sens_update && m_sensor.isUpdated()) { emit sensorUpdated(); m_sens_update = false; qDebug() << m_sensor.getValueI(); }

}

