#ifndef   chainNode_
#define chainNode_
struct chainNode
{
	int element;
	chainNode* nextNode;
	chainNode() = default;
	chainNode(int i) :element(i){ nextNode = nullptr; }//����nextnodeһ��Ҫ��Ϊnullptr����Ȼ��Ĭ�ϸ���һ����ַ�����Ͳ����ָ�룬���������
	chainNode(int i, chainNode *nextn) :element(i), nextNode(nextn){}
};
#endif
