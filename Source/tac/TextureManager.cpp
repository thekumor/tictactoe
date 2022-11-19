#include "TextureManager.hpp"

namespace tac {

    std::shared_ptr<Texture> TextureManager::GetTexture(const std::string& title)
    {
        if (m_Textures.find(title) == m_Textures.end())
        {
            m_Textures[title] = std::make_shared<Texture>();
            auto& texture = m_Textures[title];
            if (!texture->Load(title))
            {
                m_Textures.erase(title);
                return nullptr;
            }

            return texture;
        }

        return m_Textures[title];
    }

    std::vector<std::string> TextureManager::GetAllTextures()
    {
        std::vector<std::string> paths = {};

        for (auto&[path, texture] : m_Textures)
        {
            paths.emplace_back(path);
        }

        return paths;
    }

}