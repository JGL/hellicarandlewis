#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "ofxOpenCv.h"

//this is not part of the addon yet
//so include it seperately
#include "ofxCvHaarFinder.h"

#define CAPTUREWIDTH 320	
#define CAPTUREHEIGHT 240

#define SELF_GUI_SCREEN_WIDTH 1024	//the internal gui width
#define SELF_GUI_SCREEN_HEIGHT 768	//the internal gui height

#define SELF_EXT_SCREEN_WIDTH 720	//the external plasma
#define SELF_EXT_SCREEN_HEIGHT 1280	//

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		ofVideoGrabber 		vidGrabber;
		
		ofxCvColorImage			colorImg;
		
		ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;
		
		ofxCvContourFinder		contourFinder;
		ofxCvHaarFinder			haarFinder;
		
		int						threshold;
		bool					bLearnBakground;
		
		ofxCvColorImage			faceImage;
	
	int scaleStyle;
	
	ofRectangle averageRect;
	ofRectangle oldRect;
	ofRectangle newRect;

private:
	
	void grabPixelsIntoImage(ofImage* grabIntoThis, ofxCvColorImage* grabFromThis, 	float x, float y, float w, float h);
	
};

#endif
