meta:
	ADDON_NAME = ofxOpenNI2Grabber
	ADDON_DESCRIPTION = Addon for interfacing with the openni2 library.
	ADDON_AUTHOR = @jvcleave
	ADDON_TAGS = "computer vision" "depth" "openni2"
	ADDON_URL = https://github.com/jvcleave/ofxOpenNI2Grabber

#DEPTH_DEVICE is set in config.make of project file (XTION or ORBBEC)
common:
    OPENNNI2_FOLDER = libs/$(DEPTH_DEVICE)/openni2
    ADDON_CFLAGS = -I$(OPENNNI2_FOLDER)/include 
    ADDON_LIBS = $(OPENNNI2_FOLDER)/libs/libOpenNI2.a 
    ADDON_LIBS += $(OPENNNI2_FOLDER)/libs/libXnLib.a
    ADDON_LIBS += $(OPENNNI2_FOLDER)/libs/libDepthUtils.a

    ADDON_CFLAGS += -Wno-deprecated-declarations -Wno-sign-compare -Wno-unknown-pragmas -Wno-unused-function -Wno-unused-but-set-variable
    ADDON_LDFLAGS= -Wl,-rpath=./libs
