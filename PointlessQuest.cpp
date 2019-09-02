#include "Objects/World.h"
#include <SFML/Window/Joystick.hpp>
#include "Resources/Sprites.h"

int main() {
	
	sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
	sf::RenderWindow window(desktop, "Pointless Quest");

	window.setFramerateLimit(60);

  //Window Size & scale
	sf::Vector2u windowSize = window.getSize();
	const float Xscale = windowSize.x * 1.f / windowSize.y;

	const int tileSize = 32;

	/*
	*
	* LOADING TEXTURES/SPRITES (Only load ones in decided biomes)
	*
	*
	*/

  //Load Grass Sprites
	const int grassSize = 10;
	sf::Texture grassT[grassSize];
	sf::Sprite grassS[grassSize];
	loadTileSprite(1, grassSize, grassS, grassT);
	
  //Load Sand Sprites
	const int sandSize = 1;
	sf::Texture sandT[sandSize];
	sf::Sprite sandS[sandSize];
	loadTileSprite(2, sandSize, sandS, sandT);

  //Load Water Sprites
	const int waterSize = 1;
	sf::Texture waterT[waterSize];
	sf::Sprite waterS[waterSize];
	loadTileSprite(3, waterSize, waterS, waterT);

  //Load forestTree Sprites (wildlife)
	const int forestTreeTrunks = 3;
	const int forestTreeTops = 2;
	sf::Texture forestTreeT[2 * forestTreeTops + 2 * forestTreeTrunks];
	sf::Sprite forestTreeS[2 * forestTreeTops + 2 * forestTreeTrunks];
	loadForestTreeSprite(forestTreeTrunks, forestTreeTops, forestTreeS, forestTreeT);
  //Load forestSmallTree Sprites (wildlife)
	const int forestSmallTreeTrunks = 3;
	const int forestSmallTreeTops = 2;
	sf::Texture forestSmallTreeT[2 * forestSmallTreeTops + 2 * forestSmallTreeTrunks];
	sf::Sprite forestSmallTreeS[2 * forestSmallTreeTops + 2 * forestSmallTreeTrunks];
	loadForestSmallTreeSprite(forestSmallTreeTrunks, forestSmallTreeTops, forestSmallTreeS, forestSmallTreeT);
  //Load forestBush Sprites (wildlife)
	const int forestBushTrunks = 2;
	const int forestBushTops = 3;
	sf::Texture forestBushT[2 * forestBushTops + 2 * forestBushTrunks];
	sf::Sprite forestBushS[2 * forestBushTops + 2 * forestBushTrunks];
	loadForestBushSprite(forestBushTrunks, forestBushTops, forestBushS, forestBushT);
  //Load forestMoss Sprites (plantLife)
	const int forestMosses = 3;
	sf::Texture forestMossT[forestMosses];
	sf::Sprite forestMossS[forestMosses];
	loadForestMossSprite(forestMosses, forestMossS, forestMossT);
	//Currently both invisible and non are being stored as sprites, I should probably not pass textures if I dont need them later or decide
	//if i want to change sprites when inv or texture of sprite


	//Load Player
	Player player(Xscale);


	/*
	*
	* GENERATING WORLD
	*
	*
	*/


  //Random Number generator
	srand(time(NULL));
  
  //size of world, can be any size
	sf::Vector2u worldSize = sf::Vector2u(2000, 2000);

  //Create World
	World world(worldSize, *grassS, *sandS, *waterS, *forestTreeT, *forestTreeS, *forestSmallTreeT, *forestSmallTreeS, 
		       *forestBushT, *forestBushS, *forestMossS, tileSize);
	std::cout << "Finished Generating World!";

	/*
	*
	* JOYSTICK INPUT
	*
	*
	*/

  //Joystick init
	sf::Joystick::update();
	bool isGamepad, isLX, isLY, isRX, isRY;

	isGamepad = sf::Joystick::isConnected(0);
	if (!isGamepad) {
		std::cout << "No GamePad!" << std::endl;
	}
	isLX = sf::Joystick::hasAxis(0, sf::Joystick::X);
	isLY = sf::Joystick::hasAxis(0, sf::Joystick::Y);
	isRX = sf::Joystick::hasAxis(0, sf::Joystick::Z);
	isRY = sf::Joystick::hasAxis(0, sf::Joystick::R);

	/*
	*
	* GAME LOOP
	*
	*
	*/

	//Other initialization
	sf::Event event;

	while (window.isOpen()) {

		//Joystick info
		sf::Joystick::update();
		sf::Vector2f Rstick, Lstick;
	  // Get Analog's position
		if (isLX) {
			Lstick.x = sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100;
			if (sq(Lstick.x) < .005) Lstick.x = 0;
		}
		if (isLY) {
			Lstick.y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y) / 100;
			if (sq(Lstick.y) < .005) Lstick.y = 0;
		}
		if (isRX) {
			Rstick.x = sf::Joystick::getAxisPosition(0, sf::Joystick::Z) / 100;
			if (sq(Rstick.x) < .005) Rstick.x = 0;
		}
		if (isRY) {
			Rstick.y = sf::Joystick::getAxisPosition(0, sf::Joystick::R) / 100;
			if (sq(Rstick.y) < .005) Rstick.y = 0;
		}

		//Scan input
		while (window.pollEvent(event)) {

			switch (event.type) {

				case sf::Event::Closed:
					window.close();
					break;

				default:
					break;

			}

		}

		/*
		*
		* UPDATE STEP
		*
		*
		*/

		player.update(Lstick,Rstick);

		/*
		*
		* DRAW STEP
		*
		*
		*/

		window.clear();

		//Draw World (floor)
		world.draw(window, player);

		//Draw Player
		player.draw(window);

		//Draw Trees
		  //for (int i = 0; i < treeNum; i++) {
		  //	treeTrunkS.setPosition(treePos[i]);
		  //	window.draw(treeTrunkS);
		  //	treeTopS.setPosition(treePos[i]);
		  //	window.draw(treeTopS);
		  //}


	  //Display Step
		window.setView(player.getView());
		window.display();

	}

	//After Game Loop

	return 0;
}


//ADD button to autorun/actually just makes the Lstick choose angle
//Multithread
//Properly generate world
//Sprite and Texture libraries
