#pragma once

#include "Sprite.hpp"
#include <SFMl/Graphics.hpp>
#include <memory.h>

namespace tac {

	class Button
	{
	public:
		Button(const sf::Vector2f& position, std::shared_ptr<Texture> texture);
		Button() = default;

		sf::Vector2f GetPosition();
		void Draw(sf::RenderTarget& target);
		void SetTexture(std::shared_ptr<Texture> texture);
		void SetPosition(const sf::Vector2f& position);

	private:
		Sprite m_Sprite;
		std::shared_ptr<Texture> m_Texture = nullptr;
		sf::Vector2f m_Position;
	};
}