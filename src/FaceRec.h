#include <dirent.h>
#include <iostream>
#include <sstream>

class FaceRec {
public:
    char* _root;
    
    FaceRec(char* root);
    void setup();
    int readFaces(char* root);
};
