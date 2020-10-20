#include <vector>
#include <numa_allocator.hpp>

int main() {
    std::vector<int, numa::alloc::NumaAllocator<int>> v1(10, 0, numa::alloc::NumaAllocator<int>(0));
    std::vector<int, numa::alloc::NumaAllocator<int>> v2(10, 0, numa::alloc::NumaAllocator<int>());

    return 0;
}
