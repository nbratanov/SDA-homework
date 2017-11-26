#include <iostream>
#include "LStack.h"

using namespace std;

template <typename T>
class QueueFromStack
{
private:
	LStack<T> stack1, stack2;

public:
	void enQueue(T const& x);
	T dnQueue();
	T topPrint() const;
};

template <typename T>
void QueueFromStack<T>::enQueue(T const& x) 
{
	while (!stack1.empty())
	{
		stack2.push(stack1.pop());
	}
	stack1.push(x);
	while (!stack2.empty())
	{
		stack1.push(stack2.pop());
	}
}

template <typename T>
T QueueFromStack<T>::dnQueue()
{
	if (stack1.empty())
	{
		cerr << "Stack is empty" << endl;
		return 0;
	}
	return stack1.pop();
}

template <typename T>
T QueueFromStack<T>::topPrint() const
{
	return stack1.top();
}


int main()
{
	QueueFromStack<int> a;

	long long queries;
	cin >> queries;

	int query, toPush, b[100000], counter = 0;
	

	for (int i = 0; i < queries; i++)
	{
		cin >> query;
		switch (query)
		{
		case 1:
			cin >> toPush;
			a.enQueue(toPush);
			break;
		case 2:
			a.dnQueue();
			break;
		case 3:
			b[counter++] = a.topPrint();
			break;
		default:
			cout << "Invalid query" << endl;
		}
	}

	for (int i = 0; i < counter; i++)
	{
		cout << b[i] << endl;
	}

	system("pause");
	return 0;
}