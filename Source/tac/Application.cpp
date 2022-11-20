#include "Application.hpp"

#define BUTTON_DELAY 0.25f

namespace tac {

	Application::Application(const sf::Vector2u& size, const std::string& title)
		: m_Window(size, title)
	{

	}

	static sf::Clock clock;
	static sf::Time deltaButton;
	static struct Scene
	{
		void Create() 
		{
			if (OnCreate)
			{
				OnCreate();
			}
		}

		void Destroy()
		{
			Creator.Purge();
		}

		void Logic(Window& window)
		{
			for (auto& k : Creator.GetButtons())
			{
				if (window.IsHovered(*k))
				{
					k->SetColor(sf::Color::Cyan);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (deltaButton.asSeconds() + BUTTON_DELAY > clock.getElapsedTime().asSeconds())
						{
							return;
						}

						deltaButton = clock.getElapsedTime();

						k->Callback();
						return;
					}
				}
				else
				{
					k->SetColor(sf::Color::White);
				}
			}
		}

		void Draw(Window& window)
		{
			for (auto& k : Creator.GetSprites())
			{
				window.Draw(*k);
			}

			for (auto& k : Creator.GetButtons())
			{
				window.Draw(*k);
			}
		}

		ObjectCreator Creator;
		std::function<void()> OnCreate = nullptr;
	};

	void Application::Run()
	{
		Scene mainMenu;
		Scene pickMenu;
		Scene game;
		Scene* curScene = &mainMenu;

		game.OnCreate = [&]()
		{
			auto field = game.Creator.CreateSprite(sf::Vector2f(136, 50), "images/field.png");
			field->SetScale(0.08f);

			game.Creator.CreateButton(sf::Vector2f(200, 400), "images/buttons/back.png", [&]()
									  {
										  mainMenu.Create();
										  curScene = &mainMenu;
										  game.Destroy();
									  });
		};

		pickMenu.OnCreate = [&]()
		{
			pickMenu.Creator.CreateButton(sf::Vector2f(200, 140), "images/buttons/cross.png", [&]()
										  {
											  game.Create();
											  curScene = &game;
											  pickMenu.Destroy();
										  });

			pickMenu.Creator.CreateButton(sf::Vector2f(200, 200), "images/buttons/heart.png", [&]()
										  {
											  game.Create();
											  curScene = &game;
											  pickMenu.Destroy();
										  });

			pickMenu.Creator.CreateButton(sf::Vector2f(200, 260), "images/buttons/back.png", [&]()
										  {
											  mainMenu.Create();
											  curScene = &mainMenu;
											  pickMenu.Destroy();
										  });
		};

		mainMenu.OnCreate = [&]()
		{
			mainMenu.Creator.CreateButton(sf::Vector2f(200, 140), "images/buttons/play.png", [&]()
										  {
											  pickMenu.Create();
											  curScene = &pickMenu;
											  mainMenu.Destroy();
										  });

			mainMenu.Creator.CreateButton(sf::Vector2f(200, 200), "images/buttons/exit.png", [&]()
										  {
											  m_Window.Close();
										  });
		};

		mainMenu.Create();

		while (m_Window.IsOpen())
		{
			// ------------------------------------------
			// Logic
			m_Window.ProcessEvents();

			if (curScene)
				curScene->Logic(m_Window);

			// ------------------------------------------
			// Graphics
			m_Window.Clear(sf::Color(240, 185, 185));

			if (curScene)
				curScene->Draw(m_Window);

			m_Window.Display();
		}
	}

}