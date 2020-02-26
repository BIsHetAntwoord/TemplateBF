#include "machine.hpp"

#include <iostream>

template <typename A>
void print_byte_array(std::ostream& os)
{
    os << (unsigned int)A::value::value << " ";
    print_byte_array<typename A::next>(os);
}

template <>
void print_byte_array<void>(std::ostream& os)
{

}

template <typename A>
void print_char_array(std::ostream& os)
{
    os << (char)A::value::value;
    print_char_array<typename A::next>(os);
}

template<>
void print_char_array<void>(std::ostream& os)
{

}

int main()
{
    using tape = MakeArray<Byte<0>, 256>::value;
    using code = MakeCharArray<',', '[', '.', '+', ']', '\0'>::value;
    using input = MakeByteArray<'A'>::value;
    using output = void;

    using machine = Machine<tape, code, input, output, 0, 0, true>;

    using result = machine::output;
    #ifdef PRINT_BYTES
    print_byte_array<result>(std::cout);
    #else
    print_char_array<result>(std::cout);
    #endif
    std::cout << std::endl;

    #ifdef PRINT_TAPE
    using result_tape = machine::tape;
    print_byte_array<result_tape>(std::cout);
    std::cout << std::endl;
    #endif
}
