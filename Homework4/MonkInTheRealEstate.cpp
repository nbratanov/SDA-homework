#include <iostream>
#include "LList.h"
#include "IntGraph.h"
#include <queue>
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

bool member(int a, IntGraph& g)
{
	g.IterStart();
	elem_link<IntList> *q = g.Iter();
	while (q)
	{
		if (q->inf.getStart()->inf == a)
			return true;
		q = g.Iter();
	}
	return false;
}

bool member(int a, IntList &l)	
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

int numberOfCities(IntGraph &g)
{
	int cityCounter = 0;
	IntList visited;
	queue<int> q;

	q.push(g.getStart()->inf.getStart()->inf);

	while (!q.empty())
	{
		int n = q.front();
		q.pop();

		if (!member(n, visited)) {
			visited.ToEnd(n);
			cityCounter++;
		}

		elem_link<int> *nPtr = Point(n, g);
		while (nPtr)
		{
			if (!member(nPtr->inf, visited))
			{
				q.push(nPtr->inf);
			}
			nPtr = nPtr->link;
		}
	}
	return cityCounter;
}

int main()
{
	IntGraph g;

	int t;
	cin >> t;

	for (int i = 1; i <= t; i++)
	{
		int e, x, y;
		cin >> e;

		for (int i = 1; i <= e; i++)
		{
			cin >> x >> y;

			if (!member(x, g))
				AddTop(x, g);
			if (!member(y, g))
				AddTop(y, g);

			AddRib(x, y, g);
		}
		cout << numberOfCities(g) << endl;
	}

	return 0;
}