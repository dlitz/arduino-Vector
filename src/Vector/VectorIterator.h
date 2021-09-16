// ----------------------------------------------------------------------------
// VectorIterator.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef VECTOR_ITERATOR_H
#define VECTOR_ITERATOR_H

template<typename T>
class VectorIterator
{
public:
  VectorIterator(T * values_ptr = nullptr) : values_ptr_{values_ptr}, position_{0} {}

  VectorIterator(T * values_ptr, size_t size) : values_ptr_{values_ptr}, position_{size} {}

  bool operator!=(const VectorIterator<T> & other) const
  {
    return !(*this == other);
  }

  bool operator==(const VectorIterator<T> & other) const
  {
    return position_ == other.position_;
  }

  VectorIterator & operator++()
  {
    ++position_;
    return *this;
  }

  VectorIterator & operator--()
  {
    --position_;
    return *this;
  }

  VectorIterator & operator+=(ptrdiff_t n)
  {
    position_ += n;
    return *this;
  }

  VectorIterator & operator-=(ptrdiff_t n)
  {
    position_ -= n;
    return *this;
  }

  VectorIterator operator++(int)
  {
    auto copy = *this;
    ++(*this);
    return copy;
  }

  VectorIterator operator--(int)
  {
    auto copy = *this;
    --(*this);
    return copy;
  }

  VectorIterator operator+(ptrdiff_t n) const
  {
    auto copy = *this;
    copy += n;
    return copy;
  }

  VectorIterator operator-(ptrdiff_t n) const
  {
    auto copy = *this;
    copy -= n;
    return copy;
  }

  T & operator*() const
  {
    return *(values_ptr_ + position_);
  }

private:
  T * values_ptr_;
  size_t position_;

public:
  class reverse_iterator {
  public:
    reverse_iterator(VectorIterator base = nullptr) : cur{base} {}
    VectorIterator base() const { return cur; }
    bool operator!=(const reverse_iterator & other) const { return base() != other.base(); }
    bool operator==(const reverse_iterator & other) const { return base() == other.base(); }
    reverse_iterator & operator++()               { --cur; return *this; }
    reverse_iterator & operator--()               { ++cur; return *this; }
    reverse_iterator & operator+=(ptrdiff_t n)    { cur -= n; return *this; }
    reverse_iterator & operator-=(ptrdiff_t n)    { cur += n; return *this; }
    reverse_iterator operator++(int)              { auto copy = *this; ++(*this); return copy; }
    reverse_iterator operator--(int)              { auto copy = *this; --(*this); return copy; }
    reverse_iterator operator+(ptrdiff_t n) const { auto copy = *this; copy += n; return copy; }
    reverse_iterator operator-(ptrdiff_t n) const { auto copy = *this; copy -= n; return copy; }
    T & operator*() const { return *cur; }
  private:
    VectorIterator cur;
  };

};

#endif
