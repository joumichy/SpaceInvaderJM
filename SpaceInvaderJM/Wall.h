#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Bullet.h"
#include "Ship.h"
#pragma once
class Wall :public Entity {

public:
	Wall(int x, int y);
	Wall();

	void setSize(sf::Vector2f size);
	

	bool checkCollisionBullet(Bullet& bullet);

	

private:
	std::string path = "./Media/Texture/wall.png";
	sf::Vector2f size;
};