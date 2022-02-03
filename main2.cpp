#include <iostream>

#include "type_traits.hpp"
#include "vector.hpp"

int main() {
    ft::vector<int> test;

    std::cout << std::boolalpha << ft::is_integral<short>::value << std::endl;
    std::cout << std::boolalpha << ft::is_same<const short *, short *>::value << std::endl;
}
