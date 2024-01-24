#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

namespace s21 {

template <class T>
class vector {
 public:
  class VectorIterator {
    friend class s21::vector<T>;

    using value_type = T;
    using pointer = T *;

   public:
    VectorIterator() { ptr_ = nullptr; }
    VectorIterator(pointer ptr) { ptr_ = ptr; }

    value_type &operator*() const { return (*ptr_); }

    VectorIterator &operator++() {
      ptr_++;
      return *this;
    }

    VectorIterator &operator--() {
      ptr_--;
      return *this;
    }

    VectorIterator operator+(const size_t value) {
      VectorIterator tmp(this->ptr_ + value);
      return tmp;
    }

    VectorIterator operator-(const size_t value) {
      VectorIterator tmp(this->ptr_ - value);
      return tmp;
    }

    bool operator==(const VectorIterator &other) { return ptr_ == other.ptr_; }

    bool operator!=(const VectorIterator &other) { return ptr_ != other.ptr_; }

   private:
    pointer ptr_;
  };

  class VectorConstIterator {
    friend class s21::vector<T>;

    using value_type = T;
    using pointer = T *;

   public:
    VectorConstIterator() { ptr_ = nullptr; };
    VectorConstIterator(pointer ptr) { ptr_ = ptr; };
    value_type operator*() const { return (*ptr_); }

    VectorConstIterator &operator++() {
      ptr_++;
      return *this;
    }

    VectorConstIterator &operator--() {
      ptr_--;
      return *this;
    }

    bool operator==(const VectorConstIterator &other) {
      return ptr_ == other.ptr_;
    }

    bool operator!=(const VectorConstIterator &other) {
      return ptr_ != other.ptr_;
    }

   private:
    pointer ptr_;
  };

  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using pointer = value_type *;
  using iterator = VectorIterator;
  using const_iterator = VectorConstIterator;

  explicit vector() : array_(nullptr), size_(0), capacity_(0) {}
  explicit vector(size_type n) {
    if (n > max_size()) {
      throw std::length_error("The size cannot be larger than the max size");
    }
    size_ = n;
    capacity_ = n;
    array_ = new value_type[n];
  }
  explicit vector(std::initializer_list<value_type> const &items);
  explicit vector(const vector<value_type> &v);
  explicit vector(vector<value_type> &&v);
  ~vector() { delete[] array_; }
  vector &operator=(vector &&v) noexcept;

  // access specified element with bounds checking
  reference at(size_type pos);
  reference operator[](size_type pos);
  // access the first element
  const_reference front() const noexcept {
    return size_ > (size_type)0 ? array_[0] : nullptr;
  }
  // access the last element
  const_reference back() const noexcept {
    return size_ > (size_type)0 ? array_[size_ - 1] : nullptr;
  }
  // direct access to the underlying array
  pointer data() const noexcept { return array_; }

  iterator begin() const { return iterator(array_); }
  iterator end() const { return iterator(array_ + size_); }
  const_iterator cbegin() const { return const_iterator(array_); }
  const_iterator cend() const { return const_iterator(array_ + size_); }

  bool empty() { return size_ == 0; }
  size_type size() { return size_; }
  size_type max_size() { return std::numeric_limits<size_type>::max() / 2; }
  // allocate storage of size elements and copies current array elements to a
  // newely allocated array
  void reserve(size_type size);
  size_type capacity() { return capacity_; }
  // reduces memory usage by freeing unused memory
  void shrink_to_fit() noexcept;

  void clear() noexcept;
  // inserts elements into concrete pos and returns the iterator that points to
  // the new element
  iterator insert(s21::vector<value_type>::iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back() { size_ = size_ > 0 ? size_ - 1 : 0; }
  void swap(vector &other);

 private:
  pointer array_;
  size_type size_;
  size_type capacity_;
};

}  // namespace s21

#include "./vector.tpp"
