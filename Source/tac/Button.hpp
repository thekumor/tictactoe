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
		bool IsVisible();
		bool IsGhost();
		float GetScale();
		void SetScale(float scale);
		void Draw(sf::RenderTarget& target);
		void SetTexture(std::shared_ptr<Texture> texture);
		void SetPosition(const sf::Vector2f& position);
		void SetColor(const sf::Color& color);
		void SetCallback(std::function<void()> func);
		void Callback();
		void SetVisible(bool visible);
		void SetGhost(bool ghost);

	private:
		bool m_Ghost = false;
		bool m_Visible = true;
		float m_Scale = 1.0f;
		Sprite m_Sprite;
		std::shared_ptr<Texture> m_Texture = nullptr;
		sf::Vector2f m_Position;
		sf::Color m_Color = sf::Color::White;
		std::function<void()> m_Callback = nullptr;
	};
}