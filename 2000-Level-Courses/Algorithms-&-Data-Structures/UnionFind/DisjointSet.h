#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <string>
#include <sstream>
#include <array>

template <typename T, std::size_t N>
class DisjointSet
{
public:
	DisjointSet() :unionCt(0), findCt(0) { arr.fill(-1); }
	bool unionize(T, T);
	bool connected() { return (unionCt == N - 1); }
	int getUnionCt() { return unionCt; }
	int getFindCt() { return findCt; }
	std::string toString();	
private:
	int unionCt;
	int findCt; 
	int find(T);
	std::array<T, N> arr;
};

// Returns the index of the target's root. Utilizes path compression.
template <typename T, std::size_t N>
int DisjointSet<T, N>::find(T target)
{
	++findCt;
	
	auto parent = arr[target];

	if ( parent >= 0 ) // Parent is not a root
	{
		arr[target] = find(parent);
	}
	else
	{
		return target; // Roots return their own index
	}

	return arr[target];
}

// Unions two sets together.
// Employs the unioning by height heuristic.
template <typename T, std::size_t N>
bool DisjointSet<T, N>::unionize(T a, T b)
{
	auto rootA = find(a); // Index of a's root
	auto rootB = find(b); // Index of b's root

	if ( rootA == rootB ) return false; // Already in same set

	++unionCt;

	if ( arr[rootB] < arr[rootA] ) // rootB is greater
	{
		arr[rootA] = rootB;
		return true;
	}
	else
	{
		if ( arr[rootA] == arr[rootB] ) --arr[rootA]; // Decrement height if they're the same
		arr[rootB] = rootA; // rootA is (now) greater, make it the new root
		return true;
	} 
}

// Prints out the array prettily.
// Supports arrays of up to size 100.
template <typename T, std::size_t N>
std::string DisjointSet<T, N>::toString()
{
	std::ostringstream oss;
	int indexes = 0;


	// -- Values row -- //
	oss << '|';
	for (auto && e : arr)
	{
		++indexes;
		oss << " ";
		if ( e >= 0 && e < 10 ) oss << " ";
		oss << e << " |";
	}
	
	// -- Separator -- //
	oss << std::endl << '-';
	for (int i = 0; i < indexes; ++i) oss << "-----";

	// -- Indexes row -- //
	oss << std::endl << '|';
	for (int i = 0; i < indexes; ++i)
	{
		oss << " ";
		if ( i < 10 ) oss << " ";
		oss << i << " |";
	}
	
	return oss.str();
}

#endif
