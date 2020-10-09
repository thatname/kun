#pragma  once
#define NON_ENUMERATEE
template<typename T, int id = 0>
struct NON_ENUMERATEE DListNode
{
	mutable DListNode *prev;
	mutable DListNode *next;

	DListNode(const DListNode& right)
	{
		prev = next = this;
		if (!right.empty())
			right.insert_after(this);
	}
	DListNode()
	{
		prev = next = this;
	}
	void insert_after(const DListNode *node)const
	{
		node->unlink();
		node->prev = (DListNode *)this;
		node->next = next;
		next->prev = (DListNode *)node;
		next = (DListNode *)node;
	}
	void insert_before(const DListNode *node)const
	{
		node->unlink();
		node->next = (DListNode *)this;
		node->prev = prev;
		prev->next = (DListNode *)node;
		prev = (DListNode *)node;
	}
	void unlink()const
	{
		prev->next = next;
		next->prev = prev;
		next = prev = (DListNode *)this;
	}
	bool empty()const
	{
		return this == next && this == prev;
	}
	DListNode& operator=(const DListNode& right)
	{
		if (right.empty())
			unlink();
		else
			right.insert_after(this);
		return *this;
	}
	~DListNode()
	{
		unlink();
	}
};
template<typename T, int id = 0>
struct NON_ENUMERATEE DListIterator
{
	DListNode<T, id>* content;
	DListIterator()
	{
		content = nullptr;
	}
	DListIterator(DListNode<T, id>* _content)
	{
		content = _content;
	}
	operator T*()
	{
		return static_cast<T*>(content);
	}
	T* operator ->()
	{
		return static_cast<T*>(content);
	}
	DListIterator& operator ++()
	{
		content = content->next;
		return *this;
	}
	DListIterator operator ++(int)
	{
		DListIterator r = *this;
		content = content->next;
		return r;
	}
	DListIterator& operator --()
	{
		content = content->prev;
		return *this;
	}
	DListIterator operator --(int)
	{
		DListIterator r = *this;
		content = content->prev;
		return r;
	}
	void erase()
	{
		content->unlink();
	}
};
template<typename T, int id = 0>
struct NON_ENUMERATEE DList
	:public DListNode<T, id>
{
	DListIterator<T, id> begin()
	{
		return this->next;
	}
	DListIterator<T, id> end()
	{
		return (DListNode<T, id>*)this;
	}
	void insert_front(const DListNode<T, id> *node)const
	{
		this->insert_after(node);
	}
	void insert_back(const DListNode<T, id> *node)const
	{
		this->insert_before(node);
	}
	int size()
	{
		int count = 0;
		for (auto& e : *this)
			++count;
		return count;
	}
};
