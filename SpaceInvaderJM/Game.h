#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ship.h"

class Game
{

public:

	Game(int width, int height);
	int mainloop();
	void eventHandler(sf::Event events);

private:

	Ship ship;
	sf::RenderWindow window;
	int w, h;
};