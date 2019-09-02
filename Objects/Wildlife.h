#ifndef __WILDLIFE_H_INCLUDED__
#define __WILDLIFE_H_INCLUDED__

#include "../Include/Functions.h"

class Wildlife {
private:
	sf::Vector2f position, velocity;
public:
	Wildlife(sf:Vector2f position);
	void update();
	void draw(sf::RenderWindow &window, sf::Sprite* sprite);
};

#endif
