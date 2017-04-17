#include <iostream>
#include <vector>
#include "List.h"
using namespace std;

void PrintList(const List<int>& list)
{
	//const对象调用const成员函数，返回const迭代器
	List<int>::ConstIterator it = list.Begin();

	while (it != list.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void testList()
{
	List<int> l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushFront(3);
	l1.PushFront(4);
	PrintList(l1);

	l1.PopFront();
	l1.PopBack();
	PrintList(l1);

	vector<int> v;
	v.push_back(6);
	v.push_back(7);
	l1.Insert(l1.Begin(), v.begin(), v.end());
	PrintList(l1);

	char str[2] = { 'A', 'B' };
	l1.Insert(l1.End(), str, str+2);
	PrintList(l1);
}

int main()
{
	testList();
	return 0;
}