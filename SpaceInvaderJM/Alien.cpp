#include "Alien.h"

void Alien::checkCol(Bullet bullet) {

	if (bullet.getRight() > getX() &&
		bullet.getTop() < getY() + 50 &&
		bullet.getDown() > getY())
	{

		sprite.setPosition(sf::Vector2f(4234567, 4234567));

	}

}

void Alien::movement(sf::Vector2f vector) {
	
}
