#include "SHSErrorsHandler.h"

shs::ErrorsHandler::ErrorsHandler(shs::errorsCallback_t system_callback, shs::errorsCallback_t user_callback)
    : m_firstHandler(system_callback), m_secondHandler(user_callback) {}

shs::ErrorsHandler::~ErrorsHandler() {}

void shs::ErrorsHandler::attachFirstHandler(shs::errorsCallback_t callback)
{
    m_firstHandler = callback;
}

void shs::ErrorsHandler::attachSecondHandler(shs::errorsCallback_t callback)
{
    m_secondHandler = callback;
}

void shs::ErrorsHandler::error(shs::Errors error)
{
    m_lastError = error;
    m_counter++;

    if (m_firstHandler)
        m_firstHandler(error);
    if (m_secondHandler)
        m_secondHandler(error);
}

shs::Errors shs::ErrorsHandler::getLastError()
{
    return m_lastError;
}

uint8_t shs::ErrorsHandler::getCount()
{
    return m_counter;
}
