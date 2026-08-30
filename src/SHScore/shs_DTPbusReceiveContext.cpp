#include "shs_DTPbusReceiveContext.h"

shs::DTPbusReceiveContext::DTPbusReceiveContext(const DtpBusSize_t bufsize, shs::API* handler, shs::t::shs_time_t receive_timeout)
    : buffer(bufsize), receive_length(0), receive_timer(receive_timeout), handler(handler)
{}

shs::DTPbusReceiveContext::DTPbusReceiveContext(DTPbusReceiveContext&& other) noexcept
    : buffer(std::move(other.buffer)),
    receive_length(other.receive_length),
    receive_timer(other.receive_timer),
    handler(other.handler)
{
    other.receive_length = 0;
    other.handler = nullptr;
}

shs::DTPbusReceiveContext& shs::DTPbusReceiveContext::operator=(DTPbusReceiveContext&& other) noexcept
{
    if (this != &other)
    {
        buffer = std::move(other.buffer);
        receive_length = other.receive_length;
        receive_timer = other.receive_timer;
        handler = other.handler;
        other.receive_length = 0;
        other.handler = nullptr;
    }
    return *this;
}