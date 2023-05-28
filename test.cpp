#include <iostream>
#include <vector>

// myallocator在c++20中被弃用了

template <typename T>
class MyAllocator {
 public:
  using value_type = T; // Define the value_type alias required by the allocator interface

  MyAllocator() noexcept {} // Define a default constructor
  template <class U>
  MyAllocator(const MyAllocator<U>&) noexcept {} // Define a copy constructor

  T* allocate(std::size_t n) { // Define the allocate method to allocate memory for n elements
    std::cout << "Allocating " << n << " elements" << std::endl; // Print a message to indicate the allocation
    return static_cast<T*>(::operator new(n * sizeof(T))); // Allocate memory using the global operator new function
  }

  void deallocate(T* p, std::size_t n) noexcept { // Define the deallocate method to deallocate memory for n elements
    std::cout << "Deallocating " << n << " elements" << std::endl; // Print a message to indicate the deallocation
    delete(p); // Deallocate memory using the global operator delete function
  }

  template <typename... Args>
  void construct(T* p, Args&&... args) { // Define the construct method to construct an element at the given memory address p
    std::cout << "Constructing element" << std::endl; // Print a message to indicate the construction
    new (static_cast<void*>(p)) T(std::forward<Args>(args)...); // Use placement new to construct an element at the given memory address
  }

  void destroy(T* p) { // Define the destroy method to destruct an element at the given memory address p
    std::cout << "Destroying element" << std::endl; // Print a message to indicate the destruction
    p->~T(); // Call the destructor of the element
  }
};

int main() {
  std::vector<int, MyAllocator<int>> my_vector({1, 2, 3}); // Create a vector of integers using the custom allocator
  my_vector.push_back(4); // Push a new element onto the vector
  return 0;
}
