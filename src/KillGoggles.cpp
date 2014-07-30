#include "KillGoggles.h"

using namespace ofxCv;
using namespace cv;

KillGoggles::KillGoggles(char* faces_root)
    : target(faces_root) {}

void KillGoggles::setup() {
    ofSetVerticalSync(true);
    ofSetFrameRate(15);
    cam.setup(640, 480, false);
    sunglasses.loadImage("/root/sunglasses.png");
    ofEnableAlphaBlending();
    target.setup();
}

void KillGoggles::update() {
    frame = cam.grab();
    if(!frame.empty()) {
        target.update(frame);
    }
}

void KillGoggles::draw() {
    if(!frame.empty()){
        int _prediction_confidence = 4500;
        
        drawMat(frame, 0, 0);

        ofPushStyle();
        ofNoFill();
        
        for(int i = 0; i < target.size(); i++) {
            Face face = target.getFace(i);

            ofRect(face._rect);
            
        }
        ofPopStyle();
    }
}
