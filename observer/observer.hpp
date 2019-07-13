#pragma once

#include <vector>

//---------------------------------------------------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------------------------------------------------
template <typename T, typename ...Ts>
struct IsOneOfType
{
	static constexpr bool value = (std::is_same<T,Ts>::value || ...);
};

//---------------------------------------------------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------------------------------------------------
 template <typename T>
 class ListenerBase
 {
 	public:
		virtual void update(const T& o) = 0;
 };

//---------------------------------------------------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------------------------------------------------
template <typename T>
class SubjectBase
{
	public:
    virtual ~SubjectBase(){};
		void registerListener(ListenerBase<T>* obj)
		{
			m_listeners.push_back(obj);
		}
	
		void notify(const T& obj)
		{
			for(auto& el: m_listeners)
			{
				el->update(obj);
			}
		}
	private:
		std::vector<ListenerBase<T>*> m_listeners;
};

//---------------------------------------------------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------------------------------------------------
template <typename ... Args>
class Listener : public ListenerBase<Args>...
{
};

//---------------------------------------------------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------------------------------------------------
template <typename ... Args>
class Subject : public SubjectBase<Args>...
{
	public:

		template <typename ...Ts>
		void registerListener(Listener<Ts...>* obj)
		{
			helper<Listener<Ts...>, Ts...>(obj);
		}

		template <typename T>
  	void notify(const T& obj)
  	{
    	SubjectBase<T>::notify(obj);
  	}

	private:

		template <typename T>
		void helper(T* obj){}

		template <typename T , typename T1, typename ...Ts>
		void helper(T* obj)
		{
			if constexpr(IsOneOfType<T1,Args...>::value)
			{
				SubjectBase<T1>::registerListener(obj);
			}
			
			auto size = sizeof...(Ts);
			if( size > 0 )
			{
				helper<T, Ts...>(obj);
			}
		}
};
