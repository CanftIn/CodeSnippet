#ifndef REF_PTR_H_
#define REF_PTR_H_

namespace CAN
{
    class RefPtrDefaultDestructor
    {
    public:
        template<class T>
        static void Free(T* ptr)
        {
            delete ptr;
        }
    };

    class RefPtrArrayDestructor
    {
    public:
        template<class T>
        static void Free(T* ptr)
        {
            delete[] ptr;
        }
    };

    template<class T, class Destructor = RefPtrDefaultDestructor>
    class RefPtr
    {
    private:
        template<class T1, class Destructor1>
        friend class RefPtr;

        T* pPointer;
        size_t* piRefCount;

    public:
        RefPtr() : pPointer(nullptr), piRefCount(nullptr) {}
        RefPtr(T* ptr) : pPointer(nullptr), piRefCount(0) { this->operator=(ptr); }

        template<typename T1>
        RefPtr(T1* ptr) : pPointer(nullptr), piRefCount(nullptr)
        {
            this->operator=(ptr);
        }

		template<typename T1>
		RefPtr(const RefPtr<T1>& ptr) : pPointer(nullptr), piRefCount(nullptr)
		{
			this->operator=(ptr);
		}

        RefPtr(const RefPtr<T, Destructor>& ptr) : pPointer(nullptr), piRefCount(nullptr)
		{
			this->operator=(ptr);
		}

		RefPtr(RefPtr<T, Destructor>&& ptr) : pPointer(nullptr), piRefCount(nullptr)
		{
			this->operator=(std::move(ptr));
		}

        ~RefPtr() { Dereference(); }

        RefPtr<T, Destructor>& operator = (T* ptr)
        {
            Dereference();

            pPointer = ptr;
            if(ptr)
            {
                piRefCount = new size_t;
                (*piRefCount) = 1;
            }
            else
                piRefCount = nullptr;
            return *this;
        }

		template<typename T1>
		RefPtr<T, Destructor>& operator = (T1* ptr)
		{
			Dereference();

			pPointer = dynamic_cast<T*>(ptr);
			if (ptr)
			{
				piRefCount = new size_t;
				(*piRefCount) = 1;
			}
			else
				piRefCount = NULL;

			return *this;
		}

		template<typename T1>
		RefPtr<T, Destructor>& operator = (const RefPtr<T1, Destructor>& ptr)
		{
			if (ptr.pPointer != pPointer)
			{
				Dereference();
				pPointer = dynamic_cast<T*>(ptr.pPointer);
				piRefCount = ptr.piRefCount;
				(*piRefCount)++;
			}
			return *this;
		}
        
        RefPtr<T, Destructor>& operator=(RefPtr<T, Destructor>&& ptr)
		{
			if (ptr.pointer != pPointer)
			{
				Dereference();
				pPointer = ptr.pPointer;
				piRefCount = ptr.piRefCount;
				ptr.pPointer = nullptr;
				ptr.piRefCount = nullptr;
			}
			return *this;
		}

        void Dereference()
        {
            if(pPointer)
            {
                if((*piRefCount) > 1)
                {
                    (*piRefCount)--;
                }
                else
                {
                    Destructor::Free(pPointer);
                    delete piRefCount;
                }
            }
        }

        bool operator == (const T* ptr) const { return pPointer == ptr; }
		bool operator != (const T* ptr) const { return pPointer != ptr; }
		bool operator == (const RefPtr<T>& ptr) const { return pPointer == ptr.pPointer; }
		bool operator != (const RefPtr<T>& ptr) const { return pPointer != ptr.pPointer; }
		T* operator + (int offset) const { return pPointer + offset; }
		T& operator [] (int idx) const { return *(pPointer + idx); }

        T& operator * () const { return *pPointer; }
		T* operator -> () const { return pPointer; }

		T* Ptr() const { return pPointer; }

        T* Release()
		{
			if (pPointer)
			{
				if ((*piRefCount) > 1)
				{
					(*piRefCount)--;
				}
				else
				{
					delete piRefCount;
				}
			}
			auto ret = pPointer;
			pPointer = NULL;
			piRefCount = NULL;
			return ret;
		}

		operator void * () const
		{
			if (pPointer)
				return (void*)(pPointer);
			else
				return NULL;
		}
    };
}

#endif // !REF_PTR_H_
