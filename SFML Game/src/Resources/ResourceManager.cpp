#include "ResourceManager.h"

ResourceManager::ResourceManager(const std::string& mainFolder) 
	: mainFolder{mainFolder} {
}
ResourceManager::~ResourceManager(void) 
{
}

void ResourceManager::SetTexturePath(const std::string& path) {
	this->textureFolder = path;
}
void ResourceManager::SetFontPath(const std::string& path) {
	this->fontFolder = path;
}
bool ResourceManager::textureExists(const std::string& name) const {
	return this->textures.find(name) != this->textures.end();
}
bool ResourceManager::fontExists(const std::string& name) const {
	return this->fonts.find(name) != this->fonts.end();
}
void ResourceManager::AddTexture(const std::string& name, const std::string& extension) {
	std::unique_ptr<sf::Texture> texture(new sf::Texture());

	if (texture->loadFromFile(this->mainFolder + '\\' + this->textureFolder + name + extension)) {
		this->textures.insert(std::make_pair(name, *texture));
	}
	else {
		std::unique_ptr<sf::Texture> d_texture(new sf::Texture());
		d_texture->loadFromFile(mainFolder + '\\' + textureFolder + "default.jpg");
		
		textures.insert(std::make_pair(name, *d_texture));
	}
}
void ResourceManager::AddFont(const std::string& name) {
	std::unique_ptr<sf::Font> font(new sf::Font());

	if (font->loadFromFile(this->mainFolder + '\\' + this->fontFolder + name + ".tff")) {
		this->fonts.insert(std::make_pair(name, *font));
	}
	else {
		std::unique_ptr<sf::Texture> d_texture(new sf::Texture());
		d_texture->loadFromFile(this->mainFolder + '\\' + this->textureFolder + "default.jpg");
		
		this->textures.insert(std::make_pair(name, *d_texture));
	}
}
const sf::Texture& ResourceManager::GetTexture(const std::string& name) const {
	if (!this->textureExists(name)) {
		return this->defaultTexture;
	}

	return this->textures.at(name);
}
const sf::Font& ResourceManager::GetFont(const std::string& name) const {
	if (!this->fontExists(name)) {
		return this->defaultFont;
	}

	return this->fonts.at(name);
}
void ResourceManager::Init(void) {
}