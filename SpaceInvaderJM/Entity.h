
#include "pch.h"
#include "Bullet.h"
#pragma once


enum EnemyType {

	alienType = 1,
	wallType = 2,
};
class Entity {

public:
	Entity(int x, int y);

	Entity();


	void update();//Mettre à jour position
	void draw(sf::RenderWindow& window);//Afficher ) l'écran
	void setImage(const std::string& path, const std::int16_t& angle);
	void setSpeed(sf::Vector2f vector);//Mettre à jour la position

	void setPosition(sf::Vector2f position);//Modifier la position utilisateur par vecteur
	void setPositionXY(int x, int y);//Modifier la position utilisateur par entier X/Y 
	void setSpriteFromSprite(sf::Sprite mysprite);//Modiier le sprite avec un sprite
	sf::Sprite getSprite();

	EnemyType getType();
	void setNewTexture(sf::Texture texture);
	void setType(EnemyType type);
	bool checkCollisionBullet(Bullet& bullet);



	int getX();
	int getY();


protected:

	//Attribut
	sf::Vector2f position;
	sf::Vector2f speed;
	sf::Texture texture;//Zone d'image
	sf::Sprite sprite;//Image personnalisée
	EnemyType type;
	


};