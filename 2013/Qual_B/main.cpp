#include <iostream>

using namespace std;

//#define SKIP_ROW

int main(int, char **)
{
	int numTests;

	cin >> numTests;	

	for(int test = 0;test < numTests; ++test)
	{
		int w, h;

		cin >> h >> w;

		int grass[100][100] = {0};
		for(int i = 0;i < h; ++i)
		{
			for(int j = 0;j < w; ++j)
				cin >> grass[i][j];
		}
		
		bool valid = true;
		for(int i = 0;i < h; ++i)
		{
			for(int j = 0;j < w; ++j)
			{
				int number = grass[i][j];

				//check row
				bool validRow = true;

#ifdef SKIP_ROW
				bool sameNumberRow = true;
#endif

				for(int k = 0; k < w; ++k)
				{
					if(grass[i][k] > number)
					{
						validRow = false;
						break;
					}
#ifdef SKIP_ROW
					if(grass[i][k] != number)
						sameNumberRow = false;
#endif
				}

#ifdef SKIP_ROW
				//skipRow
				if(sameNumberRow)
					break;
#endif

				bool validCol = true;

				if(!validRow)
				{
					for(int k = 0; k < h; ++k)
					{
						if(grass[k][j] > number)
						{
							validCol = false;
							break;
						}
					}
				}

				if(!validRow && !validCol)
				{
					valid = false;
					goto OUTSIDE;
				}
			}
		}
OUTSIDE:
		cout << "Case #" << (test+1) << ": " << (valid ? "YES" : "NO") << endl;			

		/*
		for(int i = 0;i < h; ++i)
		{
			for(int j = 0;j < w; ++j)
				cout << grass[i][j];

			cout << endl;
		}
		cout << endl;*/
	}

	return 0;
}