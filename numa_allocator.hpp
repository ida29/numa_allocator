/*
MIT License

Copyright (c) 2020 ida29

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <new>
#include <numa.h>

namespace numa::alloc
{
template <class T>
struct NumaAllocator {
   public:
    using value_type = T;

    NumaAllocator(int node = 0)
        : node(node){};

    template <class U>
    NumaAllocator(const NumaAllocator<U>&);

    T* allocate(std::size_t n)
    {
        auto p = numa_alloc_onnode(sizeof(T) * n, node);
        if (!p) {
            throw std::bad_alloc();
        }

        return reinterpret_cast<T*>(p);
    }

    void deallocate(T* p, std::size_t n)
    {
        numa_free(p, sizeof(T) * n);
    }

    template <typename U, typename... Args>
    void construct(U* ptr, Args&&... args)
    {
        new (ptr) U(std::forward<Args>(args)...);
    };

    void destroy(T* ptr)
    {
        (ptr)->~T();
    }

   private:
    int node;
};

template <class T, class U>
bool operator==(const NumaAllocator<T>&, const NumaAllocator<U>&)
{
    return true;
}

template <class T, class U>
bool operator!=(const NumaAllocator<T>&, const NumaAllocator<U>&)
{
    return false;
}
};  // namespace numa::alloc
