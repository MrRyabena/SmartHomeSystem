#pragma once

template <typename T>
void func(T &val) {
    uint8_t *ptr = (uint8_t*)&val;
    for (uint8_t i = 0; i < sizeof(T); i ++) std::cout << *ptr << std::endl;
}