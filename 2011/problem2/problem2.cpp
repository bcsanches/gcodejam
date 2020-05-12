#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>

struct ElementKey_s
{
	ElementKey_s(char first, char second)		
	{
		if(first < second)
		{
			m_chFirst = first;
			m_chSecond = second;
		}
		else
		{
			m_chFirst = second;
			m_chSecond = first;
		}
	}

	bool operator<(const ElementKey_s &rhs) const
	{
		if(m_chFirst < rhs.m_chFirst)
			return true;
		else if(m_chFirst > rhs.m_chFirst)
			return false;
		else
		{
			return m_chSecond < rhs.m_chSecond;
		}
	}

	char m_chFirst;
	char m_chSecond;
};

typedef std::map<ElementKey_s, char> ElementMap_t;

int main(int, char **)
{
	using namespace std;

	int numTestCases;

	cin >> numTestCases;

	for(int i = 0;i < numTestCases; ++i)
	{
		std::map<ElementKey_s, char> mapCombinations;

		int num;
		cin >> num;

		for(int j = 0;j < num; ++j)
		{		
			char a, b;
			char element;

			cin >> a >> b >> element;

			mapCombinations.insert(std::make_pair(ElementKey_s(a, b), element));
		}

		char achOpposeds[256] = {0};		

		cin >> num;

		for(int j = 0;j < num; ++j)
		{		
			char a, b;			

			cin >> a >> b;

			achOpposeds[a] = b;
		}

		//
		//
		//

		char lastElement = 0;
		int numInvokes;

		std::vector<char> vecElements;

		cin >> numInvokes;
		for(int j = 0;j < numInvokes; ++j)
		{
			char element;
			cin >> element;

			ElementKey_s key(lastElement, element);

			ElementMap_t::iterator it = mapCombinations.find(key);
			if(it != mapCombinations.end())
			{			
				vecElements.pop_back();
				element = it->second;
			}

			vecElements.push_back(element);
			lastElement = element;

			for(size_t k = 0;k < vecElements.size(); ++k)
			{
				char chExistingElement = vecElements[k];
				if((achOpposeds[chExistingElement] == element) || (achOpposeds[element] == chExistingElement))
				{
					vecElements.clear();
					lastElement = 0;
					break;
				}
			}
		}

		cout << "Case #" << i + 1 << ": [";

		for(size_t j = 0;j < vecElements.size();++j)
		{
			if(j)
				cout << ", " << vecElements[j];
			else
				cout << vecElements[j];
		}

		cout << "]" << endl;
	}
}