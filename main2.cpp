#include <iostream>
#include <vector>

#include "type_traits.hpp"
#include "vector.hpp"

int main() {
    ft::vector<float> test1(34, 5.0);
    ft::vector<float> test(test1.begin(), test1.end());

    std::cout << test[5] << std::endl;
    std::cout << test.size() << std::endl;
}
