#include <iostream>
#include "LList.h"
using namespace std;

int main()
{
	LList<int> list, list2, sortedList;
	list.ToEnd(1);
	list.ToEnd(3);
	list.ToEnd(5);
	
	list2.ToEnd(2);
	list2.ToEnd(2);
	list2.ToEnd(7);
	list2.ToEnd(7);

	list.print();
	list2.print();

	list.IterStart();
	elem_link<int>* q = list.Iter();
	list2.IterStart();
	elem_link<int>* t = list2.Iter();
	
	sortedList.MergeLists(q, t);
	sortedList.print();
	sortedList.IterStart();
	elem_link<int>* s = sortedList.Iter();
	sortedList.RemoveDuplicates(s);
	sortedList.print();
	

	return 0;
}