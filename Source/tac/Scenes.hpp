#pragma once

#include "Window.hpp"
#include "ObjectCreator.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

namespace tac {

	struct SceneManager;

	struct Scene
	{
		void Create();
		void Draw(Window& window);
		void Logic(Window& window);
		void Destroy();

		ObjectCreator Creator;
		std::function<void()>OnCreate = nullptr;
	};

	struct SceneManager
	{
		std::vector <std::shared_ptr<Scene>> Scenes = {};
	};

}