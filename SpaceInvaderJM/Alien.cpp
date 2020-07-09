#include "Alien.h"

Alien::Alien() {
	dead = false;
};

Alien::Alien(int x, int y) :Entity() {
	dead = false;
};


bool Alien::checkCol(Bullet& bullet) 
{

	sf::RectangleShape bulletShape;
	bulletShape = bullet.getShape();

	if (bulletShape.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
		setDead(true);
		return true;
	}
	return false;
}

void Alien::movementAlea(sf::Vector2f vector) {
	
}

bool Alien::isDead() {

	return dead;

}

void Alien::setDead(bool death) {

	dead = death;

}






