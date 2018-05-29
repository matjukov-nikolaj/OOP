#pragma once
#include "Node.h"

template <typename U>
class CMyIterator : public std::iterator<std::bidirectional_iterator_tag, U>
{
public:
	CMyIterator() = default;

	CMyIterator(Node<U>* value)
		: m_node(value)
	{
	}

	bool operator==(const CMyIterator& rhs) const
	{
		return m_node == rhs.m_node;
	}

	bool operator!=(const CMyIterator& rhs) const
	{
		return m_node != rhs.m_node;
	}

	U& operator*() const
	{
		return m_node->data;
	}

	CMyIterator& operator++()
	{
		if (m_node->next != nullptr)
		{
			m_node = m_node->next.get();
		}
		else
		{
			throw out_of_range("Can not increment CMyList iterator!");
		}
		return *this;
	}
	CMyIterator& operator--()
	{
		if (m_node->prev != nullptr)
		{
			m_node = m_node->prev;
		}
		else
		{
			throw out_of_range("Can not decrement CMyList iterator.");
		}
		return *this;
	}

private:
	Node<U>* operator->() const
	{
		return m_node;
	}

	Node<U>* m_node = nullptr;
	template <class U>
	friend class CMyList;
};
