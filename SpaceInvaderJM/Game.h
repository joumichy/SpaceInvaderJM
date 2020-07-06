#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Alien.h"


class Game
{

public:

	Game(int width, int height);
	int mainloop();
	void eventHandler(sf::Event events);

private:

	Ship ship;
	Alien alien;
	sf::RenderWindow window;
	int w, h;
};