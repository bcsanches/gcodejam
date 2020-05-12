#include <iostream>

using namespace std;

int main(int, char** )
{
	int iNumTestCases;

	cin >> iNumTestCases;

	for (int iTest = 0; iTest < iNumTestCases; ++iTest)
	{
		double fpFarmCost;
		double fpFarmProduction;
		double fpGoal;

		cin >> fpFarmCost >> fpFarmProduction >> fpGoal;


		int iNumFarms = 0;
		double fpPreCost = 0;

		double fpBestCost = fpGoal;

		for (;;)
		{
			double fpProduction = 2 + (iNumFarms * fpFarmProduction);
			double fpCost = fpPreCost + (fpGoal / fpProduction);

			if (fpCost < fpBestCost)
			{
				fpBestCost = fpCost;
			}
			else
			{
				break;
			}

			fpPreCost += fpFarmCost / fpProduction;
			++iNumFarms;
		}

		//cout << "farms " << iNumFarms << endl;
		//cout << "Case #" << iTest + 1 << ": " << fpBestCost << endl;
		printf("Case #%d: %lf\n", iTest + 1, fpBestCost);
	}

	return 0;
}
