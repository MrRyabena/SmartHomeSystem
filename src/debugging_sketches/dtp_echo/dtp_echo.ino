#include <shs_ControlWiFi.h>
#include <shs_TcpSocket.h>

#include <shs_DTP.h>
#include <shs_DTPbus.h>
#include <shs_API.h>
#include <shs_DTPpacket.h>
#include <shs_ByteCollector.h>
#include <shs_ID.h>
#include <shs_types.h>
#include <memory>
#include <shs_Config.h>

#include <shs_TcpServer.h>

#include <shs_ByteCollector.h>
#define DEBUG
#include <shs_debug.h>

shs::DTP dtp;

//shs::TcpSocket tcp("192.168.1.10", 5000);

shs::TcpServer server(5000, dtp);

constexpr shs::t::shs_ID_t recID(10, 0, 0);
constexpr shs::t::shs_ID_t senID(12, 0, 0);

class EhoAPI : public shs::API
{
public:
    EhoAPI(const shs::t::shs_ID_t id) : API(id) { doutln(id.id); doutln(this->API_ID.id); }
    
    virtual shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) noexcept override
    {
        
        auto size = shs::DTPpacket::get_datasize(it);
        
        it.set_position(0);
        for (auto i = 0; i < it.size(); i++) doutln(int(it[i]));
       
        shs::DTPpacket p(senID, recID, it.getPtr() + shs::DTPpacket::get_dataBeg(it), size);
        
        doutln("processed!");
        return std::move(p);
    }
};

void setup()
{
    Serial.begin(115200);
    doutln();
   
    dsep();
    doutln(shs::ControlWiFi::connectWiFiWait());
    dsep();
    
    server.start();

    //dtp.attachBus(std::make_unique<shs::DTPbus>(tcp.client, senID));
    
   // doutln("this");

    dtp.attachAPI(std::make_unique<EhoAPI>(senID));

    doutln("ok"); 

}

void loop()
{
    //tcp.tick();
    dtp.tick();
    server.tick();

}
