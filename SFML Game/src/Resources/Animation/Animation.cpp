#include "Animation.h"

Animation::Animation(void) {
}
Animation::~Animation(void) {
}
void Animation::Update(const unsigned int& timeBetweenFrames) {
	this->animationTimer = this->animationClock.getElapsedTime();

	if (this->animationTimer.asMilliseconds() >= timeBetweenFrames
		&& timeBetweenFrames > 0) {
		if (this->frameCount < this->frames.size() - 1) frameCount++;
		else frameCount = 0;

		this->animationClock.restart();
	}
}
void Animation::AddFrame(sf::Texture* frame) {
	this->frames.push_back(frame);
}
const sf::Texture* Animation::GetCurrentFrame(void) const {
	return frames[frameCount];
}