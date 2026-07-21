#include "shs_lib_Color_RgbManager.h"


shs::lib::Color::RgbManager::RgbManager(RgbDriver driver)
    : m_driver(driver), m_color(0, 0, 0, 0)
{}
