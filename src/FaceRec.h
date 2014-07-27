#include <dirent.h>
#include <iostream>
#include <sstream>

#include <cv.h>
#include <highgui.h>

#include "ofMain.h"
#include "ofxCv.h"
#include "ObjectFinder.h"


class FaceRec {
public:
    char* _root;
    ofxCv::ObjectFinder _finder;
    
    FaceRec(char* root);
    void setup();
    void update(cv::Mat frame);
    int readFaces(char* root);
    ofxCv::ObjectFinder getFinder() { return _finder; };
};
