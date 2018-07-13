#ifndef  maxHeap_
#define  maxHeap_
#include <iostream>
using namespace std;
class maxHeap
{
public:
	maxHeap(int initialCapacity = 10)
	{
		heap = new int[initialCapacity];
		arrayLength = initialCapacity;
		heapSize = 0;
	}

	~maxHeap(){ delete [] heap; }

	bool empty(){ return heapSize == 0; }

	void push(int element)
	{
		if (heapSize +1== arrayLength)
		{
			arrayLength = 2 * arrayLength;
			int *newheap = new int[arrayLength];
			for (int i = 0; i<heapSize ; i++)
			{
				newheap[i] = heap[i];
			}
			heap = newheap;
		}
		int currentNode = ++heapSize / 2 - 1;
		int insertNode = heapSize-1;
		while (currentNode>=0&&element>heap[currentNode])
		{	
				int temp = heap[currentNode];
				heap[insertNode] = temp;
				heap[currentNode] = element;
				insertNode = currentNode;
				currentNode = (currentNode - 1) / 2;
		}
	}

	void initialize(int *theHeap, int size)
	{
		delete[] heap;
		heap = theHeap;
		heapSize = size;
		for (int i =size / 2-1; i >=0; i--)
		{
			int child = i * 2 + 1;
			while (child<heapSize)
			{	
				
				int pos = i;
				if (child + 1 < heapSize)//两个子
				{
					if (heap[i] < heap[child]){ pos = child; }
					if (heap[pos] < heap[child + 1]){ pos = child + 1; }
					if (pos != i){ int temp = heap[i]; heap[i] = heap[pos]; heap[pos] = temp; i = pos; }
					else break;
				}
				else//只存在在末尾
				{
					if (heap[i] < heap[child]){ int temp = heap[i]; heap[i] = heap[child]; heap[child] = temp; }
					else break;
				}
				child = i * 2 + 1;
			}		
		}
	}

	void output()
	{
		for (int i = 0; i < heapSize; i++)
		{
			cout << heap[i]<<ends;
		}
	}

	int top(){ return heap[0]; }

	void pop()
	{
		int lastElement = heap[heapSize-1];
		heapSize--;
		heap[0] = lastElement;
		int currentNode = 0;
		int child = 1;
		while (child < heapSize)
		{
			if (child+1<heapSize&&heap[child] < heap[child + 1])
				child++;
			if (lastElement>heap[child])
				break;
			heap[currentNode] = heap[child];
			currentNode = child;
			child = 2 * child+1;
		}
		heap[currentNode] = lastElement;
	}

	void heapSort(int *a)
	{
		a[0] = top();
		pop();
		if (heapSize>0)
		heapSort(a+1);
	}


private:
	int heapSize;
	int arrayLength;
	int *heap;
};
#endif