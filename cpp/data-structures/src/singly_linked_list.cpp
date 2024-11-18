#include <iostream>

template <typename T> class SinglyLinkedList {
private:
  struct Node {
    T data;
    Node *next{nullptr};
  };

  Node *m_head{nullptr};
  Node *m_tail{nullptr};

public:
  SinglyLinkedList();
  ~SinglyLinkedList();
  void append(const T &);
  Node *head();
  Node *tail();
};

template <typename T> SinglyLinkedList<T>::SinglyLinkedList() {}

template <typename T> SinglyLinkedList<T>::~SinglyLinkedList() {
  Node *current = m_head;

  while (current) {
    Node *next = current->next;
    delete current;
    current = next;
  }

  std::cout << "List destroyed" << std::endl;
}

template <typename T> void SinglyLinkedList<T>::append(const T &data) {
  Node *node = new Node{data, nullptr};

  if (m_tail) {
    m_tail->next = node;
    m_tail = node;
  } else {
    m_head = m_tail = node;
  }
}

template <typename T>
typename SinglyLinkedList<T>::Node *SinglyLinkedList<T>::head() {
  return m_head;
}

template <typename T>
typename SinglyLinkedList<T>::Node *SinglyLinkedList<T>::tail() {
  return m_tail;
}

int main() {
  SinglyLinkedList<char> list;
  list.append('l');
  list.append('e');
  list.append('e');
  list.append('t');

  std::cout << list.head()->data << std::endl;
  std::cout << list.tail()->data << std::endl;

  return 0;
}
