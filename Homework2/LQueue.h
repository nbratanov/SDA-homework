#pragma once

template <typename T>
struct node
{
	T data;
	node<T>* next;
};

template <typename T>
class LQueue
{
private:
	node<T> *front, *back;
	
	void clean();
	void copy(LQueue<T> const&);

public:
	LQueue();
	LQueue(LQueue const&);
	LQueue<T>& operator= (LQueue const&);
	~LQueue();

	bool empty() const;
	void push(T const&);
	T pop();
	T head() const;
	void print() const;
};

template <typename T>
LQueue<T>::LQueue() :front(NULL), back(NULL) {}

template <typename T>
LQueue<T>::LQueue(LQueue const& rs)
{
	copy(rs);
}

template <typename T>
LQueue<T>& LQueue<T>::operator=(LQueue const& rs)
{
	if (this != &rs)
	{
		clean();
		copy(rs);
	}
	return *this;
}

template <typename T>
LQueue<T>::~LQueue()
{
	clean();
}

template <typename T>
void LQueue<T>::clean()
{
	while (empty())
		pop();
}

template <typename T>
void LQueue<T>::copy(LQueue<T> const& rs)
{
	back = NULL;
	if (!rs.empty())
	{
		node<T>* p = rs.front;
		while (p)
		{
			push(p->data);
			p = p->next;
		}
	}
}

template <typename T>
bool LQueue<T>::empty() const
{
	return back == NULL;
}

template <typename T>
void LQueue<T>::push(T const& x)
{
	node<T>* p = new node<T>;
	p->data = x;
	p->next = NULL;
	if (!empty())
		back->next = p;
	else
		front = p;
	back = p;
}

template <typename T>
T LQueue<T>::pop()
{
	if (empty())
	{
		std::cerr << "Queue is emptyyyyy" << std::endl;
		return T();
	}
	node<T>* q = front;
	T x = q->data;
	if (q == back)
	{
		front = NULL;
		back = NULL;
	}else
		front = q->next;
	delete q;
	return x;
}

template <typename T>
T LQueue<T>::head() const
{
	if (empty())
	{
		std::cerr << "Queue is emppppty" << std::endl;
		return T();
	}
	return front->data;
}

template <typename T>
void LQueue<T>::print() const
{
	node<T>* p = front;
	while (p)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}