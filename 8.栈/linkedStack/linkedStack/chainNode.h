#ifndef   chainNode_
#define chainNode_
struct chainNode
{
	int element;
	chainNode* nextNode;
	chainNode() = default;
	chainNode(int i) :element(i){ nextNode = nullptr; }//这里nextnode一定要设为nullptr，不然会默认给他一个地址，它就不算空指针，析构会出错
	chainNode(int i, chainNode *nextn) :element(i), nextNode(nextn){}
};
#endif
