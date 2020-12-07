#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"
#include <bits/stdc++.h>


MinHeap::MinHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new int[capacity];
}

void MinHeap::MinHeapify(int i)
{
	int left_side = left(i); 
    int right_side = right(i); 
    int smallest_element = i; 
    if (left_side < heap_size && harr[left_side] < harr[i]) 
        smallest_element = left_side; 
    if (right_side < heap_size && harr[right_side] < harr[smallest_element]) 
        smallest_element = right_side; 
    if (smallest_element != i) 
    { 
        swap(harr[i], harr[smallest_element]); 
        MinHeapify(smallest_element); 
    }
}
 
int MinHeap::parent(int i)
{
	return (i - 1) / 2;
}
 
int MinHeap::left(int i)
{
	return (2 * i + 1);
}
 
int MinHeap::right(int i)
{
	return (2 * i + 2);
}
 
int MinHeap::extractMin()
{
	  int min = harr[0]; 
    harr[0] = harr[heap_size-1]; 
    heap_size--; 
    MinHeapify(0); 
  
    return min;
}
 
void MinHeap::decreaseKey(int i, int new_val)
{    
    harr[i] = new_val;
    if (i != 0){
        if (harr[parent(i)] > harr[i]){
             swap(harr[i], harr[parent(i)]); 
            i = parent(i); 
            decreaseKey(i, new_val);
        }
    }
}
 
int MinHeap::getMin()
{
	return harr[0];
}
 
void MinHeap::deleteKey(int i)
{
	if (i >= heap_size){
		return;
	}

	decreaseKey(i, INT_MIN); 
  extractMin(); 	 
}

void Helper(int *harr, int ind){
    MinHeap *minH;
    int p;
    if (ind != 0){
        p = minH->parent(ind);
        if (harr[p] > harr[ind]){
             swap(harr[ind], harr[p]);
             ind = p; 
             Helper(harr, ind);
        }
    }
}
 
void MinHeap::insertKey(int k)
{
	if (heap_size == capacity) 
   { 
     return; 
   } 
  
    heap_size++; 
    int looper = heap_size - 1; 
    harr[looper] = k; 
      
    Helper(harr, looper);
}

int* MinHeap::getHeap()
{
	return harr;
}

#endif