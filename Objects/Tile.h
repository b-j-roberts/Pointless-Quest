#ifndef __TILE_H_INCLUDED__
#define __TILE_H_INCLUDED__

#include "Player.h"

class Tile {
	private:
		int type;
		int biomeID;
		sf::Sprite *sprite;
	public:
		Tile(sf::Sprite *spriteS, int arraySize, int biomeID);
		Tile(int type, sf::Sprite *spriteS, int arraySize, int biomeID);
		void draw(sf::RenderWindow &window, float x, float y);
		//bool inView(sf::View view, float x, float y);
};

#endif
