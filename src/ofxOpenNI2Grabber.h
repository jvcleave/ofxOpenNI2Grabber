#pragma once

/*
 *  ofxOpenNI2Grabber.h
 *
 *  Created by jason van cleave on 2/28/13.
 *
 */
#include "ofMain.h"
#include "OpenNI.h"
#include "ofxOpenNI2GrabberSettings.h"
#include "DeviceController.h"

#include "RGBSource.h"
#include "DepthSource.h"
#include "IRSource.h"

using namespace openni;

class ofxOpenNI2Grabber: 
public ofThread
{
public:

	ofxOpenNI2Grabber();
    ~ofxOpenNI2Grabber();
	bool setup(ofxOpenNI2GrabberSettings, bool startImmediately = true);
    void start();
	void readFrame();
	void update();
	void draw();
	bool close();
	
	RGBSource rgbSource;
	IRSource irSource;
	DepthSource depthSource;
	DeviceController deviceController;
	
	vector<VideoStream*> streams;

	bool isReady;
	
	ofxOpenNI2GrabberSettings 			settings;
	
	
	ofVec3f convertDepthToWorld(int depthX, int depthY);
	
	ofPixels&       getDepthPixels();
	ofShortPixels&  getDepthRawPixels();
	ofPixels&       getRGBPixels();
	ofPixels&       getIRPixels();
	
	ofTexture& getDepthTextureReference();
	ofTexture& getRGBTextureReference();
	ofTexture& getIRTextureReference();
	

    bool isColorAvailable()
    {
        return colorAvailable;
    }
    bool isDepthAvailable()
    {
        return depthAvailable;
    }
    bool isIRAvailable()
    {
        return irAvailable;
    }
   
    
protected:
	void threadedFunction();
    bool irAvailable;
    bool colorAvailable;
    bool depthAvailable;
};