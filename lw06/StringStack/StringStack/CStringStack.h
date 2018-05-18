#pragma once

class CStringStack
{

	struct Node
	{
		Node(const std::string& data, const std::shared_ptr<Node>& next);
		std::string data;
		std::shared_ptr<Node> next;
	};

public:
	CStringStack();
	CStringStack(const CStringStack& stack);
	CStringStack(CStringStack&& stack);
	~CStringStack();
	CStringStack& operator=(const CStringStack& stackForCopy);
	CStringStack & operator=(CStringStack &&right);
	void Push(const std::string& data);
	bool IsEmpty() const;
	std::string GetTopValue() const;
	void Pop();
	void Clear();

private:
	std::shared_ptr<Node> m_top;
};
