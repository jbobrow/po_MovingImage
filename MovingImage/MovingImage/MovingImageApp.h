/*	Created by Jonathan Bobrow on 11/5/12.
 *	Copyright 2012 __MyCompanyName__. All rights reserved.
 */

#include "poObject.h"
#include "MovingImage.h"
#include "poControlPanel.h"

class MovingImageApp : public poObject {
public:
	MovingImageApp();
	virtual ~MovingImageApp();
	
    virtual void update();
    
    virtual void draw();
	
    virtual void eventHandler(poEvent *event);
	
    virtual void messageHandler(const std::string &msg, const poDictionary& dict=poDictionary());
	
	MovingImage		*sprite;
	
	poControlPanel	*control;
};

