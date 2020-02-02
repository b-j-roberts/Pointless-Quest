#ifndef __CITY_H_INCLUDED__
#define __CITY_H_INCLUDED__

#include "Resources/Structures.h"

class City {

  std::vector<std::vector<bool>> city_land_; // true - if is city block
  // TO DO : Change so that we can have vertical and horizontal in same position
  std::vector<std::vector<std::shared_ptr<sf::Sprite>>> city_walls_;

  virtual std::shared_ptr<sf::Sprite> get_horz_wall() { }
  virtual std::shared_ptr<sf::Sprite> get_vert_wall() { }

public:

  City(const size_t width, const size_t height):
    city_land_(get_Bounded_Region(width, height, width * height * .01),
    city_walls_(height, std::vector<std::shared_ptr<sf::Sprite>>(width, nullptr)) { 
    this->generate();
    }

  void generate() {
    // TO DO : Pass city_land_ to get Bounded instead?
    smooth_Bounded_Edges(city_land_);
    for(size_t i = 0; i < height; ++i) {
      for(size_t j = 0; j < width; ++j) {
        if(city_land_[i][j] && is_Bounded_Edge(city_land_[i][j], i, j)) {
         /* Insert correct walls here */ 
           if(!city_land_[i+1][j] || !city_land_[i-1][j]) city_walls_(this->get_horz_wall());
           else city_walls_(this->get_vert_wall());

         /* maybe make center of x (horizontal) & y (vertical) for origin so that we may have unique?*/
        }
      }
    }

  }

};

class First_City : public City {

  Texture_Obj wall_horz_t_;
  Texture_Obj wall_vert_t_;

  Sprite_Obj wall_horz_;
  Sprite_Obj wall_vert_;

  std::shared_ptr<sf::Sprite> get_horz_wall() override {
    return wall_horz_.get_rand_Ptr();
  }
  std::shared_ptr<sf::Sprite> get_vert_wall() override {
    return wall_vert_.get_rand_Ptr();
  }

public:

  First_City(const size_t width, const size_t height):
    City(width, height),
    wall_horz_t_(64, 32, 3, "Citys/city_1_wall"),
    wall_vert_t_(32, 4, 3, "Citys/city_1_wall_vert"),
    wall_horz_(std::make_shared<Sprite_Obj>(wall_horz_t_, 15, 63)),
    wall_vert_(std::make_shared<Sprite_Obj>(wall_vert_t_, 2, 15)) { }

}; 

#endif
