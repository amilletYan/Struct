// skipList.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "skipList.h"

int _tmain(int argc, _TCHAR* argv[])
{

	//cout<<ceil(logf(100) / logf(1 / 0.5)) - 1;
	skipList sl(100);
	sl.insert(pair<int, int>(1,1));
	sl.insert(pair<int, int>(3, 3));
	sl.insert(pair<int, int>(4, 4));
	/*sl.insert(pair<int, int>(7, 7));
	sl.insert(pair<int, int>(5, 5));
	sl.insert(pair<int, int>(2, 2));
	sl.insert(pair<int, int>(40, 40));
	sl.insert(pair<int, int>(24, 24));
	sl.insert(pair<int, int>(16, 16));
	sl.insert(pair<int, int>(67, 67));
	sl.insert(pair<int, int>(32, 32));
	sl.insert(pair<int, int>(0, 0));*/
	sl.output();
	system("pause");
	return 0;
}

