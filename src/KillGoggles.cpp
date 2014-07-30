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




// create a rectangle around the face      
//rectangle(frame, face_i, CV_RGB(255, 255 ,255), 1);

// if good prediction : > threshold 
//if (predicted_confidence > _prediction_confidence) {
// sprintf(sTmp,"+ prediction ok = %s (%d) confiance = (%d)",people[prediction].c_str(),prediction,(int)predicted_confidence);
	
// display name of the guy on the picture
//    string box_text;
//    box_text = "Id=" + _names[prediction];
            
//    int pos_x = std::max(face_i.tl().x - 10, 0);
//    int pos_y = std::max(face_i.tl().y - 10, 0);			   
//    putText(gray, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255,255,255), 1.0);        		
//} else {		
// trace is commented to speed up
//sprintf(sTmp,"- prediction too low = %s (%d) confiance = (%d)",people[prediction].c_str(),prediction,(int)predicted_confidence);
//trace((string)(sTmp));
//}


