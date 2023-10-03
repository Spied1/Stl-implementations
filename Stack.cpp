#pragma once
#include <iostream>
#include <vector>
template <class T> 
class Stack {

public:
  // Создает пустой стэк
  Stack()
      : stackVec()
  {}

  Stack(std::initializer_list<T> el):Stack(new T[el.size()]{}){
    int j = 0;
    for(auto i : el){
      stackVec.push_back(i);
    }
  };
  // Создает новый стэк, являющийся глубокой копией списка other [O(n)]
  Stack(const Stack &other):stackVec(other.stack){
  };



  // Перезаписывает текущий стэк стэком other
  Stack &operator=(const Stack &other){
    //stackVec(other.stackVec){};//https://ravesli.com/urok-117-spisok-initsializatsii-chlenov-klassa/
      stackVec = other.stackvec;
    }
  // Возвращает размер стэка (сколько памяти уже занято)
  std::size_t size() { return stackVec.size(); };

  // Проверяет является ли контейнер пустым
  bool empty() {
    return stackVec.empty();
  };

  // Добавляет элемент на верх стэка.
  void push(const T &x) {
    stackVec.push_back(x);
  };

  // Получает элемент на верху стэка
  T &top() {
    if(stackVec.size() == 0){
      throw
      std::runtime_error{"nothing on top"};
    }
    else{
    return stackVec[stackVec.size() - 1]; }
    };

  // Удаляет последний элемент стэка. Возвращает удаленный элемент.
  T pop() {
    if (stackVec.size() >= 0) {
      T value;
      value = stackVec[stackVec.size() - 1];
      //stackVec.erase(stackVec.begin()+(stackVec.size() - 1));
      stackVec.pop_back();
    }
    else{
      //std::cout << "error,no elements in vec to pop";
      throw
      std::runtime_error{"error,no elements in vec to pop"};
    }
  }; //+

  // Меняет содержимое с другим стэком. s1.swap(s2);
  void swap(/*const*/ Stack &other){
    // Stack<T> TempStack{stackVec.szie()};  
    // TempStack = other.stackVec;
    // other.stackVec = stackVec;
    // stackVec = TempStack;


//stackVec.swap(&other);
    stackVec.swap(other.stackVec);
  };

  Stack reverse() {
    Stack stackReversed;
    for(auto i = 0;i != stackVec.size();i++){
      stackReversed[i] = stackVec[stackVec - i];

      
    }
    return stackReversed;
  }
  ~Stack(){

  };

private:
  std::vector<T>  stackVec; //стек
  // size_t lp = 0;//последняя точка
};