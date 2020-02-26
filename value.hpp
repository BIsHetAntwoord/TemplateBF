#ifndef VALUE_HPP_INCLUDED
#define VALUE_HPP_INCLUDED

#include <cstdint>

template <uint8_t val>
struct Byte
{
    constexpr static uint8_t value = val;
};

template <char val>
struct Char
{
    constexpr static char value = val;
};

#endif // VALUE_HPP_INCLUDED
