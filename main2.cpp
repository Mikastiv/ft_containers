#include <iostream>
#include <vector>

#include "type_traits.hpp"
#include "vector.hpp"

int main() {
    ft::vector<float> test1(34, 5.0);
    ft::vector<float> test(test1.begin(), test1.end());
    float             arr[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
    ft::vector<float> test2(arr, &arr[sizeof(arr) / sizeof(float)]);

    std::cout << test2[5] << std::endl;
    std::cout << test2.size() << std::endl;

    ft::vector<char> vec(1024);
}
