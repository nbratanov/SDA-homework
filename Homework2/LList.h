#pragma once

template <typename T>
struct elem_link
{
	T inf;
	elem_link<T>* link;
};

template <typename T>
class LList
{
private:
	elem_link<T>* start, *current, *end;

	void DeleteList();
	void CopyList(LList<T> const &);

public:
	LList();
	LList(LList const &);
	LList& operator= (LList const &);
	~LList();

	void IterStart(elem_link<T> *p = NULL);
	elem_link<T>* Iter();
	void ToEnd(T const &);
	void InsertAfter(elem_link<T>*, T const &);
	void InsertBefore(elem_link<T>*, T const &);
	bool DeleteAfter(elem_link<T>*, T &);
	bool DeleteBefore(elem_link<T>*, T &);
	void DeleteElem(elem_link<T>*, T &);
	void print();
	int length();
	void concat(LList<T> const& list);
	elem_link<T>* RemoveDuplicates(elem_link<T>* head);
	elem_link<T>* MergeLists(elem_link<T>* headA, elem_link<T>* headB);
};

template <typename T>
LList<T>::LList() :start(NULL), end(NULL) {}

template <typename T>
LList<T>::LList(LList const &rs)
{
	CopyList(rs);
}

template <typename T>
LList<T>& LList<T>::operator=(LList const &rs)
{
	if (this != &rs)
	{
		DeleteList();
		CopyList(rs);
	}
	return *this;
}

template <typename T>
LList<T>::~LList()
{
	DeleteList();
}

template <typename T>
void LList<T>::DeleteList()
{
	elem_link<T>* p;
	while (start)
	{
		p = start;
		start = start->link;
		delete p;
	}
	end = NULL;
}

template <typename T>
void LList<T>::CopyList(LList<T> const &rs)
{
	start = end = NULL;
	if (rs.start) 
	{
		elem_link<T> *p = rs.start;
		while (p)
		{
			ToEnd(p->inf);
			p = p->link;
		}
	}
}

template <typename T>
void LList<T>::IterStart(elem_link<T>* p)
{
	if (p)
		current = p;
	else
		current = start;
}

template <typename T>
elem_link<T>* LList<T>::Iter()
{
	elem_link<T>* p = current;
	if (current)
		current = current->link;
	return p;
}

template <typename T>
void LList<T>::ToEnd(T const& x)
{
	current = end;
	end = new elem_link<T>;
	end->inf = x;
	end->link = NULL;
	if (current)
		current->link = end;
	else
		start = end;
}

template <typename T>
void LList<T>::InsertAfter(elem_link<T>* p, T const& x)
{
	elem_link<T>* q = new elem_link<T>;
	q->inf = x;
	q->link = p->link;
	if (p == end)
		end = q;
	p->link = q;
}

template <typename T>
void LList<T>::InsertBefore(elem_link<T>* p, T const& x)
{
	elem_link<T>* q = new node<T>;
	*q = *p;
	if (p == end)
		q = end;
	p->inf = x;
	p->link = q;
}

template <typename T>
bool LList<T>::DeleteAfter(elem_link<T>* p, T & x)
{
	if (p->link)
	{
		elem_link<T>* q = p->link;
		x = q->inf;
		p->link = q->link;
		if (q == end)
			end = p;
		delete q;
		return 1;
	}
	return 0;
}

template <typename T>
void LList<T>::DeleteElem(elem_link<T>* p, T & x)
{
	if (p == start)
	{
		x = p->inf;
		if (start == end)
			start == end == NULL;
		else
			start = start->link;
		delete p;
	}
	else 
	{
		elem_link<T>* q = start;
		while (q->link != p)
			q = q->link;
		DeleteAfter(q, x);
	}
}

template <typename T>
bool LList<T>::DeleteBefore(elem_link<T>* p, T & x)
{
	if (p != start)
	{
		elem_link<T>* q = start;
		while (q->link != p)
			q = q->link;
		DeleteElem(q, x);
		return 1;
	}
	return 0;
}

template <typename T>
void LList<T>::print()
{
	elem_link<T>* p = start;
	while (p)
	{
		cout << p->inf << " ";
		p = p->link;
	}
	cout << endl;
}

template <typename T>
int LList<T>::length()
{
	elem_link<T>* p = start;
	int l = 0;
	while (p)
	{
		l++;
		p = p->link;
	}
	return l;
}

template <typename T>
void LList<T>::concat(LList<T> const & list)
{
	elem_link<T>* p = list.start;
	while (p)
	{
		ToEnd(p->inf);
		p = p->link;
	}
}

template <typename T>
elem_link<T>* LList<T>::RemoveDuplicates(elem_link<T>* head)
{
	T x;
	elem_link<T>* p = head;
	while (p->link)
	{
		if (p->inf == p->link->inf)
		{
			x = p->inf;
			p = p->link;
			DeleteBefore(p, x);
		}else
			p = p->link;
	}
	return head;
}

template <typename T>
elem_link<T>* LList<T>::MergeLists(elem_link<T>* headA, elem_link<T>* headB)
{
	elem_link<T>* newList = start;

	while (1)
	{
		if (headA == NULL)
		{
			while (headB) {
				ToEnd(headB->inf);
				headB = headB->link;
			}
			break;
		}
		if (headB == NULL)
		{
			while (headA) {
				ToEnd(headA->inf);
				headA = headA->link;
			}
			break;
		}
		
		if (headA->inf <= headB->inf)
		{
			ToEnd(headA->inf);
			headA = headA->link;
		}
		else
		{
			ToEnd(headB->inf);
			headB = headB->link;
		}
	}
	return newList;
}
