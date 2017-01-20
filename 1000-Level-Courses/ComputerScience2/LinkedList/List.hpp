#ifndef LIST_HPP	
#define LIST_HPP

#include <functional>
#include <memory>
#include <iostream>

template <typename T>
struct Node
{
	Node(T d, std::shared_ptr<Node<T>> n) :data(d), next(n) {}
	T data;
	std::shared_ptr<Node<T>> next;
};

template <typename T>
class LinkedList
{
public:
	LinkedList() :head(nullptr) {}
	LinkedList(LinkedList const & list) { head = clone(list.head); }  // deep copy -- COPY
	LinkedList(LinkedList const && list) { head = list.head; } // shallow copy -- MOVE
	int  size()       { return getSize(head); }
	void push(T t)    { insert(t, head); }
	void remove(T t)  { searchAndDestroy(head, t); }
	void forEach(std::function<void(T)> f) { forEachE(head, f); }
	void operator=(LinkedList const &); // COPY 
	void operator=(LinkedList const &&); // MOVE
private:
	int  getSize(std::shared_ptr<Node<T>>);
	void insert(T, std::shared_ptr<Node<T>>&);
	void searchAndDestroy(std::shared_ptr<Node<T>>&, T);
	std::shared_ptr<Node<T>> find(T, std::shared_ptr<Node<T>>) const;
	std::shared_ptr<Node<T>> clone(std::shared_ptr<Node<T>>);
	std::shared_ptr<Node<T>> head;
};

template <typename T>
void LinkedList<T>::insert(T data, std::shared_ptr<Node<T>>& list)
{
	if (!list)
	{
		list = std::make_shared<Node<T>>(data, list);
	}
	else if (list->data > data)
	{
		list = std::make_shared<Node<T>>(data, list);
	}
	else
	{
		insert(data, list->next);
	}
}

template <typename T>
void LinkedList<T>::searchAndDestroy(std::shared_ptr<Node<T>>& list, T target)
{
	if (!list) return;
	while (find(target, list) != nullptr)
	{
		if (target == list->data)
		{
			list = list->next;
		}
		else
		{
			searchAndDestroy(list->next, target);
		}
	}
}

template <typename T>
void forEachE(std::shared_ptr<Node<T>> list, std::function<void(T)> f)
{
	if (!list) return;
	f(list->data);
	forEachE(list->next, f);
}

template <typename T>
void print(T t)
{
	std::cout << t << " ";
}

template <typename T>
int LinkedList<T>::getSize(std::shared_ptr<Node<T>> list)
{
	if (!list) return 0;
	return 1 + getSize(list->next);
}

template <typename T>
std::shared_ptr<Node<T>> LinkedList<T>::find(T t, std::shared_ptr<Node<T>> list) const
{
	if (!list) return nullptr;
	if (list->data == t) return list;
	return find(t, list->next);
}

template <typename T>
std::shared_ptr<Node<T>> LinkedList<T>::clone(std::shared_ptr<Node<T>> list)
{
	if (!list) return nullptr;
	return std::make_shared<Node<T>>(list->data, clone(list->next));
}

template <typename T>
void LinkedList<T>::operator=(LinkedList const & list) // Deep copy
{
	head = clone(list.head);
}

template <typename T>
void LinkedList<T>::operator=(LinkedList const && list) // Shallow copy
{
	head = list.head;
}

#endif