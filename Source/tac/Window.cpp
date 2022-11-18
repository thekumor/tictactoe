#include "Window.hpp"

namespace tac {
	
	Window::Window(const sf::Vector2u& size, const std::string& title)
		: m_Size(size), m_Title(title), m_Window(sf::VideoMode(size.x, size.y), title)
	{
	}

	void Window::ProcessEvents()
	{
		sf::Event ev;

		if (m_Window.waitEvent(ev))
		{
			switch (ev.type)
			{
				case sf::Event::Closed:
					Close();
					break;
			}
		}
	}

	void Window::Close()
	{
		m_Window.close();
	}

	void Window::Draw(Button& btn)
	{
		btn.Draw(m_Window);
	}

}