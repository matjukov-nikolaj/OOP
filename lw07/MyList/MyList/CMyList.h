#pragma once
//#include "CMyIterator.h"

template <typename T>
class CMyList
{

	struct Node
	{
		Node(const T& data, Node* prev, std::unique_ptr<Node>&& next)
			: data(data)
			, prev(prev)
			, next(std::move(next))
		{
		}
		T data;
		Node* prev;
		std::unique_ptr<Node> next;
	};

	template <typename U>
	class CMyIterator : public std::iterator<std::bidirectional_iterator_tag, U>
	{
		template <class U>
		friend class CMyList;
	public:
		CMyIterator() = default;

		CMyIterator(Node* value)
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
		Node* operator->() const
		{
			return m_node;
		}

		Node* m_node = nullptr;
	};
public:
	CMyList() = default;

	CMyList(const CMyList& listForCopy)
	{
		CMyList tmpCopy;
		for (auto node : listForCopy)
		{
			tmpCopy.PushBack(node);
		}
		std::swap(m_first, tmpCopy.m_first);
		std::swap(m_last, tmpCopy.m_last);
		m_size = tmpCopy.m_size;
	}

	~CMyList()
	{
		Clear();
	}

	size_t GetSize()
	{
		return m_size;
	}

	bool IsEmpty()
	{
		return m_size == 0;
	}

	void PushBack(const T& data)
	{
		auto node = std::make_unique<Node>(data, m_last, nullptr);
		Node* lastNode = node.get();
		if (m_last)
		{
			m_last->next = std::move(node);
		}
		else
		{
			m_first = std::move(node);
		}
		m_last = lastNode;
		m_last->next = nullptr;
		//++m_size;
	}

	void PushFront(const T& data)
	{
		std::unique_ptr<Node> node = std::make_unique<Node>(data, nullptr, std::move(m_first));
		if (node->next)
		{
			node->next->prev = node.get();
		}
		else
		{
			m_last = node.get();
		}
		m_first = std::move(node);
		m_first->prev = nullptr;
		//m_size++;
	}

	T & GetElement(const size_t& index)
	{
		if (IsEmpty() && GetSize() <= index)
		{
			std::out_of_range("Can not get element! Incorrect index.");
		}
		Node *node = m_first.get();
		for (size_t i = 0; i <= index; ++i)
		{
			node = node->next.get();
		}
		T data = node->data;
		node = nullptr;
		return data;
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
		if (IsEmpty())
		{
			throw std::out_of_range("Can not erase element if CMyList is empty!");
		}
		else if (m_size == 1)
		{
			Clear();
			return;
		}
		else
		{
			m_size--;
		}

		if (it == begin())
		{
			it->next->prev = nullptr;
			m_first = move(it->next);
		}
		else if (it == end())
		{
			it->prev->next = nullptr;
			m_last = std::move(it->prev);
		}
		else
		{
			it->next->prev = std::move(it->prev);
			it->prev->next = std::move(it->next);
		}
	}

	void Clear()
	{
		while (m_size != 0)
		{
			Erase(begin());
		}

		m_last = nullptr;
	}

	CMyIterator<T> begin()
	{
		return m_first.get();
	}

	CMyIterator<T> end()
	{
		return m_last->next.get();
	}

	CMyIterator<const T> cbegin() const
	{
		return m_first.get();
	}

	CMyIterator<const T> cend() const
	{
		return m_last->next.get();
	}

	std::reverse_iterator<CMyIterator<T>> rbegin()
	{
		return std::reverse_iterator<CMyIterator<T>>(end());
	}

	std::reverse_iterator<CMyIterator<T>> rend()
	{
		return std::reverse_iterator<CMyIterator<T>>(begin());
	}

	std::reverse_iterator<CMyIterator<const T>> crbegin() const
	{
		return std::reverse_iterator<CMyIterator<const T>>(end());
	}

	std::reverse_iterator<CMyIterator<const T>> crend() const
	{
		return std::reverse_iterator<CMyIterator<const T>>(begin());
	}

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_first = nullptr;
	Node* m_last = nullptr;
};
