#ifndef binaryTree_
#define binaryTree_

template<class T>
class binaryTree
{
public:
	virtual ~binaryTree(){}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual void preOrder(void(*func)(T*)) = 0;
	virtual void inOrder(void(*func)(T*)) = 0;
	virtual void postOrder(void(*func)(T*)) = 0;
};

#endif