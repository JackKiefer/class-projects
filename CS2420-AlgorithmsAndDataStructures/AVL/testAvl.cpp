#include "avlTreeTemplate.h"
#include <iostream>

int main()
{
	AvlTree<int> tree;

	tree.insert(1);
	tree.insert(3);
	tree.insert(5);
	tree.insert(7);
	tree.insert(9);
	tree.insert(9);
	tree.insert(9);
	tree.insert(11);
	tree.insert(2);
	tree.insert(9);
	tree.insert(4);
	tree.insert(8);

	std::cout << tree.toStringTree("add initial values") << std::endl;

	tree.remove(7);
	tree.remove(9);

	std::cout << tree.toStringTree("remove 7 and 9") << std::endl;

	tree.insert(30);
	tree.insert(50);
	tree.insert(30);
	tree.insert(30);
	tree.insert(15);
	tree.insert(18);
	
	std::cout << tree.toStringTree("add more values") << std::endl;

	std::cout << "removing minimum value: " << tree.removeMin() << std::endl;
	
	std::cout << tree.toStringTree("removeMin") << std::endl;

	std::cout << "removing minimum value: " << tree.removeMin() << std::endl;
	
	std::cout << tree.toStringTree("removeMin 2: Electric Boogaloo") << std::endl;

	std::cout << "removing minimum value: " << tree.removeMin() << std::endl;
	
	std::cout << tree.toStringTree("removeMin 3: Return of the Memory Leak") << std::endl;

	tree.insert(17);

	std::cout << tree.toStringTree("adding 17") << std::endl;
}
