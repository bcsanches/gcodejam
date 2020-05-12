#include <iostream>
#include <vector>

using namespace std;

int main(int, char **)
{
	int numTests = 0;

	std::vector<int> numbers;
	numbers.reserve(500);

	cin >> numTests;

	for(int i = 0;i < numTests; ++i)
	{
		int numNumbers;

		cin >> numNumbers;

		numbers.clear();
		counter.clear();

		for(int j = 0;j < numNumbers; ++j)
		{
			int num;

			cin >> num;
			numbers.push_back(num);			
		}

		std::sort(numbers.begin(), numbers.end());
		

		for(int offset = 0;offset < numNumbers; ++offset)
		{

		}
	}
}