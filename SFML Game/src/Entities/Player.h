#pragma once

#include "Object.h"

class Player : public Object 
{
public:

	Player(void);
	~Player(void);

	void Init(void);
	void Events(void);
	//void Update(void) override;
	//void Draw(void) override;

};