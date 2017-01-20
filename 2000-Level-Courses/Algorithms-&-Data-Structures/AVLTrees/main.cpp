#include <iostream>
#include <limits>
#include "GameTree.h"
#include "GameQueue.h"
#include "AvlTree.h"
#include "time.h"

int main()
{
	std::cout << "=== Begin AVL-tree Test Output ===" << std::endl << std::endl;
	AvlTree<int> avl;

	avl.insert(1);
	avl.insert(3);
	avl.insert(5);
	avl.insert(7);
	avl.insert(9);
	avl.insert(9);
	avl.insert(9);
	avl.insert(11);
	avl.insert(2);
	avl.insert(9);
	avl.insert(4);
	avl.insert(8);

	std::cout << avl.toStringTree("add initial values") << std::endl;

	avl.remove(7);
	avl.remove(9);

	std::cout << avl.toStringTree("remove 7 and 9") << std::endl;

	avl.insert(30);
	avl.insert(50);
	avl.insert(30);
	avl.insert(30);
	avl.insert(15);
	avl.insert(18);
	
	std::cout << avl.toStringTree("add more values") << std::endl;

	std::cout << "removing minimum value: " << avl.removeMin() << std::endl;
	
	std::cout << avl.toStringTree("removeMin") << std::endl;

	std::cout << "removing minimum value: " << avl.removeMin() << std::endl;
	
	std::cout << avl.toStringTree("removeMin 2: Electric Boogaloo") << std::endl;

	std::cout << "removing minimum value: " << avl.removeMin() << std::endl;
	
	std::cout << avl.toStringTree("removeMin 3: Return of the Memory Leak") << std::endl;

	avl.insert(17);

	std::cout << avl.toStringTree("adding 17") << std::endl;

	std::cout << "This concludes the AVL-tree testing portion of the program." << std::endl << "Please close your booklet and set your pencil down. Do not go on to the next section." << std::endl;
	std::cout << "A fifteen-minute break will now be allowed by your proctor. You may not discuss the contents of this program with the other program-takers during the break." << std::endl;
	std::cout << std::endl << "When you are ready, press ENTER to continue..." << std::endl;
	
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	Game tree;
	GameQueue q;
	Time time;
	

	std::cout << "=== Begin A* Search Algorithm Test Output  ===" << std::endl << std::endl;

	std::cout << ":::: KISS to WOOF ::::" << std::endl << std::endl;
	
	std::cout << "< Brute-force >" << std::endl;

	time.start();
	q.play("kiss","woof");
	time.end();

	std::cout << "Enqueues: " << q.enqs << std::endl;
	std::cout << "Dequeues: " << q.deqs << std::endl;
	std::cout << "Runtime:  " << time.ms() << std::endl;

	std::cout << std::endl;

	std::cout << "< A* Search >" << std::endl;

	time.start();
	tree.play("kiss","woof");
	time.end();

	std::cout << "Enqueues: " << tree.enqs << std::endl;
	std::cout << "Dequeues: " << tree.deqs << std::endl;
	std::cout << "Runtime:  " << time.ms() << std::endl;

	std::cout << "___________________________" << std::endl;
	std::cout << std::endl <<  "::: COCK to NUMB :::" << std::endl << std::endl;

	std::cout << "< Brute-force >" << std::endl;

	time.start();
	q.play("cock","numb");
	time.end();

	std::cout << "Enqueues: " << q.enqs << std::endl;
	std::cout << "Dequeues: " << q.deqs << std::endl;
	std::cout << "Runtime:  " << time.ms() << std::endl;

	std::cout << std::endl;

	std::cout << "< A* Search >" << std::endl;

	time.start();
	tree.play("cock","numb");
	time.end();

	std::cout << "Enqueues: " << tree.enqs << std::endl;
	std::cout << "Dequeues: " << tree.deqs << std::endl;
	std::cout << "Runtime:  " << time.ms() << std::endl;


	std::cout << "___________________________" << std::endl;
	std::cout << std::endl <<  "::: JURA to SUCH :::" << std::endl << std::endl;

	std::cout << "< Brute-force >" << std::endl;

	time.start();
	q.play("jura","such");
	time.end();

	std::cout << "Enqueues: " << q.enqs << std::endl;
	std::cout << "Dequeues: " << q.deqs << std::endl;
	std::cout << "Runtime:  " << time.ms() << std::endl;

	std::cout << std::endl;

	std::cout << "< A* Search >" << std::endl;

	time.start();
	tree.play("jura","such");
	time.end();

	std::cout << "Enqueues: " << tree.enqs << std::endl;
	std::cout << "Dequeues: " << tree.deqs << std::endl;
	std::cout << "Runtime:  " << time.ms() << std::endl;



	std::cout << "___________________________" << std::endl;
	std::cout << std::endl <<  "::: STET to WHEY :::" << std::endl << std::endl;

	std::cout << "< Brute-force >" << std::endl;

	time.start();
	q.play("stet","whey");
	time.end();

	std::cout << "Enqueues: " << q.enqs << std::endl;
	std::cout << "Dequeues: " << q.deqs << std::endl;
	std::cout << "Runtime:  " << time.ms() << std::endl;

	std::cout << std::endl;

	std::cout << "< A* Search >" << std::endl;

	time.start();
	tree.play("stet","whey");
	time.end();

	std::cout << "Enqueues: " << tree.enqs << std::endl;
	std::cout << "Dequeues: " << tree.deqs << std::endl;
	std::cout << "Runtime:  " << time.ms() << std::endl;



	std::cout << "___________________________" << std::endl;
	std::cout << std::endl <<  "::: JACK to SEXY :::" << std::endl << std::endl;

	std::cout << "< Brute-force >" << std::endl;

	time.start();
	q.play("jeans","fades");
	time.end();

	std::cout << "Enqueues: " << q.enqs << std::endl;
	std::cout << "Dequeues: " << q.deqs << std::endl;
	std::cout << "Runtime:  " << time.ms() << std::endl;

	std::cout << std::endl;

	std::cout << "< A* Search >" << std::endl;

	time.start();
	tree.play("jeans","fades");
	time.end();

	std::cout << "Enqueues: " << tree.enqs << std::endl;
	std::cout << "Dequeues: " << tree.deqs << std::endl;
	std::cout << "Runtime:  " << time.ms() << std::endl;


	std::cout << "Press ENTER to exit..." << std::endl;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


}

