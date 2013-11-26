
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



	
	//NiTE initialization
	nite::UserTracker userTracker;
	nite::Status niterc;
	niterc = nite::NiTE::initialize();
	if (niterc != nite::STATUS_OK)
	{
		printf("NiTE Initialization Failed! \n");
		return 1;
	}
	
	niterc = userTracker.create();
	
	nite::UserTrackerFrameRef userTrackerFrame;
	while (!wasKeyboardHit())
	{
		niterc = userTracker.readFrame(&userTrackerFrame);
		//Do other per-frame processing stuff
		printf("a");
	}
	



	return 0;
}