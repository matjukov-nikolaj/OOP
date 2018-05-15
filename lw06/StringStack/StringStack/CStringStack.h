#pragma once

class CStringStack
{

	struct Node
	{
		Node(const std::string &data, std::unique_ptr<Node> &&next);
		std::string data;
		std::unique_ptr<Node> next;
	};

public:
	CStringStack();
	void Push(const std::string &data);
	bool StackIsEmpty() const;
	std::string GetTopValue() const;
	void Pop();
	void Clear();

private:
	std::unique_ptr<Node> m_top;
};