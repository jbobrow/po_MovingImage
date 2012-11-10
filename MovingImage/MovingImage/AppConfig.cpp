/////////////////////////////////////////
//
// pocode application configuration
//
/////////////////////////////////////////


#include "poApplication.h"
#include "MovingImageApp.h"
#include "poHelpers.h"

poObject *createObjectForID(uint uid) {
	return new MovingImageApp();
}

void setupApplication() {
	lookUpAndSetPath("resources");
	applicationCreateWindow(0, WINDOW_TYPE_NORMAL, "MovingImage", 100, 100, 600, 400);
}

void cleanupApplication() {
}