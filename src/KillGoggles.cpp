#include "KillGoggles.h"

using namespace ofxCv;
using namespace cv;

KillGoggles::KillGoggles(char* faces_root)
    : target(faces_root) {}

void KillGoggles::setup() {
    ofSetVerticalSync(true);
    ofSetFrameRate(15);
    finder.setup("haarcascade_frontalface_alt2.xml");
    finder.setPreset(ObjectFinder::Fast);
    finder.getTracker().setSmoothingRate(.3);
    cam.setup(640, 480, false);
    sunglasses.loadImage("/root/sunglasses.png");
    ofEnableAlphaBlending();
    target.setup();
}

void KillGoggles::update() {
    frame = cam.grab();
    if(!frame.empty()) {
        finder.update(frame);
    }
}

void KillGoggles::draw() {
    if(!frame.empty()){
        drawMat(frame, 0, 0);

        for(int i = 0; i < finder.size(); i++) {
            ofRectangle object = finder.getObjectSmoothed(i);
            sunglasses.setAnchorPercent(.5, .5);
            float scaleAmount = .85 * object.width / sunglasses.getWidth();
            ofPushMatrix();
            ofTranslate(object.x + object.width / 2., object.y + object.height * .42);
            ofScale(scaleAmount, scaleAmount);
            sunglasses.draw(0, 0);
            ofPopMatrix();
            ofPushMatrix();
            ofTranslate(object.getPosition());
            ofDrawBitmapStringHighlight(ofToString(finder.getLabel(i)), 0, 0);
            ofLine(ofVec2f(), toOf(finder.getVelocity(i)) * 10);
            ofPopMatrix();
        }
    }
}
