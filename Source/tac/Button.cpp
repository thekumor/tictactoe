#include "Button.hpp"

namespace tac {

	Button::Button(const sf::Vector2f& position, std::shared_ptr<Texture> texture)
		: m_Position(position), m_Texture(texture), m_Sprite(position, texture)
	{
	}

	void Button::SetPosition(const sf::Vector2f& position)
	{
		m_Position = position;
		m_Sprite.SetPosition(position);
	}

	sf::Vector2f Button::GetPosition()
	{
		return m_Position;
	}

	void Button::Draw(sf::RenderTarget& target)
	{
		m_Sprite.Draw(target);
	}

	void Button::SetTexture(std::shared_ptr<Texture> texture)
	{
		m_Texture = texture;
		m_Sprite.SetTexture(texture);
	}

}