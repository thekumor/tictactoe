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

	void Button::SetColor(const sf::Color& color)
	{
		m_Color = color;
		m_Sprite.SetColor(color);
	}

	void Button::SetCallback(std::function<void()> func)
	{
		m_Callback = func;
	}

	void Button::Callback()
	{
		if (m_Callback)
		{
			m_Callback();
		}
	}

	void Button::SetVisible(bool visible)
	{
		m_Visible = visible;
	}

	sf::Vector2f Button::GetPosition()
	{
		return m_Position;
	}

	sf::Vector2u Button::GetSize()
	{
		return m_Sprite.GetSize();
	}

	sf::Vector2f Button::GetOBBs()
	{
		return m_Position + sf::Vector2f(GetSize().x * GetScale(), GetSize().y * GetScale());
	}

	bool Button::IsVisible()
	{
		return m_Visible;
	}

	float Button::GetScale()
	{
		return m_Scale;
	}

	void Button::SetScale(float scale)
	{
		m_Scale = scale;
		m_Sprite.SetScale(scale);
	}

	void Button::Draw(sf::RenderTarget& target)
	{
		if (m_Visible)
			m_Sprite.Draw(target);
	}

	void Button::SetTexture(std::shared_ptr<Texture> texture)
	{
		m_Texture = texture;
		m_Sprite.SetTexture(texture);
	}

}