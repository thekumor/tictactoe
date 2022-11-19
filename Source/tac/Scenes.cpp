#include "Scenes.hpp"

namespace tac {

	void Scene::Create()
	{
		if (OnCreate)
		{
			OnCreate();
		}
	}

	void Scene::Draw(Window& window)
	{
		for (auto& k : Creator.GetSprites())
		{
			//window.Draw(*k);
		}

		for (auto& k : Creator.GetButtons())
		{
			window.Draw(*k);
		}
	}

	void Scene::Logic(Window& window)
	{
		for (auto& k : Creator.GetButtons())
		{
			if (window.IsHovered(*k))
			{
				k->SetColor(sf::Color::Cyan);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					k->Callback();
				}
			}
			else
			{
				k->SetColor(sf::Color::White);
			}
		}
	}

	void Scene::Destroy()
	{
		Creator.Purge();
	}

}