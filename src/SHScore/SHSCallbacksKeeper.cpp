#include "SHSCallbacksKeeper.h"

void shs::CallbacksKeeper::attach(shs::API *object)
{
    if (_fined(object) == 0xff)
        _ptrs.push_back(object);
    _ptrs.shrink_to_fit();
}

void shs::CallbacksKeeper::detach(shs::API *object)
{
    uint8_t ind = _fined(object);

    if (ind == 0xff)
        return;
    for (uint8_t i = ind; i < _ptrs.size() - 1; i++)
        _ptrs[i] = _ptrs[i + 1];
    _ptrs.pop_back();
    _ptrs.shrink_to_fit();
}

uint8_t shs::CallbacksKeeper::handler(shs::ByteCollector &data)
{
    uint8_t status = 0;
    for (uint8_t i = 0; i < _ptrs.size(); i++)
        if (_ptrs[i])
            status = _ptrs[i]->handler(data);

    return status;
}

uint8_t shs::CallbacksKeeper::_fined(shs::API *object)
{
    for (uint8_t i = 0; i < _ptrs.size(); i++)
        if (_ptrs[i] == object)
            return i;
    return 0xff;
}
