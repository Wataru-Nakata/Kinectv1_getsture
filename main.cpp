#include <iostream>
#include <Windows.h>
#include <NuiApi.h>
#include <math.h>

using namespace std;

int main()
{
	cout << "Hello world" << endl;
	NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);
	int result,people;
	Vector4 Befhand, Nowhand;
	NUI_SKELETON_FRAME ourframe,old;
	NuiSkeletonGetNextFrame(40, &ourframe);
	while (true)
	{
		result = 0;
		people = 0;
		old = ourframe;
		NuiSkeletonGetNextFrame(40, &ourframe);
		for (int i = 0; i < 6; i++)
		{
			if (ourframe.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED)
			{
				people++;
				Befhand = old.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT];
				Nowhand = ourframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT];
				if (
					(Befhand.y > old.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT].y)
					&& (Nowhand.y > old.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT].y)
					&& (((Nowhand.x - Befhand.x)*(Nowhand.x - Befhand.x) + (Nowhand.y - Befhand.y)*(Nowhand.y - Befhand.y))
				> 0.001)
					)
					result += pow(2, i);
			}
		}
		cout <<"Number of people:"<< people <<"  result:"<< result  << endl;
	}
	NuiShutdown();
	return 0;
}
