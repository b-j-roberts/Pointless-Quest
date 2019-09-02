#ifndef __TEXTURES_H_INCLUDED__
#define __TEXTURES_H_INCLUDED__

#include "../Include/Functions.h"

/*Loads textures from Tile.png according to passed int number (given below, vertical position in Tiles.png file) 
 *with int size number of textures (horizonatal number of tiles, given below also)
 * type - (number, size)
 * grass - (1, 7)
 * sand - (2, 2)
 * water - (3, 5)
*/
void loadTileTexture(const int number, const int size, sf::Texture* text);

void loadForestTreeTexture(const int trunks, const int tops, sf::Texture* texture);
void loadForestSmallTreeTexture(const int trunks, const int tops, sf::Texture* texture);
void loadForestBushTexture(const int trunks, const int tops, sf::Texture* texture);
void loadForestMossTexture(const int mosses, sf::Texture* texture);

#endif