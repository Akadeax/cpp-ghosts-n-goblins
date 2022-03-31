#include "pch.h"

#include "TextureCache.h"
#include "Texture.h"

TextureCache::TextureCache()
{
	m_SheetLocations[Spritesheet::Player] = "resources/player.png";
}

TextureCache::~TextureCache()
{
	for (std::pair<Spritesheet, Texture*> const& item : m_Spritesheets)
	{
		delete item.second;
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
