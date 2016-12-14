#include <iostream>
#include <fstream>
#include <cassert>
#include "graph.h"

void print(std::ostream& out)
{
	out << "=== Graph A ===" << std::endl;
  Graph g("prog7A.txt",out);
	g.printMatrix();
  g.computeTour(); 

	out << "=== Graph B ===" << std::endl;
  Graph g1("prog7B.txt",out);
	g1.printMatrix();
  g1.computeTour();

	out << "=== Graph C ===" << std::endl;
  Graph g2("prog7C.txt",out);
	g2.printMatrix();
  g2.computeTour();
}

int main()
{
	std::ofstream fout;
	fout.open("tourOut.txt");
	assert(fout);
	
	std::cout << "VELCOME TO HYDRAULIC GRAPH CHANNEL" << std::endl;
	std::cout << "enter a 0 for output to be printed to the screen" << std::endl;
	std::cout << "enter a 1 for output to be written to tourOut.txt" << std::endl;

	int choice;
	std::cin >> choice;

	if (choice == 0) print(std::cout);
	else print(fout);
}
