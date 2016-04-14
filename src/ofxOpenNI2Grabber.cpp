/*
 *  ofxOpenNI2Grabber.cpp
 *  OpenNI2AppExample
 *
 *  Created by jason van cleave on 2/28/13.
 *
 */

#include "ofxOpenNI2Grabber.h"


ofxOpenNI2Grabber::ofxOpenNI2Grabber()
{
	isReady = false;
    irAvailable = false;
    colorAvailable = false;
    depthAvailable = false;

}


bool ofxOpenNI2Grabber::setup(ofxOpenNI2GrabberSettings settings_, bool startImmediately /*default = true */)
{
    
	settings = settings_;
    settings.validate();
    
	Status status = STATUS_OK;

	status = OpenNI::initialize();
	if (status == STATUS_OK)
	{
		ofLogVerbose() << "initialize PASS";
		deviceController.setup(settings);
	}else 
	{
		ofLog(OF_LOG_ERROR, "initialize FAIL:\n%s\n", OpenNI::getExtendedError());
	}
	
	if (status == STATUS_OK)
	{
		ofLogVerbose() << "Device open PASS";
	}else 
	{
		ofLogError() << "Device open FAIL: " << OpenNI::getExtendedError();
		deviceController.close();
		return false;
	}
	
	if (settings.doDepth) 
	{
		depthSource.doDoubleBuffering = settings.doDepthDoubleBuffering;
        
        depthAvailable = depthSource.setup(deviceController);
		if (depthAvailable)
		{
			streams.push_back(&depthSource.videoStream);
		}else 
		{
			ofLogError() << "DEPTH SOURCE FAILED";
		}
	}
	
	if (settings.doColor) 
	{
        rgbSource.doDoubleBuffering = settings.doColorDoubleBuffering;

        colorAvailable = rgbSource.setup(deviceController);
		if (colorAvailable) 
		{
			streams.push_back(&rgbSource.videoStream);
		}else 
		{
			ofLogError() << "RGB SOURCE FAILED";
		}
	}
	if(settings.doIr)
    {
        irSource.doDoubleBuffering = settings.doIRDoubleBuffering;

        irAvailable = irSource.setup(deviceController);
		if(irAvailable)
		{
			streams.push_back(&irSource.videoStream);
		}
		else
        {
            ofLogError() << "IR SOURCE FAILED";
		}
	}
	
	if(settings.doRegisterDepthToColor)
	{
		if (depthAvailable && colorAvailable)
		{
			deviceController.registerDepthToColor();
		}
		
	}
	isReady = true;
    if (startImmediately) 
    {
        start();
    }
	return isReady;
}


void ofxOpenNI2Grabber::start()
{
    if (!isReady)
    {
        ofLogError() << "NOT READY, Calling setup for you";
        setup(settings);
    }
    if (!isThreadRunning()) 
    {
        startThread();
    }else
    {
        ofLogError() << "ALREADY RUNNING";
    }
    
}
void ofxOpenNI2Grabber::threadedFunction()
{
	while (isThreadRunning()) 
	{
		int changedIndex;
		Status status = OpenNI::waitForAnyStream(&streams[0], streams.size(), &changedIndex);
		if (status != STATUS_OK)
		{
			ofLogError() << "waitForAnyStream FAIL:" << OpenNI::getExtendedError();
		}
	}
}


ofVec3f ofxOpenNI2Grabber::convertDepthToWorld(int depthX, int depthY){	
	ofVec3f result;
	CoordinateConverter::convertDepthToWorld(depthSource.videoStream,
                                             depthX,
                                             depthY,
											 (DepthPixel)(depthSource.currentRawPixels->getPixels()[depthY * depthSource.width + depthX]),
											 &result.x,
                                             &result.y,
                                             &result.z );
	return result;
}

void ofxOpenNI2Grabber::update()
{
	if (rgbSource.isOn) rgbSource.update();
	if (irSource.isOn) irSource.update();
	if (depthSource.isOn) depthSource.update();
}

void ofxOpenNI2Grabber::draw()
{
	//lock();
	if (rgbSource.isOn) rgbSource.draw();
	if (irSource.isOn) irSource.draw();
	if (depthSource.isOn) depthSource.draw();
}

ofPixels* ofxOpenNI2Grabber::getDepthPixels()
{
    ofScopedLock(mutex);
	return depthSource.currentPixels;
}

ofShortPixels* ofxOpenNI2Grabber::getDepthRawPixels()
{
	ofScopedLock(mutex);
	return depthSource.currentRawPixels;
}

ofPixels* ofxOpenNI2Grabber::getRGBPixels()
{
	ofScopedLock(mutex);
	return rgbSource.currentPixels;
}

ofPixels* ofxOpenNI2Grabber::getIRPixels()
{
	ofScopedLock(mutex);
	return irSource.currentPixels;
}

int ofxOpenNI2Grabber::getDeviceMaxDepth()
{
    int result = 0;
    if (isDepthAvailable())
    {
        result = depthSource.deviceMaxDepth;
    }
    return result;
}

ofTexture& ofxOpenNI2Grabber::getDepthTextureReference()
{
	return depthSource.texture;
}

ofTexture& ofxOpenNI2Grabber::getRGBTextureReference()
{
	return rgbSource.texture;
}

ofTexture& ofxOpenNI2Grabber::getIRTextureReference()
{
	return irSource.texture;
}

ofxOpenNI2Grabber::~ofxOpenNI2Grabber()
{
    
    if (isReady) 
    {
        close();
    }
}

bool ofxOpenNI2Grabber::close()
{
	ofLogVerbose() << "ofxOpenNI2Grabber::close";
    waitForThread(true);
	isReady = false;
    
    irAvailable = false;
    colorAvailable = false;
    depthAvailable = false;

	if (depthSource.isOn) depthSource.close();
	if (rgbSource.isOn) rgbSource.close();
	if (irSource.isOn) irSource.close();
	deviceController.close();
	OpenNI::shutdown();
	
	return isReady;
	//
}



