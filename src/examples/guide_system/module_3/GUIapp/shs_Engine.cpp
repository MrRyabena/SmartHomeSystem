#include "shs_Engine.h"


void Engine::start()
{
    m_discover.start();
    m_dtp.attachAPI(&m_sensor);
    m_dtp.start();

    startTimer(50);
}


void Engine::tick()
{
    m_dtp.tick();
    m_discover.tick();

    if (m_sens_timer.seconds() >= 1)
    {
        if (m_sensor_connected)
        {
            m_sensor.update();
            m_sens_update = true;
        }
        m_sens_timer.reset();
    }

    if (m_check_connection_timer.seconds() >= 4)
    {
        if (!m_load_connected)
        {
            m_load_connected = m_checkModuleConnection(LOAD_ID);
            emit loadConnectionSignal();
        }

        if (!m_sensor_connected)
        {
            m_sensor_connected = m_checkModuleConnection(SENSOR_ID);
            emit sensorConnectionSignal();
        }

        m_check_connection_timer.reset();
    }

    if (m_sens_update && m_sensor.isUpdated()) { emit sensorUpdated(); m_sens_update = false; }
}


bool Engine::m_checkModuleConnection(const shs::t::shs_ID_t moduleID)
{
    auto ip = m_discover.check(moduleID.getModuleID());

    if (!ip) { m_discover.discover(moduleID.getModuleID()); return false; }

    auto tcp_bus = std::make_unique<shs::TcpSocket>(ip, shs::settings::DEFAULT_TCP_PORT, m_dtp.getUniqueBusID());
    tcp_bus->connected_modules.attach(moduleID.getModuleID());
    m_dtp.attachBus(std::move(tcp_bus));

    return true;
}
