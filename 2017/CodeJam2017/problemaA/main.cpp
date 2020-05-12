#include <iostream>
#include <string>

using namespace std;

int main()
{
	int num;

	cin >> num;

	int k;
	string pancakes;
	for (int i = 0; i < num; ++i)
	{
		cin >> pancakes >> k;

		int happy = 0, sad = 0;

		for (auto it : pancakes)
		{
			((it == '+') ? happy : sad) += 1;
		}		

		int h = happy;
		int s = sad;

		int flips = 0;
		if (sad > 0)
		{
			flips = sad / k;
			
			int changes = k * flips;
			sad -= changes;
			happy += changes;

			if (sad == 0)
				goto EXIT;
			
			if (pancakes.length() <= k)
			{
				flips = -1;
				goto EXIT;
			}							
			int missing = k - sad;

			int borrow = k - missing;

			++flips;

			happy -= borrow;
			sad -= missing;

			if ((happy < 0) || (sad < 0))
			{
				flips = -1;
				goto EXIT;
			}

			sad += borrow;
			happy += missing;

			if (sad == k)
			{
				++flips;
			}
			else if(sad > 0)
			{						
				happy = h;
				sad = s;

				flips = (sad / k) - 1;
				if (flips >= 0)
				{
					int changes = k * flips;
					sad -= changes;
					happy += changes;	

					int missing = sad - k;

					int borrow = k - missing;

					++flips;

					happy -= missing;
					sad -= borrow;

					if ((happy < 0) || (sad < 0))
					{
						flips = -1;
						goto EXIT;
					}

					sad += missing;
					happy += borrow;

					if (sad == k)
					{
						++flips;
					}
					else if (sad != 0)
						flips = -1;
				}
			}				
		}								

EXIT:
		cout << "Case #" << (i + 1) << ": ";

		if (flips >= 0)
			cout << flips;
		else
			cout << "IMPOSSIBLE";

		cout << endl;
	}
}