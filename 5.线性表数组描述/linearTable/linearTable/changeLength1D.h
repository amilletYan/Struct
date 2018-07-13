using namespace std;
template<class T>
void changelength1D(T* a,int oldLength,int newLength)
{
	int num = oldLength > newLength ? newLength : oldLength;
	T* temp=new T[newLength];
	for (int i = 0; i < num;i++)
	{
		temp[i] = a[i];
	}
	delete[] a;
	a = temp;
}