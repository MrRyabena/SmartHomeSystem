
#include <memory>

#include <shs_DTP.h>
#include <shs_ProgramTimer.h>
#include <shs_debug.h>
#include <shs_types.h>

#include <shs_lib_Color_RgbManager.h>
#include <shs_lib_Color_RgbManagerVirtual.h>
#include <shs_lib_Color_RgbManagerApi.h>
#include <shs_lib_RgbDriver.h>
#include <shs_lib_Color_RgbManagerLayer.h>
#include <shs_lib_Color_FadeRgbFilter.h>
#include <shs_lib_Color_BrightSmoothFilter.h>
#include <shs_lib_Color_FireRgbEffect.h>
#include <shs_lib_Color_Wheel1530Effect.h>

#include "config.h"
#include <DtpBusWrapper.h>

std::shared_ptr<shs::lib::Color::RgbDriver> driver;
std::shared_ptr<shs::lib::Color::RgbManager> manager;
std::shared_ptr<shs::lib::Color::RgbManagerVirtual> virtual_manager;
std::shared_ptr<shs::DTP> dtp;
std::shared_ptr<shs::lib::Color::RgbManagerApi> api;

void setColorTest(const std::shared_ptr<shs::lib::Color::RgbManager>);
void setBrightnessTest(const std::shared_ptr<shs::lib::Color::RgbManager>);
void fadeLayerTest(const std::shared_ptr<shs::lib::Color::RgbManager>);
void effectsLayerTest(const std::shared_ptr<shs::lib::Color::RgbManager> );

void setup()
{
    dinit();
    using namespace shs::lib::Color;
    driver = std::make_shared<RgbDriver>(config::RED_PIN, config::GREEN_PIN, config::BLUE_PIN);
    manager = std::make_shared<RgbManager>(driver);
    dtp = std::make_shared<shs::DTP>(0);
    api = std::make_shared<shs::lib::Color::RgbManagerApi>(manager, 1);
    auto bus = std::make_shared<shs::lib::Color::tests::DtpBusWrapper>(1, api.get());
    bus->connected_modules.attach(1);
    dtp->attachBus(bus);
    virtual_manager = std::make_shared<RgbManagerVirtual>(dtp, 0, shs::t::shs_ID_t{ 1 , 0, 0 });

    driver->setup();
    manager->setBrightness(255);
    virtual_manager->setBrightness(255);

    // setColorTest(manager.get());
    // setBrightnessTest(manager.get());
    // fadeLayerTest(manager.get());
    // effectsLayerTest(manager.get());

    setColorTest(virtual_manager);
    // setBrightnessTest(virtual_manager);
    // fadeLayerTest(virtual_manager);
    effectsLayerTest(virtual_manager);


    dsep();
    doutln("TESTS COMPLETED");
    dsep();
}

void loop()
{}


void setColorTest(const std::shared_ptr<shs::lib::Color::RgbManager> sp_manager)
{
    dsep();
    dfunc();
    using shs::lib::Color::RGB888;
    doutln("red");
    sp_manager->setColor(RGB888{ 255, 0, 0 });
    delay(2500);
    doutln("green");
    sp_manager->setColor(RGB888{ 0, 255, 0 });
    delay(2500);
    doutln("blue");
    sp_manager->setColor(RGB888{ 0, 0, 255 });
    delay(2500);
    doutln("off");
    dsep();
    sp_manager->setColor(RGB888{ 0, 0, 0 });
}

void setBrightnessTest(std::shared_ptr<shs::lib::Color::RgbManager> sp_manager)
{
    dsep();
    dfunc();
    using shs::lib::Color::RGB888;
    doutln("Setting brightness");
    sp_manager->setColor(RGB888{ 255, 0, 255 });
    dout("driver color: "); dout(driver->getColor().red); dout(", "); dout(driver->getColor().green); dout(", "); doutln(driver->getColor().blue);
    for (uint8_t brightness = 0; brightness < 255; brightness++)
    {
        sp_manager->setBrightness(brightness);
        dout("set: "); dout(brightness);
        dout(" get: "); dout(sp_manager->getBrightness());
        dout("driver get: "); dout(driver->getBrightness());
        dout("driver color: "); dout(driver->getColor().red); dout(", "); dout(driver->getColor().green); dout(", "); doutln(driver->getColor().blue);
        delay(50);
    }
    doutln("finished");
    dsep();
}

void fadeLayerTest(std::shared_ptr<shs::lib::Color::RgbManager> sp_manager)
{
    dsep();
    dfunc();
    using namespace shs::lib::Color;

    constexpr auto fade_period = 5000;

    auto layer_id = sp_manager->addLayer(std::make_shared<RgbManagerLayer>(RGBV8888(0, 0, 0, 255)));
    auto layer = sp_manager->getLayer(layer_id);
    layer->setFadePeriod(fade_period);
    layer->enableFade();

    auto fade = []() {
        shs::ProgramTimer timer(fade_period + 500);
        while (!timer.check())
        {
            // dout("sp_manager color: "); dout(sp_manager->getColor().red); dout(", "); dout(sp_manager->getColor().green); dout(", "); doutln(sp_manager->getColor().blue);
            manager->tick();
            yield();
        }};

    doutln("set color 255, 0, 0");
    sp_manager->setColor(RGB888{ 255, 0, 0 });
    fade();
    delay(2500);
    doutln("set color 0, 255, 0");
    sp_manager->setColor(RGB888{ 0, 255, 0 });
    fade();
    delay(2500);
    doutln("set color 0, 0, 255");
    sp_manager->setColor(RGB888{ 0, 0, 255 });
    fade();
    delay(2500);
    doutln("set color 255, 255, 0");
    sp_manager->setColor(RGB888{ 255, 255, 0 });
    fade();
    delay(2500);
    doutln("set color 0, 0, 0");
    sp_manager->setColor(RGB888{ 0, 0, 0 });
    fade();

    return;
    auto layer_ptr = sp_manager->getLayer(layer_id);
    layer_ptr->disableFade();
    layer_ptr->enableBrightSmooth();
    layer_ptr->setBrightSmoothStepTimeout(20);
    sp_manager->setColor(RGB888{ 255, 255, 255 });

    doutln("fade brightness to 255");
    sp_manager->setBrightness(255);
    while (manager->getBrightness() < 255)
    {
       // dout("sp_manager brightness: "); dout(sp_manager->getBrightness()); dout(" driver brightness: "); doutln(driver->getBrightness());
        manager->tick();
        yield();
    }
    doutln("fade brightness to 0");
    sp_manager->setBrightness(0);
    while (manager->getBrightness() > 0)
    {
        //dout("sp_manager brightness: "); dout(sp_manager->getBrightness()); dout(" driver brightness: "); doutln(driver->getBrightness());
        manager->tick();
        yield();
    }
    sp_manager->popLayer();
    sp_manager->setColor(RGB888{ 0, 0, 0 });
    dsep();
}


void effectsLayerTest(std::shared_ptr<shs::lib::Color::RgbManager> sp_manager)
{
    using namespace shs::lib::Color;

    dsep();
    dfunc();

    auto id = sp_manager->addLayer(std::make_shared<RgbManagerLayer>(RGBV8888(0, 0, 0, 255)));
    sp_manager->getLayer(id)->pushEffect(std::make_unique<Wheel1530Effect>(10000));
    id = sp_manager->addLayer(std::make_shared<RgbManagerLayer>(RGBV8888(0, 0, 0, 255)));
    sp_manager->getLayer(id)->pushEffect(std::make_unique<FireRgbEffect>());


    shs::ProgramTimer timer(15000);
    doutln("fire effect for 15 seconds");
    while (!timer.check())
    {
        manager->tick();
        yield();
    }
    sp_manager->popLayer();
    doutln("wheel effect for 15 seconds");
    timer.reset();
    RGB888 color{};
    while (!timer.check())
    {
        auto new_color = driver->getColor();
        if (new_color != color)
        {
            color = new_color;
            dout("color: "); dout(color.red); dout(", "); dout(color.green); dout(", "); doutln(color.blue);
        }
        manager->tick();
        yield();
    }
    sp_manager->clearLayers();
    dsep();
}
