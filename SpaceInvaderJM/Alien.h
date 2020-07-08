#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Bullet.h"

class Alien : public Ship{

public :

	Alien(int x, int y) :Ship(x, y){

		setImage("./Media/Texture/alienship.png", 0);

	}

	Alien():Ship() {

	}
	void movement(sf::Vector2f vector);

	void checkCol(Bullet bullet);


private:


	
	


};