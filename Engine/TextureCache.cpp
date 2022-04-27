#include "pch.h"

#include "TextureCache.h"
#include "Texture.h"

TextureCache::~TextureCache()
{
	UnloadAllTextures();
}

void TextureCache::LoadTexture(std::string name, std::string resourceLocation)
{
	if (m_Textures.count(name) == 1) return;

	m_Textures[name] = new Texture(resourceLocation);
}

Texture* TextureCache::GetTexture(std::string name)
{
	return m_Textures[name];
}

void TextureCache::UnloadAllTextures()
{
	for (auto&& pair : m_Textures)
	{
		delete pair.second;
	}
	m_Textures.clear();
}
