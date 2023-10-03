#pragma once
#include <iostream>
#include <initializer_list>

template <class T> class Vector {
public:
  // Создает вектор размера arr_size заполненный дефолтными значениями типа T
  Vector(std::size_t arr_size = 0):
    capacityOfVec(arr_size * 2 + 1),
    vector(new T[capacityOfVec]{}),
    last_point(0){ 
  }; //✓//+

  Vector(std::initializer_list<T> initt):vector(new T[initt.size()]{}){
    int j = 0;
    for(auto i : initt){
      push_back(i);
    }
  };


  // Возвращает копию элемента по индексу
  T operator[](std::size_t index) const { return vector[index]; }; //✓//+

  // Возвращает размер выделенной памяти
  std::size_t capacity() { return capacityOfVec; }; //✓//+

  // Создает новый вектор, являющийся глубокой копией вектора other
  Vector(const Vector &other):
    capacityOfVec(other.capacityOfVec),
    vector(new T{other.capacityOfVec})
  {
    for (int i = 0; i != capacityOfVec; i++) {
      this->vector[i] = other.vector[i];
    }
    last_point = other.last_point;
  }; //!!//?

  // Возвращает ссылку на элемент по индексу (позволяет менять элемент, типа
  // v[5] = 42;)
  T & operator[](std::size_t index) {
    

    return vector[index];
  }; //!!//+

  // Добавляет элемент в конец вектора. Если нужно перевыделяет память
  void push_back(const T &x) {
    if(last_point == capacityOfVec){
      resize(capacityOfVec * 2 + 1);
      vector[last_point] = x;
      last_point++;
    }
    else{
    vector[last_point] = x;
    last_point++;}
  }; //!!//+

  // Перевыделяет память:
  // * выделяет новый кусок памяти размером равным new_capacity, +
  // * копирует столько старых элементов, сколько влезает, +
  // * удаляет старый кусок памяти. ?
  void resize(std::size_t new_capacity) {
    if(new_capacity >= capacityOfVec){
  T* vectTEMP = new T[new_capacity]{};
    for(auto i = 0;i != new_capacity;i++){
      vectTEMP[i] = vector[i]; 
    }
    delete[] vector;
    capacityOfVec = new_capacity;
    vector = vectTEMP;
      }

    else if(new_capacity < capacityOfVec){
      T* vectTEMP = new T[new_capacity]{};
    for(auto i = 0;i != capacityOfVec;i++){
      vectTEMP[i] = vector[i]; 
    }
    delete[] vector;
    capacityOfVec = new_capacity;
    vector = vectTEMP;
    }
    
  }; 

  // Перезаписывает текущий вектор вектором other
  // Vector v1{5}, v2{10};
  // v1 = v2;
  // std::cout << v1.size() == 10 << std::endl // True
  Vector &operator=(const Vector &other){
    delete[] vector;
    capacityOfVec = other.capacityOfVec;
    T *vector = new T[other.capacityOfVec];
    last_point = other.last_point;
    for (int i = 0; i != capacityOfVec + 1; i++) {
       vector[i] = other.vector[i];
    }
    
    return *this;
  };

  // Возвращает размер вектора (сколько памяти уже занято) 
  std::size_t size(){

    return last_point;
  };//!!//+

  // Проверяет является ли контейнер пустым
  bool empty(){
      return !last_point;
  }; //!!//+




  
  // Удаляет последний элемент вектора и возвращает его. 
  T pop_back() {
    int value = 0;
    value = vector[last_point -1];
    vector[last_point -1] = {};
    last_point--;
    //before_point--;
    return value;
  }; //!!//+

  // Очищает вектор (выделенная память остает выделенной)
  void clear(){
    last_point = 0;
  }; //!!//-


  // Вставляет новый элемент value на место pos.
  // [1, 2, 3].insert(1, 42) -> [1, 42, 2, 3]
  void insert(const size_t pos, T value){ //1 4
    
      push_back(value);
		for (int i = last_point - 1; i > pos; --i) {
			std::swap(vector[i], vector[i - 1]);
		}

  }; //!!//+
  
  // Удаляет элемент с идексом pos. Возвращает удаленный элемент.
  // [1, 2, 3].erase(1) -> [1, 3] (return 2)
  T erase(const size_t pos){
    int val = vector[pos];
		for (int i = last_point - 1; i > pos; --i) {
			std::swap(vector[i], vector[i - 1]);
		}
    vector[pos] = {};
    last_point--;
    
    return val;
    
    
      
  };




  
  ~Vector() { delete[] vector; } //✓



private:
  std::size_t capacityOfVec = 0;
  T *vector = 0;
  std::size_t last_point = 0;
  std::size_t arr_size;
};
