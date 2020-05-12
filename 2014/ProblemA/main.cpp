#include <iostream>

using namespace std;

void ReadCards(int iCards[4][4])
{
	for (int iRow = 0; iRow < 4; ++iRow)
	{
		for (int iCol = 0; iCol < 4; ++iCol)
		{
			cin >> iCards[iRow][iCol];
		}
	}
}

int main(int, char **)
{
	int iNumTestCases;

	cin >> iNumTestCases;

	for (int iTest = 0; iTest < iNumTestCases; ++iTest)
	{
		int iFirstRow;

		cin >> iFirstRow;

		int iCards[4][4];

		ReadCards(iCards);

		int iSecondRow;

		cin >> iSecondRow;

		--iFirstRow;
		--iSecondRow;

		int iCards2[4][4];
		ReadCards(iCards2);

		int iCount = 0;
		
		const int *piCards2Begin = iCards2[iSecondRow];
		const int *piCards2End = piCards2Begin + 4;

		int iNumber = -1;

		//Brute force should be good enough
		for (int i = 0; i < 4; ++i)
		{
			auto piFound = std::find(piCards2Begin, piCards2End, iCards[iFirstRow][i]);
			if (piFound != piCards2End)
			{
				++iCount;
				iNumber = *piFound;
			}			
		}

		cout << "Case #" << iTest + 1 << ": ";

		if (iCount == 0)
		{
			cout << "Volunteer cheated!";
		}
		else if (iCount == 1)
		{
			cout << iNumber;
		}
		else
		{
			cout << "Bad magician!";
		}

		cout << endl;
	}

	return 0;
}
