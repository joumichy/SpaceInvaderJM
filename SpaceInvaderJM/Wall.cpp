#include "Wall.h";


Wall::Wall(int x, int y) :Entity() {
	std::string path = "./Media/Texture/wall.png";
	setImage(path, 0);
	setPositionXY(x, y);
}

Wall::Wall():Entity() {
	std::string path = "./Media/Texture/wall.png";
	setImage(path, 0);
}
void Wall ::setSize(sf::Vector2f size) {
	
	size.x = sprite.getScale().x;
	sprite.setScale(size);
}


bool Wall::checkCollisionBullet(Bullet& bullet) {


	if (bullet.getRight() > getX() &&
		bullet.getTop() < getY() + 50 &&
		bullet.getDown() > getY())
	{
	
		return true;

	}
	return false;
}


