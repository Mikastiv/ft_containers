#include "map.hpp"
#include "set.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <stdlib.h>

int main()
{
    ft::set<int> t;

    srand(time(0));
    for (int i = 0; i < 30; ++i) {
        t.insert((rand()) % 100);
        t.print_tree();
        std::cout << "\n";
    }


    // for (auto it = t.begin(); it != t.end(); ++it) {
    //     std::cout << *it << "\n";
    // }
}
