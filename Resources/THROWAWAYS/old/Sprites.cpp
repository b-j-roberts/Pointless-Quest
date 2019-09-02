#include "Sprites.h"

//Load tile sprites in an array only with its own biome (also does textures)
void loadTileSprite(int number, int size, sf::Sprite* sprite, sf::Texture* texture) {
	const float tileSize = 32.f;
	loadTileTexture(number, size, texture);
	for (int i = 0; i < size; i++) {
		sprite[i].setTexture(texture[i]);
		sprite[i].setOrigin(tileSize / 2, tileSize / 2);
	}
}

//load forestTree sprite in an array of size (trunks + tops) holding trunks sprites first and then tops, then looping back over for invisible textures
void loadForestTreeSprite(const int trunks, const int tops, sf::Sprite* sprite, sf::Texture* texture) {
	const float treeTrunkWidth = 64;
	const float treeTrunkHeight = 128;
	const float treeTopWidth = 128;
	const float treeTopHeight = 96;
	loadForestTreeTexture(trunks, tops, texture);
	for (int i = 0; i < (2 * trunks) + (2 * tops); i++) {
		sprite[i].setTexture(texture[i]);
	}
	for (int i = 0; i < trunks; i++) {
		sprite[i].setOrigin(treeTrunkWidth / 2, treeTrunkHeight);
		sprite[i + trunks + tops].setOrigin(treeTrunkWidth / 2, treeTrunkHeight);
	}
	for (int i = 0; i < tops; i++) {
		sprite[i + trunks].setOrigin(treeTopWidth / 2, treeTopHeight - 16); //16 here is moving down for leeway
		sprite[i + (2 * trunks) + tops].setOrigin(treeTrunkWidth / 2, treeTrunkHeight);
		sprite[i + trunks].scale(1.7,1.5);
		sprite[i + (2 * trunks) + tops].scale(1.7, 1.5);
	}
}

void loadForestSmallTreeSprite(const int trunks, const int tops, sf::Sprite* sprite, sf::Texture* texture) {
	const float treeTrunkWidth = 32;
	const float treeTrunkHeight = 64;
	const float treeTopWidth = 32;
	const float treeTopHeight = 64;
	loadForestSmallTreeTexture(trunks, tops, texture);
	for (int i = 0; i < (2 * trunks) + (2 * tops); i++) {
		sprite[i].setTexture(texture[i]);
	}
	for (int i = 0; i < trunks; i++) {
		sprite[i].setOrigin(treeTrunkWidth / 2, treeTrunkHeight);
		sprite[i + trunks + tops].setOrigin(treeTrunkWidth / 2, treeTrunkHeight);
	}
	for (int i = 0; i < tops; i++) {
		sprite[i + trunks].setOrigin(treeTopWidth / 2, treeTopHeight - 10);
		sprite[i + (2 * trunks) + tops].setOrigin(treeTrunkWidth / 2, treeTrunkHeight);
		sprite[i + trunks].scale(1.7, 1.5);
		sprite[i + (2 * trunks) + tops].scale(1.7, 1.5);
	}
}

void loadForestBushSprite(const int trunks, const int tops, sf::Sprite* sprite, sf::Texture* texture) {
	const float treeTrunkWidth = 32;
	const float treeTrunkHeight = 32;
	const float treeTopWidth = 32;
	const float treeTopHeight = 32;
	loadForestBushTexture(trunks, tops, texture);
	for (int i = 0; i < (2 * trunks) + (2 * tops); i++) {
		sprite[i].setTexture(texture[i]);
	}
	for (int i = 0; i < trunks; i++) {
		sprite[i].setOrigin(treeTrunkWidth / 2, treeTrunkHeight);
		sprite[i + trunks + tops].setOrigin(treeTrunkWidth / 2, treeTrunkHeight);
	}
	for (int i = 0; i < tops; i++) {
		sprite[i + trunks].setOrigin(treeTopWidth / 2, treeTopHeight - 8); //3 here is moving down for leeway
		sprite[i + (2 * trunks) + tops].setOrigin(treeTrunkWidth / 2, treeTrunkHeight);
		sprite[i + trunks].scale(1.7, 1.5);
		sprite[i + (2 * trunks) + tops].scale(1.7, 1.5);
	}
}

void loadForestMossSprite(const int mosses, sf::Sprite* sprite, sf::Texture* texture) {
	const float mossWidth = 32;
	const float mossHeight = 32;
	loadForestMossTexture(mosses, texture);
	for (int i = 0; i < mosses; i++) {
		sprite[i].setTexture(texture[i]);
	}
}