#include "testApp.h"

extern "C" {
#include "macGlutfix.h"
}

//--------------------------------------------------------------
void testApp::setup(){
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(CAPTUREWIDTH, CAPTUREHEIGHT);
	
    colorImg.allocate(CAPTUREWIDTH, CAPTUREHEIGHT);
	grayImage.allocate(CAPTUREWIDTH, CAPTUREHEIGHT);
	grayBg.allocate(CAPTUREWIDTH, CAPTUREHEIGHT);
	grayDiff.allocate(CAPTUREWIDTH, CAPTUREHEIGHT);
	bLearnBakground = true;
	threshold = 80;
	
	//lets load in our face xml file
	haarFinder.setup("haarXML/haarcascade_frontalface_default.xml");
	
	faceImage.allocate(SELF_EXT_SCREEN_WIDTH, SELF_EXT_SCREEN_HEIGHT);
	
	scaleStyle = CV_INTER_NN;
}

//--------------------------------------------------------------
void testApp::update(){
	MacGLUTFix(true);
	ofBackground(0,0,0);
    
    bool bNewFrame = false;
	
	vidGrabber.grabFrame();
	bNewFrame = vidGrabber.isFrameNew();
	
	if (bNewFrame){
		
        colorImg.setFromPixels(vidGrabber.getPixels(), CAPTUREWIDTH,CAPTUREWIDTH);
		
        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}
		
		haarFinder.findHaarObjects(grayImage, 100, 99999999, 1);
	}
	
	//cout << "Width and height are: " << ofGetWidth() << ", " << ofGetHeight() << endl;
}

//--------------------------------------------------------------
void testApp::draw(){
	
	// uncomment if you want to test a fullscreen mac, crash....
//	 if (ofGetFrameNum() > 40){
//	 int * temp = new int [100];
//	 for (int i = 0; i < 200; i++){
//	 temp[i] = (int)ofRandom(0,100);	
//	 }
//	 }
	
	
	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetColor(0xffffff);
	colorImg.draw(20,20);	
	grayImage.draw(360,20);
	grayBg.draw(20,280);
	grayDiff.draw(360,280);
	
	haarFinder.draw(20, 20);	
	
	int numFace = haarFinder.blobs.size();
	
//	glPushMatrix();
//	
//	glTranslatef(20, 20, 0);
	
	float biggestAreaSoFar = 0.f;
	float indexOfFaceWithBiggestArea = 0;
	bool foundFace = false;
	
	for(int i = 0; i < numFace; i++){
		foundFace = true;
		float x = haarFinder.blobs[i].boundingRect.x;
		float y = haarFinder.blobs[i].boundingRect.y;
		float w = haarFinder.blobs[i].boundingRect.width;
		float h = haarFinder.blobs[i].boundingRect.height;
		
		float cx = haarFinder.blobs[i].centroid.x;
		float cy = haarFinder.blobs[i].centroid.y;
		
		float newArea = w*h;
		
		if(newArea > biggestAreaSoFar)
		{
			//then the face is bigger, so its the new good one  //CHANGE DONT NEED TO DO THIS AS FIRST ONE IS ALWAYS BIGGEST FACE
			biggestAreaSoFar = newArea;
			
			indexOfFaceWithBiggestArea = i;
		}
	}
	
	ofSetColor(0xFFFFFF);	
	
	faceImage.clear(); 
	faceImage.allocate(SELF_EXT_SCREEN_WIDTH, SELF_EXT_SCREEN_HEIGHT);
	
	if(foundFace)// && biggestAreaSoFar > 1000.f)
	{
		//if there is a face found, and it's area is bigger than the required minimum, then grab the screen DO AREA IN A BIT
//		float x = haarFinder.blobs[indexOfFaceWithBiggestArea].boundingRect.x;
//		float y = haarFinder.blobs[indexOfFaceWithBiggestArea].boundingRect.y;
//		float w = haarFinder.blobs[indexOfFaceWithBiggestArea].boundingRect.width;
//		float h = haarFinder.blobs[indexOfFaceWithBiggestArea].boundingRect.height;
		
		//pureOFFaceImageLazy.grabScreen(x+20,y+20,w,h*1.2); //taking account of gl translate
		//grabPixelsIntoImage(&pureOFFaceImageLazy, &colorImg, x,y,w,h);
		
		newRect = haarFinder.blobs[indexOfFaceWithBiggestArea].boundingRect;
		
		float tweenAmount = 0.7f;
		
		averageRect.x = (tweenAmount * averageRect.x) + ((1.f-tweenAmount) * newRect.x);
		averageRect.y = (tweenAmount * averageRect.y) + ((1.f-tweenAmount) * newRect.y);
		averageRect.width = (tweenAmount * averageRect.width) + ((1.f-tweenAmount) * newRect.width);
		averageRect.height = (tweenAmount * averageRect.height) + ((1.f-tweenAmount) * newRect.height);		
		
		colorImg.setROI(averageRect);
	
		oldRect = newRect;
	}else{
		//draw the full camera to temptpeople in?
		colorImg.resetROI();
		
	}
	
	faceImage.scaleIntoMe(colorImg, scaleStyle);

	/*
	 //for interpolation you can pass in:
	 //CV_INTER_NN - nearest-neigbor interpolation,
	 //CV_INTER_LINEAR - bilinear interpolation (used by default)
	 //CV_INTER_AREA - resampling using pixel area relation. It is preferred method 
	 //                for image decimation that gives moire-free results. In case of 
	 //                zooming it is similar to CV_INTER_NN method.
	 //CV_INTER_CUBIC - bicubic interpolation.
	 */
	
	colorImg.resetROI();
	faceImage.draw(SELF_GUI_SCREEN_WIDTH,0); //so it draws full screen on ext screen	
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	switch (key){
		case '1':{
			scaleStyle = CV_INTER_NN;
			break;
		}
		case '2':{
			scaleStyle = CV_INTER_LINEAR;
			break;
		}
		case '3':{
			scaleStyle = CV_INTER_AREA;
			break;
		}
		case '4':{
			scaleStyle = CV_INTER_CUBIC;
			break;
		}
		case ' ':{
			bLearnBakground = true;
			break;
		}
		case '+':{
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;			
		}
		case '-':{
			threshold --;
			if (threshold < 0) threshold = 0;
			break;			
		}
		case 's':{
			vidGrabber.videoSettings();
			break;			
		}
		case 'f':{
			ofToggleFullscreen();
			break;			
		}

	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

void testApp::grabPixelsIntoImage(ofImage* grabIntoThis, ofxCvColorImage* grabFromThis, float x, float y, float w, float h)
{
	int subX = x;
	int subY = y;
	int subWidth = w;
	int subHeight = h;
	
	grabIntoThis->resize(subWidth, subHeight);
	
	unsigned char subRegion[ subWidth * subHeight * 3  ];  // R G B 
	unsigned char * fromPixels = grabFromThis->getPixels(); //get the pointer to the pixel array
	
	for (int i = 0; i < subWidth; i++){ 
		for (int j = 0; j < subHeight; j++){ 
			int mainPixelPos = ((j+subY) * grabFromThis->width + (i+subX)) * 3; //check the logic of this! 
			int subPixlPos = (j * subWidth + i) * 3; 
			subRegion[subPixlPos] = fromPixels[mainPixelPos];   // R 
			subRegion[subPixlPos + 1] = fromPixels[mainPixelPos + 1];  // G 
			subRegion[subPixlPos + 2] = fromPixels[mainPixelPos + 2];  // B 
		} 
	}
	
	grabIntoThis->setFromPixels(subRegion, subWidth, subHeight, OF_IMAGE_COLOR, TRUE); //set it from our new pixel array it is RGB order
}
