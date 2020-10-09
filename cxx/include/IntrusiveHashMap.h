#pragma  once
#include "DList.h"
#include <string>
#include <functional>

extern unsigned int calcHash(const uint64_t& name);
template<typename T> unsigned int calcHash(const T& name)
{
	return std::hash<T>()(name);
}
template<typename T, int ListID>struct HashKey {};
template<typename T, int ListID = 0, int numentries = 512>//a simple intrusive hash map..
struct IntrusiveHashMap
{
	DListNode<T, ListID> table[numentries];
	IntrusiveHashMap()
	{
		for (int i = 0; i < numentries - 1; i++)
			table[i].insert_after((T*)&table[i + 1]);
	}


	T* operator [](const char *name)
	{
		return search(name);
	}
	//#define forall(a,b) for(a=b++;a!=b--;b=a)
	T *begin()
	{
		T *r = (T*)(DListNode<T, ListID>*)table;
		r = getnext(r);
		return (T*)r;
	}
	typedef decltype(((T*)nullptr)->template getName<ListID>()) KeyType;//clang bug.
	T *end()
	{
		return (T*)(DListNode<T, ListID>*)table;
	}
	T* getnext(T* ptr)
	{
		auto it = (DListNode<T, ListID>*)ptr;
		do it = it->next;
		while (it > this->table && it < (this + 1)->table);
		return (T*)it;
	}

	void insert(T *value)
	{
		auto name = value->template getName<ListID>();
		unsigned int hash = calcHash(name)&numentries - 1;
		//  		unsigned int hash = calcHash(value->template getName<ListID>())&numentries - 1;
		table[hash].insert_after((DListNode<T, ListID>*)value);
	}
	T * search(const KeyType &name)
	{
		unsigned int hash = calcHash(name) & numentries - 1;
		for (auto d = (DListNode<T, ListID>*)table[hash].next; !(d >= table && d < table + numentries); d = d->next)
			if (name == ((T *)d)->template getName<ListID>())
				return (T *)d;
		//not found
		return nullptr;
	}

	void deleteAll()
	{
		for (auto it = begin(); it != end(); )
		{
			auto next = getnext(it);
			delete it;
			it = next;
		}
	}
};
