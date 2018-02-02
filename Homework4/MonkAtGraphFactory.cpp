#include <iostream>
#include "llist.h"
#include <queue>
#include <stack>
#include <fstream>
using namespace std;

typedef LList<int> IntList;
typedef LList<IntList> IntGraph;

elem_link<int>* Point(int a, IntGraph &g)
{
	g.IterStart();
	elem_link<IntList> *p;
	elem_link<int> *q;

	do
	{
		p = g.Iter();
		p->inf.IterStart();
		q = p->inf.Iter();
	} while (q->inf != a);
	return q;
}

void AddTop(int a, IntGraph &g)
{
	IntList l;
	l.ToEnd(a);
	g.ToEnd(l);
}

void AddRib(int a, int b, IntGraph &g)
{
	elem_link<int> *q = Point(a, g), *p;
	while (q->link)
		q = q->link;

	p = new elem_link<int>;
	p->inf = b;
	p->link = NULL;
	q->link = p;
}

void create_graph(IntGraph &g)
{
	char c;
	do
	{
		cout << "Top of graph: ";
		int x;
		cin >> x;
		AddTop(x, g);
		cout << "Top y/n? ";
		cin >> c;
	} while (c == 'y');

	cout << "Ribs:\n";

	do
	{
		cout << "start top: ";
		int x; cin >> x;
		cout << "end top: ";
		int y; cin >> y;
		AddRib(x, y, g);
		cout << "next: y/n ";
		cin >> c;
	} while (c == 'y');
}

void LList<IntList>::print()
{
	elem_link<IntList>* p = start;
	while (p)
	{
		p->inf.print();
		p = p->link;
	}
	cout << endl;
}

bool member(int a, IntList &l)			//check if member in list
{
	l.IterStart();
	elem_link<int> *p = l.Iter();

	while (p)
	{
		if (a == p->inf)
			return true;
		p = l.Iter();
	}
	return false;
}

bool isConnected(IntGraph &g)
{
	queue<int> q;
	IntList visited;

	q.push(g.getStart()->inf.getStart()->inf);

	while (!q.empty())
	{
		int n = q.front();
		q.pop();

		if (!visited.hasElement(n))
			visited.ToEnd(n);

		elem_link<int> *nPtr = Point(n, g);
		while (nPtr)
		{
			if (!visited.hasElement(nPtr->inf))
				q.push(nPtr->inf);
			nPtr = nPtr->link;
		}
	}

	g.IterStart();
	elem_link<IntList> *p = g.Iter();
	p->inf.IterStart();
	elem_link<int> *vertex = p->inf.Iter();
	while (p)
	{
		if (!member(vertex->inf, visited))
			return false;
		if (p = g.Iter()) {
			p->inf.IterStart();
			vertex = p->inf.Iter();
		}
	}
	return true;
}

bool member(int x, stack<int> stack)			//check if member in stack
{
	while (!stack.empty())
	{
		int y = stack.top();
		if (x == stack.top())
			return true;
		stack.pop();
	}
	return false;
}

bool flag = false;

bool isCyclicUtil(IntGraph &g, int start, stack<int> &visited)
{
	elem_link<int>* p = Point(start, g);

	visited.push(p->inf);

	while (p)
	{
		if (!member(p->inf, visited))
			isCyclicUtil(g, p->inf, visited);
		else if (member(p->inf, visited) && p->inf != visited.top())
			flag = true;
		p = p->link;
	}
	visited.pop();
	if (flag)
		return true;
	return false;
}

bool isCyclic(IntGraph &g)
{
	stack<int> visited;
	int start = g.getStart()->inf.getStart()->inf;

	return isCyclicUtil(g, start, visited);
}

bool isTree(IntGraph &g)
{
	if (isConnected(g))
	{
		if (!isCyclic(g))
			return true;
		else
			return false;
	}
	return false;
}

int main()
{
	IntGraph g;
	int a, b;
	ifstream iFileName;
	iFileName.open("C:/Users/nikol/Desktop/file.txt", ios::in);

	while (!iFileName.eof()) {
		iFileName >> a;
		iFileName >> b;

		if (!member(a, g))
			AddTop(a, g);
		if (!member(b, g))
			AddTop(b, g);

		AddRib(a, b, g);
	}

	cout << isTree(g) << endl;

	return 0;
}
