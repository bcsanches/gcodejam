#include <iostream>
#include <math.h>
#include <vector>

typedef double Real_t;
typedef std::vector<Real_t> FloatVector_t;

//#define RECALC

int main(int, char **)
{
	using namespace std;

	FloatVector_t vecProbabilities;
	FloatVector_t vecTotalProbabilities;

#if (defined RECALC)
	vecProbabilities.reserve(10000);
#else
	vecTotalProbabilities.reserve(10000);
#endif

	int numTestCases;

	cin >> numTestCases;

	for(int i = 0;i < numTestCases; ++i)
	{
		int numTyped, passwordLength;

		cin >> numTyped >> passwordLength;

#if (defined RECALC)
		vecProbabilities.clear();
#else
		vecTotalProbabilities.clear();
		Real_t correctProbability = 1;
#endif		

		for(int j = 0;j < numTyped; ++j)
		{
			Real_t p;
			cin >> p;
			
#if (defined RECALC)
			vecProbabilities.push_back(p);
#else
			correctProbability *= p;
			vecTotalProbabilities.push_back(correctProbability);
#endif
		}


		Real_t best = 999999999.0;			

		for(int numBackspaces = 1; numBackspaces <= numTyped; ++numBackspaces)
		{			
			//Real_t numPossibilities = pow(2.0, numTyped - numBackspaces);

			Real_t numKeyStrokesWithBackspaceOk = (numBackspaces *2)+ 1 + (passwordLength - numTyped);
			Real_t numKeyStrokesWithBackspaceWrong = numKeyStrokesWithBackspaceOk + passwordLength + 1;

#if (defined RECALC)
			Real_t correctProbability = 1;
			for(int j = 0;j < numTyped - numBackspaces; ++j)
			{
				correctProbability *= vecProbabilities[j];
			}
#else
			correctProbability = numBackspaces == numTyped ? 1.0f : vecTotalProbabilities[numBackspaces];
#endif

			Real_t chance = (correctProbability * numKeyStrokesWithBackspaceOk) + ((1.0 - correctProbability) * numKeyStrokesWithBackspaceWrong);

			if(chance < best)
			{
				best = chance;
			}
		}

		//
		//optimal cases
		//just keep typing
#if (defined RECALC)
		Real_t correctProbability = 1;
		for(int j = 0;j < numTyped; ++j)
		{
			correctProbability *= vecProbabilities[j];
		}
#else
		correctProbability = vecTotalProbabilities[numTyped-1];
#endif

		Real_t chance = (correctProbability * ((passwordLength - numTyped) + 1)) + ((1.0 - correctProbability) * (((passwordLength - numTyped) + 1) + passwordLength + 1));
		if(chance < best)
			best = chance;

		//press enter right away
		if(passwordLength + 2 < best)
			best = passwordLength+2;

		//cout << "Case #" << i+1 << ": " << best << endl;
		printf("Case #%d: %f\n", i+1, best);
	}

	return 0;
}
