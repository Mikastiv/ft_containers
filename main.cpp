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

    srand(time(0));
    for (int i = 0; i < 30; ++i) {
        t.insert((rand()) % 100);
    }

    t.insert(5);
    t.insert(1);
    t.insert(7);

    t.print_tree();
    std::cout << "\n";
    auto it = t.begin();
    std::cout << "Erase: " << *it << "\n";
    t.erase(it);

    t.print_tree();
    std::cout << "\n";
    it = t.begin();
    std::cout << "Erase: " << *it << "\n";
    t.erase(it);

    t.print_tree();
    std::cout << "\n";
    it = t.begin();
    std::cout << "Erase: " << *it << "\n";
    t.erase(it);

    t.print_tree();
    std::cout << "\n";
    it = t.begin();
    std::cout << "Erase: " << *it << "\n";
    t.erase(it);

    t.print_tree();
    std::cout << "\n";
    it = t.begin();
    std::cout << "Erase: " << *it << "\n";
    t.erase(it);

    t.print_tree();
    std::cout << "\n";
    it = t.begin();
    std::cout << "Erase: " << *it << "\n";
    t.erase(it);

    t.print_tree();
    std::cout << "\n";
    it = t.begin();
    std::cout << "Erase: " << *it << "\n";
    t.erase(it);

    t.print_tree();
    std::cout << "\n";
    it = t.begin();
    std::cout << "Erase: " << *it << "\n";
    t.erase(it);

    t.print_tree();
    std::cout << "\n";
    std::cout << "Erase: 83" << "\n";
    t.erase(83);

    t.print_tree();
    std::cout << "\n";

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << " " << std::flush;
    }
    std::cout << "\n";
}
