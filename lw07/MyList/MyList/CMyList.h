#pragma once
#include "stdafx.h"
#include <cassert>
#include <string>
#include <memory>

template<typename T>
class CMyList
{
	struct Node
	{
		Node(const T & data, Node * prev, std::unique_ptr<Node> && next) : data(data), prev(prev), next(std::move(next)) {}

		T data;
		Node *prev;
		std::unique_ptr<Node> next;
	};

	template<typename U>
	class CMyIterator : public std::iterator<std::random_access_iterator_tag, U>
	{
	public:
		CMyIterator(Node* value, bool isReverse)
			: m_node(value)
			, m_isReverse(isReverse)
		{
		}

		friend class CMyList<T>;

		bool operator!=(CMyIterator const& rhs) const
		{
			return m_node != rhs.m_node;
		}
		bool operator==(CMyIterator const& rhs) const
		{
			return m_node == rhs.m_node;
		}

		U & operator*() const
		{
			return m_node->data;
		}

		CMyIterator& operator++()
		{
			m_node = (!m_isReverse) ? (m_node->next.get()) : (m_node->prev);
			return *this;
		}
		CMyIterator& operator--()
		{
			m_node = (!m_isReverse) ? (m_node->prev) : (m_node->next.get());
			return *this;
		}

	private:
		Node * operator->()const
		{
			return m_node;
		}

		Node* m_node = nullptr;
		bool m_isReverse = false;
	};

public:
	CMyList() = default;

	CMyList(CMyList & list)
	{
		CMyList tmp;
		for (const auto& element : list)
		{
			tmp.PushBack(element);
		}
		std::swap(m_firstNode, tmp.m_firstNode);
		std::swap(m_lastNode, tmp.m_lastNode);
		m_size = tmp.m_size;
	}

	~CMyList()
	{
		Clear();
	}

	size_t GetSize() const
	{
		return m_size;
	}

	bool IsEmpty() const
	{
		return m_size == 0u;
	}

	void PushBack(const T & data)
	{
		std::unique_ptr<Node> node = std::make_unique<Node>(data, m_lastNode, nullptr);
		Node *lastNode = node.get();
		if (m_lastNode)
		{
			m_lastNode->next = std::move(node);
		}
		else
		{
			m_firstNode = std::move(node);
		}
		m_lastNode = lastNode;
		m_lastNode->next = nullptr;
		++m_size;
	}
	void PushFront(const T & data)
	{
		std::unique_ptr<Node> node = std::make_unique<Node>(data, nullptr, std::move(m_firstNode));
		if (node->next)
		{
			node->next->prev = node.get();
		}
		else
		{
			m_lastNode = node.get();
		}
		m_firstNode = std::move(node);
		m_firstNode->prev = nullptr;
		m_size++;
	}

	T & GetBackElement()
	{
		assert(m_lastNode);
		return m_lastNode->data;
	}

	T & GetFrontElement()
	{
		assert(m_firstNode);
		return m_firstNode->data;
	}

	const T & GetBackElement() const
	{
		assert(m_lastNode);
		return m_lastNode->data;
	}

	const T & GetFrontElement() const
	{
		assert(m_firstNode);
		return m_firstNode->data;
	}

	CMyList & operator=(CMyList& listForCopy)
	{
		if (&listForCopy != this)
		{
			CMyList<T> tmp;
			for (const auto &element : listForCopy)
			{
				tmp.PushBack(element);
			}
			std::swap(m_firstNode, tmp.m_firstNode);
			std::swap(m_lastNode, tmp.m_lastNode);
			m_size = tmp.m_size;
		}
		return *this;
	}

	void Insert(const CMyIterator<T>& it, T data)
	{
		if (it == begin())
		{
			PushFront(data);
		}
		else if (it == end())
		{
			PushBack(data);
		}
		else
		{
			std::unique_ptr<Node> node = std::make_unique<Node>(data, it->prev, std::move(it->prev->next));
			it->prev = std::move(node.get());
			node->prev->next = std::move(node);
			m_size++;
		}
	}

	void Erase(const CMyIterator<T>& it)
	{
		assert(GetSize() > 0);
		if (m_size == 1)
		{
			m_firstNode = nullptr;
			m_lastNode = nullptr;
			m_size--;
			return;
		}

		if (it == begin())
		{
			m_firstNode = std::move(m_firstNode->next);
			m_firstNode->prev = nullptr;
		}
		else if (it.m_node == m_lastNode)
		{
			m_lastNode = it->prev;
			m_lastNode->next = nullptr;
		}
		else
		{
			it->next->prev = std::move(it->prev);
			it->prev->next = std::move(it->next);
		}
		m_size--;
	}

	void Clear()
	{
		while (m_lastNode)
		{
			m_lastNode->next = nullptr;
			m_lastNode = m_lastNode->prev;
		}
		m_firstNode = nullptr;
		m_size = 0;
	}

	CMyIterator<T> begin()
	{
		return CMyIterator<T>(m_firstNode.get(), false);
	}

	CMyIterator<T> end()
	{
		if (IsEmpty())
		{
			return begin();
		}
		return CMyIterator<T>(m_lastNode->next.get(), false);
	}

	const CMyIterator<const T> cbegin() const
	{
		return CMyIterator<const T>(m_firstNode.get(), false);
	}

	const CMyIterator<const T> cend() const
	{
		if (IsEmpty())
		{
			return cbegin();
		}
		return CMyIterator<const T>(m_lastNode->next.get(), false);
	}

	CMyIterator<T>  rbegin()
	{
		if (IsEmpty())
		{
			return CMyIterator<T>(m_firstNode.get(), true);
		}
		return CMyIterator<T>(m_lastNode, true);
	}

	CMyIterator<T>  rend()
	{
		if (IsEmpty())
		{
			return rbegin();
		}
		return CMyIterator<T>(m_firstNode->prev, true);
	}

	const CMyIterator<const T> crbegin() const
	{
		if (IsEmpty())
		{
			return CMyIterator<const T>(m_firstNode.get(), true);
		}
		return CMyIterator<const T>(m_lastNode, true);
	}

	const CMyIterator<const T> crend() const
	{
		if (IsEmpty())
		{
			return crbegin();
		}
		return CMyIterator<const T>(m_firstNode->prev, true);
	}

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode = nullptr;
	Node * m_lastNode = nullptr;
};