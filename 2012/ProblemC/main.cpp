#include <stdio.h>
#include <set>
#include <algorithm>

bool HasUniqueDigits(const char *str)
{
	int numbers[10] = {0};

	for(int i = 0;str[i];++i)
	{
		int pos = str[i]-'0';
		numbers[pos]++;

		if(numbers[pos] > 1)
			return false;
	}

	return true;
}

bool HasSameDigits(const char *str1, const char *str2)
{
	int numbers[10] = {0};

	for(int i = 0;str1[i];++i)
	{
		int pos = str1[i]-'0';
		numbers[pos]++;

		pos = str2[i]-'0';
		numbers[pos]++;		
	}

	for(int i = 0;i < 10; ++i)
		if((numbers[i] != 0) && (numbers[i] != 2))
			return false;

	return true;
}

int main(int, char **)
{
	int numCases;

	scanf("%d", &numCases);	
	char strM[128];
	char strN[128];

	for(int i = 0;i < numCases; ++i)
	{		
		int a,b;
		scanf("%d %d", &a, &b);

		int num = 0;
		for(int m = a +1; m <= b; ++m)
		{	
			sprintf(strM, "%d", m);
			if(!HasUniqueDigits(strM))
				continue;

			for(int n = a;n < m; ++n)
			{				
				int lenStrN = sprintf(strN, "%d", n);
				if(!HasUniqueDigits(strN))
					continue;

				if(!HasSameDigits(strN, strM))
					continue;

				for(int tries = 0;tries < lenStrN; ++tries)
				{
					std::rotate(&strN[0], &strN[lenStrN-1], &strN[lenStrN]);

					int newNumber;
					sscanf(strN, "%d", &newNumber);

					if(newNumber == m)
					{
						++num;
						break;
					}
				}
			}
		}

		printf("Case #%d: %d\n", i+1, num);		
	}
}