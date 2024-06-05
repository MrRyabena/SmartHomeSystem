#include <GyverBME280.h>
#include <GyverHTU21D.h>

namespace shs { class TemporaryWeatherStation; }

class shs::TemporaryWeatherStation
{
public:
    float getIndoorTemperature() { return bme.readTemperature(); }
    float getOutdoorTemperature() { return htu.getTemperatureWait(); }

    float getIndoorHumidity() { return bme.readHumidity(); }
    float getOutdoorHumidity() { return htu.getHumidityWait(); }

    float getPressure() { return bme.readPressure(); }


    uint8_t begin()
    {
        uint8_t status{};

        status |= !htu.begin();
        htu.setResolution(HTU21D_RES_HIGH);

        status |= !bme.begin() << 1;

        return status;
    }

    bool updateData()
    {
        data.indoorTemperature = getIndoorTemperature();
        data.outdoorTemperature = getOutdoorTemperature();
        data.indoorHumidity = getIndoorHumidity();
        data.outdoorHumidity = getOutdoorHumidity();
        data.pressure = getPressure();

        return true;
    }

    struct Data
    {
        float indoorTemperature{};
        float outdoorTemperature{};

        float indoorHumidity{};
        float outdoorHumidity{};

        float pressure{};
    }
    data
        ;

protected:
    GyverHTU21D htu;
    GyverBME280 bme;

}
