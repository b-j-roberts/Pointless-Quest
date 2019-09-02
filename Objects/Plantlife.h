#ifndef __PLANTLIFE_H_INCLUDED__
#define __PLANTLIFE_H_INCLUDED__

#include "../Include/Functions.h"
/*
class Plantlife {
private:
	sf::Vector2f position;
public:
	Plantlife(sf::Vector2f position);
	void draw(sf::RenderWindow &window, sf::Sprite* sprites);
};
*/

class forestTree {
private:
	int trunkType, topType;
	sf::Vector2f position;
	sf::Texture *texture;
	sf::Sprite* sprites[2];
public:
	forestTree(sf::Vector2f position, sf::Texture *texture, sf::Sprite* sprites, const int trunks, const int tops, const int tileSize);
	void draw(sf::RenderWindow& window, sf::View view);
};

class forestSmallTree {
private:
	int trunkType, topType;
	sf::Vector2f position;
	sf::Texture *texture;
	sf::Sprite* sprites[2];
public:
	forestSmallTree(sf::Vector2f position, sf::Texture *texture, sf::Sprite* sprites, const int trunks, const int tops, const int tileSize);
	void draw(sf::RenderWindow& window, sf::View view);
};

class forestBush {
private:
	int trunkType, topType;
	sf::Vector2f position;
	sf::Texture *texture;
	sf::Sprite* sprites[2];
public:
	forestBush(sf::Vector2f position, sf::Texture *texture, sf::Sprite* sprites, const int trunks, const int tops, const int tileSize);
	void draw(sf::RenderWindow& window, sf::View view);
};

class forestMoss {
private:
	int mossType;
	sf::Vector2f position;
	sf::Sprite* sprite;
public:
	forestMoss(sf::Vector2f position, sf::Sprite* sprite, const int mosses, const int tileSize);
	void draw(sf::RenderWindow& window);
};

#endif