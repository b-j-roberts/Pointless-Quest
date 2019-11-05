#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__

#include "World.h"

class Map {

  sf::RectangleShape background_;
  size_t width_, height_;

public:

  explicit Map(const Player& player);

  void draw(sf::RenderWindow& window, const World& world, const Player& player);

};

#endif
