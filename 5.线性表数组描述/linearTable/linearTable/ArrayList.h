#ifndef linearArray_
#define linearArray_
#include "linearList.h"
#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include"myException.h"
#include "changeLength1D.h"
template<class T>
class ArrayList : public linearList<T>
{
public:
	ArrayList(int initial = 10) ;
	ArrayList(const ArrayList<T>&);
	~ArrayList(){ delete[] elements; }
	ArrayList(initializer_list<T> ini);

	T& get(int num) const;
	int indexOf(const T& element) const;
	bool insert(int num, const T& element) ;
	bool erase(int num) ;
	void output(ostream &out) const;


	bool empty() const{ return size == 0; }
	int getsize() const{ return size; }
protected:
	void checkIndex(int index)const;
	T* elements;
	int length;
	int size;
};
template<class T>
ArrayList<T>::ArrayList(initializer_list<T> ini)
{
	size=length = ini.size();
	elements = new T[size];
	int i = 0;
	for (auto a:ini)
	{
		elements[i] = a;
			i++;
	}
}

template<class T>
ArrayList<T>::ArrayList(int initial)
{
	if (initial < 1)
	{
		ostringstream os;
		os << "initial size " << initial << "<0" << endl;
		throw illegalParameterValue(os.str());
	}
	length = initial;
	elements = new T[initial];
	size = 0;
}

template<class T>
ArrayList<T>::ArrayList(const ArrayList<T>& l)
{
	length = l.length;
	size = l.size;
	elements = new T[length];
	for (int i = 0; i < size; i++)
	{
		elements[i] = l.elements[i];
	}
}

template<class T>
void ArrayList<T>::checkIndex(int index) const
{
	if (index < 0 || index >size)
	{
		ostringstream os;
		os << "index=" << index << " is illegal" << endl;
		throw illegalParameterValue(os.str());
	}
}

template<class T>
T& ArrayList<T>::get(int num) const
{
	checkIndex(num);
	return elements[num-1];
}

template<class T>
int ArrayList<T>::indexOf(const T& element) const
{
	int index = find(elements,elements+size,element)-elements;
	if (index== size)
		return -1;
	else
		return index+1;
}

template<class T>
bool ArrayList<T>::erase(int num) 
{
	checkIndex(num);
	copy(elements + num, elements + size, elements + num - 1);
	elements[--size].~T();
	return true;
}

template<class T>
bool ArrayList<T>::insert(int num, const T& element) 
{
	if (size == length)
	{
		changelength1D(elements, length, 2 * length);
		length = 2 * length;
	}
		
	for (int i = size; i > num-1; i--)
	{
		elements[i] = elements[i - 1];

	}
	elements[num - 1] = element;
	size++;
	return true;
}

template<class T>
void ArrayList<T>::output(ostream &out) const
{
	for (int i = 0; i < size; i++)
	{

		out << elements[i] << endl;
	}

}
#endif