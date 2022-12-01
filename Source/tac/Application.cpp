#include "Application.hpp"

#define BUTTON_DELAY 0.25f

namespace tac
{

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
				if (k->IsGhost()) continue;

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
			game.Destroy();
			AI ai;

			m_FieldsBlocked = false;
			for (uint64_t x = 0; x < 3; x++)
				for (uint64_t y = 0; y < 3; y++)
					m_Fields[x][y] = Field::Empty;

			auto area = game.Creator.CreateSprite(sf::Vector2f(136, 50), "images/field.png");
			area->SetScale(0.08f);

			auto back = game.Creator.CreateButton(sf::Vector2f(200, 400), "images/buttons/back.png", [&]()
				{
					mainMenu.Create();
					curScene = &mainMenu;
					game.Destroy();
				});

			auto play = game.Creator.CreateButton(sf::Vector2f(320, 400), "images/buttons/play.png", [&]()
				{
					game.Create();
				});

			play->SetGhost(true);

			for (uint64_t x = 0; x < 3; x++)
			{
				for (uint64_t y = 0; y < 3; y++)
				{
					const sf::Vector2f position = area->GetPosition() + sf::Vector2f(124 * x, 112 * y);
					const std::shared_ptr<Button> field = game.Creator.CreateButton(position, "images/heart.png", [back, play, area, position, &game, this, x, y, &ai]()
						{
							if (!m_FieldsBlocked && m_Fields[x][y] == Field::Empty)
							{
								bool isCross = s_Choice == Field::Cross;
								const std::string path = isCross ? "images/cross.png" : "images/heart.png";
								auto tic = game.Creator.CreateSprite(position, path);
								tic->SetScale(isCross ? 0.14f : 0.11f);

								m_Fields[x][y] = s_Choice;

								Field winner = Evaluate(m_Fields);

								if (winner != Field::Invalid)
								{
									m_FieldsBlocked = true;
									back->SetPosition(back->GetPosition() - sf::Vector2f(130, 0));
									auto result = game.Creator.CreateSprite(sf::Vector2f(10, 10), "images/win.png");
									play->SetGhost(false);
								}

								// Draw, no winner.
								bool isEmpty = NoEmptyFields();
								if (isEmpty)
								{
									m_FieldsBlocked = true;
									back->SetPosition(back->GetPosition() - sf::Vector2f(130, 0));
									play->SetGhost(false);
									return;
								}

								std::pair<uint8_t, uint8_t> aiMove = ai.GetMove(*this, m_Fields);
								uint8_t aiX = aiMove.first;
								uint8_t aiY = aiMove.second;

								sf::Vector2f aiPosition = area->GetPosition() + sf::Vector2f(124 * aiX, 112 * aiY);

								const std::string aiPath = isCross ? "images/heart.png" : "images/cross.png";
								auto tac = game.Creator.CreateSprite(aiPosition, aiPath);
								tac->SetScale(isCross ? 0.11f : 0.14f);

								m_Fields[aiX][aiY] = isCross ? Field::Heart : Field::Cross;

								winner = Evaluate(m_Fields);

								if (winner != Field::Invalid)
								{
									m_FieldsBlocked = true;
									back->SetPosition(back->GetPosition() - sf::Vector2f(130, 0));
									auto result = game.Creator.CreateSprite(sf::Vector2f(10, 10), "images/lose.png");
									play->SetGhost(false);
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

	bool Application::NoEmptyFields()
	{
		uint8_t takenFields = 0;

		for (uint8_t x = 0; x < 3; x++)
			for (uint8_t y = 0; y < 3; y++)
				if (m_Fields[x][y] != Field::Invalid && m_Fields[x][y] != Field::Empty)
					takenFields++;

		return takenFields == 9;
	}

	Field Application::Evaluate(Field fields[3][3])
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
		uint8_t playerX = 10; // 10 for invalid
		uint8_t playerY = 10;
		uint8_t aiX = 10;
		uint8_t aiY = 10;

		for (uint64_t x = 0; x < 3; x++)
			for (uint64_t y = 0; y < 3; y++)
			{
				Field old = fields[x][y];

				if (old != Field::Empty)
					continue;

				fields[x][y] = s_Choice == Field::Cross ? Field::Heart : Field::Cross; // Opposite of the player
				Field forItself = app.Evaluate(fields);
				fields[x][y] = old;

				if (forItself != Field::Invalid)
				{
					aiX = x;
					aiY = y;
				}

				fields[x][y] = s_Choice == Field::Cross ? Field::Cross : Field::Heart; // Pick of the player
				Field againstPlayer = app.Evaluate(fields);
				fields[x][y] = old;

				if (againstPlayer != Field::Invalid)
				{
					playerX = x;
					playerY = y;
				}
			}

		if (aiX != 10)
		{
			return std::pair<uint8_t, uint8_t>(aiX, aiY);
		}
		if (playerX != 10)
		{
			return std::pair<uint8_t, uint8_t>(playerX, playerY);
		}

		std::default_random_engine generator;
		std::uniform_int_distribution<int> dist(0, 2);

		uint64_t randomX = 0, randomY = 0;
		do
		{
			randomX = dist(generator);
			randomY = dist(generator);
		} while (fields[randomX][randomY] != Field::Empty);

		return std::pair<uint8_t, uint8_t>(randomX, randomY);
	}

}