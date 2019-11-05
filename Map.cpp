#include "Map.h"

#include <iostream> // TO DO : Debug

Map::Map(const Player& player) {
 
  auto size = player.get_View().getSize();
  width_ = size.x * 0.75;
  height_ = size.y * 0.75;

  background_.setSize(sf::Vector2f(size.x * .2, size.y * 0.25));
  background_.setFillColor(sf::Color(15, 15, 20, 100));
  background_.setOutlineColor(sf::Color(215, 120, 15, 200));
  background_.setOutlineThickness(1);

}

void Map::draw(sf::RenderWindow& window, const World& world, const Player& player) {

  // TO DO : Think about way to do these calculations only once per 
  //         frame ( now in Map and World draw ) 
  auto size = player.get_View().getSize();
  auto center = player.get_View().getCenter();

  int begin_i = center.x - (size.x / 2);
  int begin_j = center.y - (size.y / 2);

  background_.setPosition(begin_i + width_, begin_j + height_);
  window.draw(background_);

  // TO DO : Create these colors in the biomes?
  sf::Color forest_map_color(sf::Color(0, 250, 0, 255));
  sf::Color ocean_map_color(sf::Color(0, 0, 250, 255));
  sf::Color magic_map_color(sf::Color(125, 0, 125, 255));
  sf::Color desert_map_color(sf::Color(140, 100, 0, 255));

  // TO DO : Use window size to determine size of map drawn
  sf::RectangleShape map_pixel;
  map_pixel.setSize(sf::Vector2f(1, 1));

  // TO DO : Seg fault outside of map range
  int offset_x = (begin_i - 1024) / 32;
  int offset_y = (begin_j - 1024) / 32;
  for(int i = (begin_i - 1024) / 32, end_i = (begin_i + size.x + 1024) / 32; i < end_i; ++i) {
    for(int j = (begin_j - 1024) / 32, end_j = (begin_j + size.y + 1024) / 32; j < end_j; ++j) {
      map_pixel.setPosition(sf::Vector2f(begin_i + width_ + i  - offset_x,
                                         begin_j + height_ + j - offset_y));
      switch(world.tile_map_[i][j]->biome_) {
        case Magic_:
          map_pixel.setFillColor(magic_map_color);
          break;

        case Forest_:
          map_pixel.setFillColor(forest_map_color);
          break;

        case Desert_:
          map_pixel.setFillColor(desert_map_color);
          break;

        case Ocean_:
          map_pixel.setFillColor(ocean_map_color);
          break;
      }
      
      window.draw(map_pixel);
    }
  }

}
