#pragma once

#include "Texture.h"
#include <SFMl/Graphics.hpp>
#include <memory>

namespace tac {

	class Sprite
	{
	public:
		Sprite(const sf::Vector2f& position, std::shared_ptr<Texture> texture);
		Sprite() = default;

		void SetPosition(const sf::Vector2f& position);
		void SetTexture(std::shared_ptr<Texture> texture);
		void Draw(sf::RenderTarget& target);

	private:
		sf::Vector2f m_Position = { 0, 0 };
		sf::Sprite m_Sprite;
		std::shared_ptr<Texture> m_Texture = nullptr;
	};

}