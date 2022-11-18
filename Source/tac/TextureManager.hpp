#pragma once

#include "Texture.h"
#include <SFMl/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

namespace tac {

	class TextureManager
	{
	public:
		TextureManager() = default;

		std::shared_ptr<Texture> GetTexture(const std::string& title);
		std::vector<std::string> GetAllTextures();

	private:
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures = {};
	};

}