#include <iostream>
#include <math.h>

#define MAX_SIZE 30

char archScenario[MAX_SIZE][MAX_SIZE];

void Bresenham(int x1,
    int y1,
    int x2,
    int y2)
{
    // if x1 == x2 or y1 == y2, then it does not matter what we set here
    int delta_x(x2 - x1);
    signed char ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;
 
    int delta_y(y2 - y1);
    signed char iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;
 
    //plot(x1, y1);
 
    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
 
        while (x1 != x2)
        {
            if (error >= 0)
            {
                if (error || (ix > 0))
                {
                    y1 += iy;
                    error -= delta_x;
                }
                // else do nothing
            }
            // else do nothing
 
            x1 += ix;
            error += delta_y;
 
            //plot(x1, y1);
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));
 
        while (y1 != y2)
        {
            if (error >= 0)
            {
                if (error || (iy > 0))
                {
                    x1 += ix;
                    error -= delta_y;
                }
                // else do nothing
            }
            // else do nothing
 
            y1 += iy;
            error += delta_x;
 
            //plot(x1, y1);
        }
    }
}

int Round(double n)
{
	return ((int)(floor(n))) + (n - floor(n)) < 0.5 ? 1 : 0;
}

void SuperLine(double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;

	double m = dx / dy;

	if(dy > dx)
	{

	}
}

int main(int, char **)
{
	using namespace std;

	int numTests;

	cin >> numTests;

	for(int i = 0;i < numTests; ++i)
	{
		int width, height, maxDistance;

		int startX, startY;

		cin >> height >> width >> maxDistance;

		for(int y = 0; y < height; ++y)		
		{			
			for(int x = 0;x < width; ++x)
			{
				cin >> archScenario[y][x];

				if(archScenario[y][x] == 'X')
				{
					startX = x;
					startY = y;
				}
			}
		}

		for(int y = 0; y < height; ++y)		
		{			
			for(int x = 0;x < width; ++x)
			{
				if(archScenario[y][x] == '#')
				{
					Bresenham(startX, startY, x, y);
				}
			}
		}
	}

	return 0;
}