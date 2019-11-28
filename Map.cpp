#include "Map.h"

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

  // TO DO : Think about way to do these calculations only once per 
  //         frame ( now in Map and World draw ) 
  auto size = player.get_View().getSize();
  auto center = player.get_View().getCenter();

  int begin_i = center.x - (size.x / 2);
  int begin_j = center.y - (size.y / 2);

  background_.setPosition(begin_i + pos_x_, begin_j + pos_y_);
  window.draw(background_);

  // TO DO : Use window size to determine size of map drawn
  sf::RectangleShape map_pixel;
  map_pixel.setSize(sf::Vector2f(1, 1));

  // TO DO : Seg fault outside of map range
  int offset_x = (center.x / 32) - (width_ / 2);
  int offset_y = (center.y / 32) - (height_ / 2);
  for(int i = offset_x, end_i = offset_x + width_; i < end_i; ++i){
    for(int j = offset_y, end_j = offset_y + height_; j < end_j; ++j) {
      map_pixel.setPosition(sf::Vector2f(begin_i + pos_x_ + i - offset_x,
                                         begin_j + pos_y_ + j - offset_y));
      switch(world.tile_map_[i][j]->biome_) {
        case Magic_:
          map_pixel.setFillColor(magic_map_color_);
          break;

        case Forest_:
          map_pixel.setFillColor(forest_map_color_);
          break;

        case Desert_:
          map_pixel.setFillColor(desert_map_color_);
          break;

        case Ocean_:
          map_pixel.setFillColor(ocean_map_color_);
          break;

        case Swamp_:
          map_pixel.setFillColor(swamp_map_color_);
          break;

        case Unocean_:
          map_pixel.setFillColor(unocean_map_color_);
          break;

        default:
          map_pixel.setFillColor(sf::Color(0, 0, 0, 255));
          break;
      }
     
      if(world.tile_map_[i][j]->is_water_) {
        map_pixel.setFillColor(ocean_map_color_);
      }

      window.draw(map_pixel);
    }
  }

}
