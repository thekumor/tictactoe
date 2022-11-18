#include "Application.hpp"

namespace tac {

	Application::Application(const sf::Vector2u& size, const std::string& title)
		: m_Window(size, title)
	{

	}

	void Application::Run()
	{
		Texture txt("images/buttons/play.png");
		Button btn(sf::Vector2f(0, 0), std::make_shared<Texture>(txt));

		while (m_Window.IsOpen())
		{
			// Logic
			m_Window.ProcessEvents();

			// Graphics
			m_Window.Clear();
			m_Window.Draw(btn);
			m_Window.Display();
		}
	}

}