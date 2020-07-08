#include "Wall.h";


Wall::Wall(int x, int y) :Entity() {
	setImage(path, 0);
	setPositionXY(x, y);
}
void Wall ::setSize(sf::Vector2f size) {
	
	size.x = sprite.getScale().x;
	sprite.setScale(size);
}