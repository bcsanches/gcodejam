#include <iostream>

using namespace std;

class GameState
{
	public:
		GameState():
			m_iNumX(0),
			m_iNumO(0),
			m_fTFound(false),
			m_fDotFound(false)
		{
		}

		bool UpdateState(char ch)
		{
			if(ch == '.')
			{
				m_fDotFound = true;				
				return false;
			}
			else if(ch == 'T')
			{
				m_fTFound = true;
			}
			else
			{
				ch == 'X' ? m_iNumX++ : m_iNumO++;				
			}

			return true;
		}

		bool WasDotFound() const 
		{
			return m_fDotFound;
		}

		char ComputeWinner() const
		{	
			if(m_fDotFound)
				return '.';

			const int winMax = m_fTFound ? 3 : 4;
			if(m_iNumX == winMax)
				return 'X';
			else if(m_iNumO == winMax)
				return 'O';
			else
				return '.';
		}

	private:
		int m_iNumX;
		int m_iNumO;

		bool m_fTFound;
		bool m_fDotFound;		
};

int main(int, char **)
{
	int numTestCases;

	cin >> numTestCases;

	char board[4][4];

	for(int i = 0;i < numTestCases; ++i)
	{
		for(int j = 0;j < 4; ++j)
		{
			for(int k = 0;k < 4; ++k)
				cin >> board[j][k];
		}

		bool incompleteGame = false;
		char winner = '.';

		//
		//diagonals		
		{
			GameState diag1;
			GameState diag2;

			for(int j = 0;j < 4; ++j)
			{
				diag1.UpdateState(board[j][j]);					
				diag2.UpdateState(board[j][3 - j]);
			}

			if(diag1.WasDotFound() || diag2.WasDotFound())
			{
				incompleteGame = true;				
			}

			winner = diag1.ComputeWinner();
			if(winner == '.')
				winner = diag2.ComputeWinner();
		}

		for(int j = 0;j < 4 && winner == '.'; ++j)
		{			
			GameState horizontal;
			GameState vertical;

			for(int k = 0;k < 4; ++k)
			{
				horizontal.UpdateState(board[j][k]);
				vertical.UpdateState(board[k][j]);
			}

			if(horizontal.WasDotFound() || vertical.WasDotFound())
			{
				incompleteGame = true;				
			}

			winner = horizontal.ComputeWinner();
			if(winner == '.')
				winner = vertical.ComputeWinner();
		}				

		
		
		const char *output;

		if(winner == '.')
		{
			output = incompleteGame ? "Game has not completed" : "Draw";
		}
		else 
		{
			output = winner == 'X' ? "X won" : "O won";
		}

		cout << "Case #" << (i +1) << ": " << output << std::endl;
	}

	return 0;
}
