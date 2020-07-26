#include "BackgroundManager.h"

void BackgroundManager::AddLayer(const char* path){
	sf::Texture* texture = new sf::Texture;
	if(!texture->loadFromFile(path))std::cout<<"Failed to load layer texture.\n";
	texture->setRepeated(true);

	this->multiplier.push_back(1);
	this->offset.push_back(0.0f);

	this->parallaxTextures.push_back(*texture);
	this->parallaxLayers.push_back(sf::Sprite(this->GetLast<sf::Texture>(this->parallaxTextures)));
	this->GetLast<sf::Sprite>(this->parallaxLayers).setTextureRect({0, 0, 
		static_cast<int>(texture->getSize().x), static_cast<int>(texture->getSize().y) });
}
void BackgroundManager::BuildBackground(const sf::View& view) {
	this->view = view;

	this->AddLayer("Res/Textures/Parallax/clouds_mg_1.png");
	this->AddLayer("Res/Textures/Parallax/clouds_mg_2.png");
	this->AddLayer("Res/Textures/Parallax/clouds_mg_3.png");
	this->AddLayer("Res/Textures/Parallax/glacial_mountains.png");
	this->AddLayer("Res/Textures/Parallax/clouds_bg.png");
	this->AddLayer("Res/Textures/Parallax/cloud_lonely.png");

	for(auto& i : this->parallaxLayers) {
		sf::Vector2f size(i.getTexture()->getSize().x * i.getScale().x,
						  i.getTexture()->getSize().y * i.getScale().y);

		i.setOrigin(0, size.y);
		i.setPosition(this->view.getCenter().x - this->view.getSize().x / 2,
			          this->view.getCenter().y + this->view.getSize().y / 2);

		float sclx = this->view.getSize().x / size.x;
		float scly = this->view.getSize().y / size.y;

		i.setScale({sclx, scly});
	}
}
void BackgroundManager::UpdateBackground(void) {
	for (size_t i = 0; i < parallaxLayers.size(); i++) {

		sf::Vector2f vpos(this->view.getCenter().x, this->view.getCenter().y);
		sf::Vector2f vsize(this->view.getSize().x, this->view.getSize().y);

		offset[i] += this->speed / i > 0 ? i : 1;

		sf::Vector2f sprpos(vpos.x - vsize.x / 2, vpos.y + vsize.y / 2);
		parallaxLayers.at(i).setPosition({ sprpos.x - 1, sprpos.y });
		
		float sprposx = parallaxLayers[i].getPosition().x;
		float sprwidth = parallaxLayers[i].getTexture()->getSize().x *
			parallaxLayers[i].getScale().x;

		if(sprposx + sprwidth < vpos.x + vsize.x / 2) this->multiplier[i]++;
		this->parallaxLayers[i].setTextureRect (
			{ 0, 0, static_cast<int>(this->parallaxLayers[i].getTexture()->getSize().x),
			static_cast<int>(this->parallaxLayers[i].getTexture()->getSize().y) } );
	}
}
void BackgroundManager::DrawBackground(sf::RenderTarget& target) {
	for(size_t i = this->parallaxLayers.size(); i > 0; i--) {
		target.draw(this->parallaxLayers[i - 1]);
	}
}
template<typename T>
inline T& BackgroundManager::GetLast(std::vector<T>& vec) const {
	return vec.at(vec.size() - 1);
}
