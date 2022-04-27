#include "map.hpp"
#include <iostream>
#include <memory>
#include <map>

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

    t.erase(1);

    ft::map<int, float>::key_compare kcomp = t.key_comp();

    std::cout << std::boolalpha << kcomp(t.begin()->first, it->first) << std::endl;


    std::map<int, int> stdmap;
    ft::map<int, int> ftmap;

    stdmap.insert(std::make_pair(11, 22));
    ftmap.insert(ft::make_pair(11, 22));
    stdmap.insert(std::make_pair(25, 35));
    ftmap.insert(ft::make_pair(25, 35));
    stdmap.insert(std::make_pair(9, 5));
    ftmap.insert(ft::make_pair(9, 5));
    stdmap.insert(std::make_pair(100, 256));
    ftmap.insert(ft::make_pair(100, 256));

    std::cout << "=========================================\n";
    std::cout << stdmap.lower_bound(25)->first << std::endl;
    std::cout << ftmap.lower_bound(25)->first << std::endl;
    std::cout << "=========================================\n";
    std::cout << stdmap.upper_bound(25)->first << std::endl;
    std::cout << ftmap.upper_bound(25)->first << std::endl;
    std::cout << "=========================================\n";
    std::cout << stdmap.equal_range(25).first->first << std::endl;
    std::cout << ftmap.equal_range(25).first->first << std::endl;
    std::cout << "=========================================\n";
    std::cout << stdmap.equal_range(25).second->first << std::endl;
    std::cout << ftmap.equal_range(25).second->first << std::endl;
    std::cout << "=========================================\n";
}
