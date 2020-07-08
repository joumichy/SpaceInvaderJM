#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Alien.h"
#include <list>


class Game
{

public:

	Game(int width, int height);
	int mainloop();
	void eventHandler(sf::Event events, std::vector<Bullet>& bulletVector, Alien& alien, std::vector<Alien>& listAlien);
	void initList(std::vector<Alien>& listAlien);
	void moveAliens(std::vector<Alien>& listAlien);

private:

	Ship ship;
	Alien alien;
	std::vector<Alien> listAlien;
	sf::RenderWindow window;
	int w, h;
};