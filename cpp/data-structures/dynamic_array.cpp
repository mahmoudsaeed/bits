#include <iostream>
#include <initializer_list>

template <class T, size_t initLen = 10>
class DynArr
{
  T* m_pArr;
  size_t m_nextIndex;
  size_t m_len;

  public:
    DynArr(std::initializer_list<T>);
    DynArr();
    ~DynArr();
    T& operator[](size_t);
    size_t size();
};

template <class T, size_t initLen>
DynArr<T, initLen>::DynArr() {
  m_len = initLen;
  m_nextIndex = 0;
  m_pArr = new T[m_len];

  for (size_t i = 0; i < m_len; i++)
    m_pArr[i] = 0;
}

template <class T, size_t initLen>
DynArr<T, initLen>::DynArr(std::initializer_list<T> list) {
  m_len = list.size();
  m_nextIndex = 0;
  m_pArr = new T[m_len];

  size_t i = 0;
  for (size_t e : list) {
    m_pArr[i] = e;
    i++;
  }
}

template <class T, size_t initLen>
DynArr<T, initLen>::~DynArr() {
  delete []m_pArr;
}

template <class T, size_t initLen>
T& DynArr<T, initLen>::operator[] (size_t index) {
  T* pNewArr;

  if (index >= m_len) {
    const size_t newLen = index * 2;
    m_len = newLen;

    pNewArr = new T[newLen];

    for (size_t i = 0; i < m_nextIndex; i++)
      pNewArr[i] = m_pArr[i];

    for (size_t j = m_nextIndex; j < newLen; j++)
      pNewArr[j] = 0;

    delete []m_pArr;
    m_pArr = pNewArr;
  }

  if (index > m_nextIndex)
    m_nextIndex = index + 1;

  return *(m_pArr + index);
}

template <class T, size_t initLen>
size_t DynArr<T, initLen>::size () {
  return m_len;
}

int main() {
  DynArr<int> fib {1, 1, 2, 3, 5, 7, 13};

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
