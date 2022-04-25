#include "utility.hpp"
#include "tree.hpp"
#include <memory>
#include <iostream>

int main()
{
    tree<int, ft::less<int>, std::allocator<int> > t;

    t.insert(45);
    t.insert(23);

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << "\n";
    }
}
