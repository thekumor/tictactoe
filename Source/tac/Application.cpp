#include "Application.hpp"

#define BUTTON_DELAY 0.25f

namespace tac {

	Application::Application(const sf::Vector2u& size, const std::string& title)
		: m_Window(size, title)
	{

	}

	static sf::Clock s_Clock;
	static sf::Time s_DeltaButton;
	static const std::shared_ptr<Button>* s_ButtonHovered = nullptr;
	static Field s_Choice = Field::Invalid;
	static struct Scene
	{
		void Create()
		{
			s_ButtonHovered = nullptr;

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
			bool anyHovered = false;

			for (auto& k : Creator.GetButtons())
			{
				if (window.IsHovered(*k))
				{
					anyHovered = true;
					if (k->IsVisible() && s_ButtonHovered != &k)
					{
						k->SetColor(sf::Color::Cyan);
						Sounds.GetSound("sound/hover.wav")->Play();
						s_ButtonHovered = &k;
					}

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (s_DeltaButton.asSeconds() + BUTTON_DELAY > s_Clock.getElapsedTime().asSeconds())
						{
							return;
						}

						s_DeltaButton = s_Clock.getElapsedTime();
						Sounds.GetSound("sound/click.wav")->Play();

						k->Callback();
						return;
					}
				}
				else
				{
					k->SetColor(sf::Color::White);
				}
			}

			s_ButtonHovered = anyHovered ? s_ButtonHovered : nullptr;
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

		SoundManager Sounds;
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
			m_FieldsBlocked = false;
			for (uint64_t x = 0; x < 3; x++)
				for (uint64_t y = 0; y < 3; y++)
					m_Fields[x][y] = Field::Empty;

			auto area = game.Creator.CreateSprite(sf::Vector2f(136, 50), "images/field.png");
			area->SetScale(0.08f);

			game.Creator.CreateButton(sf::Vector2f(200, 400), "images/buttons/back.png", [&]()
									  {
										  mainMenu.Create();
										  curScene = &mainMenu;
										  game.Destroy();
									  });

			for (uint64_t x = 0; x < 3; x++)
			{
				for (uint64_t y = 0; y < 3; y++)
				{
					const sf::Vector2f position = area->GetPosition() + sf::Vector2f(124 * x, 112 * y);
					const std::shared_ptr<Button> field = game.Creator.CreateButton(position, "images/heart.png", [position, &game, this, x, y]()
																					{
																						if (!m_FieldsBlocked && m_Fields[x][y] == Field::Empty)
																						{
																							bool isCross = s_Choice == Field::Cross;
																							const std::string path = isCross ? "images/cross.png" : "images/heart.png";
																							auto tic = game.Creator.CreateSprite(position, path);
																							tic->SetScale(isCross ? 0.14f : 0.11f);

																							m_Fields[x][y] = isCross ? Field::Cross : Field::Heart;

																							Field winner = Evaluate(m_Fields);

																							if (winner != Field::Invalid)
																							{
																								m_FieldsBlocked = true;
																								auto result = game.Creator.CreateSprite(sf::Vector2f(10, 10),
																																		winner == s_Choice ? "images/win.png" : "images/lose.png");
																							}
																						}
																					});
					field->SetScale(0.11f);
					field->SetVisible(false);
				}
			}
		};

		pickMenu.OnCreate = [&]()
		{
			pickMenu.Creator.CreateButton(sf::Vector2f(200, 140), "images/buttons/cross.png", [&]()
										  {
											  s_Choice = Field::Cross;
											  game.Create();
											  curScene = &game;
											  pickMenu.Destroy();
										  });

			pickMenu.Creator.CreateButton(sf::Vector2f(200, 200), "images/buttons/heart.png", [&]()
										  {
											  s_Choice = Field::Heart;
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

	Field Application::Evaluate()
	{
		// Top - down
		for (uint64_t x = 0; x < 3; x++)
		{
			Field value = Field::Invalid;
			uint8_t count = 0;
			for (int64_t y = 0; y < 3; y++)
			{
				Field& field = m_Fields[x][y];

				if (field == Field::Empty || (value != field && value != Field::Invalid))
					break;

				value = field;
				count++;
			}

			if (count == 3)
			{
				return value;
			}
		}

		// Left - right
		for (uint64_t y = 0; y < 3; y++)
		{
			Field value = Field::Invalid;
			uint8_t count = 0;
			for (int64_t x = 0; x < 3; x++)
			{
				Field& field = m_Fields[x][y];

				if (field == Field::Empty || (value != field && value != Field::Invalid))
					break;

				value = field;
				count++;
			}

			if (count == 3)
			{
				return value;
			}
		}

		// Cross
		for (uint64_t x = 0; x < 3; x += 2)
		{
			Field value = Field::Invalid;
			uint8_t count = 0;
			for (int64_t z = 0; z < 3; z++)
			{
				Field& field = m_Fields[x == 0 ? x + z : x - z][z];

				if (field == Field::Empty || (value != field && value != Field::Invalid))
					break;

				value = field;
				count++;
			}

			if (count == 3)
			{
				return value;
			}
		}

		return Field::Invalid;
	}

	std::pair<uint8_t, uint8_t> AI::GetMove(Application& app, Field fields[3][3])
	{
		for (uint64_t x = 0; x < 3; x++)
			for (uint64_t y = 0; y < 3; y++)
			{
				Field old = fields[x][y];
				
				if (old == Field::Invalid)
					continue;

				fields[x][y] = Field::Cross;
				Field result = app.Evaluate(fields);
				fields[x][y] = Field::Heart;
				Field result2 = app.Evaluate(fields);

				fields[x][y] = old;

				if (result != Field::Invalid || result2 != Field::Invalid)
				{
					return std::pair<uint8_t, uint8_t>(x, y);
				}
			}

		std::default_random_engine generator;
		std::uniform_int_distribution<int> dist(1, 3);

		uint64_t randomX = 0, randomY = 0;

		randomX = dist(generator);
		randomY = dist(generator);

		return std::pair<uint8_t, uint8_t>(randomX, randomY);
	}

}