#include "map.hpp"
#include "set.hpp"
#include <ios>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <stdlib.h>

int main()
{
    ft::set<int> t;

    srand(time(0));
    for (int i = 0; i < 1500; ++i) {
        t.insert(rand() % 1500);
    }

    for (int i = 0; i < 1350; ++i) {
        ft::set<int>::iterator it = t.end();
        while (it == t.end() && !t.empty()) {
            it = t.find(rand() % 1500);
        }

        if (t.empty()) {
            break;
        }
        std::cout << i << " Erase: " << *it << "\n";
        t.erase(it);
        t.print_tree();
        std::cout << "\n";

        bool valid_tree = t.is_red_black_tree();
        std::cout << std::boolalpha << valid_tree << "\n";
        if(!valid_tree) {
            exit(1);
        }
    }

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << " " << std::flush;
    }

    for (int i = 0; i < 500; ++i) {
        t.insert(rand() % 500);
    }


    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << " " << std::flush;
    }
    std::cout << "\n";
}
