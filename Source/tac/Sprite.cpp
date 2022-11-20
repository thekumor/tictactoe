#include "Sprite.hpp"

namespace tac {

	Sprite::Sprite(const sf::Vector2f& position, std::shared_ptr<Texture> texture)
		: m_Position(position), m_Texture(texture)
	{
		SetPosition(position);
		SetTexture(texture);
	}

	sf::Vector2f Sprite::GetPosition()
	{
		return m_Position;
	}

	sf::Vector2u Sprite::GetSize()
	{
		return m_Texture->GetSize();
	}

	void Sprite::SetScale(float size)
	{
		m_Scale = size;
		m_Sprite.setScale(size, size);
	}

	void Sprite::SetPosition(const sf::Vector2f& position)
	{
		m_Position = position;
		m_Sprite.setPosition(position);
	}

	void Sprite::SetTexture(std::shared_ptr<Texture> texture)
	{
		m_Texture = texture;
		m_Sprite.setTexture(texture->m_Texture);
	}

	void Sprite::Draw(sf::RenderTarget& target)
	{
		target.draw(m_Sprite);
	}

	void Sprite::SetColor(const sf::Color& color)
	{
		m_Color = color;
		m_Sprite.setColor(color);
	}

}
