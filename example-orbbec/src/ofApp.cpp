#include "ofApp.h"
#include "ofConstants.h"
//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    cameraWidth = 640;
    cameraHeight = 480;
    

    settings.width 	= cameraWidth;
    settings.height = cameraHeight;
    settings.fps 	= 30;
    settings.doDepth = true;
    settings.doRawDepth = false;
    settings.doColor = true;
    settings.doIr = false;
    
    settings.depthPixelFormat = PIXEL_FORMAT_DEPTH_1_MM;
    settings.colorPixelFormat = PIXEL_FORMAT_RGB888;
    settings.irPixelFormat = PIXEL_FORMAT_GRAY16;
    settings.doRegisterDepthToColor = true;
    
    settings.useOniFile = false;
    settings.oniFilePath = "UNDEFINED";

    settings.doColorDoubleBuffering = true;
    settings.doDepthDoubleBuffering = false;
    settings.doIRDoubleBuffering = true;
    
	isReady = oniGrabber.setup(settings);

    int nearClip = 50;
    int farClip = 50;
	//oniGrabber.depthSource.setDepthClipping(nearClip,farClip); 



}

void ofApp::update()
{
	if (isReady)
	{
		oniGrabber.update();
    }

}

void ofApp::draw()
{


    ofPushMatrix();
    int offset = 0;
    if (oniGrabber.isColorAvailable())
    {
        oniGrabber.getRGBTextureReference().draw(offset, 0);
        offset+=cameraWidth;
    }
    
    if (oniGrabber.isDepthAvailable())
    {
        ofTranslate(offset, 0);
        oniGrabber.getDepthTextureReference().draw(0, 0);
        offset+=cameraWidth;
    }
    
    if (oniGrabber.isIRAvailable())
    {
        ofTranslate(offset, 0);
        oniGrabber.getIRTextureReference().draw(0, 0);
        offset+=cameraWidth;
    }
    ofPopMatrix();
    
    
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()) + " fps", 40, 40, ofColor(0, 0, 0, 128), ofColor::yellow);
}


void ofApp::exit()
{
    oniGrabber.close();
}

void ofApp::keyPressed(int key)
{

}
