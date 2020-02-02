#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__

#include "World.h"

// GUI Map that shows surrounding area biomes & resources
class Map {

  // GUI Map background, view relative location, and size info
  sf::RectangleShape background_;
  size_t pos_x_, pos_y_;
  size_t width_, height_;

  // Biome's Tile Map Colors map
  const std::map<Biome_enum, sf::Color> tile_colors = {
    {Forest_,  sf::Color(124, 252, 0, 255)},
    {Ocean_,   sf::Color(0, 0, 250, 255)},
    {Magic_,   sf::Color(125, 0, 125, 255)},
    {Swamp_,   sf::Color(0, 128, 128, 255)},
    {Old_Ocean_, sf::Color(102, 51, 0, 255)},
    {Desert_,  sf::Color(140, 100, 0, 255)},
    {Tundra_,  sf::Color(240, 234, 214, 255)},

    {Cave_,    sf::Color(73, 23, 23)}
  }; 

  // Biome's Resource Map Colors map
  const std::map<Biome_enum, sf::Color> resource_colors = {
    {Forest_,  sf::Color(0, 100, 0, 255)},
    {Ocean_,   sf::Color(0, 191, 255, 255)},
    {Magic_,   sf::Color(255, 20, 147, 255)},
    {Swamp_,   sf::Color(50, 205, 50, 255)},
    {Old_Ocean_, sf::Color(255, 255, 240, 255)},
    {Desert_,  sf::Color(173, 255, 47, 255)},
    {Tundra_,  sf::Color(188, 143, 143, 255)},

    {Cave_,    sf::Color(65, 118, 159)}
  }; 

  // River Map Color
  const sf::Color river_color_ = sf::Color(0, 0, 250, 255);

public:

  // Noncopyable
  Map(const Map&) = delete;
  Map& operator=(const Map&) = delete;

  explicit Map(const Player&);

  // Draw map gui element to screen ( 1 pixel per tile )
  void draw(sf::RenderWindow&, const World&, const Player&);
};

#endif
