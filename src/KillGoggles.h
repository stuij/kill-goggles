#pragma once

#include <cv.h>
#include <highgui.h>

#include "FaceRec.h"
#include "ofMain.h"
#include "ofxCv.h"
#include "ofxCvPiCam.h"
#include "ofxPiTFT.h"


class KillGoggles : public ofBaseApp {
public:
    FaceRec target;
    ofxCvPiCam cam;
    ofxCv::ObjectFinder finder;
    cv::Mat frame;
    ofImage sunglasses;
    ofxPiTFT piTft;

    KillGoggles(char* faces_root);
    void setup();
    void update();
    void draw();
};
