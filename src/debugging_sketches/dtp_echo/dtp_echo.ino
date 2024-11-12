#include <shs_ControlWiFi.h>
#include <shs_TcpClient.h>

#include <shs_DTP.h>
#include <shs_API.h>
#include <shs_DTPpacket.h>
#include <shs_ByteCollector.h>
#include <shs_ID.h>
#include <shs_types.h>
#include <memory>

#include <shs_ByteCollector.h>
#define DEBUG
#include <shs_debug.h>

shs::DTP dtp;
shs::TcpClient tcp("192.168.1.10", 5000);

const shs::t::shs_ID_t recID(10);
const shs::t::shs_ID_t senID(12);

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
        
       
        return std::move(p);
    }
};

void setup()
{
    Serial.begin(115200);
    doutln();
    doutln((int)(uint32_t(recID.id) >> 24));

    dsep();
    doutln(shs::ControlWiFi::connectWiFiWait());
    dsep();
    //tcp.connect("192.168.1.10", 5000);
    //if (tcp.connected()) tcp.write(1);
    //doutln("tcp started");

    dtp.attachBus(std::make_unique<shs::DTPbus>(tcp, senID));
    
   // doutln("this");

    dtp.attachAPI(std::make_unique<EhoAPI>(senID));

    doutln("ok");

  

}

void loop()
{
    tcp.tick();
    dtp.tick();

}
