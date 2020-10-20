#include <vector>
#include <numa_allocator.hpp>

int main() {
    std::vector<int, NumaAllocator<int>> v1(10, 0, NumaAllocator<int>(0));
    std::vector<int, NumaAllocator<int>> v2(10, 0, NumaAllocator<int>());

    return 0;
}
