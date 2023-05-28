#include <iostream>
#include <vector>
#include <memory>

// A custom allocator that prints some messages
template <class T>
struct MyAlloc {
  using value_type = T;

  MyAlloc() = default;
  template <class U> constexpr MyAlloc(const MyAlloc<U>&) noexcept {}

  [[nodiscard] ] T* allocate(std::size_t n) {
    std::cout << "Allocating " << n << " elements of type " << typeid(T).name() << "\n";
    return static_cast<T*>(::operator new(n*sizeof(T)));
  }

  void deallocate(T* p, std::size_t n) noexcept {
    std::cout << "Deallocating " << n << " elements of type " << typeid(T).name() << "\n";
    ::operator delete(p);
  }
};

// A custom vector class that uses std::allocator_traits 
template <class T, class Alloc = std::allocator<T>>
class MyVector {
  using traits = std::allocator_traits<Alloc>;
public:
  using value_type = T;
  using allocator_type = Alloc;
  using size_type = typename traits::size_type;
  using pointer = typename traits::pointer;
  using const_pointer = typename traits::const_pointer;
  using reference = value_type&;
  using const_reference = const value_type&;

  explicit MyVector(const Alloc& alloc = Alloc()) : alloc_(alloc) {
    data_ = traits::allocate(alloc_, capacity_);
    size_ = 0;
  }

  ~MyVector() {
    clear();
    traits::deallocate(alloc_, data_, capacity_);
  }

  void push_back(const T& value) {
    if (size_ == capacity_) {
      reserve(2 * capacity_);
    }
    traits::construct(alloc_, data_ + size_, value);
    ++size_;
  }

  void pop_back() {
    if (size_ > 0) {
      --size_;
      traits::destroy(alloc_, data_ + size_);
    }
  }

  void clear() {
    for (size_type i = 0; i < size_; ++i) {
      traits::destroy(alloc_, data_ + i);
    }
    size_ = 0;
  }

  void reserve(size_type new_cap) {
    if (new_cap > capacity_) {
      pointer new_data = traits::allocate(alloc_, new_cap);
      for (size_type i = 0; i < size_; ++i) {
        traits::construct(alloc_, new_data + i, std::move(data_[i]));
        traits::destroy(alloc_, data_ + i);
      }
      traits::deallocate(alloc_, data_, capacity_);
      data_ = new_data;
      capacity_ = new_cap;
    }
  }

  reference operator[](size_type pos) { return data_[pos]; }
  const_reference operator[](size_type pos) const { return data_[pos]; }

private:
  pointer data_;
  size_type size_;
  size_type capacity_ = 10;
  Alloc alloc_;
};

int main() {
  
  // Use a custom allocator with a custom vector
  MyVector<int, MyAlloc<int>> v1;
  std::vector<int, MyAlloc<int>> v2({1,2,3}); 
  MyVector<int> v3; // None Output 

}
