#include "Bullet.h"


Bullet::Bullet(sf::Vector2f size) {

		bullet.setSize(size);
		bullet.setFillColor(sf::Color::Blue);
	
}

void Bullet::fire(int speed) {

	bullet.move(speed, 0);

}

void Bullet::setPos(sf::Vector2f newPos) {
	bullet.setPosition(newPos);
}


void Bullet::draw(sf::RenderWindow &window) {
	
	window.draw(bullet);
}

int Bullet::getLeft() {
	return bullet.getPosition().x;
}

int  Bullet::getRight() {
	return bullet.getPosition().x + bullet.getSize().x;
}

int  Bullet::getTop() {

	return bullet.getPosition().y;
}
int  Bullet::getDown() {
	return bullet.getPosition().y + bullet.getSize().y;
}
