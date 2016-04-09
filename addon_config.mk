meta:
	ADDON_NAME = ofxOpenNI2Grabber
	ADDON_DESCRIPTION = Addon for interfacing with the openni2 library.
	ADDON_AUTHOR = @jvcleave
	ADDON_TAGS = "computer vision" "depth" "openni2"
	ADDON_URL = https://github.com/jvcleave/ofxOpenNI2Grabber

common:
    ADDON_CFLAGS = -Ilibs/openni2/include 
    ADDON_CFLAGS += -Wno-deprecated-declarations -Wno-sign-compare -Wno-unknown-pragmas -Wno-unused-function -Wno-unused-but-set-variable
    ADDON_LDFLAGS= -Wl,-rpath=./libs
    ADDON_LIBS = libs/openni2/libs/rpi/libOpenNI2.a 
    ADDON_LIBS += libs/openni2/libs/rpi/libXnLib.a
