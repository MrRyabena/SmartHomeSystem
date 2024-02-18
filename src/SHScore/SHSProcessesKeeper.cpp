#include "SHSProcessesKeeper.h"

void shs::ProcessesKeeper::attach(shs::Process *object)
{
    if (_fined(object) == 0xff)
        _ptrs.push_back(object);
    _ptrs.shrink_to_fit();
}

void shs::ProcessesKeeper::detach(shs::Process *object)
{
    uint8_t ind = _fined(object);
    if (ind == 0xff)
        return;
    for (uint8_t i = ind; i < _ptrs.size() - 1; i++)
        _ptrs[i] = _ptrs[i + 1];
    _ptrs.pop_back();
    _ptrs.shrink_to_fit();
}

void shs::ProcessesKeeper::begin()
{
    for (uint8_t i = 0; i < _ptrs.size(); i++)
        if (_ptrs[i])
            _ptrs[i]->begin();
}

void shs::ProcessesKeeper::tick()
{
    for (uint8_t i = 0; i < _ptrs.size(); i++)
        if (_ptrs[i])
            _ptrs[i]->tick();
}

void shs::ProcessesKeeper::end()
{
    for (uint8_t i = 0; i < _ptrs.size(); i++)
        if (_ptrs[i])
            _ptrs[i]->end();
}

uint8_t shs::ProcessesKeeper::_fined(shs::Process *object)
{
    for (uint8_t i = 0; i < _ptrs.size(); i++)
        if (_ptrs[i] == object)
            return i;
    return 0xff;
}
