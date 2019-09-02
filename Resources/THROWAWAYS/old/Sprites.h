#ifndef __SPRITES_H_INCLUDED__
#define __SPRITES_H_INCLUDED__

#include "../Include/Functions.h"
#include "Textures.h"

//Load tile sprite array of int size
void loadTileSprite(int number, int size, sf::Sprite* sprite, sf::Texture* texture);

void loadForestTreeSprite(const int trunks, const int tops, sf::Sprite* sprite, sf::Texture* texture);
void loadForestSmallTreeSprite(const int trunks, const int tops, sf::Sprite* sprite, sf::Texture* texture);
void loadForestBushSprite(const int trunks, const int tops, sf::Sprite* sprite, sf::Texture* texture);
void loadForestMossSprite(const int mosses, sf::Sprite* sprite, sf::Texture* texture);

#endif