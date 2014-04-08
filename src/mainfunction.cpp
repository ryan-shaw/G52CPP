#include "header.h"

#include "templates.h"

// Needs one of the following #includes, to include the class definition
#include "PongMain.h"

#define BASE_SCREEN_WIDTH 800
#define BASE_SCREEN_HEIGHT 600



int main(int argc, char *argv[])
{
	int iResult;

	PongMain oMain;

	iResult = oMain.Initialise( "Pong - Ryan Shaw", BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT, "Cornerstone Regular.ttf", 24 );
	iResult = oMain.MainLoop();
	oMain.Deinitialise();

	return iResult;
}
