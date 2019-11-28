#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__

#include "World.h"

class Map {

  sf::RectangleShape background_;
  size_t pos_x_, pos_y_;
  size_t width_, height_;

  const sf::Color forest_map_color_ = sf::Color(0, 250, 0, 255);
  const sf::Color ocean_map_color_ = sf::Color(0, 0, 250, 255);
  const sf::Color magic_map_color_ = sf::Color(125, 0, 125, 255);
  const sf::Color swamp_map_color_ = sf::Color(0, 128, 128, 255);
  const sf::Color unocean_map_color_ = sf::Color(102, 51, 0, 255);
  const sf::Color desert_map_color_ = sf::Color(140, 100, 0, 255);

public:

  explicit Map(const Player& player);

  void draw(sf::RenderWindow& window, const World& world, const Player& player);

};

#endif
