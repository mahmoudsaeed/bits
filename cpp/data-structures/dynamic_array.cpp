#include <iostream>
#include <initializer_list>

template <class T, size_t init_len = 10>
class dynamic_array {
  private:
    T *ptr_arr;
    size_t next_index;
    size_t len;

  public:
    dynamic_array(std::initializer_list<T>);
    dynamic_array();
    ~dynamic_array();
    T& operator[](size_t);
    size_t size();
};

template <class T, size_t init_len>
dynamic_array<T, init_len>::dynamic_array() {
  len = init_len;
  next_index = 0;
  ptr_arr = new T[len];

  for (size_t i = 0; i < len; i++)
    ptr_arr[i] = 0;
}

template <class T, size_t init_len>
dynamic_array<T, init_len>::dynamic_array(std::initializer_list<T> list) {
  len = list.size();
  next_index = 0;
  ptr_arr = new T[len];

  size_t i = 0;
  for (size_t e : list) {
    ptr_arr[i] = e;
    i++;
  }
}

template <class T, size_t init_len>
dynamic_array<T, init_len>::~dynamic_array() {
  delete [] ptr_arr;
}

template <class T, size_t init_len>
T& dynamic_array<T, init_len>::operator[] (size_t index) {
  T *ptr_new_arr;

  if (index >= len) {
    const size_t new_len = index * 2;
    len = new_len;

    ptr_new_arr = new T[new_len];

    for (size_t i = 0; i < next_index; i++)
      ptr_new_arr[i] = ptr_arr[i];

    for (size_t j = next_index; j < new_len; j++)
      ptr_new_arr[j] = 0;

    delete []ptr_arr;
    ptr_arr = ptr_new_arr;
  }

  if (index > next_index)
    next_index = index + 1;

  return *(ptr_arr + index);
}

template <class T, size_t init_len>
size_t dynamic_array<T, init_len>::size () {
  return len;
}

int main() {
  dynamic_array<int> fib = {1, 1, 2, 3, 5, 7, 13};

  std::cout << "size of fib[] is " << fib.size() << std::endl;
  for (size_t i = 0; i < fib.size(); i++)
    std::cout << "fib[" << i << "] = " << fib[i] << std::endl;

  fib[5] = 8;
  std::cout << "now fib[5] = " << fib[5] << std::endl;

  fib[7] = 20;
  std::cout << std::endl << "now fib[7] = " << fib[7] << std::endl;
  std::cout << "now size of fib[] is " << fib.size() << std::endl;

  return 0;
}
