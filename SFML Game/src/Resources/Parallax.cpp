#include "Parallax.h"

void Parallax::Init(sf::View& view) {
	
	this->textures.push_back(sf::Texture());
	GetLast<sf::Texture>(this->textures).loadFromFile("Res/Textures/Parallax/cloud_lonely.png");

	this->textures.push_back(sf::Texture());
	GetLast<sf::Texture>(this->textures).loadFromFile("Res/Textures/Parallax/clouds_bg.png");

	this->textures.push_back(sf::Texture());
	GetLast<sf::Texture>(this->textures).loadFromFile("Res/Textures/Parallax/glacial_mountains.png");

	this->textures.push_back(sf::Texture());
	GetLast<sf::Texture>(this->textures).loadFromFile("Res/Textures/Parallax/clouds_mg_3.png");

	this->textures.push_back(sf::Texture());
	GetLast<sf::Texture>(this->textures).loadFromFile("Res/Textures/Parallax/clouds_mg_2.png");

	this->textures.push_back(sf::Texture());
	GetLast<sf::Texture>(this->textures).loadFromFile("Res/Textures/Parallax/clouds_mg_1.png");

	layers.push_back(Layer(this->textures.at(0), view));
	layers.push_back(Layer(this->textures.at(1), view));
	layers.push_back(Layer(this->textures.at(2), view)); 
	layers.push_back(Layer(this->textures.at(3), view));
	layers.push_back(Layer(this->textures.at(4), view));
	layers.push_back(Layer(this->textures.at(5), view));
} 
void Parallax::Update(const float& dt, sf::View& view, Player& player) {
	for (size_t i = 0; i < layers.size(); i++) {

		layers.at(i).speed = 1.8f * (i < 3 ? i / (3 - i) : i * 4);

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			&& player.canMoveLeft) {
			layers.at(i).deviation += layers.at(i).speed * dt;
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) 
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			&& player.canMoveRight) {
			layers.at(i).deviation -= layers.at(i).speed * dt;
		}

		sf::Vector2f pos(view.getCenter().x - view.getSize().x, view.getCenter().y + view.getSize().y / 2);
		layers.at(i).spr.setPosition(pos.x + layers.at(i).deviation, pos.y);

		sf::Vector2f sprpos(layers.at(i).spr.getPosition());
		sf::Vector2f sprdim(this->textures.at(i).getSize().x * layers.at(i).spr.getScale().x,
			this->textures.at(i).getSize().y * layers.at(i).spr.getScale().y);

		if (sprpos.x + sprdim.x < view.getCenter().x + view.getSize().x / 2) {
			layers.at(i).mod++;
			layers.at(i).spr.setTextureRect({ 0, 0, static_cast<int>(this->textures.at(i).getSize().x * layers.at(i).mod),
													static_cast<int>(this->textures.at(i).getSize().y) });
		}
	}
}
void Parallax::Draw(sf::RenderTarget& target) {
	for (auto& i : this->layers) target.draw(i.spr);
}
template<typename T>
inline T& Parallax::GetLast(std::vector<T>& vec) const
{
	return vec.at(vec.size() - 1);
}
