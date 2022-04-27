#include "map.hpp"
#include "utility.hpp"
#include <iostream>
#include <memory>

int main()
{
    ft::map<int, float> t;

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << it->second << "\n";
    }
    t.insert(ft::make_pair(45, 45.0));
    t.insert(ft::make_pair(23, 23.5));
    t.insert(ft::make_pair(34, 34.99));
    t.insert(ft::make_pair(34, 34.43));

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << it->second << "\n";
    }

    std::cout << t.count(23) << "\n";
    std::cout << t.count(1) << "\n";

    auto it = t.find(0);
    if (it != t.end()) {
        std::cout << it->second << "\n";
    }
    it = t.find(34);
    std::cout << it->second << "\n";
    --it;
    std::cout << it->second << "\n";

    it = t.insert(t.end(), ft::make_pair(66, 66.1));
    std::cout << it->second << "\n";

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << it->second << "\n";
    }

    t[1];

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << it->second << "\n";
    }

    t[1].second = 1.324;
    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << it->second << "\n";
    }

    t.at(1).second = 57.345;

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << it->second << "\n";
    }

    try {
        t.at(5);
    } catch (...) {
    }
}
