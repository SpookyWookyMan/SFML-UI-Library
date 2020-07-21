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
void Camera::MoveToTarget(const sf::Vector2f& target, float& dt){
	
	this->position = view.getCenter();
	std::unique_ptr<sf::Vector2f> dist = std::make_unique<sf::Vector2f>(target.x - this->position.x, 0.0f);

	this->view.move(dist->x * dt, 0.0f);
	this->target->setView(this->view);
}