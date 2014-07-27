#include "FaceRec.h"

FaceRec::FaceRec(char* root)
    : _root(root) {}

void FaceRec::setup() {
    readFaces(_root);
}

int FaceRec::readFaces(char* root) {
    
    struct dirent* thing;
    struct dirent* file;
    DIR* dir;
    unsigned char isFolder =0x4;
    unsigned char isFile =0x8;
    
    // read the current directory
    dir = opendir(root);
    if (dir==NULL)
        return 0;

    while ((thing = readdir(dir)) != NULL) {
        char* name = thing->d_name;
        if (thing->d_type == isFolder &&
            thing->d_name[0] != '.') {
            
            std::ostringstream fp_strm;
            fp_strm << root << "/" << name;
            std::string filepath = fp_strm.str();
            
            DIR* fdir = opendir(filepath.c_str());
            while ((file = readdir(fdir)) != NULL) {
                if (file->d_type == isFile &&
                    file->d_name[0] != '.') {
                    
                    std::ostringstream oss;
                    oss << filepath << "/" << file->d_name << std::endl;
                    std::string var = oss.str();
                    std::cout << var;
                }
            }
        }
    }
    return 0;
}
    