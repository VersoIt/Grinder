#include "SpriteManager.hpp"

namespace EngineComponents
{
	SpriteManager::SpriteManager(const std::string& path) : m_filePath{ path }
	{
		if (m_filePath != "")
		{
			m_texture.loadFromFile(path);
			m_sprite.setTexture(m_texture);
		}
	}
}