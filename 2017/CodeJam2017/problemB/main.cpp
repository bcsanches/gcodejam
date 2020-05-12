#include <iostream>
#include <string>

using namespace std;

void rotate(string &number, size_t pos)
{
	for (auto i = pos; i < number.length(); ++i)
		number[i] = '9';	

	--pos;
	while (pos > 0)
	{
		if (number[pos] == '0')
		{
			number[pos] = '9';

			--pos;
		}
		else
		{
			--number[pos];
			break;
		}
	}

	if (pos == 0)
	{
		if (number[pos] == '1')
		{
			string tmp(number.begin() + 1, number.end());
			swap(tmp, number);
		}
		else
		{
			--number[pos];
		}
	}
}

int main()
{
	int numTestCases;

	cin >> numTestCases;

	string number;

	for (int i = 0; i < numTestCases; ++i)
	{
		cin >> number;

		if (number.length() > 1)
		{		
			for (;;)
			{
				bool error = false;
				for (size_t j = 0, len = number.length(); j < len - 1; ++j)
				{
					if (number[j] > number[j + 1])
					{
						error = true;

						char max = number[j];

						for (auto k = number.length() - 1; k != j; --k)
						{
							if (number[k] < max)
							{
								rotate(number, k);
								break;
							}
						}

						break;
					}
				}

				if (!error)
					break;				
			}
		}

		cout << "Case #" << (i + 1) << ": " << number << endl;
	}

	return 0;
}