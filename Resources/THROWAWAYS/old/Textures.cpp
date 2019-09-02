#include "Textures.h"

void loadTileTexture(const int number, const int size, sf::Texture* text) {
	const int tileSize = 32;
	for (int i = 0; i < size; i++) {
		if (!text[i].loadFromFile("Resources/Tiles.png", sf::IntRect(tileSize * i, tileSize * (number - 1), tileSize, tileSize))) {
			std::cout << "Error loading tile_" << number << " texture in position [" << i << "]" << std::endl;
		}
	}
}

void loadForestTreeTexture(const int trunks, const int tops, sf::Texture* texture) {
	const int treeTrunkWidth = 64;
	const int treeTrunkHeight = 128;
	for (int i = 0; i < trunks; i++) {
		if (!texture[i].loadFromFile("Resources/forestTree.png", sf::IntRect(treeTrunkWidth * i, 0, treeTrunkWidth, treeTrunkHeight))) {
			std::cout << "Error loading forestTree_Trunk texture in position [" << i << "]" << std::endl;
		}
	}
	const int treeTopWidth = 128;
	const int treeTopHeight = 96;
	for (int i = 0; i < tops; i++) {
		if (!texture[trunks+i].loadFromFile("Resources/forestTree.png", sf::IntRect(treeTopWidth * i, treeTrunkHeight, treeTopWidth, treeTopHeight))) {
			std::cout << "Error loading forestTree_Top texture in position [" << i << "]" << std::endl;
		}
	}
	
	//Load transparent Textures
	for (int i = 0; i < trunks; i++) {
		if (!texture[trunks + tops + i].loadFromFile("Resources/forestTree.png", sf::IntRect(treeTrunkWidth * (i + trunks), 0, treeTrunkWidth, treeTrunkHeight))) {
			std::cout << "Error loading forestTree_Trunk_inv texture in position [" << i << "]" << std::endl;
		}
	}
	for (int i = 0; i < tops; i++) {
		if (!texture[2 * trunks + tops + i].loadFromFile("Resources/forestTree.png", sf::IntRect(treeTopWidth * i, treeTrunkHeight + treeTopHeight, treeTopWidth, treeTopHeight))) {
			std::cout << "Error loading forestTree_Top_inv texture in position [" << i << "]" << std::endl;
		}
	}
}

void loadForestSmallTreeTexture(const int trunks, const int tops, sf::Texture* texture) {
	const int treeTrunkWidth = 32;
	const int treeTrunkHeight = 64;
	for (int i = 0; i < trunks; i++) {
		if (!texture[i].loadFromFile("Resources/forestSmallTree.png", sf::IntRect(treeTrunkWidth * i, 0, treeTrunkWidth, treeTrunkHeight))) {
			std::cout << "Error loading forestSmallTree_Trunk texture in position [" << i << "]" << std::endl;
		}
	}
	const int treeTopWidth = 32;
	const int treeTopHeight = 64;
	for (int i = 0; i < tops; i++) {
		if (!texture[trunks + i].loadFromFile("Resources/forestSmallTree.png", sf::IntRect(treeTopWidth * i, treeTrunkHeight, treeTopWidth, treeTopHeight))) {
			std::cout << "Error loading forestSmallTree_Top texture in position [" << i << "]" << std::endl;
		}
	}

	//Load transparent Textures
	for (int i = 0; i < trunks; i++) {
		if (!texture[trunks + tops + i].loadFromFile("Resources/forestSmallTree.png", sf::IntRect(treeTrunkWidth * (i + trunks), 0, treeTrunkWidth, treeTrunkHeight))) {
			std::cout << "Error loading forestSmallTree_Trunk_inv texture in position [" << i << "]" << std::endl;
		}
	}
	for (int i = 0; i < tops; i++) {
		if (!texture[2 * trunks + tops + i].loadFromFile("Resources/forestSmallTree.png", sf::IntRect(treeTopWidth * i, treeTrunkHeight + treeTopHeight, treeTopWidth, treeTopHeight))) {
			std::cout << "Error loading forestSmallTree_Top_inv texture in position [" << i << "]" << std::endl;
		}
	}
}

void loadForestBushTexture(const int trunks, const int tops, sf::Texture* texture) {
	const int treeTrunkWidth = 32;
	const int treeTrunkHeight = 32;
	for (int i = 0; i < trunks; i++) {
		if (!texture[i].loadFromFile("Resources/forestBush.png", sf::IntRect(treeTrunkWidth * i, 0, treeTrunkWidth, treeTrunkHeight))) {
			std::cout << "Error loading forestBush_Trunk texture in position [" << i << "]" << std::endl;
		}
	}
	const int treeTopWidth = 32;
	const int treeTopHeight = 32;
	for (int i = 0; i < tops; i++) {
		if (!texture[trunks + i].loadFromFile("Resources/forestBush.png", sf::IntRect(treeTopWidth * i, treeTrunkHeight, treeTopWidth, treeTopHeight))) {
			std::cout << "Error loading forestBush_Top texture in position [" << i << "]" << std::endl;
		}
	}

	//Load transparent Textures
	for (int i = 0; i < trunks; i++) {
		if (!texture[trunks + tops + i].loadFromFile("Resources/forestBush.png", sf::IntRect(treeTrunkWidth * (i + trunks), 0, treeTrunkWidth, treeTrunkHeight))) {
			std::cout << "Error loading forestBush_Trunk_inv texture in position [" << i << "]" << std::endl;
		}
	}
	for (int i = 0; i < tops; i++) {
		if (!texture[2 * trunks + tops + i].loadFromFile("Resources/forestBush.png", sf::IntRect(treeTopWidth * i, treeTrunkHeight + treeTopHeight, treeTopWidth, treeTopHeight))) {
			std::cout << "Error loading forestBush_Top_inv texture in position [" << i << "]" << std::endl;
		}
	}
}

void loadForestMossTexture(const int mosses, sf::Texture* texture) {
	const int mossWidth = 32;
	const int mossHeight = 32;
	for (int i = 0; i < mosses; i++) {
		if (!texture[i].loadFromFile("Resources/forestMoss.png", sf::IntRect(mossWidth * i, 0, mossWidth, mossHeight))) {
			std::cout << "Error loading forestMoss texture in position [" << i << "]" << std::endl;
		}
	}
}


//Textures in different formats on tree and smalltree/bush, make consistent so we can make a general function for tree structures