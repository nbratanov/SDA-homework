#include <iostream>
#include <string>
#include "LStack.h"
using namespace std;

string isBalanced(string s)
{
	LStack<char> stack;
	bool isBalanced = 0;
	char x;
	if (s[s.size() - 1] == '[' || s[s.size() - 1] == '(' || s[s.size() - 1] == '{')
		return "NO";

	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '[' || s[i] == '(' || s[i] == '{')
			stack.push(s[i]);
		if (s[i] == ']' || s[i] == ')' || s[i] == '}')
		{
			if (!stack.empty())
				x = stack.pop();
			else
				return "NO";

			if (x == '[' && s[i] == ']')
				isBalanced = 1;
			else if (x == '(' && s[i] == ')')
				isBalanced = 1;
			else if (x == '{' && s[i] == '}')
				isBalanced = 1;
			else
				return "NO";
		}
	}
	
	if (isBalanced == 0)
		return "NO";
	else
		return "YES";
}

int main()
{
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		string s;
		cin >> s;
		string result = isBalanced(s);
		cout << result << endl;
	}

	system("pause");
	return 0;
}