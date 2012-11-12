#pragma once

/*	Created by Jonathan Bobrow on 11/6/12.
 *	Copyright 2012 Potion. All rights reserved.
 *
 *	MovingImage
 *
 *	The moving image class is a simple image sequence that can be controlled
 *  Using images, you can play at a set framerate or control the frames on your own
 *	The image will loop by default
 *
 *	Currently uses the first texture loaded to set the size
 *
 *	TODO: add sizing options
 *
 */

#include "poShapeBasics2D.h"

class MovingImage : public poRectShape
{
public:
	MovingImage(std::string localDir, std::string prefix="");
	virtual ~MovingImage();
	
	virtual void update();
	virtual void eventHandler(poEvent *event);
	virtual void messageHandler(const std::string &msg, const poDictionary& dict=poDictionary());

	void	loadImageSequence(std::string localDir, std::string prefix="");
	
	void	play();
	void	pause();
	void	reset();
	void	stop();

	void	stepForward();
	void	stepBackward();
	void	goToFrame(int frame);
	int		getCurrentFrame();
	
	void	setFrameRate(int rate);
	int		getFrameRate();
	
	int		getNumFrames();
	
	void	setLoop(bool b);
	
	bool	isPlaying();

private:
	
	std::vector<poTexture *> frames;
	
	int		currentFrame;
	int		frameRate;
	int		lastTimeMillis;
	
	bool	bPlaying;
	bool	bLoop;
};