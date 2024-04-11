#include "minHeapify.hpp"

void printTweet(tweet* twt) {
	cout << twt->username << ": " << endl;
	cout << "\tbio: " << twt->userBio << endl;
	cout << "\tcontent: " << twt->tweetContent << endl;
	cout << "\tlikes: " << twt->likes << endl;
	cout << "\tposted time: " << twt->postedTime << endl;
}

MinHeap::MinHeap()
{
    currentSize = 0;
    capacity = ARRAY_SIZE; 
    heap = new tweet*[capacity];
}

MinHeap::~MinHeap()
{
    delete [] heap;
}
 
void MinHeap::push(tweet* twt){ // insert()
   if(currentSize==capacity){
      cout << "heap is full " << endl;
   }
   else{
       int i = currentSize;
       heap[i] = twt; // appending to the end of array (heap)

       while(i != 0 && heap[parent(i)]->postedTime > heap[i]->postedTime){
          swap(i, parent(i));
          i = parent(i);
       }
    currentSize++;
   }
}
 
// for now, just return -1 if there's nothing to pop
tweet* MinHeap::pop(){ // extracMin()

    if(currentSize <= 0)
       return NULL;
    if(currentSize == 1){
       currentSize--;
       return heap[0];
    }

    tweet* poppedVal = heap[0];

    heap[0] = heap[currentSize-1];
    currentSize--;
    MinHeapify(0);

    return poppedVal;
}
 
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i){
    int leftChild = left(i);
    int rightChild = right(i);
    int smallest = i; // index of smallest value

    if(leftChild < currentSize)
		if (heap[leftChild]->postedTime < heap[i]->postedTime)
       		smallest = leftChild;
    if(rightChild < currentSize)
		if (heap[rightChild]->postedTime < heap[smallest]->postedTime)
       		smallest = rightChild;

    if( smallest != i ){
       swap(i,smallest);
       MinHeapify(smallest);
    }

}
 
void MinHeap::swap(int i, int pi){
	tweet* temp = heap[i];
	heap[i] = heap[pi];
	heap[pi] = temp;
}

void MinHeap::printHeap() {
    cout << "The heap array is currently {";
    for (int i = 0; i < currentSize; i++) {
       cout << heap[i]->postedTime;
       if (i < currentSize-1) {
          cout << ", ";
       }
    }
    cout << "}" << endl;
}


