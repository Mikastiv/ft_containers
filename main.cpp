#include "map.hpp"
#include "set.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <set>

int main()
{
    ft::set<int> t;

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << "\n";
    }
    t.insert(45);
    t.insert(23);
    t.insert(34);
    t.insert(34);

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << "\n";
    }

    std::cout << t.count(23) << "\n";
    std::cout << t.count(1) << "\n";

    auto it = t.find(0);
    if (it != t.end()) {
        std::cout << *it << "\n";
    }
    it = t.find(34);
    std::cout << *it << "\n";
    --it;
    std::cout << *it << "\n";

    it = t.insert(t.end(), 66);
    std::cout << *it << "\n";

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << "\n";
    }

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << "\n";
    }

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << "\n";
    }

    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << "\n";
    }

    t.erase(1);

    ft::set<int>::key_compare kcomp = t.key_comp();

    std::cout << std::boolalpha << kcomp(*t.begin(), *it) << std::endl;

    std::set<int> stdset;
    ft::set<int> ftset;

    stdset.insert(11);
    ftset.insert(11);
    stdset.insert(25);
    ftset.insert(25);
    stdset.insert(9);
    ftset.insert(9);
    stdset.insert(100);
    ftset.insert(100);

    std::cout << "=========================================\n";
    std::cout << *stdset.lower_bound(25) << std::endl;
    std::cout << *ftset.lower_bound(25) << std::endl;
    std::cout << "=========================================\n";
    std::cout << *stdset.upper_bound(25) << std::endl;
    std::cout << *ftset.upper_bound(25) << std::endl;
    std::cout << "=========================================\n";
    std::cout << *stdset.equal_range(25).first << std::endl;
    std::cout << *ftset.equal_range(25).first << std::endl;
    std::cout << "=========================================\n";
    std::cout << *stdset.equal_range(25).second << std::endl;
    std::cout << *ftset.equal_range(25).second << std::endl;
    std::cout << "=========================================\n";
}
