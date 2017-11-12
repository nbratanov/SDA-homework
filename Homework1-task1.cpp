#include <iostream>
using namespace std;

const int MAX = 1000;

int fib(int n)   // Recursive solution:  O(2^n)
{
	if (n == 0 || n == 1)
		return n;
	return fib(n - 1) + fib(n - 2);
}

int fib2(int n)    // Optimized solution:    O(n)
{
	int a = 0, b = 1, c;
	if (n == 0)
		return a;
	
	for (int i = 2; i <= n; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return b;
}

int f[MAX] = { 0 };

int fib3(int n) // Best solution 0(logn)
{
	if (n == 0)
		return 0;
	if (n == 1 || n == 2)
		return f[n] = 1;

	if (f[n])
		return f[n];

	int k = (n & 1) ? (n + 1) / 2 : n / 2;

	f[n] = (n & 1) ? (fib3(k)*fib3(k) + fib3(k - 1)*fib3(k - 1)) : (2 * fib3(k - 1) + fib3(k))*fib3(k);
	return f[n];
}

int main()
{
	int x;
	cin >> x;
	cout << fib(x) << endl;
	cout << fib2(x) << endl;
	cout << fib3(x) << endl;

	system("pause");
	return 0;
}