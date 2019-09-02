#include "Tile.h"

//TILE CONSTRUCTOR
Tile::Tile(sf::Sprite *spriteS, int arraySize, int biomeID) {
	this->biomeID = biomeID;
	type = rand() % arraySize;
	sprite = &spriteS[type];
}

//TILE CONSTRUCTOR (PARTICULAR TYPE, ie sprite num)
Tile::Tile(int type, sf::Sprite *spriteS, int arraySize, int biomeID) {
	this->biomeID = biomeID;
	this->type = type % arraySize;
	sprite = &spriteS[this->type];
}

//DRAW TILE
void Tile::draw(sf::RenderWindow &window, float x, float y) {
	const int tileSize = 32;
	sf::Vector2f position = sf::Vector2f(tileSize * x,tileSize * y);
	sprite->setPosition(position);
	window.draw(*sprite);
}

/*
//Returns true if tile with position, (x,y), is 'close' to the view. Currently: 'close' = in view +- 2/3 of view size in both ways
bool Tile::inView(sf::View view, float x, float y) {
	sf::Vector2f position = sf::Vector2f(16 * x, 16 * y);
	sf::Vector2f viewCenter = view.getCenter();
	sf::Vector2f viewSize = view.getSize();
	if (position.x > viewCenter.x - (2.f * viewSize.x / 3.f) && position.x < viewCenter.x + (2.f * viewSize.x / 3.f)
		&& position.y > viewCenter.y - (2.f * viewSize.y / 3.f) && position.y < viewCenter.y + (2.f * viewSize.y / 3.f)) {
		return true;
	}
	return false;
}
*/