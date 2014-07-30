#include "FaceRec.h"

using namespace ofxCv;
using namespace cv;

Face::Face(ofRectangle rect, string name, int confidence)
    : _rect(rect),
      _name(name),
      _confidence(confidence)
{}

FaceRec::FaceRec(char* root)
    : _root(root),
      _prediction_confidence(4500),
      _haar("haarcascade_frontalface_alt2.xml") // lbpcascade_frontalface.xml
{}

void FaceRec::setup() {
    _finder.setup(_haar);
    _finder.setPreset(ObjectFinder::Fast);
    _finder.getTracker().setSmoothingRate(.3);
    _model = createEigenFaceRecognizer();
    trainFaces(_root);
}

void FaceRec::update(cv::Mat frame) {
    detectFaces(frame);
}

string getSuffix(string name) {
    return name.substr(name.find_last_of(".") + 1);
}


bool isPicture(string name) {
    return getSuffix(name) == "jpg" ||
        getSuffix(name) == "jpeg" ||
        getSuffix(name) == "png" ||
        getSuffix(name) == "gif" ||
        getSuffix(name) == "pgm";
}


void FaceRec::trainFaces(char* root) {
    
    struct dirent* thing;
    struct dirent* file;
    DIR* dir;
    unsigned char isFolder = 0x4;
    unsigned char isFile = 0x8;
    int label = -1;
    
    // read the current directory
    dir = opendir(root);
    if (dir==NULL) {
        printf ("Couldn't open picture dir.");
        exit (EXIT_FAILURE);
    };
    
    while ((thing = readdir(dir)) != NULL) {
        char* name = thing->d_name;
        if (thing->d_type == isFolder &&
            thing->d_name[0] != '.') {
            label++;
            _names.push_back(name);
            
            std::ostringstream fp_strm;
            fp_strm << root << name;
            std::string filepath = fp_strm.str();
            
            DIR* fdir = opendir(filepath.c_str());
            while ((file = readdir(fdir)) != NULL) {
                std::string fname = file->d_name;
                if (file->d_type == isFile &&
                    file->d_name[0] != '.') {
                    std::ostringstream name_path;
                    name_path << filepath << "/" << fname;
                    std::cout << "trying to load: " << name_path.str() << std::endl;
                    _labels.push_back(label);
                    Mat m = imread(name_path.str(), CV_LOAD_IMAGE_GRAYSCALE);
                    if (m.cols == 0) {
                        std::cout << "Error reading img " << name_path.str() << std::endl;
                        exit (EXIT_FAILURE);
                    }
                    _images.push_back(m);                }
            }
        }
    }
    
    // Get height, width of 1st image.
    // All images must have the same dimensions.
    _im_width = _images[0].cols;
    _im_height = _images[0].rows;
    
    // Create a FaceRecognizer and train it on the images:
    // this a Eigen model, but you could replace with Fisher model
    // (in that case the threshold value should be lower) (try)
    std::cout << "Training the model" << std::endl; 
    _model->train(_images, _labels);
}

void FaceRec::detectFaces (cv::Mat frame) {
    // find faces in frame
    _finder.update(frame);
    
    Mat face, face_resized;
    _faces.clear();

    // for each face found
    for(int i = 0; i < _finder.size(); i++) 
    {       
        // crop face
        ofRectangle ofFace = _finder.getObjectSmoothed(i);
        Rect face_img = toCv(ofFace);	
        face = frame(face_img);
        
        //  resize face
        cv::resize(face, face_resized, Size(_im_width, _im_height), 1.0, 1.0, CV_INTER_NN); // INTER_CUBIC);
	
        // predict who it is
        double predicted_confidence = 0.0;
        int prediction = -1;
        _model->predict(face_resized, prediction, predicted_confidence);

        cout << "recogniser person: " << prediction << "confidence: " << predicted_confidence << endl;
        
        Face face(ofFace, _names[prediction], predicted_confidence);
        _faces.push_back(face);
    }
}

int FaceRec::size() {
    return _faces.size();
}

Face FaceRec::getFace(int index) {
    return _faces[index];
}
