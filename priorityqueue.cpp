#pragma once
#include <iostream>
#include <vector>

template <class T, class Compare = std::less<T>> class PriorityQueue {
  using container_type = std::vector<T>;
  using value_compare = Compare;
  using value_type = T;
  using size_type = size_t;
  using reference = T &;
  using const_reference = const T &;

private:
  std::vector<T> data;
  Compare comparator{};

public:
  std::size_t min(std::size_t a, std::size_t b) {
    return comparator(data[a], data[b]) ? a : b;
  }
  // Создает пустую очередь с приоритетом
  PriorityQueue() = default; //: data(){};

  // Создает новую очередь с приоритетом, являющююся глубокой копией очереди
  // other [O(n)]
  PriorityQueue(const PriorityQueue &other) = default;

  // Перезаписывает текущую очередь с приоритетом очередью other
  PriorityQueue &operator=(const PriorityQueue &other) = default;

  PriorityQueue(std::initializer_list<T> initt) {
    for (auto i : initt) {
      push(i);
    }
  };

  // Создает новую очередь с приоритетом перемещая существующую [O(1)]
  PriorityQueue(PriorityQueue &&other) = default;
  // Присваивает текущую очередь с приоритетом очередью other
  PriorityQueue &operator=(PriorityQueue &&other) = default;

  PriorityQueue &operator==(PriorityQueue &&other) { return data == other; };

  // Очищает память очереди с приоритетом
  ~PriorityQueue() = default;

  // Получает ссылку на верхний элемент очереди с приоритетом
  const_reference top() const { return data[0]; }

  // Проверяет является ли контейнер пустым
  bool empty() const { return data.empty(); };

  // Возвращает размер очереди с приоритетом (сколько памяти уже занято)
  size_type size() const { return data.size(); };
  // Добавляет элемент в очередь с приоритетом
  void push(const value_type &value) {
    data.push_back(value);

    for (int i = data.size() - 1;
         i > 0 && !comparator(data[i], data[(i - 1) / 2]); i = (i - 1) / 2) {

      std::swap(data[i], data[(i - 1) / 2]);
    }
  }

  // Добавляет элемент в очередь с приоритетом
  void push(value_type &&value) {
    data.push_back(value);

    for (int i = data.size() - 1;
         i > 0 && !comparator(data[i], data[(i - 1) / 2]); i = (i - 1) / 2) {
      std::swap(data[i], data[(i - 1) / 2]);
    }
  }

  // Удаляет элемент из начала очереди с приоритетом. Возвращает удаленный
  // элемент.
  value_type pop() {
    std::swap(data[0], data[data.size() - 1]);
    value_type tmp = data[data.size() - 1];
    data.pop_back();

    size_t current = 0;
    size_t left = 0;
    size_t right = 0;
    size_t child = 0;
    while (true) {
      bool right_exist = right < data.size();
      bool left_exist = left < data.size();
      if (right_exist && comparator(data[left], data[right])) {
        child = right;
      } else if (!left_exist) {
        break;
      } else {
        child = left;
      }
      if (comparator(data[child], data[current])) {
        break;
      }
      std::swap(data[current], data[child]);
      current = child;
      left = current * 2 + 1;
      right = current * 2 + 2;
    }
    return tmp;
  }

  // // Меняет содержимое с другой очередью с приоритетом. q1.swap(q2);
  void swap(PriorityQueue &other) { std::swap(data, other.data); };
};
