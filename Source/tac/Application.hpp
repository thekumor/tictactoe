#pragma once

#include "Window.hpp"
#include "Scenes.hpp"
#include "ObjectCreator.hpp"
#include "Button.hpp"
#include <SFMl/Graphics.hpp>
#include <string>
#include <functional>

namespace tac {

	class Application
	{
	public:
		Application(const sf::Vector2u& size, const std::string& title);
		Application() = default;

		void Run();

	private:
		Window m_Window;
		ObjectCreator m_Creator;
	};

}