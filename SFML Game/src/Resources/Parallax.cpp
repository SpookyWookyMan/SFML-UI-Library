#include "Parallax.h"

void Parallax::Init(Player& player, sf::View& view) {
	
	this->player = player;

	//Further-most layers added first
	layers.push_back(Layer("Res/Textures/Parallax/glacial_mountains.png", view)); 

} 
void Parallax::Update(const float& dt, sf::View& view) {
	for (size_t i = 0; i < layers.size(); i++) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.canMoveLeft) {
			layers.at(i).deviation += this->speed * i * dt;
			this->canMove = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.canMoveRight) {
			layers.at(i).deviation -= this->speed * i * dt;
			this->canMove = true;
		}
		else this->canMove = false;

		if (canMove) layers.at(i).spr.move(deviation * dt, 0.0f);
		
		sf::Vector2f sprpos(layers.at(i).spr.getPosition());
		sf::Vector2f sprdim(layers.at(i).txtr.getSize().x * layers.at(i).spr.getScale().x,
			layers.at(i).txtr.getSize().y * layers.at(i).spr.getScale().y);

		if (sprpos.x + sprdim.x < view.getCenter().x + view.getSize().x / 2) {
			layers.at(i).mod++;
			layers.at(i).spr.setTextureRect({ 0, 0, static_cast<int>(layers.at(i).txtr.getSize().x * layers.at(i).mod),
													static_cast<int>(layers.at(i).txtr.getSize().y) });
		}
	}
}
void Parallax::Draw(sf::RenderTarget& target) {
	for (auto& i : this->layers) target.draw(i.spr);
}