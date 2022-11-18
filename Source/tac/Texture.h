#pragma once

#include <SFMl/Graphics.hpp>
#include <string>

namespace tac {

	class Texture
	{
	public:
		friend class Sprite;

		Texture(const std::string& path);
		Texture() = default;

		bool Load(const std::string& path);

	private:
		sf::Texture m_Texture;
		std::string m_Path = "";
	};

}