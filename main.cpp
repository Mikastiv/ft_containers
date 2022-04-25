#include "utility.hpp"
#include "tree.hpp"
#include <memory>

int main()
{
    tree<int, ft::less<int>, std::allocator<int> > t;

    t.insert(45);
    t.insert(23);
}
