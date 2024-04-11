#include<iostream>
#include<ctime>
#include<queue>
#include<algorithm>

#define PRINT_ARRAY 1
using namespace std;

/*
// MUST BE LARGE ENOUGH FOR DATA SET
*/
#define ARRAY_SIZE 1500; 

struct tweet {
	string username;
	string userBio;
	float postedTime; // key
	string tweetContent;
	int likes;
};

// A class for Min Heap
class MinHeap
{
private:
	tweet* *heap; // pointer to array of elements in heap
	int capacity; // maximum possible size of min heap
	int currentSize; // Current number of elements in min heap 
	void MinHeapify(int index);
	int parent(int i)
	{
	   return (i-1)/2;
	}
	int left(int i) 
	{
	   return (2*i+1);
	}
	int right(int i)
	{
	   return (2*i + 2);
	}
	void swap(int i, int pi);
public:
	MinHeap();
	~MinHeap();
	int size() { 
		return currentSize;
	}
	int cap() {
		return capacity; 
	}
	void push(tweet* twt); // insert()
	tweet* pop(); // extracMin()
	tweet* peek()
	{
	   return heap[0];
	}
	void printHeap();
};
 
