#include "stdafx.h"
#include "CStringStack.h"

CStringStack::Node::Node(const std::string& data, std::unique_ptr<Node>&& next)
	: data(data)
	, next(std::move(next))
{
}

CStringStack::CStringStack()
	: m_top(nullptr)
{
}

CStringStack::~CStringStack()
{
	Clear();
}

void CStringStack::Push(const std::string& data)
{
	auto newNode = std::make_unique<Node>(data, std::move(m_top));
	m_top = move(newNode);
}

bool CStringStack::IsEmpty() const
{
	return m_top == nullptr;
	;
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
