#include "stdafx.h"
#include "CStringStack.h"

CStringStack::Node::Node(const std::string& data, const std::shared_ptr<Node>& next)
	: data(data)
	, next(next)
{
}

CStringStack::CStringStack()
	: m_top(nullptr)
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
		m_top = stack.m_top;
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
		std::shared_ptr<Node> node = stackForCopy.m_top;
		std::shared_ptr<Node> element = std::make_shared<Node>(node->data, nullptr);
		std::shared_ptr<Node> top = element;

		node = node->next;
		while (node)
		{
			element->next = std::make_shared<Node>(node->data, nullptr);
			element = element->next;
			node = node->next;
		}
		Clear();
		m_top = top;
	}
	return *this;
}

CStringStack & CStringStack::operator=(CStringStack && stackForMove)
{
	if (this != std::addressof(stackForMove))
	{
		m_top = stackForMove.m_top;
		stackForMove.m_top = nullptr;
	}
	return *this;
}

void CStringStack::Push(const std::string& data)
{
	m_top = std::make_shared<Node>(data, m_top);
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
	m_top = m_top->next;
}

void CStringStack::Clear()
{
	while (m_top)
	{
		Pop();
	}
}
