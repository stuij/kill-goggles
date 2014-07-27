#pragma once

#include "FaceRec.h"
#include "ofxCvPiCam.h"
#include "ofxPiTFT.h"


class KillGoggles : public ofBaseApp {
public:
    FaceRec target;
    ofxCvPiCam cam;
    cv::Mat frame;
    ofImage sunglasses;
    ofxPiTFT piTft;

    KillGoggles(char* faces_root);
    void setup();
    void update();
    void draw();
};
