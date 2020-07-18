#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

class ResourceManager 
{
private:

	std::string mainFolder;
	std::string textureFolder;
	std::string fontFolder;

	std::unordered_map<std::string, sf::Texture> textures;
	std::unordered_map<std::string, sf::Font> fonts;

	sf::Texture defaultTexture;
	sf::Font defaultFont;

	bool textureExists(const std::string& name) const;
	bool fontExists(const std::string& name) const;

public:

	ResourceManager(const std::string& mainFolder);
	~ResourceManager(void);

	void SetTexturePath(const std::string& path);
	void SetFontPath(const std::string& path);

	void AddTexture(const std::string& name, const std::string& extension);
	void AddFont(const std::string& name);
	
	const sf::Texture& GetTexture(const std::string& name) const;
	const sf::Font& GetFont(const std::string& name) const;

	void Init(void);

} __declspec(selectany) resourceManager("Res");