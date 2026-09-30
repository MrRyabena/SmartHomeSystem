#include "shs_lib_Color_RgbControllerApi.h"

#include <shs_utils.h>

#include <shs_lib_APIids.h>

shs::lib::Color::RgbControllerApi::RgbControllerApi(shs::t::shs_ID_t id, std::shared_ptr<RgbController> controller)
    : shs::API(id.setComponentID(shs::etoi(shs::lib::APIids::COLOR_RGB_CONTROLLER_API))), m_controller(controller)
{}

shs::DTPpacket shs::lib::Color::RgbControllerApi::handle(shs::ByteCollectorReadIterator<>& it)
{
    it.set_position(shs::DTPpacket::get_dataBeg(it));

    using Commands = shs::lib::Color::RgbControllerApiCommands;

    switch (static_cast<Commands>(it.read()))
    {
        case Commands::SET_COLOR:
            {
                m_controller->setColor(RGB888(it.read(), it.read(), it.read()));
            }
            break;

        case Commands::GET_COLOR:
            {
                RGB888 color = m_controller->getColor();
                shs::ByteCollector<> bc(4);

                bc.push_back(Commands::COLOR, 1);
                bc.push_back(color.red, 1);
                bc.push_back(color.green, 1);
                bc.push_back(color.blue, 1);

                return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc));
            }
            break;

        case Commands::SET_BRIGHTNESS:
            m_controller->setBrightness(it.read());
            break;

        case Commands::GET_BRIGHTNESS:
            {
                uint8_t brightness = m_controller->getBrightness();
                shs::ByteCollector<> bc;
                bc.push_back(Commands::BRIGHTNESS, 1);
                bc.push_back(brightness, 1);

                return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc));
            }
            break;

        default:
            return shs::DTPpacket{};
            break;
    }

    return shs::DTPpacket{};
}