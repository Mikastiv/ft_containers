#include "map.hpp"
#include "set.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <stdlib.h>

int main()
{
    ft::set<int> t;

    srand(55);
    for (int i = 0; i < 100; ++i) {
        t.insert(rand() % 100);
    }

    for (int i = 0; i < 50; ++i) {
        ft::set<int>::iterator it = t.end();
        while (it == t.end()) {
            it = t.find(rand() % 100);
        }
        std::cout << i << " Erase: " << *it << "\n";
        t.erase(it);
        t.print_tree();
        std::cout << "\n";
    }

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << " " << std::flush;
    }
    std::cout << "\n";
}
