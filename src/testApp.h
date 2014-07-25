#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxCvPiCam.h"
#include "ofxPiTFT.h"

class testApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
	
    ofxCvPiCam cam;
    cv::Mat frame;
    ofxCv::ObjectFinder finder;
    ofImage sunglasses;

    ofxPiTFT piTft;
};
