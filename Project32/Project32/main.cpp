
#include "NiTE.h"
#include <NiteSampleUtilities.h>
using namespace nite;


/*
#include "OpenNI.h"
#include "OniSampleUtilities.h"
using namespace openni;
*/

int main(){
	/*
	openni::Status rc;
	//openni::Device kinect;

	rc = openni::OpenNI::initialize();
	if (rc != openni::STATUS_OK)
	{
		printf("%s: Initialize failed\n%s\n");
		return 1;
	}
	openni::OpenNI::shutdown();
	*/

	for (int i = 0; i < 5; ++i)
		printf("%d\n", i);


	
	//NiTE initialization
	nite::UserTracker userTracker;
	nite::Status niterc;
	niterc = nite::NiTE::initialize();
	if (niterc != nite::STATUS_OK)
	{
		printf("NiTE Initialization Failed! \n");
		return 1;
	}
	
	/*
	TO DO here:
	Initialize Serial Bluetooth Connection
	*/

	//Control to Abort program
	int timeoutToAbort = 0;

	niterc = userTracker.create();
	nite::UserTrackerFrameRef userTrackerFrame;
	while (!wasKeyboardHit())
	{
		niterc = userTracker.readFrame(&userTrackerFrame);
		//Do other per-frame processing stuff

		//Detecting Person. note: We only need to detect one person
		const nite::Array<nite::UserData>& users = userTrackerFrame.getUsers();
		if (users.getSize() < 1){
			printf("b");
			/*
			If no one is detected for more than 50 consecutive frames, abort program
			*/
			if (timeoutToAbort>50){
				printf("No one is detected. Aborting program.\n");
				break;
			}
			else {
				timeoutToAbort++;
				continue;
			}
		}	
		const nite::UserData& user = users[0];
		timeoutToAbort = 0;
		printf("a\n"); 

		/*
		Initiate Skeleton Tracking of the User.
		*/
		//if (user.isNew())
			userTracker.startSkeletonTracking(user.getId());
		while (true){
			bool tracked = false;
			switch (user.getSkeleton().getState())
			{
				case nite::SKELETON_CALIBRATING:
					printf("C\r");
					break;
				case nite::SKELETON_NONE:
					printf("S\r");
					break;
				case nite::SKELETON_TRACKED:
					printf("\nTracked!\n");
					tracked = true;
					break;
				default:
					printf("Unknown State\r");
			}//switch
			if (tracked) break;
		}//while




		


		printf("reach\n");
	}
	


	nite::NiTE::shutdown();
	return 0;
}