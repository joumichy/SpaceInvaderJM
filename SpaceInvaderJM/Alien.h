#pragma once
#include "Entity.h"
#include "Bullet.h"


//Alien Ship 
class Alien : public Entity{

public :

	Alien(int x, int y);

	Alien();

	void movementAlea(sf::Vector2f vector);

	bool checkCol(Bullet& bullet);

	void setDead(bool death);
	bool isDead();
	


private:

	bool dead;
	EnemyType type = alienType;
	
	


};