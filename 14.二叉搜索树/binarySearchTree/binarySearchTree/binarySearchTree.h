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
		binaryTreeNode *temp = root, *parent = root,*pos=nullptr;//temp��ԭ��ָ��Ŀ�����temp=...ʱ��ԭ����Ӱ�죬temp->...�Ŷ�ԭ������Ӱ��
		bool leftflag = true;
		while (temp != nullptr)
		{
			if (temp->element.first > theKey) { parent = temp; temp = temp->leftChild; leftflag = true; }
			else if (temp->element.first < theKey) { parent = temp; temp = temp->rightChild; leftflag = false; }
			else break;
		}
		pos = temp;//pos��¼thekey��λ��
		if (temp != nullptr)
		{
			size--;
			if (temp->leftChild == nullptr&&temp->rightChild == nullptr)//ɾ������������ʱ��ֱ��ɾ���˽ڵ�
			{
				if (leftflag)   parent->leftChild = nullptr;
				else parent->rightChild = nullptr;
			}
			else if (temp->leftChild == nullptr || temp->rightChild == nullptr)//������������ʱ��������������Ƶ��˽ڵ�
			{
				if (leftflag)   parent->leftChild = (temp->leftChild == nullptr ? temp->rightChild : temp->leftChild);
				else  parent->rightChild = (temp->leftChild == nullptr ? temp->rightChild : temp->leftChild);
			}
			else//����������ʱ���������������ֵ�Ƶ��˽ڵ㣬Ȼ��ɾ�������������ֵ�ڵ�			                                                                                          
			{
				parent = temp;//parent����Ҫɾ���ĵ�
				temp = temp->leftChild;//temp��Ϊparent�����������ֵ
				leftflag = true;
				while (temp->rightChild != nullptr)
				{
					leftflag = false;
					parent = temp;
					temp = temp->rightChild;
				}
                pos->element = temp->element;//posʼ�ձ���Ҫɾ���ĵ�
				if (temp->leftChild != nullptr)     //1.���ֵ�ڵ㴦ֻ���������������������ڵ㴦
				{
					if (leftflag) parent->leftChild = temp->leftChild;//leftflagΪtrue��˵��temp��parent����������û�н���whileѭ����temp����pos��������
					else parent->rightChild = temp->leftChild;//�н���whileѭ��
				}
				else   //2.���ֵ�ڵ㴦�����������ÿ�
				{
					if (leftflag) parent->leftChild = nullptr;//leftflagΪtrue��˵��temp��parent����������û�н���whileѭ����temp����pos��������
					else parent->rightChild =nullptr;//�н���whileѭ��
				}
			}
			balance(root);
		}
		else
		{
			cout << "�޴���" << endl;
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
			cout << "���޴���" << endl;
			return nullptr;
		}
	}

	void findByIndex(int theindex)//��С����˳������������������������
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
			else if (index < theindex)//��������ʱ��theindexҪ��ȥ����index�͸�������ռ��1��
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

	int height(binaryTreeNode* node)//�ݹ���߶�
	{
		if (node != nullptr)
			return max(height(node->leftChild), height(node->rightChild)) + 1;
		else
			return 0;
	}

private:
	binaryTreeNode *root;
	int size;

	int numOfleftChinld(binaryTreeNode* node)//����ֵ=��ڵ����
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
				if (dif(temp) > 0)   LLrotation(parent,x);//����ڵ���x�ڵ������������ڵ㣬�˴�������
				                                                                    //1.����ڵ�ͳ�Ϊ����������ڵ�
				                                                                        //2.����ڵ�������������ڵ������ҽڵ�
				else  LRrotation(parent, x);
			}
			else
			{
				if (dif(temp) > 0) RLrotation(parent, x);
		        else RRrotation(parent, x);
			}		
		}
	}

	//x��Ϊ����ڵ���ҽڵ㣬��ڵ�ռx��λ�ã�ԭ�ҽڵ���Ϊx����ڵ�
	void LLrotation(binaryTreeNode *parent,binaryTreeNode *x)//x��ƽ��ֵ����2������Ľڵ㣬parent��x�ĸ��ڵ�
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

	//x��Ϊ���ҽڵ����ڵ㣬�ҽڵ�ռx��λ�ã�ԭ��ڵ���Ϊx���ҽڵ�
void RRrotation(binaryTreeNode *parent, binaryTreeNode *x)
{
	bool rightflag = false;
	if (x == root)  root = x->rightChild;
	else
	{//abs(dif(parent->leftChild)) == 2 || dif(parent->leftChild)<0
		//if (x==parent->leftChild) x = parent->leftChild;//ǰ�����㵥һRR����������LR����RR
		if (x == parent->rightChild)rightflag = true;
		if (rightflag)     parent->rightChild = x->rightChild;
		else parent->leftChild = x->rightChild;
	}
	binaryTreeNode* temp = x->rightChild->leftChild;
	x->rightChild->leftChild = x;
	x->rightChild = temp;
}

//x����ڵ��Ƚ������ң�Ȼ��x�ڵ��������
void LRrotation(binaryTreeNode *parent, binaryTreeNode *x)
{
	RRrotation(x, x->leftChild);
	LLrotation(parent, x);
}

//x���ҽڵ��Ƚ�������Ȼ��x�ڵ��������
void RLrotation(binaryTreeNode *parent, binaryTreeNode *x)
{
	LLrotation(x, x->rightChild);
	RRrotation(parent, x);
}

};

ostream& operator<<(ostream &os,binarySearchTree bst)//�������
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
			os << "first:" << s.top()->element.first << " second: " << s.top()->element.second << endl;//�����ڵ㣬Ȼ������ҽڵ�
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