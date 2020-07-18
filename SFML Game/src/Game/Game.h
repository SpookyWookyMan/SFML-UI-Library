#pragma once

#include <SFML/Graphics.hpp>
#include "../Entities/Player.h"
#include "../Resources/Map/Map.h"

class Game 
{
private:

	//sf::RenderWindow* window;
	//sf::Event event;

	sf::Clock deltaTimeClock;
	float deltaTime;

	void Init(void);
	void Events(void);
	void UpdateDeltaTime(void);
	void Update(void);
	void Draw(void);

public:

	Game();
	~Game();

	void Run(void);
};