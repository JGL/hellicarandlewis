#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"





//========================================================================
int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, SELF_GUI_SCREEN_WIDTH+SELF_EXT_SCREEN_WIDTH,SELF_GUI_SCREEN_HEIGHT+SELF_EXT_SCREEN_HEIGHT, OF_WINDOW);			// <-------- setup the GL context

	
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
