#ifndef EVENT_H_
#define EVENT_H_

#include "../Basic.h"
#include "Base.h"

namespace CAN
{
	template<typename... Params>
	class Delegate
	{
	public:
		typedef void (*FuncHandler) (Params...);

	public:
		virtual void Invoke(Params... params) const = 0;
		virtual void* GetOwner() const = 0;
		virtual void* GetFuncHandler() const = 0;
		virtual Delegate<Params...>* Clone() const = 0;

		bool operator == (const Delegate<Params...>& other) const
		{
			return GetOwner() == other.GetOwner() && GetFuncHandler() == other.GetFuncHandler();
		}
	};

	template<typename... Params>
	class StaticFuncDelegate : implements Delegate<Params...>
	{
	public:
		typedef void(*FuncHandler) (Params...);

	private:
		FuncHandler mFHandler;

	public:
		StaticFuncDelegate(FuncHandler func) : mFHandler(func) {}
		void Invoke(Params... args) const
		{
			(*mFHandler)(args...);
		}

		void* GetOwner() const { return nullptr; }
		void* GetFuncHandler() const { return (void*)(*(int*)&mFHandler); }

		virtual Delegate<Params...>* Clone() const
		{
			return new StaticFuncDelegate<Params...>(mFHandler);
		}
	};

	template<class Class, typename... Params>
	class MemberFuncDelegate : implements Delegate<Params...>
	{
	public:
		typedef void (Class::*FuncHandler)(Params...);

	private:
		Class* mpOwner;
		FuncHandler mFHandler;

	public:
		MemberFuncDelegate(Class* pOwner, FuncHandler func) : mpOwner(pOwner), mFHandler(func) {}
		void Invoke(Params... args) const
		{
			(mpOwner->*mFHandler)(args...);
		}

		void* GetOwner() const { return mpOwner; }
		void* GetFuncHandler() const { return (void*)(*(int*)&mFHandler); }

		virtual Delegate<Params...>* Clone() const
		{
			return new MemberFuncDelegate<Class, Params...>(mpOwner, mFHandler);
		}
	};

	template<typename... Params>
	class Event
	{
	protected:
		vector<Delegate<Params...>*> mvListeners;

	public:
		Event() {}
		~Event() { Release(); }

		Event(const Event<Params...>& other)
		{
			operator=(*other);
		}

		Event<Params...>& operator=(const Event<Params...>& other)
		{
			Release();
			for (const auto& it : other.mvListeners)
				mvListeners.push_back(it->Clone());
			return *this;
		}

		Event(typename StaticFuncDelegate<Params...>::FuncHandler pFunc)
		{
			Bind(pFunc);
		}

		template<class Class>
		Event(Class* pListener, typename MemberFuncDelegate<Class, Params...>::FuncHandler pFunc)
		{
			Bind(pListener, pFunc);
		}

		void Release()
		{
			for (auto& it : mvListeners) 
			{
				delete it;
				it = NULL;
			}
			mvListeners.clear();
		}

		void Invoke(Params... params)
		{
			for (auto& listener : mvListeners)
			{
				listener->Invoke(params...);
			}
		}

		bool Attached() const
		{
			return !mvListeners.empty();
		}

		// StaticFuncDelegate
		void Bind(typename StaticFuncDelegate<Params...>::FuncHandler pFunc)
		{
			mvListeners.push_back(new StaticFuncDelegate<Params...>(pFunc));
		}

		void Unbind(typename StaticFuncDelegate<Params...>::FuncHandler pFunc)
		{
			auto it = std::find(mvListeners.begin(), mvListeners.end(), StaticFuncDelegate<Params...>(pFunc));
			if (it != mvListeners.end())
			{
				delete (*it);
				mvListeners.erase(it);
			}
		}

		// MemberFuncDelegate
		template<class Class>
		void Bind(Class* pListener, typename MemberFuncDelegate<Class, Params...>::FuncHandler pFunc)
		{
			mvListeners.push_back(new MemberFuncDelegate<Class, Params...>(pListener, pFunc));
		}

		template<class Class>
		void Unbind(Class* pListener, typename MemberFuncDelegate<Class, Params...>::FuncHandler pFunc)
		{
			auto it = std::find(mvListeners.begin(), mvListeners.end(), MemberFuncDelegate<Class, Params...>(pListener, pFunc));
			if (it != mvListeners.end())
			{
				delete (*it);
				mvListeners.erase(it);
			}
		}
	};

	class EventArgs : implements Object
	{

	};

	class ResizeEventArgs : implements EventArgs
	{
	public:
		int Width, Height;

		ResizeEventArgs(int iW, int iH) : Width(iW), Height(iH)
		{
		}
	};
	
	enum class MouseAction
	{
		LButtonDown, RButtonDown, LButtonUp, RButtonUp
	};

	class MouseEventArgs : implements EventArgs
	{
	public:
		int X, Y;
		MouseAction Action;
	};

	using NotifyEvent = Event<Object*, EventArgs>;
	using ResizeEvent = Event<Object*, ResizeEventArgs>;
	using MouseEvent = Event<Object*, MouseEventArgs>;
}

#endif