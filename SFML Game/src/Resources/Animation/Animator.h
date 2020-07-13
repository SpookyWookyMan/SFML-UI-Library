#pragma once

#include "Animation.h"
#include <unordered_map>

class Animator
{
public:

	std::unordered_map<std::string, Animation*> animations;

	Animator(void);
	~Animator(void);

	const void AddAnimation(const std::string& name, Animation* anim);
	Animation* GetAnimation(const std::string& name) const;

	void Init(void);
	void Update(void);

};