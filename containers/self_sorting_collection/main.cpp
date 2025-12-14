#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <memory>

#include <iostream>
#include <stdexcept>

#include <format>
#include <tuple>

template <typename SortableType> class SelfSortingCollection {
public:
  SelfSortingCollection(size_t capacity = 10)
      : _size(0), _capacity(capacity),
        _collection(std::make_unique<SortableType[]>(capacity)) {}

  SelfSortingCollection(const SelfSortingCollection &other)
      : _size(other._size), _capacity(other._capacity),
        _collection(std::make_unique<SortableType[]>(other._capacity)) {
    std::copy(other._collection.get(), other._collection.get() + other._size,
              _collection);
  }

  SelfSortingCollection &operator=(const SelfSortingCollection &other) {

    if (this == &other) {
      return this;
    }

    auto collection = std::make_unique<SortableType[]>(other._capacity);
    std::copy(other._collection.get(), other._collection.get() + other._size,
              collection.data());
    _collection = std::move(collection);
    _size = other._size;
    _capacity = other._capacity;
    return *this;
  }

  SelfSortingCollection(SelfSortingCollection &&) noexcept = default;
  SelfSortingCollection &operator=(SelfSortingCollection &&) noexcept = default;
  ~SelfSortingCollection() = default;

  void print() const {
    std::cout << "[";
    if (_size > 0) {
      auto it = begin();
      std::cout << *it;
      it = it + 1;
      for (; it != end(); ++it) {
        std::cout << ", " << *it;
      }
    }
    std::cout << "]\n";
  }
  size_t size() const { return _size; }
  size_t capacity() const { return _capacity; }
  size_t available_space() const { return _capacity - _size; }
  bool empty() const { return _size == 0; }

  const SortableType &operator[](std::size_t index) {

    if (index >= _size) {
      throw std::out_of_range(std::format("Index {} is out of bounds", index));
    }

    return _collection[index];
  }
  void add(const SortableType &item) {

    auto index = find_index(item);

    if (_size == _capacity) {
      expand();
    }

    if (index != _size) {
      auto elements_to_move = _size - index;
      std::move_backward(_collection.get() + index, _collection.get() + _size,
                         _collection.get() + _size + 1);
    }

    _collection[index] = item;
    _size = _size + 1;
  }

  SortableType get(const size_t index) const {

    if (index >= _size) {
      const auto msg = std::format("Index {} is out of bounce", index);
      throw std::out_of_range(msg);
    }
    // Throw exception index out of bounds
    return _collection[index];
  }

private:
  size_t find_index(const SortableType item) const {
    if (_size == 0 || item < _collection[0]) {
      return 0;
    }

    if (item > _collection[_size - 1]) {
      return _size;
    }

    auto bound =
        std::lower_bound(_collection.get(), _collection.get() + _size, item);
    return std::distance(_collection.get(), bound);
  }

  // If no expansion provided it will be expand by _capacity / 2
  void expand(size_t expansion = 0) {

    if (expansion == 0) {
      expansion = _capacity / 2;
    }

    const auto capacity = _capacity + expansion;
    auto new_data = std::make_unique<SortableType[]>(capacity);
    std::move(_collection.get(), _collection.get() + _size, new_data.get());
    _collection = std::move(new_data);
    _capacity = capacity;
  }

private:
  std::unique_ptr<SortableType[]> _collection;
  size_t _size;
  size_t _capacity;

public:
  class iterator {
  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = SortableType;
    using difference_type = std::ptrdiff_t;
    using pointer = SortableType *;
    using reference = SortableType &;

    iterator() = default;
    explicit iterator(SortableType *ptr) : _ptr(ptr) {}

    // Dereference
    reference operator*() const { return *_ptr; }
    pointer operator->() const { return _ptr; }

    // Increment / decrement
    iterator &operator++() {
      ++_ptr;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp(*this);
      ++_ptr;
      return tmp;
    }
    iterator &operator--() {
      --_ptr;
      return *this;
    }
    iterator operator--(int) {
      iterator tmp(*this);
      --_ptr;
      return tmp;
    }

    // Arithmetic
    iterator &operator+=(difference_type n) {
      _ptr += n;
      return *this;
    }
    iterator &operator-=(difference_type n) {
      _ptr -= n;
      return *this;
    }
    iterator operator+(difference_type n) const { return iterator(_ptr + n); }
    iterator operator-(difference_type n) const { return iterator(_ptr - n); }
    difference_type operator-(const iterator &other) const {
      return _ptr - other._ptr;
    }

    // Comparison
    bool operator==(const iterator &other) const { return _ptr == other._ptr; }
    bool operator!=(const iterator &other) const { return _ptr != other._ptr; }
    bool operator<(const iterator &other) const { return _ptr < other._ptr; }
    bool operator>(const iterator &other) const { return _ptr > other._ptr; }
    bool operator<=(const iterator &other) const { return _ptr <= other._ptr; }
    bool operator>=(const iterator &other) const { return _ptr >= other._ptr; }

  private:
    SortableType *_ptr{nullptr};
  };

  iterator begin() { return iterator(_collection.get()); }
  iterator end() { return iterator(_collection.get() + _size); }
  iterator begin() const { return iterator(_collection.get()); }
  iterator end() const { return iterator(_collection.get() + _size); }
};

int main(void) {
  SelfSortingCollection<int> col{};

  std::cout << "Collection is empty: " << (col.empty() ? "True" : "False")
            << "\n";
  for (size_t i = 0; i < 10; ++i) {
    col.add(static_cast<int>(i));
  }

  col.add(20);
  col.add(10);
  col.add(15);
  col.add(17);
  col.add(6);
  col.add(16);

  col.print();
  std::cout << "Collection is empty: " << (col.empty() ? "True" : "False")
            << "\n";
}