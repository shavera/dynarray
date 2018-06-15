#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <exception>
#include <iterator>
#include <memory>

template<class T>
class dynarray_iterator;

template<>
template<class T>
struct std::iterator_traits<dynarray_iterator<T>>{
  using iterator_category = std::random_access_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = value_type*;
  using reference = value_type&;
};

template<class T>
class dynarray_iterator{
public:
  using difference_type = typename std::iterator_traits<dynarray_iterator<T>>::difference_type;
  using value_type = typename std::iterator_traits<dynarray_iterator<T>>::value_type;
  using pointer = typename std::iterator_traits<dynarray_iterator<T>>::pointer;
  using reference = typename std::iterator_traits<dynarray_iterator<T>>::reference;

  explicit dynarray_iterator(pointer _p = nullptr) : p{_p}{}

  dynarray_iterator& operator++(){++p; return *this;}
  dynarray_iterator operator++(int){dynarray_iterator retval = *this; ++(*this); return retval;}
  bool operator==(dynarray_iterator other) const {return p == other.p;}
  reference operator*() {return *p;}
  pointer operator->() {return p;}
  dynarray_iterator& operator--(){--p; return *this;}
  dynarray_iterator operator--(int){dynarray_iterator retval = *this; --(*this); return retval;}
  dynarray_iterator operator+(const dynarray_iterator& s){ return dynarray_iterator{p+s}; }
  dynarray_iterator operator-(const size_t& s){ return dynarray_iterator{p-s}; }
  difference_type operator-(const dynarray_iterator& other){return p - other.p;}
  bool operator<(dynarray_iterator other) const {return p < other.p;}
  dynarray_iterator& operator+=(const size_t& s){ p += s; return *this;}
  dynarray_iterator& operator-=(const size_t& s){ p -= s; return *this;}

private:
  pointer p;
};

template<class T>
class dynarray_const_iterator;

template<>
template<class T>
struct std::iterator_traits<dynarray_const_iterator<T>>{
  using iterator_category = std::random_access_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = const T;
  using pointer = value_type*;
  using reference = value_type&;
};

template<class T>
class dynarray_const_iterator{
public:
  using difference_type = typename std::iterator_traits<dynarray_const_iterator<T>>::difference_type;
  using value_type = typename std::iterator_traits<dynarray_const_iterator<T>>::value_type;
  using pointer = typename std::iterator_traits<dynarray_const_iterator<T>>::pointer;
  using reference = typename std::iterator_traits<dynarray_const_iterator<T>>::reference;

  explicit dynarray_const_iterator(pointer _p = nullptr) : p{_p}{}

  dynarray_const_iterator& operator++(){++p; return *this;}
  dynarray_const_iterator operator++(int){dynarray_const_iterator retval = *this; ++(*this); return retval;}
  bool operator==(dynarray_const_iterator other) const {return p == other.p;}
  reference operator*() {return *p;}
  pointer operator->() {return p;}
  dynarray_const_iterator& operator--(){--p; return *this;}
  dynarray_const_iterator operator--(int){dynarray_const_iterator retval = *this; --(*this); return retval;}
  dynarray_const_iterator operator+(const dynarray_const_iterator& s){ return dynarray_const_iterator{p+s}; }
  dynarray_const_iterator operator-(const size_t& s){ return dynarray_const_iterator{p-s}; }
  difference_type operator-(const dynarray_const_iterator& other){return p - other.p;}
  bool operator<(dynarray_const_iterator other) const {return p < other.p;}
  dynarray_const_iterator& operator+=(const size_t& s){ p += s; return *this;}
  dynarray_const_iterator& operator-=(const size_t& s){ p -= s; return *this;}

private:
  pointer p;

};

template<class T>
class dynarray{
public:
  using iterator = dynarray_iterator<T>;
  using difference_type = typename iterator::difference_type;
  using value_type = typename iterator::value_type;
  using pointer = typename iterator::pointer;
  using reference = typename iterator::reference;

  using const_iterator = dynarray_const_iterator<T>;

  using const_reference = const value_type&;
  using const_pointer = const value_type*;

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

  reference at(size_t pos){
    if(pos < s){
      return d[pos];
    } else {
      throw std::range_error("Tried to access index " + std::to_string(pos) + " when dynarray size is only " + std::to_string(s) + ".");
    }
  }

  const_reference at(size_t pos) const {
    if(pos < s){
      return d[pos];
    } else {
      throw std::range_error("Tried to access index " + std::to_string(pos) + " when dynarray size is only " + std::to_string(s) + ".");
    }
  }

  reference operator[](size_t pos){ return d[pos]; }
  const_reference operator[](size_t pos) const { return d[pos]; }

  reference front(){ return this->at(0); }
  const_reference front() const { return this->at(0); }

  reference back(){ return this->at(s-1); }
  const_reference back() const { return this->at(s-1); }

  pointer data(){ return d.get(); }
  const_pointer data() const { return d.get(); }

  iterator begin(){ return iterator{d.get()}; }
  const_iterator cbegin() const { return const_iterator{d.get()}; }

  iterator end(){ return iterator{d.get() + s}; }
  const_iterator cend() const { return const_iterator{d.get() + s}; }

  reverse_iterator rbegin(){ return reverse_iterator(end()); }
  const_reverse_iterator crbegin(){ return const_reverse_iterator(cend()); }

  reverse_iterator rend(){ return reverse_iterator(begin()); }
  const_reverse_iterator crend(){ return const_reverse_iterator(cbegin()); }

  size_t size(){ return s; }

  void swap(dynarray& other){ std::swap(s, other.s); std::swap(d, other.d); }

private:
  size_t s;
  std::unique_ptr<T[]> d;
};

#endif // DYNARRAY_H
