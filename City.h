#ifndef __CITY_H_INCLUDED__
#define __CITY_H_INCLUDED__

//#include "Resources/Structures.h"
#include "Player.h"

class Player; // FORWARD DECL

class Wall_Horizontal;
class Wall_Vertical;
class City;

class City_Plane {

  std::vector<std::unique_ptr<City>> cities_;

  std::vector<std::vector<bool>> city_land_; // true - if is city block
  // TO DO : Change so that we can have vertical and horizontal in same position
  std::vector<std::vector<std::shared_ptr<Resource>>> city_horz_walls_;
  std::vector<std::vector<std::shared_ptr<Resource>>> city_vert_walls_;

public:

  City_Plane(const size_t width, const size_t height):
    city_land_(get_Bounded_Region(width, height, width * height * .01)),
    city_horz_walls_(height, std::vector<std::shared_ptr<Resource>>(width, nullptr)),
    city_vert_walls_(height, std::vector<std::shared_ptr<Resource>>(width, nullptr)) { 
    this->generate(width, height); }

  void generate(size_t width, size_t height);
  void draw(sf::RenderWindow&, const Player&);

};

class City {

public:

  City() { }

  virtual std::shared_ptr<Resource> get_horz_wall(int, int) { }
  virtual std::shared_ptr<Resource> get_vert_wall(int, int) { }

};

class First_City : public City {

  Texture_Obj wall_horz_t_;
  Texture_Obj wall_vert_t_;

  std::shared_ptr<Sprite_Obj> wall_horz_;
  std::shared_ptr<Sprite_Obj> wall_vert_;

public:

  First_City():
    wall_horz_t_(64, 32, 3, "Citys/city_1_wall"),
    wall_vert_t_(96, 4, 2, "Citys/city_1_wall_vert"),
    wall_horz_(std::make_shared<Sprite_Obj>(wall_horz_t_, 0, 32)),
    wall_vert_(std::make_shared<Sprite_Obj>(wall_vert_t_, 3, 64)) { }


  std::shared_ptr<Resource> get_horz_wall(int x, int y) override;
  std::shared_ptr<Resource> get_vert_wall(int x, int y) override;

  friend Wall_Horizontal;
  friend Wall_Vertical;
};

class Wall_Horizontal final : public One_Piece {

public:

  Wall_Horizontal(const float pos_x, const float pos_y, const First_City& city):
    One_Piece(pos_x, pos_y, city.wall_horz_->get_rand_Ptr()) { }

  // TO DO : Overridden Resource Funtions

};

class Wall_Vertical final : public One_Piece {

public:

  Wall_Vertical(const float pos_x, const float pos_y, const First_City& city):
    One_Piece(pos_x, pos_y, city.wall_vert_->get_rand_Ptr()) { }

  // TO DO : Overridden Resource Funtions

};

#endif
