#pragma once
#ifndef _ITERATOR_BASE_H_
#define _ITERATOR_BASE_H_

#if 0
#define MODERN_ITERATOR_ACHIEVE
#endif

#include "type.hpp"
#include "type_traits.hpp"

namespace Can
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	//modern achievement
	namespace detail
	{
		template<typename ...>
		using void_t = void;

		template<typename T, class = void>
		struct iterator_traits_base {};

		template<typename T>
		struct iterator_traits_base < T, void_t<
			typename T::iterator_category,
			typename T::value_type,
			typename T::difference_type,
			typename T::pointer,
			typename T::reference>>
		{
			using iterator_category = typename T::iterator_category;
			using value_type = typename T::value_type;
			using pointer = typename T::pointer;
			using reference = typename T::reference;
			using difference_type = typename T::difference_type;
		};

#ifdef MODERN_ITERATOR_ACHIEVE
#include <type_traits>
		template<typename T, bool = std::is_object<T>::value>
		struct iterator_traits_base_pointer
		{
			using iterator_category = typename Can::random_access_iterator_tag;
			using value_type = typename std::remove_cv<T>::type;
			using pointer = T*;
			using reference = T&;
			using difference_type = Can::ptrdiff_t;
		};
#endif

	}

	template<typename T>
	struct iterator_traits : detail::iterator_traits_base<T> {};

	template<typename T>
	struct iterator_traits<T*>
	{
		using iterator_category = typename Can::random_access_iterator_tag;
		using value_type = typename T::value_type;
		using pointer = T*;
		using reference = T&;
		using difference_type = Can::ptrdiff_t;
	};

	template<typename T>
	struct iterator_traits < const T*>
	{
		using iterator_category = typename Can::random_access_iterator_tag;
		using value_type = typename T::value_type;
		using pointer = T*;
		using reference = T&;
		using difference_type = Can::ptrdiff_t;
	};

	template<typename Iter>
	using iter_val_t = typename iterator_traits<Iter>::value_type;

	template<typename Iter>
	using iter_dif_t = typename iterator_traits<Iter>::difference_type;

	template<typename Iter>
	using iter_cate_t = typename iterator_traits<Iter>::iterator_category;

	template<typename Iter, typename = void>
	struct is_iterator :
		Can::_false_type
	{
	};

	template<typename Iter>
	struct is_iterator<Iter,
		detail::void_t<typename iterator_traits<Iter>::iterator_category>> :
		_true_type
	{
	};

	template<typename type1,
		typename type2>
		struct is_same :
		_false_type
	{
	};

	template<typename type>
	struct is_same<type, type> :
		_true_type
	{
	};

#ifdef MODERN_ITERATOR_ACHIEVE
#include <type_traits>
	template<typename T>
	struct iterator_traits<T*> : detail::iterator_traits_base_pointer<T> {};

	template<typename T>
	struct iterator_traits<const T*> : detail::iterator_traits_base_pointer<T> {};

	template<typename inputit, class = void>
	struct is_iterator : std::false_type {};

	template <typename inputit>
	struct is_iterator<inputit, detail::void_t<
		typename DC::iterator_traits<inputit>::iterator_category>> :std::true_type {};
#endif




	/*


	//delete && remove to iterator.h

	template<typename category, typename T>
	struct iterator
	{
	using iterator_category = category;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using distance = Can::ptrdiff_t;
	};
	*/

	/*
	//traditional achievement
	template <class T, class Distance> 
	struct input_iterator
	{
		typedef input_iterator_tag	iterator_category;
		typedef T					value_type;
		typedef Distance			difference_type;
		typedef T*					pointer;
		typedef T&					reference;
	};

	struct output_iterator
	{
		typedef output_iterator_tag iterator_category;
		typedef void                value_type;
		typedef void                difference_type;
		typedef void                pointer;
		typedef void                reference;
	};

	template <class T, class Distance> struct forward_iterator
	{
		typedef forward_iterator_tag	iterator_category;
		typedef T						value_type;
		typedef Distance				difference_type;
		typedef T*						pointer;
		typedef T&						reference;
	};

	template <class T, class Distance> struct bidirectional_iterator
	{
		typedef bidirectional_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef Distance					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	template <class T, class Distance> struct random_access_iterator
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef Distance					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	template<class Category, class T, class Distance = ptrdiff_t,
		class Pointer = T*, class Reference = T&>
		struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::Category		iterator_category;
		typedef typename Iterator::value_type	value_type;
		typedef typename Iterator::Distance		difference_type;
		typedef typename Iterator::Pointer		pointer;
		typedef typename Iterator::Reference 	reference;
	};

	template<class T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag 	iterator_category;
		typedef T 							value_type;
		typedef ptrdiff_t 					difference_type;
		typedef T*							pointer;
		typedef T& 							reference;
	};

	template<class T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag 	iterator_category;
		typedef T 							value_type;
		typedef ptrdiff_t 					difference_type;
		typedef const T*					pointer;
		typedef const T& 					reference;
	};

	template<class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
		iterator_category(const Iterator& It) {
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::value_type
		value_type(const Iterator& It) {
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
		difference_type(const Iterator& It) {
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}
	*/
}



#endif