#ifndef linkedBinaryTree_
#define linkedBinaryTree_
#include "binaryTree.h"
#include "binaryTreeNode.h"
#include <vector>
#include <queue>
#include <stack>

using namespace std;
template<class T>
void clear(queue<T> &q)
{
	queue<T> emptyQ;
	swap(emptyQ, q);
}
template<class T>
class linkedBinaryTree
{
public:
	~linkedBinaryTree(){ root = NULL;; treeSize = 0; }
	linkedBinaryTree() = default;
	linkedBinaryTree(int i, vector<T> v)//先中后序构造烂尾
	{
		switch (i)
		{
		case 1 : preMakeTree(v); break;
		case 2 : inMakeTree(v); break;
		case 3 : postMakeTree(v); break;
		}
			
	}
	linkedBinaryTree(vector<T> v);//广度构造
	linkedBinaryTree(linkedBinaryTree<T> &lbk);//复制构造
	void breadthFistSearch(void(*theVisit)(binaryTreeNode<T>*)){ visit = theVisit; breadthFistSearch(root); }
	void copyTree(linkedBinaryTree<T> &lbk);
	bool empty() const { return treeSize == 0; }
	int size() const { return treeSize; }
	void preOrder(void(*theVisit)(binaryTreeNode<T>*)){ visit = theVisit;	preOrder(root); }//对于不同的T可以构建不同的visit函数，然后传进来，再进行前序遍历
	void inOrder(void(*theVisit)(binaryTreeNode<T>*)){ visit = theVisit;	inOrder(root); }
	void postOrder(void(*theVisit)(binaryTreeNode<T>*)){ visit = theVisit;	postOrder(root); }
	void unrecursivePreOrder(void(*thevisit)(binaryTreeNode<T>*)){ visit= thevisit; unrecursivePreOrder(root); }
	void unrecursiveInOrder(void(*thevisit)(binaryTreeNode<T>*)){ visit= thevisit; unrecursiveInOrder(root); }
	void unrecursivePostOrder(void(*thevisit)(binaryTreeNode<T>*)){ visit= thevisit; unrecursivePostOrder(root); }
	void unrecursivePostOrderDoubleStack(void(*thevisit)(binaryTreeNode<T>*)){ visit = thevisit; unrecursivePostOrderDoubleStack(root); }
	
	int height(binaryTreeNode<T>* node)//返回高度
	{
		if (node == nullptr)
			return 0;
		int h1 = height(node->leftChild);
		int h2 = height(node->rightChild);
		if (h1 > h2) return ++h1;
		else return ++h2;
	}
	
	int height()//用两个队列，一个保存当前层，一个保存下一层
	{
		queue<binaryTreeNode<T>*> currq;
		queue<binaryTreeNode<T>*> nextq;
		int high = 0;
		currq.push(root);
		while (!currq.empty() || !nextq.empty())
		{
			high++;
			while (!currq.empty())
			{		
				binaryTreeNode<T>* temp = currq.front();
				currq.pop();
				if (temp->leftChild != nullptr)  { nextq.push(temp->leftChild); }
				if (temp->rightChild != nullptr)  { nextq.push(temp->rightChild); }
			}currq = nextq;
			clear(nextq);
		}
		return high;
	}
	
	void preMakeTree(vector<T> v)//没写完
	{
		
		binaryTreeNode<T> *temp;
		stack<binaryTreeNode<T>**> s;	
		for (auto beg = v.begin()+1; beg != v.end(); beg++)
		{
			if (*beg != '#')
			{
				temp= new binaryTreeNode<T>(*beg);
				s.push(&temp);
				temp = temp->leftChild;
			}
			else
			{
				binaryTreeNode<T> *lastNode = s.top();
				s.pop();
				temp = lastNode->rightChild;
			}
		}
	}
	void inMakeTree(vector<T> v)
	{

	}
	void postMakeTree(vector<T> v)
	{

	}
	
	binaryTreeNode<T>* getroot(){ return root; }
protected:
	binaryTreeNode<T> *root;
	int treeSize;
	void (*visit)(binaryTreeNode<T> *node);//函数指针
	void preOrder(binaryTreeNode<T> *node)//递归前序遍历
	{
		if (node != NULL)
		{
			visit(node);
			preOrder(node->leftChild);
			preOrder(node->rightChild);
		}
	}
	void inOrder(binaryTreeNode<T> *node)//递归中序遍历
	{
		if (node != NULL)
		{
		    inOrder(node->leftChild);
			visit(node);
			inOrder(node->rightChild);
		}
	}
	void postOrder(binaryTreeNode<T> *node)//递归后序遍历
	{
		if (node != NULL)
		{
			postOrder(node->leftChild);
			postOrder(node->rightChild);
			visit(node);
		}
	}



	void  breadthFistSearch(binaryTreeNode<T> *node)//用队列实现广度优先遍历
	{
		queue<binaryTreeNode<T>*> q;
		q.push(node);
		while (!q.empty())
		{
			binaryTreeNode<T> *temp = q.front();
			q.pop();
			if(temp != NULL)
			{
				visit(temp);
				q.push(temp->leftChild);
				q.push(temp->rightChild);
			}
			//else visit(&binaryTreeNode<T>('#'));
		}	
	}

	void unrecursivePreOrder(binaryTreeNode<T> *node)//用栈实现非递归前序遍历
	{
		stack<binaryTreeNode<T>*> s;
		binaryTreeNode<T> *temp = node;
		while (temp!=NULL||!s.empty())
		{
			while (temp != NULL)
			{
			s.push(temp);
			visit(temp);
			temp = temp->leftChild;
			}
			temp = s.top();
			s.pop();
			temp = temp->rightChild;
		}
	}

	void unrecursiveInOrder(binaryTreeNode<T> *node)//用栈实现非递归中序遍历
	{
		stack<binaryTreeNode<T>*> s;
		binaryTreeNode<T> *temp = node;
		while (temp != NULL || !s.empty())
		{
			while (temp != NULL)
			{
				s.push(temp);
				temp = temp->leftChild;
			}
			temp = s.top();
			s.pop();
			visit(temp);
			temp = temp->rightChild;
		}
	}

	void unrecursivePostOrder(binaryTreeNode<T> *node)//用栈实现非递归后序遍历
	{
		stack<binaryTreeNode<T>*> s;
		binaryTreeNode<T> *temp = node;
		binaryTreeNode<T> *lastnode = NULL;
		while (temp != NULL)
		{
			s.push(temp);
			temp = temp->leftChild;
		}
		while ( !s.empty())
		{	
			temp = s.top();
			if (temp->rightChild == NULL||temp->rightChild == lastnode)//右子节点为空或已经读过时，才会读根节点
			{
				visit(temp);
				lastnode = temp;
				s.pop();
			}
			else
			{
				temp = temp->rightChild;
				while (temp != NULL)
				{
					s.push(temp);
					temp = temp->leftChild;
				}
			}
		}		
	}

	void unrecursivePostOrderDoubleStack(binaryTreeNode<T> *node)//用双栈实现非递归后序遍历
	{
		stack<binaryTreeNode<T>*> s;
		stack<binaryTreeNode<T>*> temps;
		while (node != NULL)
		{
			s.push(node);
			temps.push(node);
			node = node->rightChild;	
		}
		while (!s.empty())
		{
			if (s.top()->leftChild != NULL)
			{
				node = s.top()->leftChild;
				s.pop();
				while (node != NULL)
				{
					temps.push(node);
					s.push(node);
					node = node->rightChild;
				}
			}
			else s.pop();	
		}
		while (!temps.empty())
		{
			node = temps.top();
			temps.pop();
			visit(node);
		}
	}

	binaryTreeNode<T>* copyNode(const binaryTreeNode<T> *node) const
	{
		if (node != NULL)
		{
			binaryTreeNode<T>* newNode = new binaryTreeNode<T>(node->element);
			newNode->leftChild = copyNode(node->leftChild);
			newNode->rightChild = copyNode(node->rightChild);
			return newNode;//return的位置,中间会返回很多次newNode，但最后会返回第一次进来时创建的newNode，因为递归是倒着回去的
		}
		else return NULL;
	}
};

template<class T>
linkedBinaryTree<T>::linkedBinaryTree(vector<T> v)
{
	queue<binaryTreeNode<T>**> q;//队列中存的只是push对象的副本，即此处若用一个*的指针，front出来的只是指针的副本，对此指针操作不会改变原指针
	treeSize = v.size();
	for (auto beg = v.begin(); beg != v.end();beg++)
	{	
		if (q.empty())
		{
			root = new binaryTreeNode<T>(*beg);
			q.push(&root->leftChild);
			q.push(&root->rightChild);
			continue;
		}
		binaryTreeNode<T> **node = q.front();
		q.pop();
		if ((*beg)!= '#')
		{
			*node= new binaryTreeNode<T>(*beg);
			q.push(&(*node)->leftChild);
			q.push(&(*node)->rightChild);
			
		}
	}
	
}

template<class T>
linkedBinaryTree<T>::linkedBinaryTree(linkedBinaryTree<T> &lbk)
{
	copyTree(lbk);
}

template<class T>
void linkedBinaryTree<T>::copyTree(linkedBinaryTree<T> &lbk) 
{
	root = copyNode(lbk.root);
}

#endif