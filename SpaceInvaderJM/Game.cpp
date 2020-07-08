#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Ship.h"
#include "Alien.h"
#include "Bullet.h"
#include <vector>
#include "Wall.h"

Game::Game(int width, int height) : w(width), h(height), window(sf::VideoMode(width, height), "Game"), ship(100, height / 2), alien(600, height / 2),listAlien()
{


}



void Game::initList(std::vector<Alien> &listAlien) {

	for (unsigned int i = 0; i < 4; i++) {
		Alien alien(0, 0);
		alien.setPositionXY(700, 100 + (i*100));
		//alien.setImage("./Media/Texture/alienship.png", 0);
		listAlien.push_back(alien);
	}

};

int Game::mainloop()
{
	sf::Event events;
	sf::Clock clock;
	sf::Clock clockMove;
	
	//Define Object
	std::vector<Alien> listAlien;
	std::vector<Bullet> bulletVector;
	Wall wall(200, 200);
	wall.setSize(sf::Vector2f(10, 10));

	initList(listAlien);

	
	//Set Object
	ship.setImage("./Media/Texture/spaceship.png",90);
	//alien.setImage("./Media/Texture/alienship.png",0);
	
	
	

	if (!window.isOpen()) 
	{
		std::cout << "ERREUR Window !" << std::endl;
		return EXIT_FAILURE;

	}

	while (window.isOpen())
		//Tant que l'ecran est actif
	{
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
		

		if (clock.getElapsedTime().asSeconds() > 1.0 / 30.0)
		{
			//Tous les 1/30 secondes on met à jour la position du vaisseau
			ship.update();
			alien.update();
			clock.restart();
			
		}

		if (clockMove.getElapsedTime().asSeconds() > 0.5)
		{
			//Tous les 1/30 secondes on met à jour la position du vaisseau

			moveAliens(listAlien);
			wall.setSpeed(sf::Vector2f(-5, -5));
			wall.update();
			clockMove.restart();


		}

		//Clear Window's screen
		window.clear(sf::Color::Black);
		
		
		eventHandler(events, bulletVector, alien, listAlien);
		alien.draw(window);
		for (int i = 0; i < listAlien.size(); i++) {
			listAlien[i].draw(window);
		}
		ship.draw(window);
		wall.draw(window);
		window.display();



		//Affcher l'ecran
		
		
	}

	

	
	
}

void Game::moveAliens(std::vector<Alien>& listAlien) {

float const move = 4;
 for (int i = 0; i < listAlien.size(); i++) {

	 int x = listAlien[i].getX();
	 int y = listAlien[i].getY();
	 x -= move;
	//ADD Top/Down move
	 listAlien[i].setPositionXY(x, y);
	}
 
}


void Game::eventHandler(sf::Event events, std::vector<Bullet>& bulletVector, Alien& alien, std::vector<Alien>& listAlien)
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

			ship.setSpeed({ -speed, 0 });
			std::cout << "Left !" << std::endl;

				break;
			}

		case sf::Keyboard::Right:
		{
			ship.setSpeed({speed, 0});
			std::cout << "Right !" << std::endl;

				break;
			}

		case sf::Keyboard::Up:
			{
			ship.setSpeed({ 0, -speed });
			std::cout << "UP !" << std::endl;

				break;
			}

		case sf::Keyboard::Down:
			{
			ship.setSpeed({ 0, speed });
			std::cout << "DOWN !" << std::endl;

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
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		std::cout << "Shoot !" << std::endl;
		isShooting = true;
		 
	}
	
	window.clear();
	if (isShooting == true) {

		Bullet newBullet(sf::Vector2f(50, 5));
		newBullet.setPos(sf::Vector2f(ship.getX(), ship.getY()));
		bulletVector.push_back(newBullet);
		isShooting = false;

	}
	
	for (int i = 0; i < bulletVector.size(); i++) {

		bulletVector[i].draw(window);

		bulletVector[i].fire(3);
		
	}

	for (int i = 0; i < bulletVector.size(); i++) {
		alien.checkCol(bulletVector[i]);
		for (int elem = 0; elem < listAlien.size(); elem++) {
			listAlien[elem].checkCol(bulletVector[i]);
		}
		
	}
		
	
}