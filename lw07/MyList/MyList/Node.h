#pragma once
#include "stdafx.h"

template <typename T>
class Node
{
public:
	Node(const T& data, Node<T>* prev, std::unique_ptr<Node<T>>&& next)
		: data(data)
		, prev(prev)
		, next(std::move(next))
	{
	}
	T data;
	Node<T>* prev;
	std::unique_ptr<Node<T>> next;
};
