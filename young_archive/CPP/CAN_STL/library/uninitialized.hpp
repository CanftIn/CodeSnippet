#pragma once
#ifndef _UNINITIALIZED_H_
#define _UNINITIALIZED_H_

#include "iterator.hpp"
#include "type_traits.hpp"
#include "construct.hpp"

#include <cstring> /* memcpy() */

namespace Can
{
	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
		ForwardIterator result, _true_type)
	{
		memcpy(result, first, (last - first) * sizeof(*first));
		return result + (last - first);
	}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
		ForwardIterator result, _false_type)
	{
		for (int i = 0; first != last; ++first, ++i)
		{
			construct((result + i), *first);
		}
		return (result + i);
	}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
	{
		using isPODType = typename _type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type;
		return _uninitialized_copy_aux(first, last, result, isPODType);
	}

	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _true_type) 
	{
		std::fill(first, last, value);
	}

	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,const T& value, _false_type)
	{
		int i = 0;
		for (; first != last; ++first, ++i) 
		{
			construct(first, value);
		}
	}

	template<class ForwardIterator, class T>
	void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		typedef typename _type_traits<T>::is_POD_type isPODType;
		_uninitialized_fill_aux(first, last, value, isPODType());
	}

	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_n_fill_aux(ForwardIterator first,
		Size n, const T& x, _true_type) 
	{
		return std::fill_n(first, n, x);
	}

	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_n_fill_aux(ForwardIterator first,
		Size n, const T& x, _false_type) 
	{
		int i = 0;
		for (; i != n;) 
		{
			construct((first + i), x);
		}
		return (first + i);
	}

	template<class ForwardIterator, class Size, class T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x) 
	{
		using isPODType = typename _type_traits<T>::is_POD_type;
		return _uninitialized_n_fill_aux(first, n, x, isPODType());
	}
}

#endif