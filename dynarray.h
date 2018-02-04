#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <memory>

template<class T>
class dynarray{
public:
    dynarray(size_t size)
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
