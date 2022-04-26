#include "tree.hpp"
#include "utility.hpp"
#include <iostream>
#include <memory>

int main()
{
    tree<int, ft::less<int>, std::allocator<int> > t;

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << "\n";
    }
    t.insert(45);
    t.insert(23);
    t.insert(34);
    t.insert(34);

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << "\n";
    }

    std::cout << t.count(23) << "\n";
    std::cout << t.count(1) << "\n";

    auto it = t.find(0);
    if (it != t.end()) {
        std::cout << *it << "\n";
    }
    it = t.find(34);
    std::cout << *it << "\n";
}
