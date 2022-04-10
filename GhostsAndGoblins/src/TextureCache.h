#pragma once
#include <unordered_map>

class Texture;

class TextureCache final
{
public:
	TextureCache();

	enum class Spritesheet
	{
		Player, Stage
	};
	TextureCache& operator=(const TextureCache& other) = delete;
	TextureCache(const TextureCache& other) = delete;
	TextureCache(TextureCache&&) = delete;
	TextureCache& operator=(TextureCache&&) = delete;
	~TextureCache();

	Texture* GetTexture(Spritesheet spritesheet);

private:
	std::unordered_map<Spritesheet, Texture*> m_Spritesheets;
	std::unordered_map<Spritesheet, std::string> m_SheetLocations;
};

