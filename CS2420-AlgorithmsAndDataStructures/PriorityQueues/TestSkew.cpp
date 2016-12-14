#include <time.h>
#include "Median.h"


int main()
{
	const int TEST_VALUE = 15;
	srand(unsigned (time(0)));
	
	Median<int> m;

	for (int i = 0; i < TEST_VALUE; ++i)
	{
		int num = rand() % 1000;
		m.addNum(num);
	}

	m.report(true);  // print Heaps

	int size = 32;

	for (int i = TEST_VALUE; i < 1028; ++i)
	{  
		int num = rand()%1000;
	  //std::cout << num << " ";
	  m.addNum(num);
	  if (i == size)
		{
		  m.report(false);
		  size*=2;
	  }
	}
	
}
