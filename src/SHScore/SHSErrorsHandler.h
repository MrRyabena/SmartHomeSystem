#pragma once
#include <stdint.h>

namespace shs
{
    class ErrorsHandler;
    typedef void (*errorsCallback_t)(shs::Errors error);
    
    enum Errors;
};

enum shs::Errors : uint8_t
{
    OK,
    DTPtimeout,
    DTPcrc,
};

class shs::ErrorsHandler
{
public:
    ErrorsHandler(shs::errorsCallback_t system_callback = nullptr, shs::errorsCallback_t user_callback = nullptr);
    ~ErrorsHandler();

    void attachFirstHandler(shs::errorsCallback_t callback);
    void attachSecondHandler(shs::errorsCallback_t callback);

    void error(shs::Errors error);

    [[nodiscard]] shs::Errors getLastError();
    [[nodiscard]] uint8_t getCount();

private:
    shs::Errors m_lastError{};
    uint8_t m_counter = 0;

    shs::errorsCallback_t m_firstHandler{};
    shs::errorsCallback_t m_secondHandler{};
};
