#include "World.h"
/*
class Biome {
private:
	int biomeID;
	std::vector<Wildlife> wildlife;
	std::vector<Plantlife> plantlife;
	//std::vector<Dungons, Events?, ...>
public:
	
	void generate();
	void update();
	void draw(sf::RenderWindow &window);
};

void Biome::Biome(int biomeID, std::vector<std::vector<Tile>> Tiles) {
	this->biomeID = biomeID;
}

class World {
private:
	std::vector<std::vector<Tile>> Tiles;
	std::vector<Biome> Biomes;
public:
	void update();
	void draw(sf::RenderWindow &window);
};
*/

//WORLD CONSTRUCTOR (GENERATES WORLD)
World::World(sf::Vector2u worldSize , sf::Sprite &grassS, sf::Sprite &sandS, sf::Sprite &waterS, sf::Texture &forestTreeT, sf::Sprite &forestTreeS,
	         sf::Texture &forestSmallTreeT, sf::Sprite &forestSmallTreeS, sf::Texture &forestBushT, sf::Sprite &forestBushS, sf::Sprite &forestMossS, 
	         const int tileSize) {

	const int grassSize = 10;
	const int sandSize = 1;
	const int waterSize = 1;
	const int forestTreeTops = 2;
	const int forestTreeTrunks = 3;
	const int forestSmallTreeTops = 2;
	const int forestSmallTreeTrunks = 3;
	const int forestBushTops = 3;
	const int forestBushTrunks = 2;
	const int forestMossSize = 3;

  //Get Perlin world (of size, smallest power of 2 larger than worldSize)
	int smallest2Power = 1;
	while (smallest2Power < worldSize.x || smallest2Power < worldSize.y) smallest2Power *= 2;

	std::cout << "Getting perlinBiomes" << std::endl;
	std::vector<std::vector<float>> perlinBiome = perlin2D(smallest2Power);
	const int avgPDepthBiome = 5;
	std::vector<std::vector<std::vector<float>>> avgPerlinBiome;
	avgPerlinBiome.push_back(perlinBiome);
	for (int i = 0; i < avgPDepthBiome - 1; i++) {
		std::vector<std::vector<float>> avgPerlinInew;
		for (int j = 0; j < avgPerlinBiome[i].size(); j++) {
			std::vector<float> avgPerlinIJnew;
			for (int k = 0; k < avgPerlinBiome[i][j].size(); k++) {
				avgPerlinIJnew.push_back(averageAbout(j,k,avgPerlinBiome[i],i + 2));
			}
			avgPerlinInew.push_back(avgPerlinIJnew);
		}
		avgPerlinBiome.push_back(avgPerlinInew);
	}

	std::cout << "Getting perlinTop" << std::endl;
	std::vector<std::vector<float>> perlinTop = perlin2D(smallest2Power);
	const int avgPDepthTop = 3;
	std::vector<std::vector<std::vector<float>>> avgPerlinTop;
	avgPerlinTop.push_back(perlinTop);
	for (int i = 0; i < avgPDepthTop - 1; i++) {
		std::vector<std::vector<float>> avgPerlinInew;
		for (int j = 0; j < avgPerlinTop[i].size(); j++) {
			std::vector<float> avgPerlinIJnew;
			for (int k = 0; k < avgPerlinTop[i][j].size(); k++) {
				avgPerlinIJnew.push_back(averageAbout(j, k, avgPerlinTop[i], i + 2));
			}
			avgPerlinInew.push_back(avgPerlinIJnew);
		}
		avgPerlinTop.push_back(avgPerlinInew);
	}

  //Biome Select
	int biomes[3] = { 1,2,3 };

  //Initialize Tiles / Biome positions (uses halfDiff to determine inside of perlin vector)
	sf::Vector2u halfDiff = sf::Vector2u((perlinBiome.size() - worldSize.x) / 2, (perlinBiome.size() - worldSize.y) / 2);
	
	std::cout << "Getting Biome Bounds" << std::endl;
	float highBoundBiome, midBoundBiome, lowBoundBiome;
	highBoundBiome = percentBound(.01, avgPerlinBiome[avgPDepthBiome - 1]);
	midBoundBiome = percentBound(.90, avgPerlinBiome[avgPDepthBiome - 1]);
	lowBoundBiome = percentBound(.99, avgPerlinBiome[avgPDepthBiome - 1]);
	
	std::cout << "Getting Top Bounds" << std::endl;
	float highBoundTop, midBoundTop, lowBoundTop, treeBound, lowtreeBound;
	highBoundTop = percentBound(.05, avgPerlinTop[avgPDepthTop - 1]);
	midBoundTop = percentBound(.15, avgPerlinTop[avgPDepthTop - 1]);
	treeBound = percentBound(.3, avgPerlinTop[avgPDepthTop - 1]);
	lowtreeBound = percentBound(.8, avgPerlinTop[avgPDepthTop - 1]);

	std::cout << "Pasting Tiles into world" << std::endl;
	for (int i = halfDiff.x; i < worldSize.x + halfDiff.x; i++) {
		std::vector<Tile> tempTiles;
		for (int j = halfDiff.y; j < worldSize.y + halfDiff.y; j++) {
			float avgPBiome = averageAbout(i, j, avgPerlinBiome[avgPDepthBiome - 1], avgPDepthBiome);
			float avgPTop = averageAbout(i, j, avgPerlinTop[avgPDepthTop - 1], avgPDepthTop);
			if (avgPBiome >= highBoundBiome) tempTiles.push_back(Tile(&sandS, sandSize, biomes[1]));
			else if (avgPBiome >= midBoundBiome) {
				if(avgPTop >= highBoundTop) tempTiles.push_back(Tile(rand() % 10, &grassS, grassSize, biomes[0]));
				else if(avgPTop >= midBoundTop) tempTiles.push_back(Tile(rand() % 9, &grassS, grassSize, biomes[0]));
				else if(avgPTop >= treeBound) tempTiles.push_back(Tile(rand() % 5, &grassS, grassSize, biomes[0]));
				else if (avgPTop >= lowtreeBound) {
					tempTiles.push_back(Tile(rand() % 5, &grassS, grassSize, biomes[0]));
					int tempRand = rand() % 100;
					if (tempRand < 2) {
						forestTrees.push_back(forestTree(sf::Vector2f(j, i), &forestTreeT, &forestTreeS, forestTreeTrunks, forestTreeTops, tileSize)); std::cout << i << " " << j << std::endl;
					}
					else if(tempRand < 15) forestSmallTrees.push_back(forestSmallTree(sf::Vector2f(j, i), &forestSmallTreeT, &forestSmallTreeS, forestSmallTreeTrunks, forestSmallTreeTops, tileSize));
					else if(tempRand < 40) forestBushs.push_back(forestBush(sf::Vector2f(j, i), &forestBushT, &forestBushS, forestBushTrunks, forestBushTops, tileSize));
				}
			}
			else if (avgPBiome >= lowBoundBiome) tempTiles.push_back(Tile(&sandS, sandSize,biomes[1]));
			else tempTiles.push_back(Tile(&waterS, waterSize,biomes[2]));
		}
		Tiles.push_back(tempTiles);
	}

	std::cout << forestTrees.size() << " " << forestSmallTrees.size() << " " << forestBushs.size() << std::endl;
	/*
	std::cout << "Pasting Trees into the world" << std::endl;
	for (int i = 0; i < 1000; i++) {
		forestTrees.push_back(forestTree(sf::Vector2f(rand() % 2000, rand() % 2000), &forestTreeT, &forestTreeS, forestTreeTrunks, forestTreeTops , tileSize));
	}

	std::cout << "Pasting SmallTrees into the world" << std::endl;
	for (int i = 0; i < 2000; i++) {
		forestSmallTrees.push_back(forestSmallTree(sf::Vector2f(rand() % 2000, rand() % 2000), &forestSmallTreeT, &forestSmallTreeS, forestSmallTreeTrunks, forestSmallTreeTops, tileSize));
	}

	std::cout << "Pasting Bushs into the world" << std::endl;
	for (int i = 0; i < 3000; i++) {
		forestBushs.push_back(forestBush(sf::Vector2f(rand() % 2000, rand() % 2000), &forestBushT, &forestBushS, forestBushTrunks, forestBushTops, tileSize));
	}
	*/
	std::cout << "Pasting Mosses into the world" << std::endl;
	for (int i = 0; i < 3000; i++) {
		forestMosses.push_back(forestMoss(sf::Vector2f(rand() % 2000, rand() % 2000), &forestMossS, forestMossSize, tileSize));
	}
}

//UPDATE WORLD
void World::update() {

}

//DRAW WORLD
void World::draw(sf::RenderWindow &window, Player &player) {
	const float tileSize = 32.f;
	sf::View view = player.getView();
	sf::Vector2f viewCenter = view.getCenter();
	sf::Vector2f viewSize = view.getSize();
	for (int i = max(0,(viewCenter.x - (2.f * viewSize.x / 3.f))/ tileSize); i < min((viewCenter.x + (2.f * viewSize.x / 3.f))/tileSize, window.getSize().x); i++) {
		for (int j = max(0,(viewCenter.y - (2.f * viewSize.y / 3.f))/tileSize); j < min((viewCenter.y + (2.f * viewSize.y / 3.f))/tileSize, window.getSize().y); j++) {
				Tiles[j][i].draw(window, i, j);
		}
	}
	for (int i = 0; i < forestTrees.size(); i++) {
		forestTrees[i].draw(window, view);
	}
	for (int i = 0; i < forestSmallTrees.size(); i++) {
		forestSmallTrees[i].draw(window, view);
	}
	for (int i = 0; i < forestBushs.size(); i++) {
		forestBushs[i].draw(window, view);
	}
	for (int i = 0; i < forestMosses.size(); i++) {
		forestMosses[i].draw(window);
	}
}
