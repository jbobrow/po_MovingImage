/*	Created by Jonathan Bobrow on 11/5/12.
 *	Copyright 2012 Potion. All rights reserved.
 * 
 *  Animated Sprite (Shifty)
 *	by James Patterson.
 *
 *	borrowed from the Processing Animation Sample
 *	repurposed to show simple image sequence demo of new MovingImage class for pocode
 */

#include "MovingImageApp.h"
#include "poApplication.h"
#include "poCamera.h"

// APP CONSTRUCTOR. Create all objects here.
MovingImageApp::MovingImageApp() {
	addModifier(new poCamera2D(poColor(.9,.9,.9)));
	
	sprite = new MovingImage("sprites/shifty/", "PT_Shifty");
	sprite->setFrameRate(30);
	sprite->position.set(100,100,0);
	addChild(sprite);
	
	control = new poControlPanel("controls", poColor( 0,.1,.1,.8 ), 9);
	control->addSliderI("framerate", 1, 60, this);
	control->addButton("play", this);
	control->addButton("pause", this);
	control->addButton("reset", this);
	control->addButton("stop", this);
	control->addButton("step forward", this);
	control->addButton("step backward", this);
	control->addToggle("loop", this);
	control->addSliderI("goto frame", 0, 36, this);
	
	addChild(control);
	
	addEvent(PO_KEY_DOWN_EVENT, this);
}

// APP DESTRUCTOR. Delete all objects here.
MovingImageApp::~MovingImageApp() {
}

// UPDATE. Called once per frame. Animate objects here.
void MovingImageApp::update() {
	control->setInt("goto frame", sprite->getCurrentFrame());
}

// DRAW. Called once per frame. Draw objects here.
void MovingImageApp::draw() {
	
}

// EVENT HANDLER. Called when events happen. Respond to events here.
void MovingImageApp::eventHandler(poEvent *event) {
	
	// because we all love pressing space bar to mean play/pause
	if( event->type == PO_KEY_DOWN_EVENT && event->keyChar == ' '){
		if(sprite->isPlaying())
			sprite->pause();
		else
			sprite->play();
	}
}

// MESSAGE HANDLER. Called from within the app. Use for message passing.
void MovingImageApp::messageHandler(const std::string &msg, const poDictionary& dict) {
	if( msg == "framerate"){
		sprite->setFrameRate(control->getInt("framerate"));
	}else if( msg == "play"){
		sprite->play();
	}else if( msg == "pause"){
		sprite->pause();
	}else if( msg == "reset"){
		sprite->reset();
	}else if( msg == "stop"){
		sprite->stop();
	}else if( msg == "step forward"){
		sprite->stepForward();
	}else if( msg == "step backward"){
		sprite->stepBackward();
	}else if( msg == "loop"){
		sprite->setLoop(control->getBool("loop"));
	}else if( msg == "goto frame"){
		sprite->goToFrame(control->getInt("goto frame"));
	}
}
