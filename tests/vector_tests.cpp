#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector.hpp>
#include <vector>

void test_ctor() {
    {
        ft::vector<int>  v(64);
        std::vector<int> v2(64);

        assert(v.size() == 64);
        assert(v2.size() == 64);
        assert(v.end() - v.begin() == 64);
        assert(std::accumulate(v.begin(), v.end(), 0) == 0);

        assert(v.capacity() == 64);
        assert(v2.capacity() == 64);
    }
    try {
        ft::vector<int> v(ft::vector<int>().max_size());
        assert(false);
    } catch (...) {}

    {
        
    }
}

int main() {
    test_ctor();
}
