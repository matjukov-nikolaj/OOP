#pragma once
#include "stdafx.h"
#include "CMyList.h"
#include "Node.h"

template <typename ValueType>
class CMyIterator : public std::iterator<std::bidirectional_iterator_tag, ValueType>
{

public:
	using NodeType = Node<std::decay_t<ValueType>>;

	CMyIterator() = default;

	CMyIterator(NodeType * node)
		: m_node(node)
	{
	}

	ValueType& operator*() const
	{
		return (m_node->data).value();
	}

	bool operator==(CMyIterator<ValueType> const& other) const
	{
		return m_node == other.m_node;
	}

	bool operator!=(CMyIterator<ValueType> const& other) const
	{
		return m_node != other.m_node;
	}

	CMyIterator<ValueType> & operator++()
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

	CMyIterator<ValueType> & operator--()
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

	CMyIterator<ValueType> operator++(int)
	{
		CMyIterator<ValueType> tmp = *this;
		++*this;
		return tmp;
	}

	CMyIterator<ValueType> operator--(int)
	{
		if (m_node->prev != nullptr && m_node->prev->prev != nullptr)
		{
			CMyIterator<ValueType> tmp = *this;
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