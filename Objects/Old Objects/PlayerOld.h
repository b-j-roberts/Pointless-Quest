#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include "Tile.h"
#include <SFML/Graphics/View.hpp>

class Player {
	private:
		sf::Vector2f position, velocity;
		float angle;
		sf::View view;
		sf::Texture texture;
		sf::Sprite sprite;

	public:
		Player(float Xscale);
		Player(sf::Vector2f position, float Xscale);
		void update(sf::Vector2f Lstick, sf::Vector2f Rstick);
		void draw(sf::RenderWindow &window);
		sf::View getView();
};

#endif