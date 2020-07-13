#pragma once
#include "pch.h"
#include "Ship.h"
#include "Alien.h"
#include "Wall.h"




class Game
{

public:

	Game(int width, int height);
	int mainloop();
	void eventHandler(sf::Event events,
		std::vector<Bullet>& bulletVector,
		std::vector<Bullet>& alienBulletVector,
		std::vector<Alien>& aliens,
		std::vector<Wall>& walls,
		Ship& ship
		);
	void eventHandlerPLayerShooting(sf::Event events,
		std::vector<Bullet>& bulletVector
	);
	
	//Alien Gestion
	void initListAliens(std::vector<Alien>& listAlien, sf::Texture& texture, std::string alienImagePath);
	
	void aleaAliensMove(std::vector<Alien>& listAlien);
	void alienShoot(std::vector<Alien>& aliens, std::vector<Bullet>& alienBullet);

	//Wall Gestion
	void initListWalls(std::vector<Wall>& listWall, sf::Texture& texture, std::string wallImagePath);
	
	bool isGameOver();
	void setGameOver(bool gameover);

	//TextGestion

	void updateText();
	void initShip(sf::Texture& texture, std::string wallImagePath);

	//Enemy Gestion :
	void moveEnemy(std::vector<Entity>& enemyEntity);

private:

	Ship ship;
	Alien alien;
	Wall wall;

	sf::RenderWindow window;
	int w, h;
	int score = 0;
	int lives = 3;
	bool gameOver = false;

	//Event Object
	std::vector<Alien> aliens;
	std::vector<Wall> walls;
	std::vector<Entity> entitiesEnemy;

	sf::Texture textureShip;
	sf::Texture textureAlien;
	sf::Texture textureWall;
	sf::Texture textureExplosion;
	sf::Texture textureBackGround;

	sf::Image imageExplosion;
	sf::Image imageWall;
	sf::Image imageShip;



	sf::Text scoreText;
	sf::Text livesText;
	sf::Text gameOverText;

	EnemyType typeAlien = alienType;
	EnemyType typeWall = wallType;





	

};