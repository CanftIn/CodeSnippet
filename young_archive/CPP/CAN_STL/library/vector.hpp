/*
	vector.h
	created by CanftIn at 2/4/2018
	power by CanftIn_tools project https://github.com/CanftIn/CanftIn_tools
*/
#pragma once
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "allocator.hpp"
#include "iterator.hpp"
#include "uninitialized.hpp"

// not support difference_type iterator
// you can do it like:
// const viter<T> *left - const viter<T> *right
namespace Can
{
	template<typename T>
	class viter final : public iterator<random_access_iterator<T, ptrdiff_t>, T>
	{
	public:
		viter() :ptr_(0) {}

		explicit viter(T *ptr) : _ptr(ptr) {}

		viter(const viter& vit) {
			_ptr = vit._ptr;
		}

		vite& operator= (const viter& vit) {
			if (this != &vit) {
				_ptr = vit._ptr;
			}
		}

		viter& operator++()
		{
			++(this->_ptr);
			return *this;
		}

		viter operator++(int)
		{
			viter old_value(*this);
			this->operator++();
			return old_value;
		}

		viter& operator--()
		{
			--(this->_ptr);
			return *this;
		}

		viter operator--(int)
		{
			viter old_value(*this);
			this->operator--();
			return old_value;
		}

		constexpr bool operator==(const viter& it) const
		{
			return this->_ptr == it->_ptr;
		}

		constexpr bool operator!= (const viter& it) const
		{
			return this->_ptr != it->_ptr;
		}

		constexpr T& operator*() const
		{
			return *(this->_ptr);
		}

		constexpr T* operator->() const
		{
			return this->_ptr;
		}
	private:
		T *_ptr;
	};

	template<typename T, class Alloc = Allocator<T>>
	class vector final
	{
	private:
		T *start_;
		T *finish_;
		T *endOfStorage_;

	public:
		using size_type = unsigned int;
		using value_type = T;
		using iterator = Can::viter<value_type>;
		using reference = T&;
		using pointer = iterator;

	private:
		T* m_array{ nullptr };
		size_type m_size{ 0 }, m_capacity{ 0 };

	public:
		constexpr vector() : start_(0), finish_(0), endOfStorage_(0) {} = default;

		vector(const size_type n)
		{
			start_ = Alloc::allocate(n);
			uninitialized_fill_n(start_, n, value_type());
			finish_ = endOfStorage_ = start_ + n;
		}

		vector(const size_type n, const value_type& value)
		{
			start_ = Alloc::allocate(n);
			uninitialized_fill_n(start_, n, value);
			finish_ = endOfStorage_ = start_ + n;
		}

		vector(const std::initializer_list<value_type>& list)
		{
			start_ = Alloc::allocate(list.size());
			iterator = start_;
			for (const auto& it : list)
			{
				new(iterator) value_type(it);
				iterator++;
			}
		}

		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			start_ = Alloc::allocate(last - first);
			finish = uninitialized_copy(first, last, start_);
			endOfStorage_ = finish_;
		}

		/*
		vector(const vector& vec)
		{
			this->reserve(vec.m_capacity);
			size_type index = 0;
			for (const auto& p : vec)
			{
				new(&this->m_array[index]) value_type(p);
				index++;
			}
			this->m_size = vec.m_size;
		}

		vector(vector&& vec) : m_array(vec.m_array), m_capacity(vec.m_capacity), m_size(vec.m_size)
		{
			vec.m_capacity = vec.m_size = 0;
			vec.m_array = nullptr;
		}
		*/

		~vector() noexcept
		{
			Alloc::destroy(start_, finish_);
			Alloc::deallocate(start_, endOfStorage_ - start_);
		}

		/*
		vector& operator=(const vector& vec)
		{
			this->clear();
			this->reserve(vec.m_capacity);

			size_type index = 0;
			for (const auto& p : vec)
			{
				new(&this->m_array[index]) value_type(p);
				index++;
			}
			this->m_size = vec.m_size;

			return *this;
		}

		vector& operator=(vector&& vec)
		{
			if (m_array != nullptr)
			{
				for (size_type i = 0; i < m_size; ++i)
					m_array[i].~value_type();

				free(m_array);
			}

			this->m_array = vec.m_array;
			this->m_capacity = vec.m_capacity;
			this->m_size = vec.m_size;

			vec.m_capacity = vec.m_size = 0;
			vec.m_array = nullptr;

			return *this;
		}

		void reserve(const size_type& new_cap)
		{
			if (new_cap <= m_capacity)
				return;

			value_type *mem = reinterpret_cast<value_type*>(malloc(sizeof(value_type) * new_cap));

			if (mem == 0)
				throw std::bad_alloc();

			for (size_type i = 0; i < this->m_size; ++i)
			{
				new(&mem[i]) value_type(std::move(this->m_array[i]));
				this->m_array[i].~value_type();
			}

			free(this->m_array);

			this->m_array = mem;
			this->m_capacity = new_cap;
		}

		void resize(const size_type& new_size)
		{
			if (new_size == this->m_size)
				return;

			if (new_size > this->m_size)
			{
				if (new_size > this->m_capacity)
					this->reserve(new_size);

				for (size_type i = this->m_size; i < new_size; ++i)
					new(&this->m_array[i]) value_type();

				this->m_size = new_size;
				return;
			}

			if (new_size < this->m_size) {
				if (new_size == 0) {
					for (size_type i = 0; i < this->m_size; i++)
						this->m_array[i].~value_type();
				}
				else {
					for (size_type i = this->m_size - 1; i >= new_size; i--)
						this->m_array[i].~value_type();
				}

				this->m_size = new_size;

				return;
			}
		}
		*/

		iterator begin() 
		{ 
			return iterator(start_); 
		}

		iterator end()
		{ 
			return iterator(finish_); 
		}

		void clear()
		{
			Alloc::destroy(start_, finish_);
			finish_ = start_;
		}
	};
}

#endif // !_VECTOR_H_
