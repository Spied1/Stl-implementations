#pragma once
#include <iostream>
#include <initializer_list>

template<typename T>
	class vector
	{
	private:
		size_t m_capacity;
		size_t m_size;
		T* m_arr;
	public:
		vector(size_t size = 0) :
			m_size(size),
			m_capacity(m_size * 2 + 1),
			m_arr(new T[m_capacity])
		{

		}

		vector(const nstd::vector<T> & other)
		{
			m_capacity = other.m_capacity;
			m_size = other.m_size;

			m_arr = new T[m_capacity];

			for (size_t i = 0; i < m_size; ++i)
			{
				m_arr[i] = other.m_arr[i];
			}
		}

		vector(std::initializer_list<T> elements) :
			m_arr(new T[elements.size()])
		{
			for (const T& i : elements)
			{
				push_back(i);
			}
		}

		vector& operator=(nstd::vector<T>& other)
		{
			this->m_capacity = other.m_capacity;
			this->m_size = other.m_size;

			this->m_arr = new T[m_capacity];

			for (size_t i = 0; i < this->m_size; ++i)
			{
				this->m_arr[i] = other.m_arr[i];
			}
		}

		void reserve(size_t new_size)
		{
			if (new_size < m_capacity)
			{
				return;
			}


			T* temp = new T[new_size]{};

			for (size_t i = 0; i < m_size; ++i)
			{
				temp[i] = m_arr[i];
			}

			delete[] m_arr;
			m_arr = temp;
			m_capacity = new_size;
		}

		void push_back(const T& element)
		{
			if (m_size == m_capacity)
			{
				reserve(m_size * 2 + 1);
			}

			m_arr[m_size] = element;
			m_size++;
		}

		void push_front(const T& element)
		{
			push_back(element);
			for (size_t i = m_size - 1; i > 0; --i)
			{
				std::swap(m_arr[i], m_arr[i - 1]);
			}
		}

		void pop_back()
		{
			if (m_size == 0)
			{
				return;
			}

			m_size--;
		}

		void pop_front()
		{
			for (size_t i = 0; i < m_size - 1; ++i)
			{
				std::swap(m_arr[i],m_arr[i + 1]);
			}
			
			pop_back();
		}

		void insert(size_t pos, const T& element)
		{
			push_back(element);

			for (size_t i = m_size - 1; i > pos + 1; --i)
			{
				std::swap(m_arr[i], m_arr[i - 1]);
			}
		}

		bool empty()
		{
			return !m_size;
		}

		const size_t& size()
		{
			return m_size;
		}

		T& operator[](const size_t& index)
		{
			return m_arr[index];
		}

		void clear()
		{
			m_size = 0;
		}

		~vector()
		{
			delete[] m_arr;
		}
	};
