#include <SFML/Window.hpp>

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"


int main()
{

	//On parametre la r�solution
	Game game(1000, 600);

	//Lancement du jeu.
	return game.mainloop();





}

