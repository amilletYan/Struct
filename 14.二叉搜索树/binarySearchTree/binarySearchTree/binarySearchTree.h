#ifndef _binarySearchTree
#define _binarySearchTree
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
struct binaryTreeNode
{
	binaryTreeNode() = default;
	binaryTreeNode(pair<int, int> newPair){ element = newPair; }
	binaryTreeNode(pair<int, int> newPair, binaryTreeNode *left, binaryTreeNode *right){ element = newPair; leftChild = left; rightChild = right; }
	pair<int, int> element;
	binaryTreeNode *leftChild=nullptr;
	binaryTreeNode *rightChild=nullptr;
};
class binarySearchTree
{
	friend ostream& operator<<(ostream &os, binarySearchTree bst);
public:
	binarySearchTree(){ root = nullptr; size = 0; }

	void insert(pair<int, int> newNode)
	{
		if (root == nullptr)
		{
			root = new binaryTreeNode(newNode);
			size++;
			return;
		}
		binaryTreeNode *temp = root,*last=nullptr;
		while (temp != nullptr)
		{
			last = temp;
			if (newNode.first > temp->element.first)  temp = temp->rightChild;
			else if (newNode.first < temp->element.first) temp = temp->leftChild;
			else{ temp->element.second = newNode.second; break; }
		}
		if (last != temp)
		{
			binaryTreeNode *newTreeNode = new binaryTreeNode(newNode);
			if (newNode.first>last->element.first) last->rightChild = newTreeNode;
			else last->leftChild = newTreeNode;
			size++;
		}
		balance(root);
	}

	void erase(int theKey)
	{
		binaryTreeNode *temp = root, *parent = root,*pos=nullptr;//temp是原树指针的拷贝，temp=...时对原树无影响，temp->...才对原树产生影响
		bool leftflag = true;
		while (temp != nullptr)
		{
			if (temp->element.first > theKey) { parent = temp; temp = temp->leftChild; leftflag = true; }
			else if (temp->element.first < theKey) { parent = temp; temp = temp->rightChild; leftflag = false; }
			else break;
		}
		pos = temp;//pos记录thekey的位置
		if (temp != nullptr)
		{
			size--;
			if (temp->leftChild == nullptr&&temp->rightChild == nullptr)//删除点无左右树时，直接删除此节点
			{
				if (leftflag)   parent->leftChild = nullptr;
				else parent->rightChild = nullptr;
			}
			else if (temp->leftChild == nullptr || temp->rightChild == nullptr)//有左树或右树时，将其左或右树移到此节点
			{
				if (leftflag)   parent->leftChild = (temp->leftChild == nullptr ? temp->rightChild : temp->leftChild);
				else  parent->rightChild = (temp->leftChild == nullptr ? temp->rightChild : temp->leftChild);
			}
			else//左右树都有时，将其左树中最大值移到此节点，然后删除其左树中最大值节点			                                                                                          
			{
				parent = temp;//parent成了要删除的点
				temp = temp->leftChild;//temp成为parent的左树中最大值
				leftflag = true;
				while (temp->rightChild != nullptr)
				{
					leftflag = false;
					parent = temp;
					temp = temp->rightChild;
				}
                pos->element = temp->element;//pos始终保存要删除的点
				if (temp->leftChild != nullptr)     //1.最大值节点处只有左树，将左树移至最大节点处
				{
					if (leftflag) parent->leftChild = temp->leftChild;//leftflag为true，说明temp是parent的左树，即没有进行while循环，temp就是pos的左子树
					else parent->rightChild = temp->leftChild;//有进行while循环
				}
				else   //2.最大值节点处无左右树，置空
				{
					if (leftflag) parent->leftChild = nullptr;//leftflag为true，说明temp是parent的左树，即没有进行while循环，temp就是pos的左子树
					else parent->rightChild =nullptr;//有进行while循环
				}
			}
			balance(root);
		}
		else
		{
			cout << "无此数" << endl;
		}
	}

	binaryTreeNode*  find(int theKey)
	{
		binaryTreeNode *temp = root;
		while (temp != nullptr)
		{
			if (temp->element.first > theKey)  temp = temp->leftChild;
			else if(temp->element.first < theKey)  temp = temp->rightChild;
			else break;
		}
		if (temp != nullptr)
		{
			cout << "first:" << temp->element.first << " second: " << temp->element.second << endl;
			return temp;
		}			
		else
		{
			cout << "查无此数" << endl;
			return nullptr;
		}
	}

	void findByIndex(int theindex)//从小到大顺序排索引，索引二叉搜索树
	{
		theindex--;
		binaryTreeNode *temp = root;
		int index = numOfleftChinld(temp);
		while (index != theindex)
		{
			if (index > theindex)
			{
				temp = temp->leftChild;
				index = numOfleftChinld(temp);
			}
			else if (index < theindex)//进入右树时，theindex要减去父树index和父树本身占用1个
			{
				temp = temp->rightChild;
				theindex = theindex - index - 1;
				index = numOfleftChinld(temp);
			}
			else if (temp == nullptr) break;
		}
		if (temp != nullptr)
			cout << "first:" << temp->element.first << " second:" << temp->element.second<< endl;
	}

	int getsize()
	{
		return size;
	}

	int height(binaryTreeNode* node)//递归求高度
	{
		if (node != nullptr)
			return max(height(node->leftChild), height(node->rightChild)) + 1;
		else
			return 0;
	}

private:
	binaryTreeNode *root;
	int size;

	int numOfleftChinld(binaryTreeNode* node)//索引值=左节点个数
	{
		queue<binaryTreeNode*> q;
		int num = 0;
		if (node->leftChild != nullptr)
		{
			num++;
			q.push(node->leftChild);
		}
		while (!q.empty())
		{
			binaryTreeNode *temp = q.front();
			q.pop();
			if (temp->leftChild != nullptr) { q.push(temp->leftChild); num++; }
			if (temp->rightChild != nullptr){ q.push(temp->rightChild); num++; }
		}
		return num;
	}

	int dif(binaryTreeNode*node)
	{
		if (node!=nullptr)
		return height(node->leftChild) - height(node->rightChild);
	}

	void balance(binaryTreeNode* node)
	{
		bool flage = false;
		bool left = true;
		binaryTreeNode *parent = root;
		binaryTreeNode *x = root;
		binaryTreeNode *temp = root;
		while (dif(temp) == 2 || dif(temp) == -2)
		{
			flage = true;
			x = temp;
			if (abs(dif(temp->leftChild ))== 2 || abs(dif(temp->rightChild)) == 2)
			parent = temp;
			if (dif(temp) == 2) 
			{
				left = true;
				temp = temp->leftChild;
			}
			else
			{
				left = false;
				temp = temp->rightChild;
			}
		}
		if (flage)
		{
			if (left)
			{
				if (dif(temp) > 0)   LLrotation(parent,x);//插入节点在x节点的左子树的左节点，此处分两种
				                                                                    //1.插入节点就成为左子树的左节点
				                                                                        //2.插入节点是左子树的左节点的左或右节点
				else  LRrotation(parent, x);
			}
			else
			{
				if (dif(temp) > 0) RLrotation(parent, x);
		        else RRrotation(parent, x);
			}		
		}
	}

	//x移为其左节点的右节点，左节点占x的位置，原右节点移为x的左节点
	void LLrotation(binaryTreeNode *parent,binaryTreeNode *x)//x是平衡值等于2且最深的节点，parent是x的父节点
	{
		bool leftflag = false;
		if (x == root)  root = x->leftChild;
		else
		{
			//abs(dif(parent->leftChild)) == 2 || dif(parent->leftChild)>0
			if (x == parent->leftChild) { leftflag = true; }
			if (leftflag)     parent->leftChild = x->leftChild;
			else                 parent->rightChild = x->leftChild;

		}
			binaryTreeNode* temp=x->leftChild->rightChild;
			x->leftChild->rightChild = x;
			x->leftChild = temp;
	  }

	//x移为其右节点的左节点，右节点占x的位置，原左节点移为x的右节点
void RRrotation(binaryTreeNode *parent, binaryTreeNode *x)
{
	bool rightflag = false;
	if (x == root)  root = x->rightChild;
	else
	{//abs(dif(parent->leftChild)) == 2 || dif(parent->leftChild)<0
		//if (x==parent->leftChild) x = parent->leftChild;//前面满足单一RR，后面满足LR中先RR
		if (x == parent->rightChild)rightflag = true;
		if (rightflag)     parent->rightChild = x->rightChild;
		else parent->leftChild = x->rightChild;
	}
	binaryTreeNode* temp = x->rightChild->leftChild;
	x->rightChild->leftChild = x;
	x->rightChild = temp;
}

//x的左节点先进行右右，然后x节点进行左左
void LRrotation(binaryTreeNode *parent, binaryTreeNode *x)
{
	RRrotation(x, x->leftChild);
	LLrotation(parent, x);
}

//x的右节点先进行左左，然后x节点进行右右
void RLrotation(binaryTreeNode *parent, binaryTreeNode *x)
{
	LLrotation(x, x->rightChild);
	RRrotation(parent, x);
}

};

ostream& operator<<(ostream &os,binarySearchTree bst)//中序遍历
{
	binaryTreeNode *temp = bst.root;
	stack<binaryTreeNode*> s;
	while (temp != nullptr)
	{
		s.push(temp);
		temp = temp->leftChild;
	}
	while (!s.empty())
	{
		//if (s.top()->rightChild == nullptr)
		//{
		//	os << "first:" << s.top()->element.first << " second: " << s.top()->element.second << endl;
		//	s.pop();
		//}
		//else
		//{
			temp = s.top()->rightChild;
			os << "first:" << s.top()->element.first << " second: " << s.top()->element.second << endl;//读根节点，然后遍历右节点
			s.pop();
			while (temp != nullptr)
			{
				s.push(temp);
				temp = temp->leftChild;
			}
	//	}
	}
	cout << "size:" << bst.size << endl;
	return os;
}

#endif