#include "stdafx.h"
#include "CStringStack.h"

CStringStack::Node::Node(const std::string& data, std::unique_ptr<Node>&& next)
	: data(data)
	, next(std::move(next))
{
}

CStringStack::CStringStack()
{
}

CStringStack::CStringStack(const CStringStack& stack)
{
	*(this) = stack;
}

CStringStack::CStringStack(CStringStack && stack)
{
	if (this != std::addressof(stack))
	{
		m_top = std::move(stack.m_top);
		stack.m_top = nullptr;
	}
}

CStringStack::~CStringStack()
{
	Clear();
}

CStringStack& CStringStack::operator=(const CStringStack& stackForCopy)
{
	if (stackForCopy.IsEmpty())
	{
		Clear();
		return *this;
	}

	if (this != std::addressof(stackForCopy))
	{
		Node* node = stackForCopy.m_top.get();
		std::unique_ptr<Node> element = std::make_unique<Node>(node->data, nullptr);
		std::unique_ptr<Node> top = std::make_unique<Node>(element->data, nullptr);

		node = node->next.get();
		while (node)
		{
			element->next = std::make_unique<Node>(node->data, nullptr);
			element = std::move(element->next);
			node = node->next.get();
		}
		Clear();
		m_top.swap(top);
	}
	return *this;
}

CStringStack & CStringStack::operator=(CStringStack && stackForMove)
{
	if (stackForMove.IsEmpty())
	{
		Clear();
		return *this;
	}

	if (this != std::addressof(stackForMove))
	{
		m_top = std::move(stackForMove.m_top);
		stackForMove.m_top = nullptr;
	}
	return *this;
}

void CStringStack::Push(const std::string& data)
{
	auto newNode = std::make_unique<Node>(data, std::move(m_top));
	m_top = std::move(newNode);
}

bool CStringStack::IsEmpty() const
{
	return m_top == nullptr;
}

std::string CStringStack::GetTopValue() const
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty.");
	}
	return m_top->data;
}

void CStringStack::Pop()
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty.");
	}
	m_top = std::move(m_top->next);
}

void CStringStack::Clear()
{
	while (m_top)
	{
		Pop();
	}
}
