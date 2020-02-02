#include "Map.h"

// TO DO : Error : weird lines on map

Map::Map(const Player& player) {
 
  // Size GUI Map
  auto size = player.get_View().getSize();
  pos_x_ = size.x * 0.8;
  pos_y_ = size.y * 0.8;
  width_ = size.x * .2;
  height_ = size.y * 0.2;

  background_.setSize(sf::Vector2f(width_, height_));
  background_.setFillColor(sf::Color(15, 15, 20, 100));
  background_.setOutlineColor(sf::Color(215, 120, 15, 200));
  background_.setOutlineThickness(1);
}

void Map::draw(sf::RenderWindow& window, const World& world, const Player& player) {

  // Calculate views top left position
  auto size = player.get_View().getSize();
  auto center = player.get_View().getCenter();
  int view_left = center.x - (size.x / 2);
  int view_top = center.y - (size.y / 2);
  // Draw background relative to view
  background_.setPosition(view_left + pos_x_, view_top + pos_y_);
  window.draw(background_);


  sf::RectangleShape map_pixel;
  map_pixel.setSize(sf::Vector2f(1, 1));

  // Start index positions for map
  int map_x = (center.x / 32) - (width_ / 2);
  int map_y = (center.y / 32) - (height_ / 2);

  // TO DO : do generation_range square for resources instead of single dot
  // TO DO : make different colors for different resources?
  const auto& tile_map_ = world.planes_.at(player.current_plane())->tile_map_;
  const auto& resource_map_ = world.planes_.at(player.current_plane())->resource_map_;
  for(int j = max(0, map_y), end_j = min(map_y + height_, tile_map_.size()); j < end_j; ++j) {
    for(int i = max(0, map_x), end_i = min(map_x + width_, tile_map_[j].size()); i < end_i; ++i) {

      map_pixel.setPosition(sf::Vector2f(view_left + pos_x_ + i - map_x,
                                         view_top + pos_y_ + j - map_y));

      // Set map color based on layer priority & draw ( resource, water, tile )
      if(resource_map_[j][i]) { // checks if there is a resource
        map_pixel.setFillColor(resource_colors.at(tile_map_[j][i]->biome_));
        window.draw(map_pixel);
      } else if(tile_map_[j][i]) { // checks if there is a tile
        if(tile_map_[j][i]->is_water_) {
          map_pixel.setFillColor(river_color_);
        } else {
          map_pixel.setFillColor(tile_colors.at(tile_map_[j][i]->biome_));
        }
        window.draw(map_pixel);
      }
    }
  }

}
