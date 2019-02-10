#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <initializer_list>
#include <memory>
#include <exception>

namespace Can
{
    template<typename T>
    class iterator final
    {
    public:
        iterator(T *ptr) : _ptr(ptr) {}

        iterator& operator++()
        {
            ++(this->_ptr);
            return *this;
        }

        iterator operator++(int)
        {
            iterator old_value(*this);
            this->operator++();
            return old_value;
        }

        iterator& operator--()
        {
            --(this->_ptr);
            return *this;
        }

        iterator operator--(int)
        {
            iterator old_value(*this);
            this->operator--();
            return old_value;
        }

        constexpr bool operator==(const iterator& it) const
        {
            return this->_ptr == it->_ptr;
        }

        constexpr bool operator!= (const iterator& it) const
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

    template<typename T>
    class vector final
    {
    public:
        using size_type = unsigned int;
        using value_type = T;
        using iterator = Can::iterator<value_type>;

    public:
        constexpr vector() = default;

        vector(const size_type& reserve_size)
        {
            void *mem = malloc(sizeof(value_type) * reserve_type);

            if(mem == 0)
                throw std::bad_alloc();

            m_array = reinterpret_cast<T*>(mem);
            m_capacity = reserve_size;
        }

        vector(const std::initializer_list<value_type>& list)
        {
            void *mem = malloc(sizeof(value_type) * list.size());
            if(mem == 0)
                throw std::bad_alloc();

            m_array = reinterpret_cast<T*>(mem);
            m_capacity = list.size();

            size_type index = 0;
            for(const auto& it : list)
            {
                new(&m_array[index]) value_type(it);
                index++;
            }

            m_size = index;
        }

        vector(const vector& vec)
        {
            this->reserve(vec.m_capacity);
            size_type index = 0;
            for(const auto& p : vec)
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

        ~vector() noexcept
        {
            if(m_array == 0)
                return ;

            for(size_type i = 0; i < m_size; ++i)
                m_array[i].~value_type();

            free(m_array);
        }

        vector& operator=(const vector& vec)
        {
            this->clear();
            this->reserve(vec.m_capacity);

            size_type index = 0;
            for(const auto& p : vec)
            {
                new(&this->m_array[index]) value_type(p);
                index++;
            }
            this->m_size = vec.m_size;

            return *this;
        }

        vector& operator=(vector&& vec)
        {
            if(m_array != nullptr)
            {
                for(size_type i = 0; i < m_size; ++i)
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
            if(new_cap <= m_capacity)
                return ;
            
            value_type *mem = reinterpret_cast<value_type*>(malloc(sizeof(value_type) * new_cap));

            if(mem == 0)
                throw std::bad_alloc();

            for(size_type i = 0; i < this->m_size; ++i)
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
            if(new_size == this->m_size)
                return ;
            
            if(new_size > this->m_size)
            {
                if(new_size > this->m_capacity)
                    this->reserve(new_size);

                for(size_type i = this->m_size; i < new_size; ++i)
                    new(&this->m_array[i]) value_type();

                this->m_size = new_size;
                return ;
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

				return ;
			}
        }


    private:
        T* m_array{nullptr};
        size_type m_size{0}, m_capacity{0};
    };
}

#endif // !_VECTOR_H_
