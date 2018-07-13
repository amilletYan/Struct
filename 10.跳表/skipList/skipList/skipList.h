#include <utility>
#include <math.h>
#include  <iostream>
using namespace std;
struct skipNode
{
	pair<int,int> element;
	skipNode **next;
	skipNode(pair<int, int> thePair, int size) :element(thePair){ next = new skipNode *[size]; }
	
};

class skipList
{
public:
	skipList(int largekey, int maxpair = 10000, float prob = 0.5)
	{
		maxlevel = ceil(logf(maxpair) / logf(1 / prob)) - 1;
		cutoff = prob*RAND_MAX;
		pair<int, int> headerPair,tailPair;
		headerPair.first = largekey;
		tailPair = headerPair;
		headerNode = new skipNode(headerPair,maxlevel+1);
		tailNode = new skipNode(tailPair, 0);
		last = new skipNode *[maxlevel + 1];
		levels = 0;
		for (int i = 0; i <= maxlevel; i++) headerNode->next[i] = tailNode;
	}

	~skipList()
	{
		skipNode *next;
		while (headerNode!=tailNode)
		{
			next = headerNode->next[0];
			delete headerNode;
			headerNode = next;
		}
		delete tailNode;
		delete[]last;
	}

	pair<int, int>* find(int thekey)
	{
		if (thekey > headerNode->element.first)
			throw  exception("keyÌ«´ó");
		skipNode *beforeNode = headerNode;
		for (int i = maxlevel; i >= 0; i--)
			while (beforeNode->next[i]->element.first< thekey)
				beforeNode = beforeNode->next[i];
		if (beforeNode->next[0]->element.first == thekey)
			return &beforeNode->next[0]->element;
		return nullptr;
	}

	int level()
	{
		int lev = 0;
		while (rand() < cutoff)
			lev++;
		return lev > maxlevel ? maxlevel : lev;
	}

	skipNode* search(int thekey)
	{
		skipNode *beforenode=headerNode;
		for (int i = maxlevel; i >= 0; i--)
		{
			while (beforenode->next[i]->element.first <thekey)
				beforenode = beforenode->next[i];
			last[i] = beforenode;
		}
		return beforenode;
	}

	void insert(pair<int, int> thepair)
	{
		skipNode *thenode = search(thepair.first);
		if (thenode->next[0]->element.first == thepair.first)
		{
			thenode->element.second = thepair.second;
		}
		int thelevel = level();
		if (thelevel > levels)
		{
			thelevel = ++levels;
			last[thelevel] = headerNode;
		}
		skipNode *newnode = new skipNode(thepair,thelevel+1);
		for (int i = 0; i <= thelevel; i++)
		{
			newnode = last[i]->next[i];
			last[i]->next[i] = newnode;
		}
		size++;
	}

	void erase(int thekey)
	{
		skipNode *node = search(thekey);
		if (node->next[0]->element.first != thekey)
			return;
		for (int i = 0; i <= levels&&last[i]->next[i] == node; i++)
			last[i]->next[i] = node->next[i];
		size--;
		while (levels > 0 && headerNode->next[levels] == tailNode)
			levels--;
		delete node;
	}

	void output()
	{
		skipNode* current = headerNode;
		for (int i = 0; i < size; i++)
		{
			cout << "first:" << current->element.first << " second:" << current->element.second << endl;
			current = current->next[0];
		}
	}
private:
	int  size;
	int levels;
	int maxlevel;
	skipNode *headerNode;
	skipNode *tailNode;
	int cutoff;
	skipNode **last;
};