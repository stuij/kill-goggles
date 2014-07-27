#include "KillGoggles.h"


int main(int argc, char** argv) {
    ofSetupOpenGL(640, 480, OF_WINDOW);
    ofRunApp(new KillGoggles(argv[1]));
}
