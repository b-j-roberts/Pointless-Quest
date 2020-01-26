#ifndef __CITY_H_INCLUDED__
#define __CITY_H_INCLUDED__

#include "Functions.h"

class City {

  std::vector<std::vector<bool>> city_land_; // true - if is city block
  //std::map<size_t?, std::map<size_t?, std::shared_ptr<sf::Sprite>> city_walls_;

  virtual std::shared_ptr<sf::Sprite> get_wall() { }

public:

  City(const size_t width, const size_t height):
    city_land_(height, std::vector<bool>(width, false));

  void generate() {
    // TO DO : Pass city_land_ to get Bounded instead?
    auto region = get_Bounded_Region(width, height, width * height * .01);
    smooth_Bounded_Edges(region);
    for(size_t i = 0; i < height; ++i) {
      for(size_t j = 0; j < width; ++j) {
        if(is_Bounded_Edge(vec[i][j])) {
         /* Insert correct walls here */ 
         /* maybe make center of x (horizontal) & y (vertical) for origin so that we may have unique?*/
        }
      }
    }

  }

};

class First_City : public City {

  Sprite_Obj wall_sprite_obj_;

  // TO DO : Think about choosing vertical or horizontal wall sprite
  std::shared_ptr<sf::Sprite> get_wall() override {
    return wall_sprite_obj_/*TO DO : Index sprite here */;
  }

public:

  First_City(const size_t width, const size_t height):
    City(width, height),
    wall_sprite_obj_(/* TO DO*/) { this->generate(); }

}; 

#endif
