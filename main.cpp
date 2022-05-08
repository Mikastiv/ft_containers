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
}
