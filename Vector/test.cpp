#include <iostream>
#include "Vector.h"
using namespace std;

template <typename T>
void PrintVector(Vector<T>& v)
{
	Vector<T>::Iterator it = v.Begin();
	while (it != v.End())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

int main()
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	v.PushBack(5);
	PrintVector(v);
	cout << v[3] << endl;
	cout << v.Front() << endl;
	cout << v.Back() << endl;
	Vector<int> v1 = v;
	PrintVector(v1);
	v.PopBack();
	PrintVector(v);
	v.Insert(v.Begin() + 1, 6);
	PrintVector(v);
	v.Erase(v.End()-1);
	PrintVector(v);
	system("pause");
	return 0;
}