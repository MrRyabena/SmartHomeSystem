#include "shs_lib_Color_BrightSmoothFilterApi.h"

#include <shs_ByteCollector.h>
#include <shs_lib_APIids.h>

shs::lib::Color::BrightSmoothFilterApi::BrightSmoothFilterApi(std::shared_ptr<BrightSmoothFilter> filter, const shs::t::shs_ID_t id)
    : shs::API(id), m_filter(std::move(filter))
{}

shs::DTPpacket shs::lib::Color::BrightSmoothFilterApi::handle(shs::ByteCollectorReadIterator<>& it)
{

    it.set_position(shs::DTPpacket::get_dataBeg(it));

    switch (it.read())
    {
        case Commands::IS_ENABLED:
            {
                shs::ByteCollector<> bc(2);
                bc.push_back(Commands::ENABLED, 1);
                bc.push_back(m_filter->isEnabled(), 1);
                return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc));
            }
            break;
        case Commands::GET_STEP_TIMEOUT:
            {
                shs::ByteCollector<> bc(2 + sizeof(shs::t::shs_time_t));
                bc.push_back(Commands::STEP_TIMEOUT, 1);
                bc.push_back(m_filter->getStepTimeout());
                return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc));
            }
            break;
        case Commands::GET_STEP:
            {
                shs::ByteCollector<> bc(2);
                bc.push_back(Commands::STEP, 1);
                bc.push_back(m_filter->getStep(), 1);
                return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc));
            }
            break;
        case Commands::GET_TARGET:
            {
                shs::ByteCollector<> bc(2);
                bc.push_back(Commands::TARGET, 1);
                bc.push_back(m_filter->getTarget(), 1);
                return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc));
            }
            break;
        default:
            {
                it.set_position(shs::DTPpacket::get_dataBeg(it));
                handle(it, m_filter);
            }
            break;
    }

    return shs::DTPpacket();
}

void shs::lib::Color::BrightSmoothFilterApi::handle(shs::ByteCollectorReadIterator<>& it, std::shared_ptr<BrightSmoothFilter> filter)
{
    using Commands = BrightSmoothFilterApiCommands;

    switch (it.read())
    {
        case Commands::ENABLE: filter->enable(); break;
        case Commands::DISABLE: filter->disable(); break;
        case Commands::SET_STEP_TIMEOUT: filter->setStepTimeout(it.get<shs::t::shs_time_t>()); break;
        case Commands::SET_STEP: filter->setStep(it.read()); break;
        case Commands::SET_TARGET: filter->setTarget(it.read()); break;
        default: break;
    }
}
