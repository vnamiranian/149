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

/*

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

int catch_signal(int sig, void (*handler)(int)){
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	return sigaction (sig, &action, NULL);
}


int read_in(int socket, char *buf, int len) {
	char *s = buf;
	int slen = len;
	int c = recv(socket, s, slen, 0);
	while ((c > 0) && (s[c-1] != '\n')) {
		s += c; slen -= c;
		c = recv(socket, s, slen, 0);
	}
	if (c < 0)
		return c;
	else if (c == 0)
		buf[0] = '\0';
	else
		s[c-1]='\0';
	return len - slen;
}

int listener_d;
void handle_shutdown(int sig){
	if (listener_d)
		close(listener_d);
	fprintf(stderr, "Bye!\n");
	exit(0);
}

void error(char *msg){
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}



//CREATES AN INTERNET STREAMING SOCKET
int open_listener_socket() {
	int s = socket(PF_INET, SOCK_STREAM, 0);
	if (s == -1) { error("Can't open socket"); }
	return s;
}


void bind_to_port(int socket, int port) {
	struct sockaddr_in name;
	name.sin_family = PF_INET;
	name.sin_port = (in_port_t)htons(30000);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	int reuse = 1;
	if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1) {
		error("Can't set the reuse option on the socket");
	}
	int c = bind (socket, (struct sockaddr *) &name, sizeof(name));
	if (c == -1) { error("Can't bind to socket");}
}

//SENDING A STRING MSG TO THE CLIENT
int say(int socket, char *s) {
	int result = send(socket, s, strlen(s), 0);
	if (result == -1) {
		fprintf(stderr, "%s: %s\n", "Error talking to the client", strerror(errno));
	}
	return result;
}

int main(int argc, char *argv[])
{
	if (catch_signal(SIGINT, handle_shutdown) == -1){
		error ("Can't set the interrupt handler"); //calls hanler shutdown if cltr_c is hit
	}
	listener_d = open_listener_socket();
	bind_to_port (listener_d, 30000); //creates a socket on port 30000

	if (listen(listener_d, 10) == -1) {
		error("can't listen");
	}
	struct sockaddr_storage client_addr;
	unsigned int address_size = sizeof(client_addr);
	puts("waiting for connection");

	char buf[255];

	while(1) {
		//Listening for the connectoion
		int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
		if (connect_d == -1){
			error("Can't open secondry spcket");
		}
		//send msgs to the client
		if (say(connect_d,
		"Testing client \r\n Version 1.0 \r\n send something: (should be who's there?)\r\n") != -1) {
			read_in(connect_d, buf, sizeof(buf));
			if (strncasecmp("Who's there?", buf, 12))
				say(connect_d, "You should say  'Who is there'?");
			else{
				if (say(connect_d, "Vesta \r\n ") != -1){
					read_in(connect_d, buf, sizeof(buf));
					if (strncasecmp("Vesta who?", buf, 10))
						say(connect_d, "You should say 'Vesta who?'! \r\n");
					else
						say(connect_d, "Finishing convo now\r\n");
				}
			}
		}

		close (connect_d);
	}
	return 0;
}
*/
