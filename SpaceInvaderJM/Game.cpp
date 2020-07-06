#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Ship.h"
#include "Alien.h"

Game::Game(int width, int height): w(width), h(height), window(sf::VideoMode(width, height), "Game"), ship(100,height/2),alien(600,height/2)
{


}

int Game::mainloop()
{
	sf::Event events;
	sf::Clock clock;
	ship.setImage("./Media/Texture/spaceship.png",90);
	alien.setImage("./Media/Texture/alienship.png",0);

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
		eventHandler(events);

		if (clock.getElapsedTime().asSeconds() > 1.0 / 30.0)
		{
			//Tous les 1/30 secondes on met à jour la position du vaisseau
			ship.update();
			alien.update();
			clock.restart();
			
		}

		//Clear Window's screen
		window.clear(sf::Color::Black);
		ship.draw(window);
		alien.draw(window);

		//Afficher l'ecran
		window.display();
	}

	

	

}

void Game::eventHandler(sf::Event events)
{
	if (events.type == sf::Event::EventType::KeyPressed)
	{
		//Si on appuie sur une touche on modifie la vitesse du vaisseau
		switch (events.key.code)
		{
		case sf::Keyboard::Left:
			{

			ship.setSpeed({ -5.0, 0 });
			std::cout << "Left !" << std::endl;

				break;
			}

		case sf::Keyboard::Right:
		{
			ship.setSpeed({5.0, 0});
			std::cout << "Right !" << std::endl;

				break;
			}

		case sf::Keyboard::Up:
			{
			ship.setSpeed({ 0, -5.0 });
			std::cout << "UP !" << std::endl;

				break;
			}

		case sf::Keyboard::Down:
			{
			ship.setSpeed({ 0, 5.0 });
			std::cout << "DOWN !" << std::endl;

				break;
			}
	
		}
	}
	else if (events.type == sf::Event::EventType::KeyReleased)
	{
		//Dès qu'on relache on remet la vitesse à 0;
		ship.setSpeed({0.0, 0.0});
	}
}