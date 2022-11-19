#include "ObjectCreator.hpp"

namespace tac {

	const std::list<std::shared_ptr<Button>>& ObjectCreator::GetButtons()
	{
		return m_Buttons;
	}

	const std::list<std::shared_ptr<Sprite>>& ObjectCreator::GetSprites()
	{
		return m_Sprites;
	}

	std::shared_ptr<Button>& ObjectCreator::CreateButton(const sf::Vector2f& position, const std::string& texturePath, std::function<void()> onClick)
    {
        std::shared_ptr<Texture> texture = m_Manager.GetTexture(texturePath);
        std::shared_ptr<Button> newButton = std::make_shared<Button>(position, texture);
		newButton->SetCallback(onClick);

        return m_Buttons.emplace_back(newButton);
    }

	std::shared_ptr<Sprite>& ObjectCreator::CreateSprite(const sf::Vector2f& position, const std::string& texturePath)
	{
		std::shared_ptr<Texture> texture = m_Manager.GetTexture(texturePath);
		std::shared_ptr<Sprite> newSprite = std::make_shared<Sprite>(position, texture);

		return m_Sprites.emplace_back(newSprite);
	}

	void ObjectCreator::Purge()
	{
		m_Buttons.clear();
		m_Sprites.clear();
	}

}