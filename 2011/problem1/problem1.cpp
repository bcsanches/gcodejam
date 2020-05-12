#include <stdio.h>
#include <algorithm>
#include <iostream>

class Robot_c
{
	public:
		Robot_c():			
			m_iCurrentPos(1),
			m_iSequenceStep(0),
			m_iFreeTime(0)
		{
		}		

		void AddFreeTime(int time)
		{
			m_iFreeTime += time;			
			m_fAddedFreeTime = true;
		}

		int PressButton(int pos)
		{
			int iMovement = abs(m_iCurrentPos - pos);
			m_iCurrentPos = pos;

			//count the button press time
			int iCost = iMovement;
			
			if(m_iFreeTime > 0)
			{
				int iNewCost= iCost - std::min(m_iFreeTime, iCost);
				//m_iFreeTime -= std::min(m_iFreeTime, iCost);				
				m_iFreeTime = 0;

				iCost = iNewCost;
			}			

			return iCost+1;
		}


	private:
		int m_iFreeTime;	
		bool m_fAddedFreeTime;

		int m_iCurrentPos;

		int m_iSequenceStep;		
};

int main(int, char **)
{
	using namespace std;

	int numTests;
	cin >> numTests;

	for(int i = 0;i < numTests; ++i)
	{
		Robot_c clOrange;
		Robot_c clBlue;		

		int numPushes;
		cin >> numPushes;

		int ariSequence[100] = {0};
		char achRobot[100] = {0};
		int iSequenceSize = 0;

		for(int j = 0;j < numPushes; ++j)
		{			
			char robot;
			cin >> robot;

			int step;

			cin >> step;

			ariSequence[iSequenceSize] = step;
			achRobot[iSequenceSize] = robot;

			++iSequenceSize;			
		}

		int totalTime = 0;
		
		for(int j = 0; j < iSequenceSize; ++j)
		{
			Robot_c &rclRobot = (achRobot[j] == 'B') ? clBlue : clOrange;
			Robot_c &rclOtherRobot = (achRobot[j] == 'B') ? clOrange : clBlue;

			int cost = rclRobot.PressButton(ariSequence[j]);
			totalTime += cost;

			rclOtherRobot.AddFreeTime(cost);
		}
		cout << "Case #" << (i+1) << ": " << totalTime << std::endl;
	}

	return 0;
}
