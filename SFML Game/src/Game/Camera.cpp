#include "Camera.h"

Camera::Camera(sf::RenderTarget& target, const sf::Vector2f& position, const sf::Vector2f& size)
	: target{&target}, position{position}, size{size}, speed{1.0f} {
	this->view.setCenter(this->position);
	this->view.setSize(this->size);
	this->target->setView(this->view);
}
Camera::Camera(sf::RenderTarget& target, const sf::Vector2f& position)
	: target{&target}, position{position}, size{500.0f, 500.0f}, speed{1.0f} {
	this->view.setCenter(this->position);
	this->view.setSize(this->size);
	this->target->setView(this->view);
}
Camera::Camera(sf::RenderTarget& target) 
	: target{&target}, position{0.0f,0.0f}, size{500.0f, 500.0f}, speed{1.0f} {
	this->target->setView(this->view);
}
Camera::Camera(void) : target{nullptr}, position{0.0f,0.0f}, size{500.0f, 500.0f}, speed{1.0f} {
}
Camera::~Camera(void) {
}

void Camera::SetRenderTarget(sf::RenderTarget& target) {
	this->target = &target;
	this->target->setView(this->view);
}
void Camera::SetCameraPosition(const sf::Vector2f& position){
	this->position = position;
	this->view.setCenter(this->position);
}
void Camera::SetCameraSize(const sf::Vector2f& size){
	this->size = size;
	this->view.setSize(this->size);
}
void Camera::SetBounds(const float& upper, const float& lower)
{
	this->upperBounds = upper;
	this->lowerBounds = lower;
}
void Camera::MoveToTarget(const sf::Vector2f& target, const float& speed, const float& dt){
	
	this->position = view.getCenter();
	sf::Vector2f dist(target - this->position);
	sf::Vector2f moveDir(dist.x * speed * dt, 0.0f);

	//if (upperBounds > 0 && lowerBounds > 0)
	//	if (this->position.y - this->size.y / 2 > upperBounds&&
	//	this->position.y + this->size.y / 2 < lowerBounds) moveDir.y = dist.y * speed * dt;
	
	this->view.move(moveDir);
	this->target->setView(this->view);
}