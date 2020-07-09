#include "Alien.h"

Alien::Alien() :Ship() {
	dead = false;
	//setImage("./Media/Texture/alienship.png", 0);
};

Alien::Alien(int x, int y) :Ship() {
	//setImage("./Media/Texture/alienship.png", 0);
};

Alien::Alien(sf::Texture texture) {
	dead = false;
	setImageFromTexture(texture, 0);
};

bool Alien::checkCol(Bullet& bullet) {

	/*if (bullet.getRight() > getX() &&
		bullet.getTop() < getY() + 50 &&
		bullet.getDown() > getY())
	{
		//bullet.setPos(sf::Vector2f(5000000, 5000000));
		//sprite.setPosition(sf::Vector2f(100000, 10000));
		return true;
	}
	return false;*/

	sf::RectangleShape bulletShape;
	bulletShape = bullet.getShape();

	if (bulletShape.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
		setDead(true);
		return true;
	}
	return false;
}

void Alien::movement(sf::Vector2f vector) {
	
}

bool Alien::isDead() {

	return dead;

}

void Alien::setDead(bool death) {

	dead = death;

}






