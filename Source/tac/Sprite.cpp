#include "Sprite.hpp"

namespace tac {

	Sprite::Sprite(const sf::Vector2f& position, std::shared_ptr<Texture> texture)
		: m_Position(position), m_Texture(texture)
	{
		SetPosition(position);
		SetTexture(texture);
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

}
