#ifndef MACHINE_HPP_INCLUDED
#define MACHINE_HPP_INCLUDED

#include <cstddef>

#include "array.hpp"
#include "command.hpp"

//Tape: array of Byte
//Code: array of Char
//Input: array of Byte
//Output: array of Byte
template <typename Tape, typename Code, typename Input, typename Output, size_t IP, size_t SP, bool Active>
struct Machine
{
    using command = Command<Get<Code, IP>::value::value, Tape, Input, Output, Code, IP, SP>;
    using new_machine = Machine<typename command::tape, Code, typename command::input, typename command::output, command::ip, command::sp, command::active>;

    using tape = typename new_machine::tape;
    using code = typename new_machine::code;
    using input = typename new_machine::input;
    using output = typename new_machine::output;
    constexpr static size_t ip = new_machine::ip;
    constexpr static size_t sp = new_machine::sp;
    constexpr static bool active = Active;
};

template <typename Tape, typename Code, typename Input, typename Output, size_t IP, size_t SP>
struct Machine<Tape, Code, Input, Output, IP, SP, false>
{
    using tape = Tape;
    using code = Code;
    using input = Input;
    using output = Output;
    constexpr static size_t ip = IP;
    constexpr static size_t sp = SP;
    constexpr static bool active = false;
};

#endif // MACHINE_HPP_INCLUDED
