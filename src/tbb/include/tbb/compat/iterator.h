
#ifndef TBB_COMPAT_ITERATOR_H
#define TBB_COMPAT_ITERATOR_H

#include <cstddef>

#include <iterator>

namespace tbb {

template <
    typename Category,
    typename T,
    typename Distance = std::ptrdiff_t,
    typename Pointer = T*,
    typename Reference = T& 
> struct iterator
{
    using iterator_category = Category;
    using value_type = T;
    using difference_type = Distance;
    using pointer = Pointer;
    using reference = Reference;
};

} // end namespace tbb

#endif

