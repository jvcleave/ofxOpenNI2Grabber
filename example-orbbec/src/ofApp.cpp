#include "ofApp.h"
#include "ofConstants.h"
//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    cameraWidth = 320;
    cameraHeight = 240;
    

    settings.width 	= cameraWidth;
    settings.height = cameraHeight;
    settings.fps 	= 30;
    settings.doDepth = true;
    settings.doRawDepth = true;
    settings.doColor = false;
    settings.doIr = false;
    
    settings.depthPixelFormat = PIXEL_FORMAT_DEPTH_1_MM;
    settings.colorPixelFormat = PIXEL_FORMAT_RGB888;
    settings.irPixelFormat = PIXEL_FORMAT_GRAY16;
    settings.doRegisterDepthToColor = true;
    
    settings.useOniFile = false;
    settings.oniFilePath = "UNDEFINED";


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
    if (settings.doColor)
    {
        oniGrabber.getRGBTextureReference().draw(0, 0);
    }
    
    if (settings.doDepth)
    {
        ofTranslate(cameraWidth, 0);
        oniGrabber.getDepthTextureReference().draw(0, 0);
    }
    
    if (settings.doIr)
    {
        ofTranslate(cameraWidth, 0);
        oniGrabber.getIRTextureReference().draw(0, 0);
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
