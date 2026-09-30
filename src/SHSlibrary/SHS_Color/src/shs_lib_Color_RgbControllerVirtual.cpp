#include "shs_lib_Color_RgbControllerVirtual.h"

#include <memory>
#include <shs_ByteCollector.h>
#include <shs_utils.h>

#include <shs_lib_APIids.h>

#include "shs_lib_Color_RgbControllerApiCommands.h"


shs::lib::Color::RgbControllerVirtual::RgbControllerVirtual(shs::DTP& dtp, shs::t::shs_ID_t id, shs::t::shs_ID_t remote_id)
    : API(id.setComponentID(shs::etoi(shs::lib::APIids::COLOR_RGB_CONTROLLER_API))),
    m_remote_id(remote_id), m_dtp(dtp)
{}


void shs::lib::Color::RgbControllerVirtual::setColor(const RGB888 color)
{
    RgbController::setColor(color);

    shs::ByteCollector<> bc(4);
    bc.push_back(RgbControllerApiCommands::SET_COLOR, 1);
    bc.push_back(color, 3);

    m_dtp.sendPacket(shs::DTPpacket(API_ID, m_remote_id, std::move(bc)));
}

void shs::lib::Color::RgbControllerVirtual::setBrightness(const uint8_t brightness) noexcept
{
    RgbController::setBrightness(brightness);

    shs::ByteCollector<> bc(2);
    bc.push_back(RgbControllerApiCommands::SET_BRIGHTNESS, 1);
    bc.push_back(brightness, 1);

    m_dtp.sendPacket(shs::DTPpacket(API_ID, m_remote_id, std::move(bc)));
}

shs::DTPpacket shs::lib::Color::RgbControllerVirtual::handle(shs::ByteCollectorReadIterator<>& it)
{
    it.set_position(shs::DTPpacket::get_dataBeg(it));

    using Commands = shs::lib::Color::RgbControllerApiCommands;

    switch (static_cast<Commands>(it.read()))
    {
        case Commands::SET_COLOR:
            {
                auto brightness = m_color.value;
                m_color = static_cast<RGBV8888>(it.read(), it.read(), it.read());
                m_color.value = brightness;
            }
            break;

        case Commands::SET_BRIGHTNESS:
            {
                m_color.value = it.read();
            }
            break;

        default:
            break;
    }

    return shs::DTPpacket{};
}
