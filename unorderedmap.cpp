#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>

template <class Key, class Value, class Hash = std::hash<Key>>
class UnorderedMap {
private:
  std::vector<std::list<std::pair<Key, Value>>> node;


public:
  class Iterator;
  class ConstIterator;
  // Создает пустой словарь
  UnorderedMap() : node(4){};
  friend Iterator;
  // // Создает новый UnorderedMap, являющийся глубокой копией other [O(n)]
  // // UnorderedMap<std::string, int>  map;
  // // map["something"] = 69;
  // // map["anything"] = 199;
  // // UnorderedMap<std::string, int> copied{map};
  // // copied["something"] == map["something"] == 69
  UnorderedMap(const UnorderedMap &other) = default;

  int hashing(const Key &key) const {
    int k = Hash{}(key);
    k = abs(k);
    k %= node.size();
    return k;
  }
  // Конструктор перемещения
  UnorderedMap(UnorderedMap &&other) = default;
  // Перезаписывает текущий словарь словарем other
  UnorderedMap &operator=(const UnorderedMap &other) = default;
  // Присваивание перемещением;l
  UnorderedMap &operator=(UnorderedMap &&other) = default;

  ~UnorderedMap() = default;
  // // Возвращает итератор на первый элемент
  Iterator begin() { return Iterator{1, node}; }
  // // Возвращает константный итератор на первый элемент
  ConstIterator begin() const { return ConstIterator{1, node}; };
  // // Возвращает итератор обозначающий конец контейнера (за последним
  // элементом)
  Iterator end() { return Iterator{0, node}; };
  // // Возвращает константный итератор, обозначающий конец контейнера
  ConstIterator end() const { return ConstIterator{0, node}; };
  // // Возвращает размер UnorderedMap (сколько элементов добавлено)
  std::size_t size() const {
    std::size_t counter = 0;
    for (size_t i = 0; i < node.size(); i++) {
      const auto &lists = node[i];
      for (const auto &li : lists) {
        counter++;
      }
    }
    return counter;
  }

  // // Проверяет является ли UnorderedMap пустым
  bool empty() const { return !size(); }

  // // Возвращает элемент по ключу. Если отсутсвует, выбрасывает исключение
  const Value &operator[](const Key &key) const {

    std::pair<Key, Value> temp = {{}, {}};
    std::pair<Key, Value> res = {{}, {}};
    if (contains(key) == true) {
      const auto &lis = node[hashing(key)];
      for (const auto &elements : lis) {
        if (key == elements.first) {
          return elements.second;
        }
      }
    }
    // if(find(key) != end()){
    //   return find(key).second;
    // }

    else {
      throw std::out_of_range("no elem");
    }
  };

  //  // Возвращает ссылку на элемент по Key (позволяет менять элемент). Если
  // // элемент с таким ключом отсутствует, создает его и инициализирует
  // дефолтным
  // // значением map["something"] = 75;
  Value &operator[](Key key) {
    auto list = find(key);
    if (list != end()) {
      return (*list).second;
    }

    if ((size() / node.size()) >= 4) {
      reheshing();
    }

    node[hashing(key)].push_back({key, Value{}});
    return node[hashing(key)].back().second;
  };

  // // Проверяет есть ли в контейнере элемент с таким Key
  bool contains(const Key &key) const {
    auto tempN = node[hashing(key)];
    int i = 0;
    while (tempN.size() > 0) {
      if (tempN.front().first == key) {
        return true;
      } else {
        tempN.pop_front();
      }
    }

    return false;
  };
  // // Возвращяет Итератор на элемент который ищем, если нет такого элемента
  // // возвращает итератор на последный элемент
  Iterator find(const Key &key) {
    std::size_t idx = hashing(key);

    if (node[hashing(key)].empty()) {
      return end();
    }

    Iterator it = begin();

    for (it.it_list = node[idx].begin();
         it.it_list != node[idx].end(); ++it) {
      if ((*it).first == key) {
        return it;
      }
    }
    return end();
  }

  bool size_check() {
    for (auto it = 0; it < node.size(); it++) {
      if (node[it].size() >= 4) {
        return true;
      } else {
        return false;
      }
    }
    return true;
  }
  // // Добавляет новый элемент с ключем и значением, если нет уже существуюшего
  // // элемента с таким же ключом Map<int, std::string> c =
  // //   {
  // //       {1, "one" }, {2, "two" }, {3, "three"},
  // //       {4, "four"}, {5, "five"}, {6, "six"  }
  // //   };
  // // c.(5,"something");
  // // возвращает false, потому что элмемент с key = 5 уже существует․
  bool insert(const Key &k, const Value &v) {
    if (size_check()) {
      // std::cout << "rehash was declered" << std::endl;
      reheshing();
      insert(k, v);
    } else if (contains(k) == true) {
      // std::cout << "there is no elem like that";
      return false;
    } else {
      std::pair<Key, Value> temp = {k, v};
      node[hashing(k)].push_back(temp);
    }
    return true;
  };
  // // Удаляет элемент по ключу и возвращает результат операции
  // // UnorderedMap<int, std::string> c =
  // //   {
  // //       {1, "one" }, {2, "two" }, {3, "three"},
  // //       {4, "four"}, {5, "five"}, {6, "six"  }
  // //   };
  // // c.erase(4) == true
  // // c =
  // //   {
  // //       {1, "one" }, {2, "two" }, {3, "three"},
  // //             {5, "five"}, {6,"six"  }
  // //   }; результат после erase
  bool erase(const Key &key) {
    size_t idx = std::hash<Key>{}(key);
    auto &collisions = node[hashing(key)];
    for (auto it = collisions.begin(); it != collisions.end(); ++it) {
      if (key == it->first) {
        collisions.erase(it);
        return true;
      }
    }
    return false;
  }

  void reheshing() {
    Key key;
    Value value;
    int k = 0;
    size_t ts = node.size() * 2;
    std::vector<std::list<std::pair<Key, Value>>> nodeREH(ts);
    std::list<std::pair<Key, Value>> templist;
    for (auto it = 0; it < node.size(); it++) {
      templist = node[it];
      for (auto itk : templist) {
        key = itk.first;
        value = itk.second;
        k = std::hash<Key>{}(key);
        k = abs(k);
        k %= ts;
        nodeREH[k].push_back({key, value});
      }
    }
    std::swap(node, nodeREH);
    // node = nodeREH;
  };

  class Iterator {
    using ValueType = std::pair<Key, Value>;

    std::pair<Key, Value> p_it;
    std::vector<std::list<ValueType>> &vec;

  public:
    std::size_t index;
    typename std::list<ValueType>::iterator it_list;
    // Заполнить
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::pair<Key, Value>;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;

    
    Iterator(bool is_begin, std::vector<std::list<ValueType>> &data)
        : vec(data) {
      if (is_begin) {
        for (int i = 0; i < data.size(); ++i) {
          if (!data[i].empty()) {
            it_list = data[i].begin();
            index = i;
            break;
          }
          it_list = data[i].end();
          index = i;
        }
      } else {
        it_list = data[data.size() - 1].end();
        index = data.size() - 1;
      }
    }
    bool operator!=(const typename std::list<ValueType>::iterator &other) {
      return it_list != other;
    }

    Iterator &operator++() {
      if (vec.empty()) {
        it_list = vec[0].begin();
        return *this;
      }

      if (it_list == vec[index].end()) {
        index++;
        it_list = vec[index].begin();
      } else {
        ++it_list;
      };

      if (index == vec.size() && it_list == vec[index].end()) {
        Iterator itt{0, vec};
        *this = itt;
      }
      return *this;
    }

    void operator=(const Iterator &other) {
      it_list = other.it_list;
      index = other.index;
      vec = other.vec;
    }
    bool operator!=(const Iterator &other) { return it_list != other.it_list; }
    bool operator==(const Iterator &other) { return it_list == other.it_list; }

    std::pair<Key, Value> &operator*() { return *it_list; }

  };

  class ConstIterator {
    Iterator it;

  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::pair<Key, Value>;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;

    ConstIterator(bool is_begin,
                  std::vector<std::list<std::pair<Key, Value>>> &data)
        : it{is_begin, data} {}

    ConstIterator &operator++() { ++it; }

    ConstIterator &operator--() { --it; }

    bool operator!=(const ConstIterator &other) { return it != other.it; }

    bool operator==(const ConstIterator &other) { return it == other.it; }

    // единственное отличие от Iterator, что возвращает константную ссылку
    const std::pair<const Key, Value> &operator*() { return *it; }
  };
};
