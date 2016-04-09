#pragma once

#include "ofMain.h"
#include "ofxOpenNI2Grabber.h"
#include "ofxOpenNI2Recorder.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    
    ofxOpenNI2Grabber oniGrabber;
    bool isReady;
    
    int cameraWidth;
    int cameraHeight;
    ofxOpenNI2GrabberSettings settings;
};