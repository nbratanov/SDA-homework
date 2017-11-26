#pragma once

template <typename T>
struct elem_link2
{
	T inf;
	elem_link2<T> *next;
	elem_link2<T> *prev;
};

template <typename T>
class DList
{
private:
	elem_link2<T> *start;
	elem_link2<T> *end;
	elem_link2<T> *currentS;
	elem_link2<T> *currentE;

	void DeleteList();
	void CopyList(DList<T> const &);

public:
	DList();
	DList(DList<T> const &);
	DList<T>& operator= (DList<T> const &);
	~DList();

	void IterStart(elem_link2<T> *p = NULL);
	void IterEnd(elem_link2<T> *p = NULL);
	
	elem_link2<T>* IterNext();
	elem_link2<T>* IterPrev();

	void ToEnd(T const &);
	void DeleteElem(elem_link2<T> *, T &);
	void print();
	void print_reverse();
	int length();

	elem_link2<T>* Reverse(elem_link2<T>*);
};

template <typename T>
DList<T>::DList() : start(NULL), end(NULL) {}

template <typename T>
DList<T>::DList(DList<T> const &rs)
{
	CopyList(rs);
}

template <typename T>
DList<T>& DList<T>::operator= (DList<T> const &rs)
{
	if (this != &rs)
	{
		DeleteList();
		CopyList(rs);
	}
	return *this;
}

template <typename T>
DList<T>::~DList()
{
	DeleteList();
}

template <typename T>
void DList<T>::DeleteList()
{
	elem_link2<T>* p;
	while (start)
	{
		p = start;
		start = start->next;
		delete p;
	}
	start = end = NULL;
}

template <typename T>
void DList<T>::CopyList(DList<T> const &rs)
{
	start = end = NULL;
	if (rs.start) {
		elem_link2<T> *p = rs.start;
		while (p)
		{
			ToEnd(p->inf);
			p = p->next;
		}
	}
}

template <typename T>
void DList<T>::IterStart(elem_link2<T> *p)
{
	if (p)
		currentS = p;
	else
		currentS = start;
}

template <typename T>
void DList<T>::IterEnd(elem_link2<T> *p)
{
	if (p)
		currentE = p;
	else
		currentE = end;
}

template <typename T>
elem_link2<T>* DList<T>::IterNext()
{
	elem_link2<T> *p = currentS;
	if (currentS)
		currentS = currentS->next;
	
	return p;
}

template <typename T>
elem_link2<T>* DList<T>::IterPrev()
{
	elem_link2<T> *p = currentE;
	if (currentE)
		currentE = currentE->prev;

	return p;
}

template <typename T>
void DList<T>::ToEnd(T const &x)
{
	elem_link2<T> *p = end;
	end = new elem_link2<T>;
	end->inf = x;
	end->next = NULL;

	if (p)
		p->next = end;
	else
		start = end;

	end->prev = p;
}

template <typename T>
void DList<T>::DeleteElem(elem_link2<T> *p, T & x)
{
	x = p->inf;
	if (start == end)
	{
		start = NULL;
		end == NULL;
	}
	else if (p == start)
	{
		start = start->next;
		start->prev = NULL;
	}
	else if (p == end)
	{
		end = end->prev;
		end->next = NULL;
	}
	else
	{
		p->next->prev = p->prev;
		p->prev->next = p->next;
	}
	delete p;
}

template <typename T>
void DList<T>::print()
{
	elem_link2<T> *p = start;
	while (p)
	{
		cout << p->inf << " ";
		p = p->next;
	}
	cout << endl;
}

template <typename T>
void DList<T>::print_reverse()
{
	elem_link2<T> *p = end;
	while (p)
	{
		cout << p->inf << " ";
		p = p->prev;
	}
	cout << endl;
}

template <typename T>
int DList<T>::length()
{
	int n = 0;
	elem_link2<T> *p = start;
	while (p)
	{
		n++;
		p = p->next;
	}
	return n;
}

template <typename T>
elem_link2<T>* DList<T>::Reverse(elem_link2<T>* head)
{
	elem_link2<T> *tmp;
	elem_link2<T> *p = head;
	elem_link2<T>* newHead = head;

	while (p)
	{
		tmp = p->prev;
		p->prev = p->next;
		p->next = tmp;
		newHead = p;
		p = p->prev;
	}
	return newHead;
}