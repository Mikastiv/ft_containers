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
    std::set<int> s;

    srand(time(0));
    for (int i = 0; i < 1500; ++i) {
        int n = rand() % 1500;
        t.insert(n);
        s.insert(n);
    }

    std::cout << *t.equal_range(6).first << std::endl;
    std::cout << *t.equal_range(6).second << std::endl;
    std::cout << *t.equal_range(6).first << std::endl;
    std::cout << *t.equal_range(6).second << std::endl;
    std::cout << *s.equal_range(6).first << std::endl;
    std::cout << *s.equal_range(6).second << std::endl;
    std::cout << *s.equal_range(6).first << std::endl;
    std::cout << *s.equal_range(6).second << std::endl;

    for (int i = 0; i < 1000; ++i) {
        int n = rand() % 1500;
        t.erase(n);
        s.erase(n);
    }

    t.print_tree();
    std::cout << std::boolalpha << t.is_red_black_tree() << std::endl;
}
