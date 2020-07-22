#pragma once

#include <SFML/Graphics.hpp>
#include "../Entities/Player.h"
#include "../Resources/Map/Map.h"
#include "Camera.h"
#include "../UI/UI.h"

class Game 
{
private:

	sf::Clock deltaTimeClock;
	float deltaTime = 0.0f;

	bool paused;

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