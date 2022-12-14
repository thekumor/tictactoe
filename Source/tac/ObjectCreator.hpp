#pragma once

#include "TextureManager.hpp"
#include "Button.hpp"
#include "Sprite.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <functional>

namespace tac {

	class ObjectCreator
	{
	public:
		ObjectCreator() = default;

		const std::vector<std::shared_ptr<Button>>& GetButtons();
		const std::vector<std::shared_ptr<Sprite>>& GetSprites();
		std::shared_ptr<Button> CreateButton(const sf::Vector2f& position, const std::string& texturePath, std::function<void()> onClick);
		std::shared_ptr<Sprite> CreateSprite(const sf::Vector2f& position, const std::string& texturePath);
		void Purge();

	private:
		TextureManager m_Manager;
		std::vector<std::shared_ptr<Button>> m_Buttons = {};
		std::vector<std::shared_ptr<Sprite>> m_Sprites = {};
	};

}