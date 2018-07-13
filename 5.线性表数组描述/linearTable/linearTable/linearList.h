#ifndef linearList_
#define linearList_

#include <iostream>
using namespace std;
template<class T> 
class linearList
{
public:
	virtual ~linearList(){};
	virtual bool empty() const = 0;
	virtual int getsize() const = 0;
	virtual T& get(int num) const = 0;
	virtual int indexOf(const T& element) const = 0;
	virtual bool insert(int num, const T& element)  = 0;
	virtual bool erase(int num)  = 0;
	virtual void output(ostream &os) const = 0;
	
};
#endif