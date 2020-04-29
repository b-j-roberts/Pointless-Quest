#include "City.h"

#include <iostream>
void City_Plane::generate(size_t width, size_t height) {
  // TO DO : Pass city_land_ to get Bounded instead?
  cities_.push_back(std::make_unique<First_City>());

  // TO DO : Debug
  for(size_t i = width / 2 - 2; i < width / 2 + 3; ++i) {
    for(size_t j = height / 2 - 2; j < height / 2 + 3; ++j) {
      city_land_[j][i] = true;
    }
  }

  smooth_Bounded_Edges(city_land_);
  for(size_t i = 0; i < height; ++i) {
    for(size_t j = 0; j < width; ++j) {
      if(city_land_[i][j] && is_Bounded_Edge(city_land_, i, j)) {
        // Insert Proper wall
        if(!city_land_[i+1][j] || !city_land_[i-1][j]) { 
          //std::cout << "wall at : x,y : " << j * 32 <<" , " << i * 32 << "\n"; 
          city_horz_walls_[i][j] = cities_[0]->get_horz_wall(j, i);
        }
        if(!city_land_[i][j-1]) {
          if(city_land_[i+1][j]) city_vert_walls_[i][j-1] = cities_[0]->get_vert_wall(j, i+1);
        }
        if(!city_land_[i][j+1]) {
          if(city_land_[i+1][j]) city_vert_walls_[i][j+1] = cities_[0]->get_vert_wall(j + 1, i+1);
        }
       /* maybe make center of x (horizontal) & y (vertical) for origin so that we may have unique?*/
      }
    }
  }

}

void City_Plane::draw(sf::RenderWindow& window, const Player& player) {

  sf::FloatRect player_box = player.bounding_box();

  for(size_t j = player.y_range().first; j < player.y_range().second; ++j) {
    for(size_t i = player.x_range().first; i < player.x_range().second; ++i) {
      if(city_horz_walls_[j][i]) { // ignores nullptr
        if(city_horz_walls_[j][i]->is_overlapped(player_box)) {
          city_horz_walls_[j][i]->transparent_draw(window);
        } else {
          city_horz_walls_[j][i]->draw(window);
        }
      }
      if(city_vert_walls_[j][i]) { // ignores nullptr
        if(city_vert_walls_[j][i]->is_overlapped(player_box)) {
          city_vert_walls_[j][i]->transparent_draw(window);
        } else {
          city_vert_walls_[j][i]->draw(window);
        }
      }
    }
  }
}

std::shared_ptr<Resource> First_City::get_horz_wall(int x, int y) {
  return std::make_shared<Wall_Horizontal>(x * 32, y * 32, *this);
}

std::shared_ptr<Resource> First_City::get_vert_wall(int x, int y) {
  return std::make_shared<Wall_Vertical>(x * 32, y * 32, *this);
}
