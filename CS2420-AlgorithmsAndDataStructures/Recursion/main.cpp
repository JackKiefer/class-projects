#include <iostream>
#include <memory>
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <limits>
#include "tree.h"

int main()
{
  const auto SIZE = 12;

  std::ifstream file;
  file.open("prog2In.txt");
  assert(file);

  std::vector< Tree<std::string> > tree(SIZE);
  
  for (int i = 0; i < SIZE; ++i)
  {
   tree[i].buildFromPrefix(file);
   std::cout << "Tree " << i << ":" << std::endl;
   std::cout << tree[i].printTree();
   std::cout << "Fringe nodes: " << tree[i].fringe() << std::endl << std::endl;
  }
  
  if (!tree[0].find("dins")) std::cout << "dins not found" << std::endl;
	if (!tree[0].find("tone")) std::cout << "tone not found" << std::endl;

	tree[0].upCase();

	std::cout << tree[0].printTree() << std::endl;

	if (!tree[0].find("guck")) std::cout << "guck not found" << std::endl;
	if (!tree[0].find("TONE")) std::cout << "TONE not found" << std::endl;
  
	tree[7].makeEmpty();
	std::cout << "Tree 7 has been emptied. Empty tree fringe: " << tree[7].fringe() << std::endl << std::endl;

	for (int i = 0; i < SIZE; ++i)
  {
		std::cout << "Nodes in level 2 of tree " << i << ": " << tree[i].nodesInLevel(2) << std::endl;
	}
	
	std::cout << std::endl << "TREE 3" << std::endl << tree[3].printTree() << std::endl;
	std::cout << "TREE 10" << std::endl << tree[10].printTree() << std::endl;
	tree[3] = tree[10].clone();
	tree[3].upCase();
	std::cout << " TREE 3 cloned" << std::endl << tree[3].printTree() << std::endl;
	std::cout << " TREE 10" << std::endl << tree[10].printTree() << std::endl;;

  for (int i = 0; i < SIZE; ++i)
		for (int j = i + 1; j < SIZE; ++j)
			if (tree[i].isIsomorphic( tree[j]) )
        std::cout << "Two trees are isomorphic! Tree " << i << " and tree " << j << std::endl << std::endl; 

	std::cout << "Common Ancestor of lade and gunk: " << std::endl << tree[2].commonAncestor("lade", "gunk") << std::endl;
	std::cout << "Common Ancestor of luce and gunk: " << std::endl << tree[1].commonAncestor("luce", "gunk") << std::endl;
	std::cout << "Common Ancestor of lick and dene: " << std::endl << tree[1].commonAncestor("lick", "dene") << std::endl;
	std::cout << "Common Ancestor of lick and muck: " << std::endl << tree[1].commonAncestor("lick", "muck") << std::endl;
	
	std::cout << "Press Enter to exit..." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
