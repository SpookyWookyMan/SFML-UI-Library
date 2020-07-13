#pragma once
#include <SFML/Graphics.hpp>

class Animation 
{
public:

	Animation(void);
	~Animation(void);

	const sf::Texture* GetCurrentFrame(void) const;

	void Update(const unsigned int& timeBetweenFrames);
	void AddFrame(sf::Texture* frame);

private:

	unsigned int frameCount;

	std::vector<sf::Texture*> frames;

	sf::Clock animationClock;
	sf::Time animationTimer;

};