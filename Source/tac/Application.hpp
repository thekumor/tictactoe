#pragma once

#include "Window.hpp"
#include "ObjectCreator.hpp"
#include "Button.hpp"
#include "Sound.hpp"
#include <SFMl/Graphics.hpp>
#include <string>
#include <functional>
#include <random>
#include <utility>

namespace tac {

	enum class Field
	{
		Invalid = -1,
		Empty = 0,
		Heart = 1,
		Cross = 2
	};

	class Application;

	class AI
	{
	public:
		AI() = default;

		std::pair<uint8_t, uint8_t> GetMove(Application& app, Field fields[3][3]);

	private:

	};

	class Application
	{
	public:
		Application(const sf::Vector2u& size, const std::string& title);
		Application() = default;

		void Run();
		Field Evaluate(Field fields[3][3]);

	private:
		Field m_Fields[3][3] = {Field::Empty};
		bool m_FieldsBlocked = false;
		Window m_Window;
		ObjectCreator m_Creator;
	};

}