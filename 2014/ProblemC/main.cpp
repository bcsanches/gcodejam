#include <iostream>

#include <list>

using namespace std;

struct MineField
{
	bool IsMine(int iRow, int iCol)
	{
		return archField[iRow][iCol] == '*';
	}

	void Clear()
	{
		memset(archField, 'Z', sizeof(archField));
	}

	void InitializeWithMines()
	{
		for (int i = 0; i < iNumRows; ++i)
		{
			memset(archField[i], '*', iNumCols * sizeof(char));
		}
	}

	void InitializeWithBlank()
	{
		for (int i = 0; i < iNumRows; ++i)
		{
			memset(archField[i], '.', iNumCols * sizeof(char));
		}
	}

	int GetNumCells()
	{
		return iNumRows * iNumCols;
	}

	char archField[50][50];

	int iNumRows;
	int iNumCols;
};

int CountNeighborMines(MineField &field, int iRow, int iCol)
{
	int iCount = 0;

	if (iRow > 0)
	{
		iCount += field.IsMine(iRow - 1, iCol);
		if (iCol > 0)
			iCount += field.IsMine(iRow - 1, iCol - 1);

		if (iCol < field.iNumCols - 1)
			iCount += field.IsMine(iRow - 1, iCol + 1);
	}

	if (iCol > 0)
		iCount += field.IsMine(iRow, iCol - 1);	

	if (iCol < field.iNumCols - 1)
		iCount += field.IsMine(iRow, iCol + 1);

	if (iRow < field.iNumRows - 1)
	{
		iCount += field.IsMine(iRow + 1, iCol);
		if (iCol > 0)
			iCount += field.IsMine(iRow + 1, iCol - 1);

		if (iCol < field.iNumCols - 1)
			iCount += field.IsMine(iRow + 1, iCol + 1);
	}

	return iCount;
}

int Expand_r(MineField &field, int iRow, int iCol)
{	
	if (iRow < 0)
		return 0;

	if (iCol < 0)
		return 0;

	if (iRow == field.iNumRows)
		return 0;

	if (iCol == field.iNumCols)
		return 0;

	if (field.archField[iRow][iCol] == 'X')
		return 0;

	int iCount = 0;
	if (!field.IsMine(iRow, iCol))
	{				
		char chPrevious = field.archField[iRow][iCol];
		field.archField[iRow][iCol] = 'X';

		++iCount;

		//dont expand numbers
		if (chPrevious != '.')
			return 1;
	}
	else
	{
		//no need to expand mines
		return 0;
	}

	iCount += Expand_r(field, iRow - 1, iCol - 1);
	iCount += Expand_r(field, iRow - 1, iCol);
	iCount += Expand_r(field, iRow - 1, iCol + 1);
	iCount += Expand_r(field, iRow, iCol + 1);
	iCount += Expand_r(field, iRow + 1, iCol + 1);
	iCount += Expand_r(field, iRow + 1, iCol - 0);
	iCount += Expand_r(field, iRow + 1, iCol - 1);
	iCount += Expand_r(field, iRow, iCol - 1);

	return iCount;
}

void ClearCell(MineField &field, int iRow, int iCol, int &iFreeCells)
{
	if (iFreeCells == 0)
		return;

	if (iRow < 0)
		return ;

	if (iCol < 0)
		return ;

	if (iRow == field.iNumRows)
		return ;

	if (iCol == field.iNumCols)
		return ;

	if (field.archField[iRow][iCol] == '.')
		return;

	--iFreeCells;
	field.archField[iRow][iCol] = '.';
}

struct Position
{
	Position(int row, int col):
		iRow(row),
		iCol(col)
	{
		//empty;
	}

	int iRow, iCol;
};

typedef std::list<Position> PositionQueue;

void AddMine(MineField &field, int &iNumMines, PositionQueue &queue)
{
	if (queue.empty())
		return;

	Position pos = *queue.begin();
	queue.pop_front();

	int iRow = pos.iRow;
	int iCol = pos.iCol;

	if (iNumMines == 0)
		return;

	if (iRow < 0)
		return;

	if (iCol < 0)
		return ;

	if (iRow == field.iNumRows)
		return ;

	if (iCol == field.iNumCols)
		return ;

	if (field.archField[iRow][iCol] == '*')
		return;

	--iNumMines;
	field.archField[iRow][iCol] = '*';

	queue.push_back(Position(iRow, iCol + 1));
	queue.push_back(Position(iRow + 1, iCol));
	queue.push_back(Position(iRow + 1, iCol + 1));

	/*

	AddMine_r(field, iRow, iCol + 1, iNumMines);
	AddMine_r(field, iRow + 1, iCol, iNumMines);
	AddMine_r(field, iRow + 1, iCol + 1, iNumMines);
	*/
}

void FillMineField2(MineField &field, int iNumMines)
{
	int iCenterRow = field.iNumRows / 2;
	int iCenterCol = field.iNumCols / 2;

	field.InitializeWithMines();

	int iFreeCells = field.GetNumCells() - iNumMines;

	field.archField[iCenterRow][iCenterCol] = '.';
	--iFreeCells;

	int iRadius = 1;

	while (iFreeCells > 0)
	{
		int iStartRow = iCenterRow - iRadius;
		int iStartCol = iCenterCol - iRadius;

		int iLength = (iRadius * 2) + 1;

		for (int iRow = 0; iRow < iLength; ++iRow)
		{
			for (int iCol = 0; iCol < iLength; ++iCol)
			{
				ClearCell(field, iStartRow + iRow, iStartCol + iCol, iFreeCells);
			}
		}		

		++iRadius;
	}

	for (int iRow = 0; iRow < field.iNumRows; ++iRow)
	{
		for (int iCol = 0; iCol < field.iNumCols; ++iCol)
		{
			if (field.archField[iRow][iCol] == '*')
				continue;

			int iCount = CountNeighborMines(field, iRow, iCol);

			field.archField[iRow][iCol] = iCount == 0 ? '.' : '0' + iCount;
		}
	}
}

void FillMineField(MineField &field, int iNumMines)
{
#if 0
	int iCenterRow = field.iNumRows / 2;
	int iCenterCol = field.iNumCols / 2;

	field.InitializeWithMines();

	int iFreeCells = field.GetNumCells() - iNumMines;

	field.archField[iCenterRow][iCenterCol] = '.';
	--iFreeCells;

	int iRadius = 1;

	while (iFreeCells > 0)
	{
		int iStartRow = iCenterRow - iRadius;
		int iStartCol = iCenterCol - iRadius;

		int iLength = (iRadius * 2) + 1;

		for (int iRow = 0; iRow < iLength; ++iRow)
		{
			for (int iCol = 0; iCol < iLength; ++iCol)
			{
				ClearCell(field, iStartRow + iRow, iStartCol + iCol, iFreeCells);
			}
		}		

		++iRadius;
	}
#endif

	field.InitializeWithBlank();

	PositionQueue queue;

	queue.push_back(Position(0, 0));

	while (!queue.empty())
	{
		AddMine(field, iNumMines, queue);
	}	

	for (int iRow = 0; iRow < field.iNumRows; ++iRow)
	{
		for (int iCol = 0; iCol < field.iNumCols; ++iCol)
		{
			if (field.archField[iRow][iCol] == '*')
				continue;

			int iCount = CountNeighborMines(field, iRow, iCol);

			field.archField[iRow][iCol] = iCount == 0 ? '.' : '0' + iCount;
		}		
	}
}

bool TryToSolve(MineField field, int iCenterRow, int iCenterCol, int iNumMines)
{
	int iCount = Expand_r(field, iCenterRow, iCenterCol);

	if ((iCount + iNumMines) < field.GetNumCells())
	{				
		return false;
	}
	else
	{
		for (int iRow = 0; iRow < field.iNumRows; ++iRow)
		{
			for (int iCol = 0; iCol < field.iNumCols; ++iCol)
			{
				field.archField[iRow][iCol] = field.archField[iRow][iCol] == 'X' ? '.' : field.archField[iRow][iCol];
			}
		}

		field.archField[iCenterRow][iCenterCol] = 'c';

		for (int iRow = 0; iRow < field.iNumRows; ++iRow)
		{
			for (int iCol = 0; iCol < field.iNumCols; ++iCol)
			{
				cout << field.archField[iRow][iCol];
			}

			cout << endl;
		}

		return true;
	}
}

int main(int, char **)
{
	MineField stMineField;

	int iNumTestCases;

	cin >> iNumTestCases;

	for (int iTest = 0; iTest < iNumTestCases; ++iTest)
	{
		int iNumMines;

		stMineField.Clear();

		cin >> stMineField.iNumRows >> stMineField.iNumCols >> iNumMines;

		cout << "Case #" << (iTest + 1) << ":" << endl;

		bool firstTry = true;

TRY_AGAIN:
		if (firstTry)
			FillMineField(stMineField, iNumMines);
		else
			FillMineField2(stMineField, iNumMines);		

		int iCenterRow = stMineField.iNumRows / 2;
		int iCenterCol = stMineField.iNumCols / 2;

		bool fUpdated = false;

		for (int iRow = 0; iRow < stMineField.iNumRows && !fUpdated; ++iRow)
		{
			for (int iCol = 0; iCol < stMineField.iNumCols && !fUpdated; ++iCol)
			{
				if (stMineField.IsMine(iRow, iCol))
					continue;

				if (TryToSolve(stMineField, iRow, iCol, iNumMines))
					fUpdated = true;

#if 0

				if (stMineField.archField[iRow][iCol] == '.')
				{
					iCenterRow = iRow;
					iCenterCol = iCol;

					fUpdated = true;
				}				

				if (stMineField.archField[iRow][iCol] != '*')
				{
					iCenterRow = iRow;
					iCenterCol = iCol;
				}
#endif
			}
		}		

		if(!fUpdated)
		{
			if (firstTry)
			{
				firstTry = false;

				goto TRY_AGAIN;
			}

			cout << "Impossible" << endl;
		}

#if 0
		int iCount = Expand_r(stMineField, iCenterRow, iCenterCol);

		if ((iCount + iNumMines) < stMineField.GetNumCells())
		{
			if (firstTry)
			{
				firstTry = false;

				goto TRY_AGAIN;
			}
			cout << "Impossible" << endl;			
		}
		else
		{ 
			for (int iRow = 0; iRow < stMineField.iNumRows; ++iRow)
			{
				for (int iCol = 0; iCol < stMineField.iNumCols; ++iCol)
				{
					stMineField.archField[iRow][iCol] = stMineField.archField[iRow][iCol] == 'X' ? '.' : stMineField.archField[iRow][iCol];					
				}				
			}

			stMineField.archField[iCenterRow][iCenterCol] = 'c';

			for (int iRow = 0; iRow < stMineField.iNumRows; ++iRow)
			{
				for (int iCol = 0; iCol < stMineField.iNumCols; ++iCol)
				{
					cout << stMineField.archField[iRow][iCol];
				}

				cout << endl;
			}
		}		
#endif
	}
}
