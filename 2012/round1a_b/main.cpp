#include <iostream>
#include <map>
#include <list>

using namespace std;

struct Level_s
{
	int iNumStarsRequired[2];
	bool fCompleted[2];
};

typedef std::list<Level_s> LevelSet_t;

std::pair<LevelSet_t::iterator, int> FindBestLevelWithLowestRequirement(int numStars, LevelSet_t &levels, int numLevels)
{
	int rating = -1;

	LevelSet_t::iterator best = levels.end();
	int bestEarns = 0;
	int bestRequirement = 9999999;	

	for(LevelSet_t::iterator it = levels.begin(), end = levels.end();it != end; ++it)
	{
		if(it->fCompleted[1])
			continue;

		if((it->iNumStarsRequired[1] <= numStars) && !(it->fCompleted[1]))
		{
			return std::make_pair(it, 1);
		}
		
		if((it->iNumStarsRequired[0] <= numStars) && !(it->fCompleted[0]))
		{
			best = it;
		}		
	}

	return best != levels.end() ? std::make_pair(best, 0) : std::make_pair(best, -1);
}

int main(int, char**)
{
	int numTestCases;
	LevelSet_t levels;

	cin >> numTestCases;

	for(int i = 0;i < numTestCases; ++i)
	{
		int numLevels;

		cin >> numLevels;

		levels.clear();

		for(int j = 0;j < numLevels; ++j)
		{
			Level_s level;

			cin >> level.iNumStarsRequired[0] >> level.iNumStarsRequired[1];
			level.fCompleted[0] = level.fCompleted[1] = false;

			levels.push_back(level);
		}

		int numPlayed = 0;
		int numCompleted = 0;
		int numStars = 0;

		for(;;)
		{
			std::pair<LevelSet_t::iterator, int> pair = FindBestLevelWithLowestRequirement(numStars, levels, numLevels);

			if(pair.second < 0)
			{
				break;
			}
			else
			{
				numStars += pair.second == 0 ? 1 : 1 + !pair.first->fCompleted[0];
				pair.first->fCompleted[pair.second] = true;

				++numPlayed;

				if(pair.second == 1)
				{
					++numCompleted;
					//levels.erase(pair.first);
					if(numCompleted == numLevels)
						break;
				}
			}
		}

		if(numCompleted < numLevels)
		{
			printf("Case #%d: Too Bad\n", i+1);
		}
		else
		{
			printf("Case #%d: %d\n", i+1, numPlayed);
		}
	}
}