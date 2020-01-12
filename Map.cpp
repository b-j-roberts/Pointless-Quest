#include "Map.h"

// TO DO : Error in weird lines being missed

Map::Map(const Player& player) {
 
  auto size = player.get_View().getSize();
  pos_x_ = size.x * 0.75;
  pos_y_ = size.y * 0.75;
  width_ = size.x * .2;
  height_ = size.y * 0.25;

  background_.setSize(sf::Vector2f(width_, height_));
  background_.setFillColor(sf::Color(15, 15, 20, 100));
  background_.setOutlineColor(sf::Color(215, 120, 15, 200));
  background_.setOutlineThickness(1);

}

void Map::draw(sf::RenderWindow& window, const World& world, const Player& player) {

  auto size = player.get_View().getSize();
  auto center = player.get_View().getCenter();

  int begin_i = center.x - (size.x / 2);
  int begin_j = center.y - (size.y / 2);

  background_.setPosition(begin_i + pos_x_, begin_j + pos_y_);
  window.draw(background_);

  // TO DO : Use window size to determine size of map drawn ?
  sf::RectangleShape map_pixel;
  map_pixel.setSize(sf::Vector2f(1, 1));

  int offset_x = (center.x / 32) - (width_ / 2);
  int offset_y = (center.y / 32) - (height_ / 2);

  // TO DO : do generation_range square for resources instead of single dot
  // TO DO : make different colors for different resources?
  for(int i = max(0, offset_x), end_i = min(offset_x + width_, world.tile_map_.size()); 
      i < end_i; ++i) {
    for(int j = max(0, offset_y), end_j = min(offset_y + height_, world.tile_map_[i].size()); 
        j < end_j; ++j) {
      map_pixel.setPosition(sf::Vector2f(begin_i + pos_x_ + i - offset_x,
                                         begin_j + pos_y_ + j - offset_y));

      // According to layer priority, set map color ( resource, water, tile )
      if(world.resource_map_[i][j]){
        map_pixel.setFillColor(resource_colors.at(world.tile_map_[i][j]->biome_));
      } else if(world.tile_map_[i][j]->is_water_) {
        map_pixel.setFillColor(river_color_);
      } else {
        map_pixel.setFillColor(tile_colors.at(world.tile_map_[i][j]->biome_));
      }

      window.draw(map_pixel);
    }
  }

}
