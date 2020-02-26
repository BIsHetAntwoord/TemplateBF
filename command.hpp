#ifndef COMMAND_HPP_INCLUDED
#define COMMAND_HPP_INCLUDED

#include "value.hpp"
#include "array.hpp"

#include "jump.hpp"

//Basic command, NOP, increase IP
template <char C, typename Tape, typename Input, typename Output, typename Code, size_t IP, size_t SP>
struct Command
{
    using tape = Tape;
    using input = Input;
    using output = Output;
    constexpr static size_t ip = IP + 1;
    constexpr static size_t sp = SP;
    constexpr static bool active = true;
};

//+ command
template <typename Tape, typename Input, typename Output, typename Code, size_t IP, size_t SP>
struct Command<'+', Tape, Input, Output, Code, IP, SP>
{
    using tape = typename Set<Tape, Byte<(uint8_t)(Get<Tape, SP>::value::value + 1u)>, SP>::value;
    using input = Input;
    using output = Output;
    constexpr static size_t ip = IP + 1;
    constexpr static size_t sp = SP;
    constexpr static bool active = true;
};

//- command
template <typename Tape, typename Input, typename Output, typename Code, size_t IP, size_t SP>
struct Command<'-', Tape, Input, Output, Code, IP, SP>
{
    using tape = typename Set<Tape, Byte<(uint8_t)(Get<Tape, SP>::value::value - 1u)>, SP>::value;
    using input = Input;
    using output = Output;
    constexpr static size_t ip = IP + 1;
    constexpr static size_t sp = SP;
    constexpr static bool active = true;
};

//> command
template <typename Tape, typename Input, typename Output, typename Code, size_t IP, size_t SP>
struct Command<'>', Tape, Input, Output, Code, IP, SP>
{
    using tape = Tape;
    using input = Input;
    using output = Output;
    constexpr static size_t ip = IP + 1;
    constexpr static size_t sp = SP + 1;
    constexpr static bool active = true;
};

//< command
template <typename Tape, typename Input, typename Output, typename Code, size_t IP, size_t SP>
struct Command<'<', Tape, Input, Output, Code, IP, SP>
{
    using tape = Tape;
    using input = Input;
    using output = Output;
    constexpr static size_t ip = IP + 1;
    constexpr static size_t sp = SP - 1;
    constexpr static bool active = true;
};

//[ command
template <typename Tape, typename Input, typename Output, typename Code, size_t IP, size_t SP>
struct Command<'[', Tape, Input, Output, Code, IP, SP>
{
    using tape = Tape;
    using input = Input;
    using output = Output;
    constexpr static size_t ip = FindMatchingClose<Get<Tape, SP>::value::value == 0, Code, IP>::ip + 1;
    constexpr static size_t sp = SP;
    constexpr static bool active = true;
};

//] command
template <typename Tape, typename Input, typename Output, typename Code, size_t IP, size_t SP>
struct Command<']', Tape, Input, Output, Code, IP, SP>
{
    using tape = Tape;
    using input = Input;
    using output = Output;
    constexpr static size_t ip = FindMatchingOpen<Get<Tape, SP>::value::value != 0, Code, IP>::ip + 1;
    constexpr static size_t sp = SP;
    constexpr static bool active = true;
};

//. command
template <typename Tape, typename Input, typename Output, typename Code, size_t IP, size_t SP>
struct Command<'.', Tape, Input, Output, Code, IP, SP>
{
    using tape = Tape;
    using input = Input;
    using output = typename Append<Output, typename Get<Tape, SP>::value>::value;
    constexpr static size_t ip = IP + 1;
    constexpr static size_t sp = SP;
    constexpr static bool active = true;
};

//, command
template <typename Tape, typename Input, typename Output, typename Code, size_t IP, size_t SP>
struct Command<',', Tape, Input, Output, Code, IP, SP>
{
    using tape = typename Set<Tape, typename Get<Input, 0>::value, SP>::value;
    using input = typename RemoveFirst<Input>::value;
    using output = Output;
    constexpr static size_t ip = IP + 1;
    constexpr static size_t sp = SP;
    constexpr static bool active = true;
};

//Termination of input
template <typename Tape, typename Input, typename Output, typename Code, size_t IP, size_t SP>
struct Command<'\0', Tape, Input, Output, Code, IP, SP>
{
    using tape = Tape;
    using input = Input;
    using output = Output;
    constexpr static size_t ip = IP;
    constexpr static size_t sp = SP;
    constexpr static bool active = false;
};

#endif // COMMAND_HPP_INCLUDED
