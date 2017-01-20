This program tests the speed at which a number of sorting algorithms can sort variously-sized vectors filled with random integers. It includes three O(n^2) algorithms:

- Bubble sort
- Insertion sort
- Selection sort

and three O(n log n) algorithms:

- Merge sort
- Quicksort
- std::sort

The algrorithms are tested by generating vectors filled using the Mersenne Twister RNG and passing them through the sorting functions. Starting with a vector size of 1,000 integers, each algorithm sorts the vector ten times, reports an average sorting time, and moves on to sort the next vector that is 1,000 integers larger than the last. It does this until sorting the final vector that is 100,000 integers in size.

The vector iterations and vector sizes can easily be changed by modifying the for-loop values in int main(), and the number of times to resort each vector to obtain an average may easily be modified by changing REPEATS in the anonymous namespace.
