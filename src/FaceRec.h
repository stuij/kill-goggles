#include <dirent.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "regex.h"

#include <cv.h>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/contrib/contrib.hpp>
#include "ofMain.h"
#include "ofxCv.h"
// #include "/home/zeno/pi/pi-root/opt/libfacerec/include/facerec.hpp"

class Face {
public:
    ofRectangle _rect;
    string _name;
    int _confidence;

    Face(ofRectangle rect, string name, int confidence);
};

class FaceRec {

public:
    int size();
    Face getFace(int index);    
    void setup();
    void update(cv::Mat frame);
    FaceRec(char* root);
    
private:
    char* _root;
    ofxCv::ObjectFinder _finder;
    vector<cv::Mat> _images;
    vector<int> _labels;
    vector<string> _names;
    int _prediction_confidence;
    cv::Ptr<cv::FaceRecognizer> _model;
    string _haar;
    int _im_width;		// image width
    int _im_height;		// image height
    vector<Face> _faces;
    
    void getImg(const string& name_path, const string& name);
    void trainFaces(char* root);
    void detectFaces(cv::Mat frame);
};

