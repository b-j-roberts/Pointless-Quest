#include "Plantlife.h"
/*
//CONSTRUCTOR PLANTLIFE
Plantlife::Plantlife(sf::Vector2f position) {
	this->position = position;
}
*/

//CONSTRUCTOR FOREST TREE
forestTree::forestTree(sf::Vector2f position, sf::Texture *texture, sf::Sprite* sprites, const int trunks, const int tops, const int tileSize) {
	this->position = sf::Vector2f(position.x * tileSize, position.y * tileSize);
	trunkType = rand() % trunks;
	topType = rand() % tops;
	this->texture = texture;
	this->sprites[0] = &sprites[trunkType];
	this->sprites[1] = &sprites[trunks + topType];
}

//DRAW FOREST TREE
void forestTree::draw(sf::RenderWindow& window, sf::View view) {
	//in window function
	sf::Vector2f viewCenter = view.getCenter();
	sf::Vector2f viewSize = view.getSize();
	if (position.x > ((viewCenter.x - (2.f * viewSize.x / 3.f))) && position.x < (viewCenter.x + (2.f * viewSize.x / 3.f))&&
		position.y > ((viewCenter.y - (2.f * viewSize.y / 3.f))) && position.y < (viewCenter.y + (2.f * viewSize.y / 3.f))) {
		const float treeTrunkHeight = 128;
		sprites[0]->setPosition(sf::Vector2f(position.x, position.y));
		sprites[1]->setPosition(sf::Vector2f(position.x, position.y - treeTrunkHeight));
		window.draw(*sprites[0]);
		window.draw(*sprites[1]);
	}
}


//CONSTRUCTOR FOREST SMALL TREE
forestSmallTree::forestSmallTree(sf::Vector2f position, sf::Texture *texture, sf::Sprite* sprites, const int trunks, const int tops, const int tileSize) {
	this->position = sf::Vector2f(position.x * tileSize, position.y * tileSize);
	trunkType = rand() % trunks;
	topType = rand() % tops;
	this->texture = texture;
	this->sprites[0] = &sprites[trunkType];
	this->sprites[1] = &sprites[trunks + topType];
}

//DRAW FOREST SMALL TREE
void forestSmallTree::draw(sf::RenderWindow& window, sf::View view) {
	//in window function
	sf::Vector2f viewCenter = view.getCenter();
	sf::Vector2f viewSize = view.getSize();
	if(position.x > ((viewCenter.x - (2.f * viewSize.x / 3.f))) && position.x < (viewCenter.x + (2.f * viewSize.x / 3.f)) &&
		position.y > ((viewCenter.y - (2.f * viewSize.y / 3.f))) && position.y < (viewCenter.y + (2.f * viewSize.y / 3.f))) {
		const float treeTrunkHeight = 64;
		sprites[0]->setPosition(sf::Vector2f(position.x, position.y));
		sprites[1]->setPosition(sf::Vector2f(position.x, position.y - treeTrunkHeight));
		window.draw(*sprites[0]);
		window.draw(*sprites[1]);
	}
}

//CONSTRUCTOR FOREST BUSH
forestBush::forestBush(sf::Vector2f position, sf::Texture *texture, sf::Sprite* sprites, const int trunks, const int tops, const int tileSize) {
	this->position = sf::Vector2f(position.x * tileSize, position.y * tileSize);
	trunkType = rand() % trunks;
	topType = rand() % tops;
	this->texture = texture;
	this->sprites[0] = &sprites[trunkType];
	this->sprites[1] = &sprites[trunks + topType];
}

//DRAW FOREST BUSH
void forestBush::draw(sf::RenderWindow& window, sf::View view) {
	//in window function
	sf::Vector2f viewCenter = view.getCenter();
	sf::Vector2f viewSize = view.getSize();
	if (position.x > ((viewCenter.x - (2.f * viewSize.x / 3.f))) && position.x < (viewCenter.x + (2.f * viewSize.x / 3.f)) &&
		position.y > ((viewCenter.y - (2.f * viewSize.y / 3.f))) && position.y < (viewCenter.y + (2.f * viewSize.y / 3.f))) {
		const float treeTrunkHeight = 32;
		sprites[0]->setPosition(sf::Vector2f(position.x, position.y));
		sprites[1]->setPosition(sf::Vector2f(position.x, position.y - treeTrunkHeight));
		window.draw(*sprites[0]);
		window.draw(*sprites[1]);
	}
}

//CONSTRUCTOR FOREST MOSS
forestMoss::forestMoss(sf::Vector2f position, sf::Sprite* sprite, const int mosses, const int tileSize) {
	this->position = sf::Vector2f(position.x * tileSize, position.y * tileSize);
	mossType = rand() % mosses;
	this->sprite = &sprite[mossType];
}

//DRAW FOREST MOSS
void forestMoss::draw(sf::RenderWindow& window) {
	sprite->setPosition(sf::Vector2f(position.x, position.y));
	window.draw(*sprite);
}