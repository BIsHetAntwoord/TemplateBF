#ifndef ARRAY_HPP_INCLUDED
#define ARRAY_HPP_INCLUDED

#include <cstddef>

#include "value.hpp"

template <typename T, typename N>
struct Array
{
    using value = T;
    using next = N;
};

template <typename A, size_t index>
struct Get
{
    using value = typename Get<typename A::next, index-1>::value;
};

template <typename A>
struct Get<A, 0>
{
    using value = typename A::value;
};

template <typename A, typename V, size_t index>
struct Set
{
    using value = Array<typename A::value, typename Set<typename A::next, V, index-1>::value>;
};

template <typename A, typename T>
struct Set<A, T, 0>
{
    using value = Array<T, typename A::next>;
};

template <typename A, typename V>
struct Append
{
    using value = Array<typename A::value, typename Append<typename A::next, V>::value>;
};

template <typename V>
struct Append<void, V>
{
    using value = Array<V, void>;
};

template <typename A>
struct RemoveFirst
{
    using value = typename A::next;
};

template <typename V, size_t size>
struct MakeArray
{
    using value = Array<V, typename MakeArray<V, size-1>::value>;
};

template <typename V>
struct MakeArray<V, 0>
{
    using value = void;
};

template <char c, char... X>
struct MakeCharArray
{
    using value = Array<Char<c>, typename MakeCharArray<X...>::value>;
};

template <char c>
struct MakeCharArray<c>
{
    using value = Array<Char<c>, void>;
};

template <uint8_t c, uint8_t... X>
struct MakeByteArray
{
    using value = Array<Byte<c>, typename MakeByteArray<X...>::value>;
};

template <uint8_t c>
struct MakeByteArray<c>
{
    using value = Array<Byte<c>, void>;
};

#endif // ARRAY_HPP_INCLUDED
