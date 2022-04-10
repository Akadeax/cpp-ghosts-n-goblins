#include "pch.h"

#include "TextureCache.h"
#include "Texture.h"

TextureCache::TextureCache()
{
	m_SheetLocations[Spritesheet::Player] = "resources/player.png";
	m_SheetLocations[Spritesheet::Stage] = "resources/stage.png";
}

TextureCache::~TextureCache()
{
	for (auto& spritesheet : m_Spritesheets)
	{
		delete spritesheet.second;
		spritesheet.second = nullptr;
	}
}

Texture* TextureCache::GetTexture(Spritesheet spritesheet)
{
	if (!m_Spritesheets.contains(spritesheet))
	{
		m_Spritesheets[spritesheet] = new Texture(m_SheetLocations[spritesheet]);
	}

	return m_Spritesheets[spritesheet];
}
