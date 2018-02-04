#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <iterator>
#include <memory>

template<class T>
class dynarray{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = std::iterator<std::random_access_iterator_tag, T>;
    using const_iterator = std::iterator<std::random_access_iterator_tag, T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    explicit dynarray(size_t size)
        : s{size}
        , d{std::make_unique<T[]>(size)}
    {}

    dynarray()
        : s{0}
        , d{nullptr}
    {}

private:
    size_t s;
    std::unique_ptr<T[]> d;
};

#endif // DYNARRAY_H
