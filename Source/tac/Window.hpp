#pragma once

#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <string>

namespace tac {

	class Window
	{
	public:
		Window(const sf::Vector2u& size, const std::string& title);
		Window() = default;

		inline bool IsOpen()
		{
			return m_Window.isOpen();
		}

		inline void Display()
		{
			m_Window.display();
		}

		inline void Clear(const sf::Color& color = {0u, 0u, 0u, 255u})
		{
			m_Window.clear();
		}

		void ProcessEvents();
		void Close();
		void Draw(Button& btn);

	private:
		sf::RenderWindow m_Window;
		sf::Vector2u m_Size = { 0, 0 };
		std::string m_Title = "";
	};

}