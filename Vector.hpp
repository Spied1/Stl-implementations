#pragma once
#include <iostream>
#include <initializer_list>

template <class T>
class Vector 
{
public:
    // Creates vector with size of arr_size 
    Vector(std::size_t arr_size = 0) :
        capacityOfVec(arr_size * 2 + 1),
        vector(new T[capacityOfVec]{}),
        last_point(0) 
    {

    }; 

    Vector(std::initializer_list<T> initt) :vector(new T[initt.size()]{}) 
    {
        int j = 0;
        for (auto i : initt) 
        {
            push_back(i);
        }
    };


    //Returns copy of element with index
    T operator[](std::size_t index) const 
    { 
        return vector[index]; 
    };

    // Returns capacity
    std::size_t capacity() 
    {
        return capacityOfVec; 
    };

    // Creates a new vector with deep copy of other
    Vector(const Vector& other) :
        capacityOfVec(other.capacityOfVec),
        vector(new T{ other.capacityOfVec })
    {
        for (int i = 0; i != capacityOfVec; i++) 
        {
            this->vector[i] = other.vector[i];
        }
        last_point = other.last_point;
    };

    // Returns adress of element through index
    T& operator[](std::size_t index) 
    {
        return vector[index];
    };

    // Returns element in end of the vector with possible resize
    void push_back(const T& x) 
    {
        if (last_point == capacityOfVec) 
        {
            resize(capacityOfVec * 2 + 1);
            vector[last_point] = x;
            last_point++;
        }
        else 
        {
            vector[last_point] = x;
            last_point++;
        }
    };

    // Doing resize of vector
    void resize(std::size_t new_capacity) {
        if (new_capacity >= capacityOfVec) {
            T* vectTEMP = new T[new_capacity]{};
            for (auto i = 0; i != new_capacity; i++) {
                vectTEMP[i] = vector[i];
            }
            delete[] vector;
            capacityOfVec = new_capacity;
            vector = vectTEMP;
        }

        else if (new_capacity < capacityOfVec) {
            T* vectTEMP = new T[new_capacity]{};
            for (auto i = 0; i != capacityOfVec; i++) {
                vectTEMP[i] = vector[i];
            }
            delete[] vector;
            capacityOfVec = new_capacity;
            vector = vectTEMP;
        }

    };

    // Rewrites vector with other
    Vector& operator=(const Vector& other) 
    {
        delete[] vector;
        capacityOfVec = other.capacityOfVec;
        T* vector = new T[other.capacityOfVec];
        last_point = other.last_point;
        for (int i = 0; i != capacityOfVec + 1; i++) 
        {
            vector[i] = other.vector[i];
        }

        return *this;
    };

    // Returns size of vector 
    std::size_t size() 
    {
        return last_point;
    };

    // Checks if container is empty
    bool empty() 
    {
        return !last_point;
    };





    // Delets the last element and returns it(for tests)
    T pop_back() 
    {
        int value = 0;
        value = vector[last_point - 1];
        vector[last_point - 1] = {};
        last_point--;
        return value;
    };

    // Clears elements without changing capacity
    void clear() 
    {
        last_point = 0;
    };


    // Changes an element in given index
    void insert(const size_t pos, T value) 
    {

        push_back(value);
        for (int i = last_point - 1; i > pos; --i) 
        {
            std::swap(vector[i], vector[i - 1]);
        }

    }; 

    // Delets element on given position
    T erase(const size_t pos) 
    {
        int val = vector[pos];
        for (int i = last_point - 1; i > pos; --i) 
        {
            std::swap(vector[i], vector[i - 1]);
        }
        vector[pos] = {};
        last_point--;

        return val;



    };





    ~Vector() { delete[] vector; };



private:
    std::size_t capacityOfVec = 0;
    T* vector = 0;
    std::size_t last_point = 0;
    std::size_t arr_size;
};
