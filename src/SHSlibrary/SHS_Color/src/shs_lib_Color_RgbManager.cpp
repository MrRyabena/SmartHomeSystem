#include "shs_lib_Color_RgbManager.h"


shs::lib::Color::RgbManager::RgbManager(std::shared_ptr<RgbController> controller)
    : m_controller(controller), m_color(0, 0, 0, 255)
{}
