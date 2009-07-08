#ifndef OF_CV_HAAR_FINDER
#define OF_CV_HAAR_FINDER

/*
* ofxCvHaarFinder.h
*  Charlie Blobtracking faces test...
*  Equal ofContourFinder but using CvHaarClassifierCascade to detect faces, 
and BlobTracker to...tracking objects. -thanks to stefanix-
*  
*/


#include "ofMain.h"
#include "ofxCvMain.h"

#define  MAX_NUM_CONTOURS_TO_FIND   500  // alther this if you think you will
// be looking for more then this
// although we use a vector as output
// we currently cap the results to this amount

class ofxCvHaarFinder{

  public:
		
    vector<ofxCvBlob> blobs;
    
    
    ofxCvHaarFinder();
    ~ofxCvHaarFinder();
    void findHaarObjects( ofxCvGrayscaleImage& input,
                       int minArea, int maxArea,
                       int nConsidered);
    void draw( float x, float y );
    void setup(string haarFile);
    void setScaleHaar(float scaleHaar);

    
    
  protected:
  
    ofxCvGrayscaleImage  inputCopy;
    CvMemStorage*  contour_storage;
    CvMemStorage*  storage;
    CvMoments*  myMoments;

    int nFacesFound;
    float scaleHaar;
	CvSeq*  cvSeqFaces[MAX_NUM_CONTOURS_TO_FIND];
  
    CvHaarClassifierCascade* cascade;
    const char* cascade_name;
    
    void reset();  
    
};



#endif
