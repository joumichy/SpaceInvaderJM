#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Bullet.h"

class Alien : public Ship{

public :

	Alien(int x, int y);

	Alien();

	Alien(sf::Texture texture);

	void movement(sf::Vector2f vector);

	bool checkCol(Bullet& bullet);

	void setDead(bool death);
	bool isDead();
	


private:

	bool dead;
	
	


};