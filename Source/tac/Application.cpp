#include "Application.hpp"

namespace tac {

	Application::Application(const sf::Vector2u& size, const std::string& title)
		: m_Window(size, title)
	{

	}

	void Application::Run()
	{
		SceneManager sceneManager;
		//sceneManager.Scenes.reserve(3);
		for (uint64_t i = 0; i < 3; i++) sceneManager.Scenes.emplace_back(std::make_shared<Scene>());
		std::shared_ptr<Scene> mainMenu = sceneManager.Scenes[0], pickMenu = sceneManager.Scenes[1], game = sceneManager.Scenes[2];

		std::shared_ptr<Scene> curScene = mainMenu;
		mainMenu->OnCreate = [&]()
		{
			auto& play = mainMenu->Creator.CreateButton(sf::Vector2f(200, 130), "images/buttons/play.png", [&]()
													   {
														   mainMenu->Destroy();
														   pickMenu->Create();
														   curScene = pickMenu;
													   });
			auto& exit = mainMenu->Creator.CreateButton(sf::Vector2f(200, 200), "images/buttons/exit.png", [&]()
													   {
														   m_Window.Close();
													   });
		};

		pickMenu->OnCreate = [&]()
		{
			auto& cross = pickMenu->Creator.CreateButton(sf::Vector2f(200, 130), "images/buttons/cross.png", [&]()
														{

														});
			auto& heart = pickMenu->Creator.CreateButton(sf::Vector2f(200, 200), "images/buttons/heart.png", [&]()
														{

														});
			auto& back = pickMenu->Creator.CreateButton(sf::Vector2f(200, 270), "images/buttons/back.png", [&]()
													   {
														   pickMenu->Destroy();
														   mainMenu->Create();
														   curScene = mainMenu;
													   });
		};

		mainMenu->Create();

		while (m_Window.IsOpen())
		{
			// Logic
			m_Window.ProcessEvents();
			curScene->Logic(m_Window);

			// Graphics
			m_Window.Clear(sf::Color(240, 185, 185));
			curScene->Draw(m_Window);
			m_Window.Display();
		}
	}

}