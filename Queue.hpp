#pragma once
#include <initializer_list>
#include <iostream>
#include <list>

template <class T> 
class Queue {
public:
  // Создает пустую очередь
  Queue() : QueueList() {} //+

  Queue(std::initializer_list<T> el) : Queue() {
    int j = 0;
    for (auto i : el) {
      QueueList.push_back(i);
    }
  };

  // Создает новую очередь, являющююся глубокой копией очереди other [O(n)]
  Queue(const Queue &other) { QueueList = other.QueueList; };

  // Добавляет элемент в конец очереди.
  void push(const T &x) { QueueList.push_back(x); }; 

  // Возвращает размер очереди (сколько памяти уже занято)
  std::size_t size() { return QueueList.size(); }; 

  // Получает ссылку на первый элемент очереди
  T &front() { return QueueList.front(); }; 

  // Получает ссылку на последний элемент очереди
  T &back() { return QueueList.end(); }; 

  // Проверяет является ли контейнер пустым
  bool empty() { return QueueList.empty(); }; 

  // Удаляет элемент из начала очереди. Возвращает удаленный элемент.
  T pop() {
    if (QueueList.size() > 0) {
      T value = QueueList.back();
      QueueList.pop_back();

      return value;
    } else {
      throw std::runtime_error{"nothing to pop"};
    }
  }; //+

  // Меняет содержимое с другой очередью. q1.swap(q2);
  void swap(Queue &other) { QueueList.swap(other.QueueList); }; 
  // Очищает память очереди
  ~Queue(){

  }; //+

  std::list<T> giveElement() { return QueueList; }

  // Перезаписывает текущую очередь очередью other
  Queue &operator=(const Queue &other) { QueueList = other.QueueList; }; 

  // Создает новую очередь перемещая существующую
  Queue(Queue &&other) {
    QueueList = move(other.QueueList);
    // return other.QueueList;
  };

  // Перезаписывает текущую очередь очередью other
  Queue &operator=(Queue &&other) {
    QueueList = move(other.QueueList);
    return &QueueList;
  };

  template <typename A>
  friend std::ostream& operator<<(std::ostream& out, const Queue<A>&);
  //friend Queue<T> concat(const Queue<T> &que);
private:
  std::list<T> QueueList;
};

template <typename A> 
Queue<A> concat(Queue<A> other1, Queue<A> other2) {
  std::list<A> first = other1.giveElement();
  std::list<A> second = other2.giveElement();
  Queue<A> Merged;
  for (auto i : first) {
    Merged.push(i);
  }
  for (auto i : second) {
    Merged.push(i);
  }
  return Merged;
};


template <typename A> 
std::ostream& operator<<(std::ostream& out, const Queue<A>& other){
  out << "aaaaaaaa";
 return out; 
}
