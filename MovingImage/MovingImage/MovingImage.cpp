#include "MovingImage.h"
#include "poHelpers.h"


//--------------------------------------------------------------
MovingImage::MovingImage(std::string localDir, std::string prefix)
{
	bPlaying = false;
	bLoop = true;
	lastTimeMillis = 0;
	currentFrame = 0;
	
	loadImageSequence(localDir, prefix);
}


//--------------------------------------------------------------
MovingImage::~MovingImage()
{
}


//--------------------------------------------------------------
void MovingImage::update()
{
	if( bPlaying ){
				
		if(poGetElapsedTimeMillis() - lastTimeMillis > 1000/(float)frameRate ){
			
			currentFrame++;
			
			if( bLoop )
				currentFrame = currentFrame % frames.size();	// loop
			else if (currentFrame >= frames.size())
				currentFrame = frames.size() - 1;				// stay on last frame
			
			lastTimeMillis = poGetElapsedTimeMillis();
			
			this->placeTexture(frames[currentFrame], PO_TEX_FIT_EXACT);
			//printf("placing texture %i\n", currentFrame);
			
		}
	}
}


//--------------------------------------------------------------
void MovingImage::eventHandler(poEvent *event)
{
}


//--------------------------------------------------------------
void MovingImage::messageHandler(const std::string &msg, const poDictionary& dict)
{
}


//--------------------------------------------------------------
void MovingImage::loadImageSequence(std::string localDir, std::string prefix)
{
	frames.clear();
	
	//  look in folder
	//  count number of images with prefix
	//  load each of them consecutively
	//  if missing a number, just add a blank texture
	
	std::string filename;
	
	for ( boost::filesystem::recursive_directory_iterator end, dir(localDir); dir != end; ++dir ) {
		filename = dir->path().filename().string();
		
		// only load files with this prefix if there is a prefix
		if( prefix.compare("") == 0 || filename.compare(0, prefix.size(), prefix) == 0 ){
			std::string url = localDir + filename;
			frames.push_back(poGetTexture(url));
		}
	}
	
	reshape(frames[0]->getWidth(), frames[0]->getHeight());
	placeTexture(frames[0]);
}


//--------------------------------------------------------------
void MovingImage::play()
{
	bPlaying = true;
}


//--------------------------------------------------------------
void MovingImage::pause()
{
	bPlaying = false;
}


//--------------------------------------------------------------
void MovingImage::reset()
{
	currentFrame = 0;
	this->placeTexture(frames[currentFrame]);
}

//--------------------------------------------------------------
void MovingImage::stop()
{
	pause();
	reset();
	this->placeTexture(frames[currentFrame]);
}

//--------------------------------------------------------------
void MovingImage::stepForward()
{
	if( currentFrame == frames.size()-1 ) return;

	currentFrame++;
	this->placeTexture(frames[currentFrame]);
}


//--------------------------------------------------------------
void MovingImage::stepBackward()
{
	if( currentFrame == 0 ) return;
	
	currentFrame--;
	this->placeTexture(frames[currentFrame]);
}


//--------------------------------------------------------------
void MovingImage::goToFrame(int frame)
{
	if(frame >= 0 || frame < frames.size()){
		currentFrame = frame;
		this->placeTexture(frames[currentFrame]);
	}
	else
		printf("!!! frame %i doesn't exist !!!", frame);
}

//--------------------------------------------------------------
int MovingImage::getCurrentFrame()
{
	return currentFrame;
}

//--------------------------------------------------------------
void MovingImage::setFrameRate(int rate)
{
	frameRate = rate;
}


//--------------------------------------------------------------
int MovingImage::getFrameRate()
{
	return frameRate;
}

//--------------------------------------------------------------
void MovingImage::setLoop(bool b)
{
	bLoop = b;
}

//--------------------------------------------------------------
int MovingImage::getNumFrames()
{
	return frames.size();
}

//--------------------------------------------------------------
bool MovingImage::isPlaying()
{
	return bPlaying;
}