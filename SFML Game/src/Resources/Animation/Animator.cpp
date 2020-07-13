#include "Animator.h"

Animator::Animator(void)
{
}
Animator::~Animator(void)
{
}

const void Animator::AddAnimation(const std::string& name, Animation* anim)
{
	animations.insert(std::make_pair(name, anim));
}
Animation* Animator::GetAnimation(const std::string& name) const
{
	return animations.at(name);
}

void Animator::Init(void) 
{

}
void Animator::Update(void)
{

}