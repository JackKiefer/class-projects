#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <iostream> 
#include <assert.h>
#include <sstream>

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x  
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// string toStringList(string message )      --> Print tree in sorted order
// string toStringTree(string message )      --> Print tree as a tree thingy
// Comparable  removeMin  -->  You are not allowed simply to do a find Min and then a remove on that value.  
//                            That would require that you traverse the tree twice  (once to find and once to delete).  We want a true removeMin that 
//                            only traverses in order to delete.
// ******************ERRORS********************************


//HINT:   The class you use as Comparable must have overloaded operators for > == and <.
//        nullptr is another way of saying NULL.  It has some interesting properties for implicit conversions.
//        && is an "rvalue reference".  They are beyond the scope of this class.  A good explanation is at http://thbecker.net/articles/rvalue_references/section_01.html


template <typename Comparable>
class AvlTree
{
public:
	AvlTree() : root{ nullptr }
	{
		size = 0;
	}

	int getSize(){ return size; }

  AvlTree(const AvlTree & otherTree) : root{ nullptr }
	{
		size = otherTree.size;
		root = clone(otherTree.root);
	}

	AvlTree(AvlTree && otherTree) : root{ otherTree.root }
	{
		otherTree.root = nullptr;
	}

	~AvlTree()
	{
		makeEmpty();
	}

	/* Deep copy. */
	AvlTree & operator=(const AvlTree & otherTree)  
	{
		AvlTree copy = otherTree;
		std::swap(*this, copy);
		return *this;
	}

	/* Move. */
	AvlTree & operator=(AvlTree && otherTree)
	{
		std::swap(root, otherTree.root);

		return *this;
	}

	/* Find the smallest item in the tree. Throw UnderflowException if empty. */
	const Comparable & findMin() const
	{
		assert(!isEmpty()); 
			return findMin(root)->element;
	}

	/* Find the largest item in the tree.	 */
	const Comparable & findMax() const
	{
		assert(!isEmpty());
			return findMax(root)->element;
	}

	/* Returns true if target is found in the tree. */
	bool contains(const Comparable & target) const
	{
		return contains(target, root);
	}

	/* Test if the tree is logically empty.	 */
	bool isEmpty() const
	{
		return root == nullptr;
	}

	/* String contains the tree contents in sorted order. */
	std::string toStringList(std::string message) const
	{
		std::ostringstream oss;
		oss << message << std::endl;
		if (isEmpty())
			oss << "Empty tree" << std::endl;
		else
			oss << toStringList(root);
		oss << "END " << message << std::endl;
		return oss.str();
	}

	/* String contains the tree contents in a sorta tree lookin thing. */
	std::string toStringTree(std::string message) const
	{
		std::ostringstream oss;
		int tabNumber;
		oss << message << std::endl;
		if (isEmpty())
			oss << "Empty tree" << std::endl;
		else
			oss << toStringTree(root, -1);
		oss << "END " << message << std::endl;
		return oss.str();
	}

	/* Make the tree logically empty. */
	void makeEmpty()
	{
		makeEmpty(root);
	}

	/*	Insert data into the tree; 	 */
	void insert(const Comparable & data)
	{
		++size;
		insert(data, root);
	}

	/**
	 * Insert data into the tree; 
	 * && is termed an rvalue reference.
	 * a good explanation is at http://thbecker.net/articles/rvalue_references/section_01.html
	 */
	void insert(Comparable && data)
	{
		++size;
		insert(std::move(data), root);
	}

	/* Remove element from the tree. Nothing is done if x is not found.	 */
	void remove(const Comparable & target)
	{
		--size;
		remove(target, root);
	}
	/* remove smallest element from the tree.  Return the value found there*/
	Comparable removeMin(){
		--size;
		AvlNode * min = removeMin(root);
		assert(min);
		auto nodeValue = min->element;
		delete min;
		return nodeValue;
	}

	/* Returns the element at the root of the tree */
	Comparable getRoot() { return root->element; }

private:
	struct AvlNode
	{
		Comparable element;
		AvlNode   *left;
		AvlNode   *right;
		int       height;

		AvlNode(const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0)
			: element{ ele }, left{ lt }, right{ rt }, height{ h } { }

		AvlNode(Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0)
			: element{ std::move(ele) }, left{ lt }, right{ rt }, height{ h } { }
	};

	AvlNode *root;
	int size;


	/**
	 * Internal method to insert into a subtree.
	 * data is the item to insert.
	 * r is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert(const Comparable & data, AvlNode * & r)
	{
		if (!r)
			r = new AvlNode{ data, nullptr, nullptr };
		else if (data < r->element)
			insert(data, r->left);
		else 
			insert(data, r->right);

		balance(r);
	}

	/**
	 * Internal method to insert into a subtree.
	 * data is the item to insert.
	 * r is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert(Comparable && data, AvlNode * & r)
	{
		if (!r)
			r = new AvlNode{ std::move(data), nullptr, nullptr };
		else if (data < r->element)
			insert(std::move(data), r->left);
		else 
			insert(std::move(data), r->right);

		balance(r);
	}

	/**
	 * Internal method to remove from a subtree.
	 * target is the item to remove.
	 * r is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void remove(const Comparable & target, AvlNode * & r)
	{
		if (!r)
			return;   // Item not found; do nothing

		if (target < r->element)
			remove(target, r->left);
		else if (r->element < target)
			remove(target, r->right);
		else if (r->left != nullptr && r->right != nullptr) // Two children
		{
			r->element = findMin(r->right)->element;
			remove(r->element, r->right);
		}
		else
		{
			AvlNode *oldNode = r;
			r = (r->left != nullptr) ? r->left : r->right;
			delete oldNode;
		}

		balance(r);
	}

	AvlNode*  removeMin(AvlNode * & t)
	{
		AvlNode* oldNode;
		if (!t) return nullptr;
		if (!t->left) 
		{
			oldNode = t;
			t = t->right;
			return oldNode;
		}
		
		auto minNode = removeMin(t->left);
		balance(t);
		return minNode; 
	}
	static const int ALLOWED_IMBALANCE = 1;

	// Assume t is balanced or within one of being balanced
	void balance(AvlNode * & t)
	{
		if (t == nullptr)
			return;

		if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
			if (height(t->left->left) >= height(t->left->right))
				rotateWithLeftChild(t);
			else
				doubleWithLeftChild(t);
		else
			if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
				if (height(t->right->right) >= height(t->right->left))
					rotateWithRightChild(t);
				else
					doubleWithRightChild(t);

		t->height = max(height(t->left), height(t->right)) + 1;
	}

	/**
	 * Internal method to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 */
	AvlNode * findMin(AvlNode *t) const
	{
		if (t == nullptr)
			return nullptr;
		if (t->left == nullptr)
			return t;
		return findMin(t->left);
	}

	/**
	 * Internal method to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 */
	AvlNode * findMax(AvlNode *t) const
	{
		if (t != nullptr)
			while (t->right != nullptr)
				t = t->right;
		return t;
	}


	/**
	 * Internal method to test if an item is in a subtree.
	 * data is item to search for.
	 * t is the node that roots the tree.
	 */
	bool contains(const Comparable & data, AvlNode *t) const
	{
		if (t == nullptr)
			return false;
		else if (data < t->element)
			return contains(data, t->left);
		else if (t->element < data)
			return contains(data, t->right);
		else
			return true;    // Match
	}

	/**
	 * Internal method to make subtree empty.
	 */
	void makeEmpty(AvlNode * & t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}

	/**
	 * Internal method to create a string for a subtree rooted at t in sorted order.
	 */
	std::string toStringList(AvlNode * t) const
	{   
		std::stringstream ss;
		if (t->left) ss << toStringList(t->left);
		ss << t->element << std::endl;
		if (t->right) ss << toStringList(t->right);
		return ss.str();
	}

	/**
	 * Internal method to create a string for a subtree rooted at t as a tree thingy
	 */
	std::string toStringTree(AvlNode * t, int tabNumber) const
	{   
		std::stringstream ss;
		++tabNumber;

		if (t->right) ss << toStringTree(t->right, tabNumber);

		std::string tabs = std::string(tabNumber, '\t');

		ss << tabs << t->element << std::endl;

		if (t->left) ss << toStringTree(t->left, tabNumber);
		return ss.str();
	}

	/**
	 * Internal method to clone subtree.
	 */
	AvlNode * clone(AvlNode *t) const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new AvlNode{ t->element, clone(t->left), clone(t->right), t->height };
	}
	// Avl manipulations
	/**
	 * Return the height of node t or -1 if nullptr.
	 */
	int height(AvlNode *t) const
	{
		return t == nullptr ? -1 : t->height;
	}

	int max(int a, int b) const
	{
		return a > b ? a : b;
	}

	/**
	 * Rotate binary tree node with left child.
	 * For AVL trees, this is a single rotation for case 1.
	 * Update heights, then set new root.
	 */

	void rotateWithLeftChild(AvlNode * & sad)
	{
		AvlNode *leftChild = sad->left;
		sad->left = leftChild->right;
		leftChild->right = sad;
		sad->height = max(height(sad->left), height(sad->right)) + 1;
		leftChild->height = max(height(leftChild->left), sad->height) + 1;
		sad = leftChild;
	}

	/**
	 * Rotate binary tree node with right child.
	 * For AVL trees, this is a single rotation for case 4.
	 * Update heights, then set new root.
	 */
	void rotateWithRightChild(AvlNode * & sad)
	{
		AvlNode *rightChild = sad->right;
		sad->right = rightChild->left;
		rightChild->left = sad;
		sad->height = max(height(sad->left), height(sad->right)) + 1;
		rightChild->height = max(height(rightChild->right), sad->height) + 1;
		sad = rightChild;
	}

	/**
	 * Double rotate binary tree node: first left child.
	 * with its right child; then node 'sad' with new left child.
	 * For AVL trees, this is a double rotation for case 2.
	 * Update heights, then set new root.
	 */
	void doubleWithLeftChild(AvlNode * & sad)
	{
		rotateWithRightChild(sad->left);
		rotateWithLeftChild(sad);
	}

	/**
	 * Double rotate binary tree node: first right child.
	 * with its left child; then node 'sad' with new right child.
	 * For AVL trees, this is a double rotation for case 3.
	 * Update heights, then set new root.
	 */
	void doubleWithRightChild(AvlNode * & sad)
	{
		rotateWithLeftChild(sad->right);
		rotateWithRightChild(sad);
	}
};

#endif
