#ifndef SKEWHEAP_H
#define SKEWHEAP_H

#include <memory>
#include <string>
#include <sstream>
#include <algorithm>

template <typename T>
struct Node
{
	Node(
		T d, std::shared_ptr<Node<T>> l, std::shared_ptr<Node<T>> r
	) :data(d), left(l), right(r) {}
	T data;
	std::shared_ptr<Node<T>> left;
	std::shared_ptr<Node<T>> right;
};

template <typename T>
class SkewHeap
{
public:
	SkewHeap() :heapType("min"), root(nullptr) {}
	SkewHeap(std::string const & s) :heapType(s), root(nullptr) {}
	bool empty() { return (heapSize == 0); }
	std::string print() { std::stringstream ss; return print(root,0,ss); }	
	unsigned int mergeCt() { return merges; }
	unsigned int size() { return heapSize; }
	void insert(T);
	T removeMin();
	T removeMax() { return removeMin(); } // removeMin and removeMax are the same function
private:
	std::shared_ptr<Node<T>> merge(std::shared_ptr<Node<T>>, std::shared_ptr<Node<T>>);
	std::shared_ptr<Node<T>> root;
	std::string print(std::shared_ptr<Node<T>> &, int, std::stringstream&);
	bool compare(T a, T b);
	unsigned int merges = 0;
	unsigned int heapSize = 0;
	std::string heapType;
};

// Selects proper heap node comparison based off of the type of heap
template <typename T>
bool SkewHeap<T>::compare(T a, T b)
{
	if (heapType == "min") return ( a <= b );

	return ( a > b );
}

// Merges heaps together given their roots 
template <typename T>
std::shared_ptr<Node<T>> SkewHeap<T>::merge(std::shared_ptr<Node<T>> firstRoot, std::shared_ptr<Node<T>> secondRoot) 
{
	if (!firstRoot) return secondRoot;
	if (!secondRoot) return firstRoot;

	if (compare(firstRoot->data,secondRoot->data))
	{
		firstRoot->right = merge(firstRoot->right, secondRoot);
		std::swap(firstRoot->right, firstRoot->left);
		++merges;
		return firstRoot;
	}

	else 
	{
		secondRoot->right = merge(secondRoot->right, firstRoot);
		std::swap(secondRoot->right, secondRoot->left);
		++merges;
		return secondRoot;
	}
}

// Inserts values into the heap by creating a one-node heap and merging it in
template <typename T>
void SkewHeap<T>::insert(T newValue)
{
	auto babyRoot = std::make_shared<Node<T>>(newValue, nullptr, nullptr);	
	root = merge(root, babyRoot);	
	++heapSize;
}

// Removes the minimum/maximum value of the heap and returns the data within
template <typename T>
T SkewHeap<T>::removeMin()
{
	--heapSize;

	auto oldRoot = root;
	root = merge(root->left, root->right);
	return oldRoot->data;	
}

// Prints the contents of the heap in an orderly fashion. Be wary of large heaps!
template <typename T>
std::string SkewHeap<T>::print(std::shared_ptr<Node<T>> & r, int tabSize, std::stringstream& ss) 
{
  if (!r) return "Empty";


  if (r->left) print(r->left, tabSize + 1, ss);

  for (int i = 0; i < tabSize; ++i) ss << "     ";

  ss << r->data << std::endl;

  if (r->right) print(r->right, tabSize + 1, ss);


  return ss.str();
}

#endif
