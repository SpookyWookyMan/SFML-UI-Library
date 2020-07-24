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

	bool paused = false;

	void Init(void);
	void Events(void);
	void UpdateDeltaTime(void);
	void Update(void);
	void Draw(void);

public:

	enum class States
	{
		NORMAL,
		PAUSED,
		MENU
	} state;

	Game();
	~Game();

	void Run(void);
};