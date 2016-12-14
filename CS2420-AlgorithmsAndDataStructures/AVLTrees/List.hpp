// A doubley-linked list with some nice features

#ifndef LIST_HPP	
#define LIST_HPP

#include <cassert>
#include <functional>
#include <memory>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

template <typename T>
struct Node
{
	Node(T d, std::shared_ptr<Node<T>> n, std::shared_ptr<Node<T>> p) 
    :data(d), next(n), prev(p) {}
	T data;
	std::shared_ptr<Node<T>> next;
  std::shared_ptr<Node<T>> prev;
  std::string toString();
};

template <typename T>
class LinkedList
{
public:
	LinkedList() :head(nullptr), tail(nullptr) {}
	LinkedList(LinkedList const & list) { head = clone(list.head); } 
	LinkedList(LinkedList const && list) { head = list.head; }
	int  size() { return getSize(head); }
	void push_back(T t) { push_back(t, head); }
  void pop_front();
  void clear();
	void remove_element(T t)  { remove_element(head, t); }
  T const & getTail() { return tail->data; }
  T const & getHead() { return head->data; }
	void forEach(std::function<void(T)> f) { forEach(head, f); }
  bool empty() { return !head; }
  void printVectors(std::ostream& o) { printVectors(o, head); }
	void operator=(LinkedList const &); // COPY 
	void operator=(LinkedList const &&); // MOVE
  T& operator[](size_t const &);
  const T& operator[](size_t const &) const;
private:
	int  getSize(std::shared_ptr<Node<T>>);
	void push_back(T, std::shared_ptr<Node<T>>&);
  void pop_front(std::shared_ptr<Node<T>>&);
	void remove_element(std::shared_ptr<Node<T>>&, T);
  void printVectors(std::ostream&,std::shared_ptr<Node<T>>&);
  void forEach(std::shared_ptr<Node<T>> &, std::function<void(T)>); 
	std::shared_ptr<Node<T>> find(T, std::shared_ptr<Node<T>>) const;
  T& get(size_t const & i) { return get(i, head); }
  T& get(size_t const &, std::shared_ptr<Node<T>> &);
	std::shared_ptr<Node<T>> clone(std::shared_ptr<Node<T>>);
	std::shared_ptr<Node<T>> head;
  std::shared_ptr<Node<T>> tail;
};

template <typename T>
void LinkedList<T>::clear() // Clears the entire list
{
  head = nullptr;
  tail = nullptr;
}

template <typename T>
void LinkedList<T>::printVectors(std::ostream & out, std::shared_ptr<Node<T>> & list)
{ // For usage in lists of containers:  prints the containers' contents
  if (!list) return;
  out << list->toString() << " ";
  printVectors(out, list->next);
}

template <typename T>
std::string Node<T>::toString()
{ // For usage in lists of containers:  string-ifies the containers
  std::ostringstream oss;
  oss << "[";
  for (int i = 0; i < data.size(); ++i)
  {
    oss << data[i];
    if (i != data.size() - 1) oss << ",";
  }
  oss << "]";
  return oss.str();
}

template <typename T>
void LinkedList<T>::pop_front()
{
  if (!head) return;
  head = head->next;
}

template <typename T>
void LinkedList<T>::push_back(T data, std::shared_ptr<Node<T>>& list)
{
  if (!list) 
  {
    list = std::make_shared<Node<T>>(data, list, tail);
    tail = list;
  }
  else
  {
    auto newNode = std::make_shared<Node<T>>(data, nullptr, tail);
    tail->next = newNode;
    tail = newNode;
  }
}

template <typename T>
void LinkedList<T>::remove_element(std::shared_ptr<Node<T>>& list, T target)
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
			remove_element(list->next, target);
		}
	}
}

template <typename T>
void LinkedList<T>::forEach(std::shared_ptr<Node<T>> & list, std::function<void(T)> f)
{
	if (!list) return;
	f(list->data);
	forEach(list->next, f);
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
std::shared_ptr<Node<T>> LinkedList<T>::find(
  T t, 
  std::shared_ptr<Node<T>> list) const
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

template <typename T>
T& LinkedList<T>::get(const size_t & i, std::shared_ptr<Node<T>> & list)
{
  assert(list);
  if( i == 0 ) return list->data;
  else return get(i - 1, list->next);
}

template <typename T>
T& LinkedList<T>::operator[](const size_t & i)
{
  return this->get(i);
}
  
template<typename T>
const T& LinkedList<T>::operator[](const size_t & i) const
{
  return this->get(i);
}

#endif
