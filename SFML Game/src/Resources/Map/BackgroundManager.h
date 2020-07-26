#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class BackgroundManager 
{
public:

	sf::View view;

	std::vector<sf::Sprite> parallaxLayers;
	float speed = 0.00002f;

	void AddLayer(const char* path);

	void BuildBackground(const sf::View& view);
	void UpdateBackground(void);
	void DrawBackground(sf::RenderTarget& target);

private:

	std::vector<sf::Texture> parallaxTextures;
	std::vector<unsigned> multiplier;
	std::vector<float> offset;

	template<typename T>
	inline T& GetLast(std::vector<T>& vec) const;
};