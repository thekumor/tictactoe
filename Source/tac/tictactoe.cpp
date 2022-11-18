#include "Application.hpp"

int main()
{
	tac::Application game(sf::Vector2u(640, 480), "Tic Tac Toe");
	game.Run();
}