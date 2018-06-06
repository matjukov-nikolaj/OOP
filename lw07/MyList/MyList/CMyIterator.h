#pragma once
#include "stdafx.h"
#include "CMyList.h"
#include "Node.h"

template <typename T>
class CMyIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
public:
	using NodeType = Node<std::decay_t<T>>;

	CMyIterator() = default;

	CMyIterator(NodeType * node)
		: m_node(node)
	{
	}

	T& operator*() const
	{
		return (m_node->data).value();
	}

	bool operator==(const CMyIterator<T>& other) const
	{
		return m_node == other.m_node;
	}

	bool operator!=(const CMyIterator<T>& other) const
	{
		return m_node != other.m_node;
	}

	CMyIterator<T> & operator++()
	{
		if (m_node->next != nullptr)
		{
			m_node = m_node->next.get();
		}
		else
		{
			throw out_of_range("CMyList iterator not incrementable");
		}
		return *this;
	}

	CMyIterator<T> & operator--()
	{
		if (m_node->prev != nullptr && m_node->prev->prev != nullptr)
		{
			m_node = m_node->prev;
		}
		else
		{
			throw out_of_range("CMyList iterator not decrementable");
		}
		return *this;
	}
	
	NodeType* operator->()const
	{
		return (&m_node->data).value();
	}

	CMyIterator<T> operator++(int)
	{
		CMyIterator<T> tmp = *this;
		++*this;
		return tmp;
	}

	CMyIterator<T> operator--(int)
	{
		if (m_node->prev != nullptr && m_node->prev->prev != nullptr)
		{
			CMyIterator<T> tmp = *this;
			--*this;
			return tmp;
		}
		else
		{
			throw out_of_range("CMyList iterator not decrementable");
		}
	}
private:
	NodeType * m_node = nullptr;
	template <class T>
	friend class CMyList;
};