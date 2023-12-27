#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "SFML/Audio/Music.hpp"

int main()
{
	sf::RenderWindow window;
	Game game(window);
	game.createWindow();

	sf::Clock clock;
	while (window.isOpen()) //TODO: сменить на game.isOpen()
	{
		game.handleEvents();
		game.update(clock);
		game.render();
	}
}