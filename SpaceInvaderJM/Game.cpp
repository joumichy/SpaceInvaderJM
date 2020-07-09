#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>  
#include "Game.h"
#include "Ship.h"
#include "Alien.h"
#include "Wall.h"
#include "Bullet.h"
#include <vector>
#include <chrono>
#include <thread>
#include <string> 

#define WIDTH 1000
#define HEIGHT 600
#define MAX_WIDTH 1000
#define MAX_HEIGHT 600
#define MIN_WIDTH 0
#define MIN_HEIGHT 0
#define SPEED 5.0
#define TAB_X 20
#define TAB_Y 20
#define START_X 50
#define START_Y 300

Game::Game(int width, int height) : w(WIDTH), h(HEIGHT), window(sf::VideoMode(WIDTH, HEIGHT), "Game"), ship(START_X, HEIGHT / 2), alien(600, HEIGHT / 2), listAlien()
{


}




void Game::gameInit(sf::Text& scoreText) {
	sf::Font font;
	if (!font.loadFromFile("./Media/Font/arial.ttf")) {
		std::cout << "Echec fichie ttf" << std::endl;
		system("pause");
	}


}


int Game::mainloop()
{
	sf::Event events;
	sf::Clock clock;
	sf::Clock clockMove;
	sf::Clock clockAlienGenerator;
	sf::Clock clockWallGenerator;
	sf::Clock clockAlienShot;
	

	sf::Font font;
	if (!font.loadFromFile("./Media/Font/arial.ttf")) {
		std::cout << "Echec fichie ttf" << std::endl;
		system("pause");
	}
	scoreText.setFillColor(sf::Color::Green);
	scoreText.setFont(font);
	scoreText.setPosition(10.f, 100.f);
	scoreText.setCharacterSize(20);
	scoreText.setString(std::to_string(score));


	livesText.setFillColor(sf::Color::Green);
	livesText.setFont(font);
	livesText.setPosition(10.f, 120.f);
	livesText.setCharacterSize(20);
	livesText.setString(std::to_string(lives));
	
	//Define Object
	//std::vector<Alien> listAlien;
	//std::vector<Wall> listWall;
	
	

	std::vector<Bullet> bulletVector;
	std::vector<Bullet> alienBulletVector;

	Wall wall(MAX_WIDTH, 200);
	std::vector<std::vector<Wall>> allListWalls;
	std::vector<std::vector<Alien>> allListAlien;


	std::vector<Wall> newListWall;
	std::vector<Alien> newListAlien;
	
	newListAlien.resize(4);
	newListWall.resize(4);
	allListAlien.resize(TAB_Y);
	
	//initListWalls(listWall);

	
	//Set Object
	ship.setImage("./Media/Texture/spaceship.png",90);

	const std::string alienImagePath = "./Media/Texture/alienship.png";
	const std::string wallImagePath = "./Media/Texture/wall.png";
	

	

	
	
	

	if (!window.isOpen()) 
	{
		std::cout << "ERREUR Window !" << std::endl;
		return EXIT_FAILURE;

	}

	while (window.isOpen())
		//Tant que l'ecran est actif
	{
		if (gameOver) {
			std::cout << "PARTIE TERMINEE !" << std::endl;
		}
		while (window.pollEvent(events))
		{
			//On traite ici tous les events
			if (events.type == sf::Event::EventType::Closed)
			{
				//Arret écran
				window.close();
			}
		}



		//Gestion des evenements
		
		window.clear(sf::Color::Black);
		if (clock.getElapsedTime().asSeconds() > 1.0 / 30.0)
		{
			//Tous les 1/30 secondes on met à jour la position du vaisseau
			ship.update();
			clock.restart();
			
		}
		if (clockAlienShot.getElapsedTime().asSeconds() > 1)
		{
			//rand shot
			int prob = rand() % 100 + 1;
			alienShoot(aliens,alienBulletVector);
			clockAlienShot.restart();

		}

		if (clockMove.getElapsedTime().asSeconds() > 0.2)
		{
			//Tous les 1/30 secondes on met à jour la position du vaisseau

			moveAliens(aliens);
			moveWalls(walls);

			//moveAliens(newListAlien);
			//moveWalls(listWall);
			//moveWalls(newListWall);
			clockMove.restart();


		}


		if (clockWallGenerator.getElapsedTime().asSeconds() > 5)
		{
			
			//initListWalls(newListWall);
			//allListWalls.push_back(newListWall);
			clockWallGenerator.restart();

		


		}

		if (clockAlienGenerator.getElapsedTime().asSeconds() > 3)
		{
			
			int WallOrAlien = rand()%100 + 1;

			if (WallOrAlien < 50) {
				initListAliens(newListAlien, textureAlien, alienImagePath);
				//initListWalls(newListWall, textureWall, wallImagePath);

			}
			else
			{
				//initListAliens(newListAlien, textureAlien, alienImagePath);
				initListWalls(newListWall, textureWall, wallImagePath);
			}
			
			clockAlienGenerator.restart();
			
			

			

		}
		//Clear Window's screen
		
		
		
		eventHandler(events, bulletVector,
			alien, listAlien, walls,
			ship, allListAlien,
			newListAlien,alienBulletVector);

		//Show First Alien Colonne
		
		for (unsigned int i = 0; i < aliens.size(); i++) {
			aliens[i].draw(window);
			
		}

		//Show Wall
		for (unsigned int i = 0; i < walls.size(); i++) {
			walls[i].draw(window);
		}
		updateText();
		ship.draw(window);
	
		window.draw(scoreText);
		window.draw(livesText);
		window.display();



		//Affcher l'ecran
		
		
	}

	

	
	
}




void Game::eventHandler(sf::Event events,
	std::vector<Bullet>& bulletVector,
	Alien& alien, std::vector<Alien>& listAlien,
	std::vector<Wall>& listWall,
	Ship& ship,
	std::vector<std::vector<Alien>>& allListAlien,
	std::vector<Alien>& newlistAlien,
	std::vector<Bullet>& alienBulletVector )
{
	

	
	
	bool isShooting = false;
	
	float const speed = 4.0;
	if (events.type == sf::Event::EventType::KeyPressed)
	{
		//Si on appuie sur une touche on modifie la vitesse du vaisseau
		switch (events.key.code)
		{
		case sf::Keyboard::Left:
			{

			ship.setSpeed({ -SPEED, 0 });
			//std::cout << "Left !" << std::endl;

				break;
			}

		case sf::Keyboard::Right:
		{
			ship.setSpeed({ SPEED, 0});
			//std::cout << "Right !" << std::endl;

				break;
			}

		case sf::Keyboard::Up:
			{
			ship.setSpeed({ 0, -SPEED });
			//std::cout << "UP !" << std::endl;

				break;
			}

		case sf::Keyboard::Down:
			{
			ship.setSpeed({ 0, SPEED });
			//std::cout << "DOWN !" << std::endl;

				break;
			}
	
		}
	}

	//Reseting Move
	else if (events.type == sf::Event::EventType::KeyReleased)
	{
		//Dès qu'on relache on remet la vitesse à 0;
		ship.setSpeed({0.0, 0.0});
	}


	//Shooting
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{

	
			isShooting = true;
			//std::cout << "Shoot !" << std::endl;

	}
	
	
	
	window.clear();
	if (isShooting == true) {
		
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
		Bullet newBullet(sf::Vector2f(10, 5));
		newBullet.setPos(sf::Vector2f(ship.getX(), ship.getY()));
		
		bulletVector.push_back(newBullet);
		
		isShooting = false;
		

	}
	

	//Ship Shot
	for (unsigned int i = 0; i < bulletVector.size(); i++) {

		
		bulletVector[i].draw(window);
	
		bulletVector[i].fire(1);
	 
		
	}


	//Alien Shot
	for (unsigned int i = 0; i < alienBulletVector.size(); i++) {

		
		alienBulletVector[i].draw(window);
	
		alienBulletVector[i].fire(-1);
	 
		
	}

	//BUllet Alien on Ship
	for (unsigned int i = 0; i < alienBulletVector.size(); i++) {

		if (ship.getSprite().getGlobalBounds().intersects(alienBulletVector[i].getShape().getGlobalBounds())
		&& !alienBulletVector[i].isShipBullet()) {

	
				alienBulletVector.erase(alienBulletVector.begin() + i);
				//lives -= 1;
				//ship.setPositionXY(START_X, START_Y);

		};


	}


	//IMPACT Alien
	for (unsigned int i = 0; i < bulletVector.size(); i++) {
		
		for (unsigned int elem = 0; elem < aliens.size(); elem++) {
			if (aliens[elem].checkCol(bulletVector[i]) && bulletVector[i].isShipBullet()) {

			
				//Kill Alien
				//listAlien.erase(listAlien.begin() + elem);

				//Destroy bullet
				//bulletVector.erase(bulletVector.begin() + i);
				if (aliens[elem].isDead()) {
					aliens.erase(aliens.begin() + elem);
					bulletVector.erase(bulletVector.begin() + i);
					score += 100;
				}


			};

		}
		
	

		//IMPACT MUR
		for (unsigned int elemWall = 0; elemWall < walls.size(); elemWall++) {

			if (walls[elemWall].checkCollisionBullet(bulletVector[i])) {

				//Destroy Bullet
				bulletVector.erase(bulletVector.begin() + i);
			};
		}
	

		
	}

	//Alien Hit  Ship
	for(Alien alien : aliens){
	
		if (alien.getSprite().getGlobalBounds().intersects(ship.getSprite().getGlobalBounds())) {
			lives -= 1;
			ship.setPositionXY(START_X, START_Y);
			if (lives == 0) {

				
				setGameOver(true);
			}

			//ship.restart();
		}
	}

	for (Wall wall : walls) {

		if (wall.getSprite().getGlobalBounds().intersects(ship.getSprite().getGlobalBounds())) {
			lives -= 1;
			ship.setPositionXY(START_X, START_Y);
			if (lives == 0) {


				setGameOver(true);
			}

			//ship.restart();
		}
	}

	
	
	
}

void Game::moveAliens(std::vector<Alien>& listAlien) {

	
	for (unsigned int i = 0; i < listAlien.size(); i++) {

		int x = listAlien[i].getX();
		int y = listAlien[i].getY();
		x -= SPEED;
		//ADD Top/Down move
		listAlien[i].setPositionXY(x, y);
	}

}

void Game::initListAliens(std::vector<Alien> &listAlien,sf::Texture& texture, std::string alienImagePath) {

	if (!texture.loadFromFile(alienImagePath)) {
		std::cout << "Erreur image " << std::endl;
		system("pause");
	}
	
	
	sf::Sprite sprite;
	
	sprite.setTexture(texture);
	int numberOfAliens = rand() % 4 + 1;
	int positionOfAliens = rand() % 10 + 1;
	for (unsigned int i = 0; i < numberOfAliens; i++) {
		//Alien alien(600,600);
		
		alien.setSpriteFromSprite(sprite);
		alien.setPositionXY(MAX_WIDTH, positionOfAliens*10 + (i * 100));

		aliens.push_back(alien);
	}

};

void Game::initListWalls(std::vector<Wall>& listWall, sf::Texture& texture,std::string wallImagePath) {

	if (!texture.loadFromFile(wallImagePath)) {
		std::cout << "Erreur image " << std::endl;
		system("pause");
	}


	sf::Sprite sprite;

	sprite.setTexture(texture);
	int numberOfWall = rand() % 4 + 1;
	int positionOfWall = rand() % 10 + 1;
	for (unsigned int i = 0; i < numberOfWall; i++) {
		//Alien alien(600,600);

		int wallLength = wall.getSprite().getGlobalBounds().width;
		wall.setSpriteFromSprite(sprite);
		wall.setPositionXY(MAX_WIDTH, positionOfWall + i*wallLength);
		walls.push_back(wall);
		
	}

}

void Game::moveWalls(std::vector<Wall>& listWall) {
	for (unsigned int i = 0; i < listWall.size(); i++) {
		listWall[i].setSpeed(sf::Vector2f(-SPEED, 0));
		listWall[i].update();

	}
	
}

void Game:: updateText() {

	std::string stringScore = "Score: " + std::to_string(score);
	scoreText.setString(stringScore);

	std::string stringLives = "Lives: " + std::to_string(lives);
	livesText.setString(stringLives);
}


bool Game::isGameOver() {

	return gameOver;
}

void Game::setGameOver(bool result) {

	gameOver = result;
}

//Alien shot
void Game::alienShoot(std::vector<Alien>& alien, std::vector<Bullet>& alienBulletVector) {
	bool toAlienMode = false;
	sf::Color color = sf::Color::Red;

	for (Alien alien : aliens) {
		int prob = rand() % +100 + 1;
		if (prob < 20) {
		


			Bullet alienBullet(sf::Vector2f(10, 5), color);
			alienBullet.setPos(sf::Vector2f(alien.getX(), alien.getY()));
			
			alienBullet.setToAlienBullet(toAlienMode);
			alienBulletVector.push_back(alienBullet);
			
			

			//shot

		}
	}
}