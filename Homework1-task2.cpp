#include <iostream>
using namespace std;

template <typename T>
struct node
{
	T data;
	node<T>* next;
};

template <typename T>
class LStack
{
private:
	node<T>* topNode;

	void copy(node<T>* const&);
	void copyStack(LStack const&);
	void eraseStack();
public:
	LStack();
	LStack(LStack const&);
	LStack& operator= (LStack const&);
	~LStack();

	bool empty() const;
	void push(T const&);
	T pop();
	T top();
	void print() const;
	T maxElement();
};

int main()
{
	/*                      MAXIMUM ELEMENT EXCERCISE
	LStack<int> stack;
	int queries;
	cin >> queries;

	int query, toPush, b[100000], counter = 0;

	for (int i = 0; i < queries; i++)
	{
		cin >> query;
		switch (query)
		{
		case 1:
			cin >> toPush;
			stack.push(toPush);
			break;
		case 2:
			stack.pop();
			break;
		case 3:
			b[counter++] = stack.maxElement();
			break;
		default:
			cout << "Invalid query" << endl;
			break;
		}
	}

	for (int i = 0; i < counter; i++)
	{
		cout << b[i] << endl;
	}*/
	int games;							// GAME OF TWO STACKS
	cin >> games;
	for (int k = 0; k < games; k++)
	{
		int n, m, x;
		cin >> n >> m >> x;


		LStack<int> stack1, stack2;
		int arr1[100000], arr2[100000];
		int a;
		for (int i = n - 1; i >= 0; i--)
		{
			cin >> a;
			arr1[i] = a;
		}

		int b;
		for (int i = m - 1; i >= 0; i--)
		{
			cin >> b;
			arr2[i] = b;
		}


		for (int i = 0; i < n; i++)
		{
			stack1.push(arr1[i]);
		}

		for (int i = 0; i < m; i++)
		{
			stack2.push(arr2[i]);
		}

		int sum = 0, counter = 0;
		for (int i = 0; i < n + m; i++)
		{
			if (stack1.top() <= stack2.top())
			{
				sum += stack1.pop();
				if (sum > x)
					break;
					counter++;
			}
			else
			{
				sum += stack2.pop();
				if (sum > x)
					break;
					counter++;
			}
		}
		cout << counter << endl;
	}

	system("pause");
	return 0;
}

template<typename T>
void LStack<T>::copy(node<T>* const & toCopy)
{
	if (toCopy == nullptr)
		return;
	copy(toCopy->next);
	push(toCopy->data);
}

template<typename T>
void LStack<T>::copyStack(LStack const & ls)
{
	topNode == nullptr;
	copy(ls.topNode);
}

template<typename T>
void LStack<T>::eraseStack()
{
	while (!empty())
		pop();
}

template<typename T>
LStack<T>::LStack() : topNode(nullptr) {}

template<typename T>
LStack<T>::LStack(LStack const & ls)
{
	copyStack(ls);
}

template<typename T>
LStack<T>& LStack<T>::operator=(LStack const & ls)
{
	if (this != &ls)
	{
		eraseStack();
		copyStack(ls);
	}
	return *this;
}

template<typename T>
LStack<T>::~LStack()
{
	eraseStack();
}

template<typename T>
bool LStack<T>::empty() const
{
	return topNode == nullptr;
}

template<typename T>
void LStack<T>::push(T const & x)
{
	node<T>* p = new node<T>;
	p->data = x;
	p->next = topNode;
	topNode = p;

}

template<typename T>
T LStack<T>::pop()
{
	if (empty())
	{
		cerr << "Stack is empty" << endl;
		return T();
	}
	T x = topNode->data;
	node<T>* p = topNode;
	topNode = topNode->next;
	delete p;
	return x;
}

template<typename T>
T LStack<T>::top()
{
	if (empty())
	{
		cerr << "Stack is empty" << endl;
		return T();
	}
	return topNode->data;
}

template<typename T>
void LStack<T>::print() const
{
	if (empty())
	{
		cerr << "Stack is empty" << endl;
		return;
	}
	node<T>* p = topNode;
	while(p)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

template<typename T>
T LStack<T>::maxElement()
{
	T maximum = topNode->data;
	node<T>* p = topNode;
	while (p)
	{
		if (maximum <= p->data)
			maximum = p->data;
		p = p->next;
	}
	return maximum;
}
