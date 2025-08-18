#pragma once

namespace shs
{
    struct WiFiConfig;
}


struct shs::WiFiConfig
{
    char ssid[32]{};
    char pass[64]{};
};
