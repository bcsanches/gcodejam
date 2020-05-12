#include <iostream>
#include <sstream>

using namespace std;

typedef unsigned long long Integer_t;

bool IsPalindrome(const std::string &str)
{
	size_t len = str.length()-1;
	if(len == 0)
		return true;

	for(size_t i = 0;i <= len; ++i, --len)
	{
		if(str[i] != str[len])
			return false;
	}

	return true;
}

int main(int, char **)
{
	int numTestCases;

	cin >> numTestCases;

	/*
	cout << IsPalindrome("101") << endl;
	cout << IsPalindrome("11") << endl;;
	cout << IsPalindrome("1") << endl;;

	cout << IsPalindrome("1010") << endl;;
	cout << IsPalindrome("111") << endl;;
	cout << IsPalindrome("subinoonibus") << endl;;*/	

	for(int i = 0; i < numTestCases; ++i)
	{
		Integer_t first, last;

		cin >> first >> last;

		Integer_t count = 0;

		double firstRoot = sqrt(first);

		Integer_t firstIntRoot = (int)fabs(firstRoot);		

		Integer_t firstNumber = firstIntRoot * firstIntRoot;

		while(firstNumber < first)
		{
			++firstIntRoot;
			firstNumber = firstIntRoot * firstIntRoot;
		}

		while(firstNumber <= last)
		{
			std::stringstream stream;
			stream << firstIntRoot;

			if(IsPalindrome(stream.str()))
			{
				stream = std::stringstream();
				stream << firstNumber;

				if(IsPalindrome(stream.str()))
				{
					++count;
				}
			}

			++firstIntRoot;
			firstNumber = firstIntRoot * firstIntRoot;
		}
		
		cout << "Case #" << (i+1) << ": " << count << endl;
	}

	return 0;
}
