#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <exception>
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

    explicit dynarray(size_type size)
        : s{size}
        , d{std::make_unique<T[]>(size)}
    {}

    dynarray()
        : s{0}
        , d{nullptr}
    {}

    reference at(size_type pos){
        if(pos < s){
            return d[pos];
        } else {
            throw std::range_error("Tried to access index " + std::to_string(pos) + " when dynarray size is only " + std::to_string(s) + ".");
        }
    }

    const_reference at(size_type pos) const {
        if(pos < s){
            return d[pos];
        } else {
            throw std::range_error("Tried to access index " + std::to_string(pos) + " when dynarray size is only " + std::to_string(s) + ".");
        }
    }

    reference operator[](size_type pos){ return d[pos]; }
    const_reference operator[](size_type pos) const { return d[pos]; }

    reference front(){ return this->at(0); }
    const_reference front() const { return this->at(0); }

    reference back(){ return this->at(s-1); }
    const_reference back() const { return this->at(s-1); }

    pointer data(){ return d.get(); }
    const_pointer data() const { return d.get(); }


private:
    size_type s;
    std::unique_ptr<T[]> d;
};

#endif // DYNARRAY_H
