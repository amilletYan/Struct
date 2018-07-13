#ifndef linkeStack_
#define linkedStack_
#include "chainNode.h"
#include <iostream>
using namespace std;
class linkedStack
{
public:
	linkedStack(int element)
	{
		stackTop = new chainNode(element);
		stackSize = 1;
	}
	linkedStack(int element, chainNode* node)
	{
		stackTop = new chainNode(element, node);
		stackSize = 1;
		while (node != nullptr)
		{
			stackSize++;
			node++;
		}
	}
	~linkedStack()
	{
		while (stackTop != nullptr)
		{
			chainNode *node = stackTop->nextNode;
			delete stackTop;
			stackTop = node;
		}
	}
	int top(){ return stackTop->element; }
	void push(int i)
	{
		stackTop = new chainNode(i, stackTop);
		stackSize++;
	}
	void pop()
	{
		chainNode *node = stackTop->nextNode;
		delete stackTop;
		stackTop = node;
		stackSize--;
	}
	
	ostream& operator<<(ostream &os)//�����������������Ϊ��Ա��������Ҫ��ʱ�������ͳ���<<�������������cpp
	{
		os << stackSize<< endl;
		return os;
	}
private:
	chainNode* stackTop;
	int stackSize;
};
#endif