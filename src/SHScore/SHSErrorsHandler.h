#pragma once
#include <stdint.h>

/*
  Last update: v1.0.0
  Versions:
    v0.1.0 — created.
    v0.2.0 — corrected.
    v1.0.0 — release.
*/

/*
  It will be actively used for error handling and debugging information output.
*/

namespace shs
{
    namespace Errors
    {
        enum Errors : uint8_t;
    };
    class ErrorsHandler;
    typedef void (*errorsCallback_t)(shs::Errors::Errors error);
};

enum shs::Errors::Errors : uint8_t
{
    OK,
    DTP_TIMEOUT,
    DTP_CRC,
    DTP_PROCESSED,
    DTP_INVALIDaddress,
    DTP_PTRerror,
    DTP_CMDerror,
};

class shs::ErrorsHandler
{
public:
    ErrorsHandler(shs::errorsCallback_t system_callback = nullptr, shs::errorsCallback_t user_callback = nullptr);
    ~ErrorsHandler();

    void attachFirstHandler(shs::errorsCallback_t callback);
    void attachSecondHandler(shs::errorsCallback_t callback);

    void error(const shs::Errors::Errors error);

    [[nodiscard]] shs::Errors::Errors getLastError();
    [[nodiscard]] uint8_t getCount();

private:
    shs::Errors::Errors m_lastError{};
    uint8_t m_counter = 0;

    shs::errorsCallback_t m_firstHandler{};
    shs::errorsCallback_t m_secondHandler{};
};
