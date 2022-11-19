#pragma once

#include "Sprite.hpp"
#include <SFMl/Graphics.hpp>
#include <memory.h>
#include <functional>

namespace tac {

	class Button
	{
	public:
		Button(const sf::Vector2f& position, std::shared_ptr<Texture> texture);
		Button() = default;

		sf::Vector2f GetPosition();
		sf::Vector2u GetSize();
		sf::Vector2f GetOBBs();
		void Draw(sf::RenderTarget& target);
		void SetTexture(std::shared_ptr<Texture> texture);
		void SetPosition(const sf::Vector2f& position);
		void SetColor(const sf::Color& color);
		void SetCallback(std::function<void()> func);
		void Callback();

	private:
		Sprite m_Sprite;
		std::shared_ptr<Texture> m_Texture = nullptr;
		sf::Vector2f m_Position;
		sf::Color m_Color = sf::Color::White;
		std::function<void()> m_Callback = nullptr;
	};
}