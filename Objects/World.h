#ifndef __WORLDGEN_H_INCLUDED__
#define __WORLDGEN_H_INCLUDED__

#include "../Objects/Tile.h"
#include "Plantlife.h"

/* BIOME INDEX NUMBERS:
 * 1 - FOREST (Grass, Trees, ...)
 * 2 - Desert (Sand, Cactus, ...)
 * 3 - Ocean (Water, ...)
 * 4 - Tundra (Snow, ice, ...)
 * 5 - 
 * 6 - 
 * 7 - Magic (Dark Grass, ...)
 */
/*
class Biome {
	private:
		int biomeID;
		std::vector<Wildlife> wildlife;
		std::vector<Plantlife> plantlife;
		//std::vector<Dungons, Events?, ...>
	public:
		Biome();
		void generate();
		void update();
		void draw(sf::RenderWindow &window);
};
*/
class World {
	private:
		std::vector<std::vector<Tile>> Tiles;
		std::vector<forestTree> forestTrees;
		std::vector<forestSmallTree> forestSmallTrees;
		std::vector<forestBush> forestBushs;
		std::vector<forestMoss> forestMosses;
		//std::vector<Biome> Biomes;
	public:
		World(sf::Vector2u worldSize, sf::Sprite &grassS, sf::Sprite &sandS, sf::Sprite &waterS, sf::Texture &forestTreeT, sf::Sprite &forestTreeS, 
			  sf::Texture &forestSmallTreeT, sf::Sprite &forestSmallTreeS, sf::Texture &forestBushT, sf::Sprite &forestBushS, sf::Sprite &forestMossS,
			  const int tileSize);
		void update();
		void draw(sf::RenderWindow &window, Player &player);
};

#endif