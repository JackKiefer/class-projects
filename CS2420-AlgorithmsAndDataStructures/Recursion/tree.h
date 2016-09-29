#ifndef TREE_H
#define TREE_H

#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>

template <typename T>
struct Node
{
  Node(
    T d, 
    unsigned int cCt = 0, 
    unsigned int nCt = 1,
    std::shared_ptr<Node<T>> c = nullptr, 
    std::shared_ptr<Node<T>> s = nullptr,
    std::shared_ptr<Node<T>> p = nullptr
  ) :data(d), childCt(cCt), child(c), sibling(s), parent(p), nodeCt(nCt) {}
  
  T data;
  std::shared_ptr<Node<T>> child;
  std::shared_ptr<Node<T>> sibling;
  std::shared_ptr<Node<T>> parent;
  unsigned int childCt;
  unsigned int nodeCt;
};

template <typename T>
class Tree
{
public:
  Tree() :root(nullptr) {}
  Tree<T> clone() { Tree<T> t; t.setRoot(clone(root, nullptr)); return t; }

  void buildFromPrefix(std::ifstream& file) { root = buildFromPrefix(file, nullptr); }
  std::string toPreorder() { std::stringstream ss; return toPreorder(root, ss); }

  std::shared_ptr<Node<T>> find(T target);
  std::string printTree() { std::stringstream ss; return printTree(root, 0, ss); }

  void upCase() { upCase(root); }
  void makeEmpty() { root = nullptr; } // Smart pointers auto-delete themselves
  
  unsigned int fringe() { unsigned int l = 0; return fringe(root, l); }
  unsigned int nodesInLevel(unsigned int targetLvl) 
  { 
    unsigned int levelNodes = 0;
    return nodesInLevel(root, targetLvl, 0, levelNodes); 
  }

  bool isIsomorphic(Tree<T> otherTree) { return isIsomorphic(root, otherTree.getRoot()); }

  std::shared_ptr<Node<T>>& getRoot() { return root; }
  void setRoot(std::shared_ptr<Node<T>> newRoot) { root = newRoot; }
  
  std::string commonAncestor(T, T);

private:
  std::shared_ptr<Node<T>> buildFromPrefix(std::ifstream&, std::shared_ptr<Node<T>>);
  std::shared_ptr<Node<T>> clone(std::shared_ptr<Node<T>>, std::shared_ptr<Node<T>>);
  std::string toPreorder(std::shared_ptr<Node<T>>&, std::stringstream&);

  void find(T, std::shared_ptr<Node<T>>&, std::shared_ptr<Node<T>>&);
  std::string printTree(std::shared_ptr<Node<T>>&, int, std::stringstream&);

  void upCase(std::shared_ptr<Node<T>>&);

  unsigned int fringe(std::shared_ptr<Node<T>>&, unsigned int&);
  unsigned int nodesInLevel(std::shared_ptr<Node<T>>&, unsigned int, unsigned int, unsigned int&);
  void getSubtreeCount(std::shared_ptr<Node<T>>&,unsigned int&);

  void makeIsoVector(std::shared_ptr<Node<T>>&, std::vector<unsigned int>&);
  bool isIsomorphic(std::shared_ptr<Node<T>>&, std::shared_ptr<Node<T>>&);
  
  void getLineage(std::shared_ptr<Node<T>>&, std::vector<T>&);
  std::string error(T);

  std::shared_ptr<Node<T>> root;
};

template <typename T>
void Tree<T>::getSubtreeCount(std::shared_ptr<Node<T>>& node, unsigned int& nodesInSubtrees) // Counts the number of nodes in a subtree given its root
{ 
  if (!node) return;
  ++nodesInSubtrees; 
  getSubtreeCount(node->child, nodesInSubtrees);
  getSubtreeCount(node->sibling, nodesInSubtrees);
}

template <typename T>
std::shared_ptr<Node<T>> Tree<T>::buildFromPrefix(std::ifstream& file, std::shared_ptr<Node<T>> p) // Builds a tree given the preorder traversal
{ 
  T data;
  unsigned int children;
  file >> data >> children;

  auto newNode = std::make_shared<Node<T>>(data,children);
  newNode->parent = p;

  std::shared_ptr<Node<T>> cur;
  for (int i = 0; i < children; ++i)
  {
    if (i == 0)
    {
      newNode->child = buildFromPrefix(file, newNode);
      cur = newNode->child;
    }
    else
    {
      cur->sibling = buildFromPrefix(file, newNode);
      cur = cur->sibling;
    }
  }
  
  unsigned int nodesInSubtrees = 0;
  getSubtreeCount(newNode, nodesInSubtrees);
  newNode->nodeCt = nodesInSubtrees;

  return newNode;
}

template <typename T>
void Tree<T>::find(T target, std::shared_ptr<Node<T>>& r, std::shared_ptr<Node<T>>& targetNode) // Traverses through the tree looking for a node
{
  if (!r) return;
  if (r->data == target) targetNode = r;
  find(target, r->child, targetNode);
  find(target, r->sibling, targetNode);
}

template <typename T>
std::shared_ptr<Node<T>> Tree<T>::find(T target) // Finds a node using the node's data
{
  std::shared_ptr<Node<T>> targetNode = nullptr;
  find(target, root, targetNode);
  return targetNode;
}

template <typename T>
std::string Tree<T>::printTree(std::shared_ptr<Node<T>> & r, int tabSize, std::stringstream& ss) // Prints the tree in an orderly fashion
{
  if (!r) return "Empty";
  for (int i = 0; i < tabSize; ++i) ss << "| ";

  ss << r->data << " [" << r->nodeCt << ":" << r->childCt << "]" << std::endl;

  if (r->child) printTree(r->child, tabSize + 1, ss);
  if (r->sibling) printTree(r->sibling, tabSize, ss);

  return ss.str();
}

template <typename T>
std::string Tree<T>::toPreorder(std::shared_ptr<Node<T>> & r, std::stringstream& ss) // Returns a preorder string in the same format expected by buildFromPrefix 
{
  ss << r->data << " " << r->childCt << " ";
  if (r->child) toPreorder(r->child, ss);
  if (r->sibling) toPreorder(r->sibling, ss);
  
  return ss.str();
}

template <typename T>
void Tree<T>::upCase(std::shared_ptr<Node<T>>& r) // Converts the entire tree into capital letters
{
  if(!r) return;
  std::locale loc;
  for (auto&& c : r->data) c = std::toupper(c,loc); 
  upCase(r->child);
  upCase(r->sibling);
}

template <typename T>
unsigned int Tree<T>::fringe(std::shared_ptr<Node<T>>& r, unsigned int& leaves) // Counts the number of leaf nodes
{
  if (!r) return 0;
  if (!r->child) ++leaves;
  if (r->child) fringe(r->child, leaves);
  if (r->sibling) fringe(r->sibling, leaves);
  unsigned int leafCount = leaves;
  return leafCount;
}

template <typename T>
unsigned int Tree<T>::nodesInLevel( // Counts the number of nodes on a given level
  std::shared_ptr<Node<T>>& r, 
  unsigned int targetLvl, 
  unsigned int curLvl,
  unsigned int& levelNodes)
{
  if (!r) return 0;
  if (curLvl == targetLvl)
  {
    ++levelNodes;
  }
  if (r->child) nodesInLevel(r->child, targetLvl, curLvl + 1, levelNodes);
  if (r->sibling) nodesInLevel(r->sibling, targetLvl, curLvl, levelNodes);
  return levelNodes;
}

template <typename T>
void Tree<T>::makeIsoVector(std::shared_ptr<Node<T>>& r, std::vector<unsigned int>& isoVector) // Fills vectors with isomorphic determination data
{
  isoVector.push_back(r->childCt);  
  if (r->child) makeIsoVector(r->child, isoVector);
  if (r->sibling) makeIsoVector(r->sibling, isoVector);
}


template <typename T>
bool Tree<T>::isIsomorphic(std::shared_ptr<Node<T>>& tree_a, std::shared_ptr<Node<T>>& tree_b) // Checks to see if two trees are isomorphic
{
  if (!tree_a || !tree_b) return false;

  std::vector<unsigned int> preOrder_a;
  std::vector<unsigned int> preOrder_b;

  makeIsoVector(tree_a, preOrder_a); 
  makeIsoVector(tree_b, preOrder_b);

  if ( preOrder_a.size() != preOrder_b.size() ) return false;

  for (auto i = 0u; i < preOrder_a.size(); ++i)
  {
    if (preOrder_a[i] != preOrder_b[i]) return false;
  }

  return true;
}

template <typename T>
std::string Tree<T>::error(T node) // Called if a node is not found in the tree. Prints an error
{
  std::stringstream ss;
  ss << "Error: \"" << node << "\" not found in tree" << std::endl;
  return ss.str();
}

template <typename T>
void Tree<T>::getLineage(std::shared_ptr<Node<T>>& node, std::vector<T>& parentVector) // Fills a vector with all of a node's parents
{
  parentVector.push_back(node->data);
  if (node->parent) getLineage(node->parent, parentVector);
}

template <typename T>
std::string Tree<T>::commonAncestor(T data_a, T data_b) // Finds the least common ancestor given two data points
{
  auto node_a = find(data_a);
  auto node_b = find(data_b);

  if (!node_a) return error(data_a);
  if (!node_b) return error(data_b);
  
  std::vector<T> parents_a;
  std::vector<T> parents_b;

  getLineage(node_a, parents_a);
  getLineage(node_b, parents_b);
  
  std::stringstream ss;

  for (auto i = 0u; i < parents_a.size(); ++i)
    for (auto j = 0u; j < parents_b.size(); ++j)
      if (parents_a[i] == parents_b[j])
      {
        ss << parents_a[i];
        return ss.str();
      }
}


template <typename T>
std::shared_ptr<Node<T>> Tree<T>::clone(std::shared_ptr<Node<T>> r, std::shared_ptr<Node<T>> p) // Constructs a deep copy of the tree
{
  if (!r) return nullptr;
  auto newNode = std::make_shared<Node<T>>(r->data, r->childCt, r->nodeCt, nullptr, nullptr, p);

  newNode->child = clone(r->child, newNode);
  newNode->sibling = clone(r->sibling, p);

  return newNode;
}

#endif
