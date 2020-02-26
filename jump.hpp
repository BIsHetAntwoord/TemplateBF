#ifndef JUMP_HPP_INCLUDED
#define JUMP_HPP_INCLUDED

//Scan for next [
template<char Instruction, typename Code, size_t IP, size_t level>
struct FindMatchingCloseInternal
{
    constexpr static size_t value = FindMatchingCloseInternal<Get<Code, IP+1>::value::value, Code, IP+1, level>::value;
};

template <typename Code, size_t IP>
struct FindMatchingCloseInternal<']', Code, IP, 0>
{
    constexpr static size_t value = IP;
};

template <typename Code, size_t IP, size_t level>
struct FindMatchingCloseInternal<']', Code, IP, level>
{
    constexpr static size_t value = FindMatchingCloseInternal<Get<Code, IP+1>::value::value, Code, IP+1, level-1>::value;
};

template <typename Code, size_t IP, size_t level>
struct FindMatchingCloseInternal<'[', Code, IP, level>
{
    constexpr static size_t value = FindMatchingCloseInternal<Get<Code, IP+1>::value::value, Code, IP+1, level+1>::value;
};

template <bool, typename Code, size_t IP>
struct FindMatchingClose;

template<typename Code, size_t IP>
struct FindMatchingClose<false, Code, IP>
{
    constexpr static size_t ip = IP;
};

template <typename Code, size_t IP>
struct FindMatchingClose<true, Code, IP>
{
    constexpr static size_t ip = FindMatchingCloseInternal<Get<Code, IP+1>::value::value, Code, IP+1, 0>::value;
};

//Scan for previous [
template<char Instruction, typename Code, size_t IP, size_t level>
struct FindMatchingOpenInternal
{
    constexpr static size_t value = FindMatchingOpenInternal<Get<Code, IP-1>::value::value, Code, IP-1, level>::value;
};

template <typename Code, size_t IP>
struct FindMatchingOpenInternal<'[', Code, IP, 0>
{
    constexpr static size_t value = IP;
};

template <typename Code, size_t IP, size_t level>
struct FindMatchingOpenInternal<'[', Code, IP, level>
{
    constexpr static size_t value = FindMatchingOpenInternal<Get<Code, IP-1>::value::value, Code, IP-1, level-1>::value;
};

template <typename Code, size_t IP, size_t level>
struct FindMatchingOpenInternal<']', Code, IP, level>
{
    constexpr static size_t value = FindMatchingCloseInternal<Get<Code, IP-1>::value::value, Code, IP-1, level+1>::value;
};

template <bool, typename Code, size_t IP>
struct FindMatchingOpen;

template<typename Code, size_t IP>
struct FindMatchingOpen<false, Code, IP>
{
    constexpr static size_t ip = IP;
};

template <typename Code, size_t IP>
struct FindMatchingOpen<true, Code, IP>
{
    constexpr static size_t ip = FindMatchingOpenInternal<Get<Code, IP-1>::value::value, Code, IP-1, 0>::value;
};

#endif // JUMP_HPP_INCLUDED
