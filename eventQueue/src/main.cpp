#include "ofMain.h"
#include "ofApp.h"


// main
//--------------------------------------------------------------------------------
int main()
{
	ofSetupOpenGL( 320, 240, OF_WINDOW );//setup the GL context
	ofRunApp( new ofApp() );// run ofApp
}
