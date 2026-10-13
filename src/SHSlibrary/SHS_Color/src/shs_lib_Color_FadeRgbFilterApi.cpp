#include "shs_lib_Color_FadeRgbFilterApi.h"

#include <shs_lib_APIids.h>

shs::lib::Color::FadeRgbFilterApi::FadeRgbFilterApi(std::shared_ptr<FadeRgbFilter> filter, const shs::t::shs_ID_t id)
    : shs::API(id.setComponentID(shs::APIids::COLOR_FADE_RGB_FILTER)), m_filter(std::move(filter))
{}


shs::DTPpacket shs::lib::Color::FadeRgbFilterApi::handle(shs::ByteCollectorReadIterator<>& it)
{
    it.set_position(shs::DTPpacket::get_dataBeg(it));

    switch (it.read())
    {
        case Commands::ENABLE: m_filter->enable(); break;
        case Commands::DISABLE: m_filter->disable(); break;
        case Commands::IS_ACTIVE:
            {
                shs::ByteCollector<> bc(2);
                bc.push_back(Commands::ACTIVE, 1);
                bc.push_back(m_filter->isActive(), 1);
                return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc));
            }
            break;
        case Commands::SET_PERIOD: m_filter->setPeriod(it.get<shs::t::shs_time_t>()); break;
        case Commands::GET_PERIOD:
            {
                shs::ByteCollector<> bc(2 + sizeof(shs::t::shs_time_t));
                bc.push_back(Commands::PERIOD, 1);
                bc.push_back(m_filter->getPeriod());
                return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc));
            }
            break;
        case Commands::SET_TARGET: m_filter->setTarget(it.get<RGB888>()); break;
        case Commands::GET_TARGET:
            {
                shs::ByteCollector<> bc(2 + sizeof(RGB888));
                bc.push_back(Commands::TARGET, 1);
                bc.push_back(m_filter->getTarget());
                return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc));
            }
            break;
        default: break;
    }

    return shs::DTPpacket();
}
