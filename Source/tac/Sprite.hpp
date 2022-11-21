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

		sf::Vector2f GetPosition();
		sf::Vector2u GetSize();
		float GetScale();
		void SetScale(float size);
		void SetPosition(const sf::Vector2f& position);
		void SetTexture(std::shared_ptr<Texture> texture);
		void Draw(sf::RenderTarget& target);
		void SetColor(const sf::Color& color);

	private:
		float m_Scale = 1.0f;
		sf::Vector2f m_Position = { 0, 0 };
		sf::Color m_Color = sf::Color::White;
		sf::Sprite m_Sprite;
		std::shared_ptr<Texture> m_Texture = nullptr;
	};

}