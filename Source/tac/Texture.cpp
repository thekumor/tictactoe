#include "Texture.h"

namespace tac {

	Texture::Texture(const std::string& path)
		: m_Path(path)
	{
		Load(path);
	}

	sf::Vector2u Texture::GetSize()
	{
		return m_Texture.getSize();
	}

	bool Texture::Load(const std::string& path)
	{
		m_Path = path;

		if (!m_Texture.loadFromFile(path))
		{
			// Nothing, maybe an error in the future
			return false;
		}

		return true;
	}

}