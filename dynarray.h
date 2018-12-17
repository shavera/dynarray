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

    class iterator : public std::iterator<std::random_access_iterator_tag, T>{
        pointer p;
    public:
        explicit iterator(pointer _p = nullptr) : p{_p}{}
        iterator& operator++(){++p; return *this;}
        iterator operator++(int){iterator retval = *this; ++(*this); return retval;}
        bool operator==(iterator other) const {return p == other.p;}
        bool operator!=(iterator other) const {return !((*this) == other);}
        reference operator*() {return *p;}
        pointer operator->() {return p;}
        iterator& operator--(){--p; return *this;}
        iterator operator--(int){iterator retval = *this; --(*this); return retval;}
        iterator operator+(const size_type& s){ return iterator{p+s}; }
        iterator operator-(const size_type& s){ return iterator{p-s}; }
        difference_type operator-(const iterator& other){return p - other.p;}
        bool operator<(iterator other) const {return p < other.p;}
        iterator& operator+=(const size_type& s){ p += s; return *this;}
        iterator& operator-=(const size_type& s){ p -= s; return *this;}
    };
    class const_iterator : public std::iterator<std::random_access_iterator_tag, T>{
        const_pointer p;
    public:
        explicit const_iterator(const_pointer _p) : p{_p}{}
        const_iterator(iterator i) : p{&(*i)}{}
        const_iterator& operator++(){++p; return *this;}
        const_iterator operator++(int){const_iterator retval = *this; ++(*this); return retval;}
        bool operator==(const_iterator other) const {return p == other.p;}
        bool operator!=(const_iterator other) const {return !((*this) == other);}
        const_reference operator*() const {return *p;}
        const_iterator& operator--(){--p; return *this;}
        const_iterator operator--(int){const_iterator retval = *this; --(*this); return retval;}
        const_iterator operator+(const size_type& s){ return const_iterator{p+s}; }
        const_iterator operator-(const size_type& s){ return const_iterator{p-s}; }
        difference_type operator-(const const_iterator& other){return p - other.p;}
        bool operator<(const_iterator other) const {return p < other.p;}
        const_iterator& operator+=(const size_type& s){ p += s; return *this;}
        const_iterator& operator-=(const size_type& s){ p -= s; return *this;}
    };
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

    dynarray(const dynarray& other)
        : dynarray(other.s)
    {
        std::copy(other.cbegin(), other.cend(), begin());
    }

    dynarray& operator=(const dynarray& other){
        s = other.s;
        d = std::make_unique<T[]>(s);
        std::copy(other.cbegin(), other.cend(), begin());
        return *this;
    }

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

    iterator begin(){ return iterator{d.get()}; }
    const_iterator cbegin() const { return const_iterator{d.get()}; }
    const_iterator begin() const {return cbegin();}

    iterator end(){ return iterator{d.get() + s}; }
    const_iterator cend() const { return const_iterator{d.get() + s}; }
    const_iterator end() const {return cend();}

    reverse_iterator rbegin(){ return reverse_iterator(end()); }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
    const_reverse_iterator rbegin() const { return crbegin(); }

    reverse_iterator rend(){ return reverse_iterator(begin()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }
    const_reverse_iterator rend() const { return crend(); }

    size_type size() const { return s; }

    void swap(dynarray& other){ std::swap(s, other.s); std::swap(d, other.d); }

private:
    size_type s;
    std::unique_ptr<T[]> d;
};

#endif // DYNARRAY_H
