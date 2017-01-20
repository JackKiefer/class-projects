#include <vector>
#include <algorithm>
#include "Sort.hpp"

void bubbleSort(std::vector<int>& v)
{
//	                                           /
//                        _,.------....___,.' ',.-.
//    bubblesort       ,-'          _,.--"        |
//    bubblesor      ,'         _.-'              .
//    bulbasaur     /   ,     ,'                   `
//                 .   /     /                     ``.
//                 |  |     .                       \.\
//       ____      |___._.  |       __               \ `.
//     .'    `---""       ``"-.--"'`  \               .  \
//    .  ,            __               `              |   .
//    `,'         ,-"'  .               \             |    L
//   ,'          '    _.'                -._          /    |
//  ,`-.    ,".   `--'                      >.      ,'     |
// . .'\'   `-'       __    ,  ,-.         /  `.__.-      ,'
// ||:, .           ,'  ;  /  / \ `        `.    .      .'/
// j|:D  \          `--'  ' ,'_  . .         `.__, \   , /
//  L:_  |                 .  "' :_;                `.'.'
//.    ""'                  """""'                    V
// `.                                 .    `.   _,..  `
//   `,_   .    .                _,-'/    .. `,'   __  `
//    ) \`._        ___....----"'  ,'   .'  \ |   '  \  .
//   /   `. "`-.--"'         _,' ,'     `---' |    `./  |
//  .   _  `""'--.._____..--"   ,             '         |
//  | ." `. `-.                /-.           /          ,
//  | `._.'    `,_            ;  /         ,'          .
// .'          /| `-.        . ,'         ,           ,
// '-.__ __ _,','    '`-..___;-...__   ,.'\ ____.___.'
// `"^--'..'   '-`-^-'"--    `-^-'`.''"""""`.,^.`.--'
	bool done = false;
	while (!done)
	{
		done = true;
		for (unsigned int i = 0; i < v.size() - 1; ++i)
		{
			if (v[i] > v[i + 1])
			{
				std::swap(v[i], v[i + 1]);
				done = false;
			}
		}
	}
}

void insertionSort(std::vector<int>& v)
{
	for (unsigned int i = 1; i < v.size(); ++i)
	{
		for (unsigned int j = 0; j < i; ++j)
		{
			if (v[j] < v[i]) std::swap(v[j], v[i]);
		}
	}
}

int getMin(std::vector<int>& v, int start)
{

	int min = std::numeric_limits<int>::max();
	int	current = -1;
	for (unsigned int i = start; i < v.size(); ++i)
	{
		if (min > v[i])
		{
			min = v[i];
			current = i;
		}
	}
	return current;
}

void selectionSort(std::vector<int>& v)
{
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		int smallest = getMin(v, i);
		std::swap(v[i], v[smallest]);
	}
}

int partition(std::vector<int>& v, int start, int end, int pivot)
{
	std::swap(v[pivot], v[end - 1]);
	int firstGreater = start;
	for (int i = start; i < end - 1; ++i)
	{
		if (v[i] <= v[end - 1])
		{
			std::swap(v[i], v[firstGreater]);
			++firstGreater;
		}
	}
	std::swap(v[end - 1], v[firstGreater]);
	return firstGreater;
}

int getPivot(std::vector<int>& v, int start, int end)
{
	auto first = v[start];
	auto last = v[end - 1];
	auto mid = v[(start + end) / 2];
	if      ((first <= last && last <= mid)  || (mid <= last && last <= first)) return end - 1;
	else if ((last <= first && first <= mid) || (mid <= first && first <= last)) return start;
	else if ((first <= mid  && mid <= last)  || (last <= mid && mid <= first)) return (start + end) / 2;
	else return mid;
}

void quickSortActual(std::vector<int>& v, int start, int end)
{
	if (end - start <= 1) return;
	auto pivot = getPivot(v, start, end);
	pivot = partition(v, start, end, pivot);
	
	quickSortActual(v, start, pivot);
	quickSortActual(v, pivot, end);
}

void quickSort(std::vector<int>& v) 
{ 
	quickSortActual(v, 0, v.size()); 
}

void stdSort(std::vector<int>& v)
{
	std::sort(v.begin(), v.end());
}

std::vector<int> merge(std::vector<int>& a, std::vector<int>& b)
{
	int i = 0;
	int j = 0;
	std::vector<int> merged;
	merged.reserve(a.size() + b.size());
	while (i < a.size() && j < b.size())
	{
		if (a[i] < b[j])
		{
			merged.push_back(a[i]);
			++i;
		}
		else
		{
			merged.push_back(b[j]);
			++j;
		}
	}
	if (i < a.size())
	{
		for (int k = i; k < a.size(); ++k)
		{
			merged.push_back(a[k]);
		}
	}
	else
	{
		for (int k = j; k < b.size(); ++k)
		{
			merged.push_back(b[k]);
		}
	}
	return merged;
}

std::vector<int> mergeSortActual(std::vector<int> v, int low, int high)
{
	int mid;
	std::vector<int> sorted;
	if (high - low > 1)
	{
		mid = (low + high) / 2;
		std::vector<int> a = mergeSortActual(v, low, mid);
		std::vector<int> b = mergeSortActual(v, mid, high);
		sorted = merge(a, b	);
	}
	else sorted = std::vector<int>(v.begin() + low, v.begin() + high);
	return sorted;
}

void mergeSort(std::vector<int>& v)
{
	v = mergeSortActual(v, 0, v.size());
}
