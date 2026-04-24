#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

namespace knk {

  template< class T >
  class Vector {
   public:
    struct VectorIterator {
      using iterator_category = std::random_access_iterator_tag;
      using value_type        = T;
      using difference_type   = std::ptrdiff_t;
      using pointer           = T*;
      using reference         = T&;

      VectorIterator() noexcept : ptr_(nullptr) {}
      explicit VectorIterator(T* p) noexcept : ptr_(p) {}

      reference  operator*()  const noexcept { return *ptr_; }
      pointer    operator->() const noexcept { return  ptr_; }
      reference  operator[](difference_type n) const noexcept { return ptr_[n]; }

      VectorIterator& operator++()    noexcept { ++ptr_; return *this; }
      VectorIterator  operator++(int) noexcept { VectorIterator t(*this); ++ptr_; return t; }
      VectorIterator& operator--()    noexcept { --ptr_; return *this; }
      VectorIterator  operator--(int) noexcept { VectorIterator t(*this); --ptr_; return t; }

      VectorIterator& operator+=(difference_type n) noexcept { ptr_ += n; return *this; }
      VectorIterator& operator-=(difference_type n) noexcept { ptr_ -= n; return *this; }

      VectorIterator operator+(difference_type n) const noexcept { return VectorIterator(ptr_ + n); }
      VectorIterator operator-(difference_type n) const noexcept { return VectorIterator(ptr_ - n); }
      difference_type operator-(const VectorIterator& o) const noexcept { return ptr_ - o.ptr_; }

      friend VectorIterator operator+(difference_type n, const VectorIterator& it) noexcept {
        return VectorIterator(it.ptr_ + n);
      }

      bool operator==(const VectorIterator& o) const noexcept { return ptr_ == o.ptr_; }
      bool operator!=(const VectorIterator& o) const noexcept { return ptr_ != o.ptr_; }
      bool operator< (const VectorIterator& o) const noexcept { return ptr_ <  o.ptr_; }
      bool operator> (const VectorIterator& o) const noexcept { return ptr_ >  o.ptr_; }
      bool operator<=(const VectorIterator& o) const noexcept { return ptr_ <= o.ptr_; }
      bool operator>=(const VectorIterator& o) const noexcept { return ptr_ >= o.ptr_; }

     private:
      T* ptr_;
    };

    struct ConstVectorIterator {
      using iterator_category = std::random_access_iterator_tag;
      using value_type        = T;
      using difference_type   = std::ptrdiff_t;
      using pointer           = const T*;
      using reference         = const T&;

      ConstVectorIterator() noexcept : ptr_(nullptr) {}
      explicit ConstVectorIterator(const T* p) noexcept : ptr_(p) {}
      ConstVectorIterator(const VectorIterator& it) noexcept : ptr_(&(*it)) {}

      reference  operator*()  const noexcept { return *ptr_; }
      pointer    operator->() const noexcept { return  ptr_; }
      reference  operator[](difference_type n) const noexcept { return ptr_[n]; }

      ConstVectorIterator& operator++()    noexcept { ++ptr_; return *this; }
      ConstVectorIterator  operator++(int) noexcept { ConstVectorIterator t(*this); ++ptr_; return t; }
      ConstVectorIterator& operator--()    noexcept { --ptr_; return *this; }
      ConstVectorIterator  operator--(int) noexcept { ConstVectorIterator t(*this); --ptr_; return t; }

      ConstVectorIterator& operator+=(difference_type n) noexcept { ptr_ += n; return *this; }
      ConstVectorIterator& operator-=(difference_type n) noexcept { ptr_ -= n; return *this; }

      ConstVectorIterator operator+(difference_type n) const noexcept { return ConstVectorIterator(ptr_ + n); }
      ConstVectorIterator operator-(difference_type n) const noexcept { return ConstVectorIterator(ptr_ - n); }
      difference_type operator-(const ConstVectorIterator& o) const noexcept { return ptr_ - o.ptr_; }

      friend ConstVectorIterator operator+(difference_type n, const ConstVectorIterator& it) noexcept {
        return ConstVectorIterator(it.ptr_ + n);
      }

      bool operator==(const ConstVectorIterator& o) const noexcept { return ptr_ == o.ptr_; }
      bool operator!=(const ConstVectorIterator& o) const noexcept { return ptr_ != o.ptr_; }
      bool operator< (const ConstVectorIterator& o) const noexcept { return ptr_ <  o.ptr_; }
      bool operator> (const ConstVectorIterator& o) const noexcept { return ptr_ >  o.ptr_; }
      bool operator<=(const ConstVectorIterator& o) const noexcept { return ptr_ <= o.ptr_; }
      bool operator>=(const ConstVectorIterator& o) const noexcept { return ptr_ >= o.ptr_; }

     private:
      const T* ptr_;
    };

    VectorIterator      begin()  noexcept       { return VectorIterator(data_); }
    VectorIterator      end()    noexcept       { return VectorIterator(data_ + size_); }
    ConstVectorIterator begin()  const noexcept { return ConstVectorIterator(data_); }
    ConstVectorIterator end()    const noexcept { return ConstVectorIterator(data_ + size_); }
    ConstVectorIterator cbegin() const noexcept { return ConstVectorIterator(data_); }
    ConstVectorIterator cend()   const noexcept { return ConstVectorIterator(data_ + size_); }

    ~Vector();
    Vector();
    Vector(size_t size, const T& value);
    explicit Vector(std::initializer_list< T > il);
    Vector(const Vector< T >& rhs);
    Vector(Vector< T >&& rhs) noexcept;
    Vector< T >& operator=(const Vector< T >& rhs);
    Vector< T >& operator=(Vector< T >&& rhs) noexcept;
    void swap(Vector< T >& rhs) noexcept;

    void insert(size_t id, const T& t);
    void insert(size_t id, const Vector< T >& rhs, size_t beg, size_t end);
    void erase(size_t id);
    void erase(size_t beg, size_t end);

    VectorIterator insert(VectorIterator pos, const T& value);
    VectorIterator insert(VectorIterator pos, size_t k, const T& value);
    template< class FwdIterator >
    VectorIterator insert(VectorIterator pos, FwdIterator first, FwdIterator last);

    VectorIterator erase(VectorIterator pos);
    VectorIterator erase(VectorIterator first, VectorIterator last);
    VectorIterator erase(VectorIterator first, VectorIterator last, const T& value);

    bool   isEmpty()    const noexcept;
    size_t getSize()    const noexcept;
    size_t getCapcity() const noexcept;

    void pushBack(const T&);
    void pushBackRepeat(const T&, size_t k);
    void popBack();
    void pushFront(const T&);

    T&       operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T&       at(size_t id);
    const T& at(size_t id) const;

   private:
    T*     data_;
    size_t size_, capacity_;

    explicit Vector(size_t size);
  };

  template< class T >
  bool operator==(const Vector< T >& lhs, const Vector< T >& rhs);

}

template< class T >
knk::Vector< T >::Vector(std::initializer_list< T > il):
  Vector(il.size())
{
  size_t j = 0;
  for (auto i = il.begin(); i != il.end(); ++i) {
    data_[j++] = *i;
  }
}
template< class T >
void knk::Vector< T >::pushBackRepeat(const T& t, size_t k)
{
  Vector< T > cpy(*this);
  for (size_t i = 0; i < k; ++i) {
    cpy.pushBack(t);
  }
  swap(cpy);
}
template< class T >
void knk::Vector< T >::pushBack(const T& t)
{
  Vector< T > v(getSize() + 1);
  for (size_t i = 0; i < getSize(); ++i) {
    v[i] = (*this)[i];
  }
  v[getSize()] = t;
  swap(v);
}
template< class T >
void knk::Vector< T >::pushFront(const T& t)
{
  Vector< T > v(getSize() + 1);
  v[0] = t;
  for (size_t i = 1; i < v.getSize(); ++i) {
    v[i] = (*this)[i - 1];
  }
  swap(v);
}
template< class T >
void knk::Vector< T >::popBack()
{
  if (isEmpty()) throw std::out_of_range("popBack on empty vector");
  erase(size_ - 1);
}
template< class T >
T& knk::Vector< T >::at(size_t id)
{
  const Vector< T >* cthis = this;
  const T& cr = cthis->at(id);
  T& r = const_cast< T& >(cr);
  return r;
}
template< class T >
const T& knk::Vector< T >::at(size_t id) const
{
  if (id < getSize()) {
    return (*this)[id];
  }
  throw std::out_of_range("id out of bound");
}
template< class T >
T& knk::Vector< T >::operator[](size_t id) noexcept {
  return const_cast< T& >((*static_cast< const Vector< T >* >(this))[id]);
}
template< class T >
const T& knk::Vector< T >::operator[](size_t id) const noexcept {
  return data_[id];
}
template< class T >
knk::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i) {
    data_[i] = rhs.data_[i];
  }
}
template< class T >
void knk::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}
template< class T >
knk::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
  Vector()
{
  swap(rhs);
}
template< class T >
knk::Vector< T >& knk::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}
template< class T >
knk::Vector< T >& knk::Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}
template< class T >
knk::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}
template< class T >
knk::Vector< T >::Vector(size_t size, const T& value):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i) {
    data_[i] = value;
  }
}
template< class T >
knk::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}
template< class T >
knk::Vector< T >::~Vector() {
  delete [] data_;
}
template< class T >
size_t knk::Vector< T >::getSize() const noexcept { return size_; }
template< class T >
bool knk::Vector< T >::isEmpty() const noexcept { return !size_; }
template< class T >
size_t knk::Vector< T >::getCapcity() const noexcept { return capacity_; }
template< class T >
void knk::Vector< T >::insert(size_t id, const T& t)
{
  if (id > size_) throw std::out_of_range("insert: id out of range");
  Vector< T > v(size_ + 1);
  for (size_t i = 0; i < id; ++i)     v[i]     = data_[i];
  v[id] = t;
  for (size_t i = id; i < size_; ++i) v[i + 1] = data_[i];
  swap(v);
}
template< class T >
void knk::Vector< T >::insert(size_t id, const Vector< T >& rhs, size_t beg, size_t end)
{
  if (id > size_ || beg > end || end > rhs.getSize())
    throw std::out_of_range("insert range: invalid arguments");
  size_t count = end - beg;
  Vector< T > v(size_ + count);
  for (size_t i = 0;  i < id;    ++i) v[i]         = data_[i];
  for (size_t i = 0;  i < count; ++i) v[id + i]    = rhs[beg + i];
  for (size_t i = id; i < size_; ++i) v[i + count] = data_[i];
  swap(v);
}
template< class T >
void knk::Vector< T >::erase(size_t id)
{
  if (id >= size_) throw std::out_of_range("erase: id out of range");
  Vector< T > v(size_ - 1);
  for (size_t i = 0;      i < id;    ++i) v[i]     = data_[i];
  for (size_t i = id + 1; i < size_; ++i) v[i - 1] = data_[i];
  swap(v);
}
template< class T >
void knk::Vector< T >::erase(size_t beg, size_t end)
{
  if (beg > end || end > size_) throw std::out_of_range("erase range: invalid arguments");
  size_t count = end - beg;
  Vector< T > v(size_ - count);
  for (size_t i = 0;   i < beg;   ++i) v[i]         = data_[i];
  for (size_t i = end; i < size_; ++i) v[i - count] = data_[i];
  swap(v);
}
template< class T >
typename knk::Vector< T >::VectorIterator
knk::Vector< T >::insert(VectorIterator pos, const T& value)
{
  size_t id = static_cast< size_t >(pos - begin());
  insert(id, value);
  return VectorIterator(data_ + id);
}
template< class T >
typename knk::Vector< T >::VectorIterator
knk::Vector< T >::insert(VectorIterator pos, size_t k, const T& value)
{
  size_t id = static_cast< size_t >(pos - begin());
  Vector< T > src(k, value);
  insert(id, src, 0, k);
  return VectorIterator(data_ + id);
}
template< class T >
template< class FwdIterator >
typename knk::Vector< T >::VectorIterator
knk::Vector< T >::insert(VectorIterator pos, FwdIterator first, FwdIterator last)
{
  size_t id = static_cast< size_t >(pos - begin());
  Vector< T > tmp;
  for (FwdIterator it = first; it != last; ++it) {
    tmp.pushBack(*it);
  }
  insert(id, tmp, 0, tmp.getSize());
  return VectorIterator(data_ + id);
}
template< class T >
typename knk::Vector< T >::VectorIterator
knk::Vector< T >::erase(VectorIterator pos)
{
  size_t id = static_cast< size_t >(pos - begin());
  erase(id);
  return VectorIterator(data_ + id);
}
template< class T >
typename knk::Vector< T >::VectorIterator
knk::Vector< T >::erase(VectorIterator first, VectorIterator last)
{
  size_t beg = static_cast< size_t >(first - begin());
  size_t end = static_cast< size_t >(last  - begin());
  erase(beg, end);
  return VectorIterator(data_ + beg);
}
template< class T >
typename knk::Vector< T >::VectorIterator
knk::Vector< T >::erase(VectorIterator first, VectorIterator last, const T& value)
{
  VectorIterator it = last;
  while (it != first) {
    --it;
    if (*it == value) {
      it = erase(it);
      first = begin();
      last  = it;
    }
  }
  return end();
}

#endif
