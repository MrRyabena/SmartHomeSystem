#include "SHSSensorAPI.h"

/*
  ----------------------------------------
  SensorAPIvirtual
  ----------------------------------------
*/

shs::SensorAPIvirtual::SensorAPIvirtual(const shs::settings::shs_ID_t apiID, const shs::settings::shs_ModuleID_t to)
    : ::shs::API(apiID, to), ::shs::Sensor(apiID) {}

int16_t shs::SensorAPIvirtual::getValueI(const shs::settings::shs_ID_t ID)
{
    m_prepareCommand(ID, shs::SensorAPIcmds::getValueI);
    return 0;
}

shs::settings::shs_float_t shs::SensorAPIvirtual::getValueF(const shs::settings::shs_ID_t ID)
{
    m_prepareCommand(ID, shs::SensorAPIcmds::getValueF);
    return 0;
}

shs::settings::shs_double_t shs::SensorAPIvirtual::getValueD(const shs::settings::shs_ID_t ID)
{
    m_prepareCommand(ID, shs::SensorAPIcmds::getValueD);
    return 0;
}

int16_t shs::SensorAPIvirtual::getAverageI(const shs::settings::shs_ID_t ID)
{
    m_prepareCommand(ID, shs::SensorAPIcmds::getAverageI);
    return 0;
}

shs::settings::shs_float_t shs::SensorAPIvirtual::getAverageF(const shs::settings::shs_ID_t ID)
{
    m_prepareCommand(ID, shs::SensorAPIcmds::getAverageF);
    return 0;
}

shs::settings::shs_double_t shs::SensorAPIvirtual::getAverageD(const shs::settings::shs_ID_t ID)
{
    m_prepareCommand(ID, shs::SensorAPIcmds::getAverageD);
    return 0;
}

/*
  ----------------------------------------
  PRIVATE/PROTECTED
  ----------------------------------------
*/

void shs::SensorAPIvirtual::m_prepareCommand(const shs::settings::shs_ID_t ID, const shs::SensorAPIcmds::SensorAPIcmds command)
{
    shs::ByteCollector bc(3);
    bc.add(ID, 2);
    bc.add(command, 1);
    shs::module.sendPacket(&bc, m_to, m_apiID);
}

/*
  ----------------------------------------
  SensorAPIhandler
  ----------------------------------------
*/

shs::SensorAPIhandler::SensorAPIhandler(const shs::settings::shs_ID_t apiID, const shs::settings::shs_ModuleID_t to,
                                        shs::Sensor *sensors)
    : ::shs::API(apiID, to), m_sensors(sensors) {}

uint8_t shs::SensorAPIhandler::handler(shs::ByteCollector &data)
{
    data.readPtr = data.buf + 3;
    shs::settings::shs_ID_t apiID{};
    data.get(apiID, 2);

    if (apiID != m_apiID)
        return 1;

    if (!m_sensors)
        return 2;

    shs::settings::shs_ID_t ID;
    shs::SensorAPIcmds::SensorAPIcmds cmd{};

    data.get(ID, 2);
    data.get(cmd, 1);

    switch (cmd)
    {
        namespace cmd = shs::SensorAPIcmds;

    [[likely]] case cmd::getValueI:
    {
        int16_t value{};
        value = m_sensors->getValueI(ID);
        m_prepareAnswer(ID, cmd::retValueI, value);
    }
    break;

    case cmd::getValueF:
    {
        shs::settings::shs_float_t value{};
        value = m_sensors->getValueF(ID);
        m_prepareAnswer(ID, cmd::retValueF, value);
    }
    break;

    [[unlikely]] case cmd::getValueD:
    {
        shs::settings::shs_double_t value{};
        value = m_sensors->getValueD(ID);
        m_prepareAnswer(ID, cmd::retValueD, value);
    }
    break;

    [[likely]] case cmd::getAverageI:
    {
        int16_t value{};
        value = m_sensors->getAverageI(ID);
        m_prepareAnswer(ID, cmd::retAverageI, value);
    }
    break;

    case cmd::getAverageF:
    {
        shs::settings::shs_float_t value{};
        value = m_sensors->getAverageF(ID);
        m_prepareAnswer(ID, cmd::retAverageF, value);
    }
    break;

    case cmd::getAverageD:
    {
        shs::settings::shs_double_t value{};
        value = m_sensors->getAverageD(ID);
        m_prepareAnswer(ID, cmd::retAverageD, value);
    }
    break;

    default:
        return 3;
        break;
    }

    return 0;
}

/*
  ----------------------------------------
  PRIVATE/PROTECTED
  ----------------------------------------
*/

void shs::SensorAPIhandler::m_prepareAnswer(const shs::settings::shs_ID_t ID, const shs::SensorAPIcmds::SensorAPIcmds cmd, const int16_t value)
{
    shs::ByteCollector bc(5);
    bc.add(ID, 2);
    bc.add(cmd, 1);
    bc.add(value, 2);
    shs::module.sendPacket(&bc, m_to, m_apiID);
}

void shs::SensorAPIhandler::m_prepareAnswer(const shs::settings::shs_ID_t ID, const shs::SensorAPIcmds::SensorAPIcmds cmd, const shs::settings::shs_float_t value)
{
    shs::ByteCollector bc(3 + sizeof(value));
    bc.add(ID, 2);
    bc.add(cmd, 1);
    bc.add(value);
    shs::module.sendPacket(&bc, m_to, m_apiID);
}

void shs::SensorAPIhandler::m_prepareAnswer(const shs::settings::shs_ID_t ID, const shs::SensorAPIcmds::SensorAPIcmds cmd, const shs::settings::shs_double_t &value)
{
    shs::ByteCollector bc(3 + sizeof(value));
    bc.add(ID, 2);
    bc.add(cmd, 1);
    bc.add(value);
    shs::module.sendPacket(&bc, m_to, m_apiID);
}
