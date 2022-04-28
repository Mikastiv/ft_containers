#include "map.hpp"
#include "set.hpp"
#include <stdlib.h>
#include <iostream>
#include <map>
#include <memory>
#include <set>

int main()
{
    ft::set<int> t;

    srand(time(0));
    for (int i = 0; i < 15; ++i) {
        t.insert((rand()) % 100);
    }

    t.print_tree();
}
