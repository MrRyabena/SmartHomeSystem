#include "shs_lib_Color_BrightSmoothFilterApi.h"

#include <shs_ByteCollector.h>
#include <shs_lib_APIids.h>

shs::lib::Color::BrightSmoothFilterApi::BrightSmoothFilterApi(std::shared_ptr<BrightSmoothFilter> filter, const shs::t::shs_ID_t id)
    : shs::API(id), m_filter(std::move(filter))
{}

shs::DTPpacket shs::lib::Color::BrightSmoothFilterApi::handle(shs::ByteCollectorReadIterator<>& it)
{
    const auto command = static_cast<BrightSmoothFilterApiCommands>(it[2]);

    switch (command)
    {
        case BrightSmoothFilterApiCommands::ENABLE:
            m_filter->enable();
            return shs::DTPpacket(getID(), it.getSenderID(), { static_cast<uint8_t>(BrightSmoothFilterApiCommands::ENABLED), 1 });
        case BrightSmoothFilterApiCommands::DISABLE:
            m_filter->disable();
            return shs::DTPpacket(getID(), it.getSenderID(), { static_cast<uint8_t>(BrightSmoothFilterApiCommands::ENABLED), 0 });
        case BrightSmoothFilterApiCommands::IS_ENABLED:
            return shs::DTPpacket(getID(), it.getSenderID(), { static_cast<uint8_t>(BrightSmoothFilterApiCommands::ENABLED), m_filter->isEnabled() ? 1 : 0 });
        case BrightSmoothFilterApiCommands::SET_STEP_TIMEOUT:
            m_filter->setStepTimeout(it[3]);
            return shs::DTPpacket(getID(), it.getSenderID(), { static_cast<uint8_t>(BrightSmoothFilterApiCommands::STEP_TIMEOUT), static_cast<uint8_t>(m_filter->getStepTimeout()) });
        case BrightSmoothFilterApiCommands::GET_STEP_TIMEOUT:
            return shs::DTPpacket(getID(), it.getSenderID(), { static_cast<uint8_t>(BrightSmoothFilterApiCommands::STEP_TIMEOUT), static_cast<uint8_t>(m_filter->getStepTimeout()) });
        case BrightSmoothFilterApiCommands::SET_STEP:
            m_filter->setStep(it[3]);
            return shs::DTPpacket(getID(), it.getSenderID(), { static_cast<uint8_t>(BrightSmoothFilterApiCommands::STEP), m_filter->getStep() });
        case BrightSmoothFilterApiCommands::GET_STEP:
            return shs::DTPpacket(getID(), it.getSenderID(), { static_cast<uint8_t>(BrightSmoothFilterApiCommands::STEP), m_filter->getStep() });
        case BrightSmoothFilterApiCommands::SET_TARGET:
            m_filter->setTarget(it[3]);
            return shs::DTPpacket(getID(), it.getSenderID(), { static_cast<uint8_t>(BrightSmoothFilterApiCommands::TARGET), m_filter->getTarget() });
        case BrightSmoothFilterApiCommands::GET_TARGET:
            return shs::DTPpacket(getID(), it.getSenderID(), { static_cast<uint8_t>(BrightSmoothFilterApiCommands::TARGET), m_filter->getTarget() });
    }
}
