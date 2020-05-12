#include <iostream>
#include <assert.h>

#define MAX 100

int ariCeiling_g[MAX][MAX];
int ariFloor_g[MAX][MAX];
int iNumRows_g;
int iNumCols_g;
double dWaterLevel_g;
double dTime_g = 0;

using namespace std;

void ReadData(int dest[MAX][MAX], int n, int m)
{
	for(int row = 0; row < n; ++row)
	{
		for(int col = 0; col < m; ++col)
		{
			cin >> dest[col][row];
		}
	}
}

bool CanMoveTo(int currentFloor, int currentCeiling, int destX, int destY)
{
	int nextFloor = ariFloor_g[destX][destY];
	int nextCeiling = ariCeiling_g[destX][destY];

	if(nextCeiling >= currentCeiling)
		return false;

	if(nextCeiling <= currentFloor)
		return false;

	int minCeiling = std::min(currentCeiling, nextCeiling);
	int maxCeiling = std::max(currentFloor, nextFloor);

	assert(minCeiling >= maxCeiling);

	return (minCeiling - maxCeiling) >= 50;
}

void FindExit(int currentX, int currentY, int &nextX, int &nextY)
{
	int currentFloor = ariFloor_g[currentX][currentY];
	int currentCeiling = ariCeiling_g[currentX][currentY];

	if(currentX < iNumCols_g-1)
	{
		for(int i = 0;i < iNumRows_g; ++i)
		{
			if(CanMoveTo(currentFloor, currentCeiling, currentX+1, i))
			{
				nextX = currentX+1;
				nextY = i;

				return;
			}
		}
	}
}


void AdvanceTime(double time)
{
	dTime_g += time;
	dWaterLevel_g -= time * 10;
	
	dWaterLevel_g = std::max(dWaterLevel_g, 0.0);
}

void WaitWater(int expectedHeight)
{
	if(dWaterLevel_g <= expectedHeight)
		return;

	AdvanceTime((dWaterLevel_g - expectedHeight) / 10);
}

void MoveFrom(int currentX, int currentY)
{
	if((dWaterLevel_g - ariFloor_g[currentX][currentY]) > 20)
		AdvanceTime(1);
	else
		AdvanceTime(10);	
}


int main(int, char**)
{	
	int numTestCases;

	cin >> numTestCases;

	for(int i = 0;i < numTestCases; ++i)
	{		
		cin >> dWaterLevel_g >> iNumRows_g >> iNumCols_g;

		ReadData(ariCeiling_g, iNumRows_g, iNumCols_g);		
		ReadData(ariFloor_g, iNumRows_g, iNumCols_g);

		int startX = 0, startY = 0;
		dTime_g = 0;

		for(;;)
		{
			int nextX,  nextY;
			FindExit(startX, startY, nextX, nextY);

			WaitWater(ariCeiling_g[nextX][nextY]-50);

			MoveFrom(startX, startY);			

			startX = nextX;
			startY = nextY;

			if((startX == iNumCols_g -1) && (startY == iNumRows_g-1))
			{
				//MoveFrom(startX, startY);
				break;
			}
		}

		cout << "Case #" << (i+1) << ": " << dTime_g << std::endl;
	}

	return 0;
}

