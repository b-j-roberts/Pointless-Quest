#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/View.hpp>

#include "World.h"

#include <iostream> // TO DO

class Player; // Forward Declaration
class World; // Forward Declaration


// Special Interface on Animation class for player
class Body : public Animation {

  float angle_ = 0; // TO DO : Useless atm

public:

  const size_t body_size = 15; // TO DO : Temp

  // Noncopyable
  Body(const Body&) = delete;
  Body& operator=(const Body&) = delete;

  // params : texture_obj holding animation, pos_x, pos_y
  Body(const Texture_Obj& player_text, float x = 0, float y = 0):
    Animation(x, y, player_text, 15 /* TO DO */, 15 /* TO DO */) { }

  // Update w/ the following : position, collisions, animation, & even Player view
  // params : vel_x, vel_y, player - with this body, World - for collisions
  void update(float, float, Player&, const World&);

  // Return box which bounds the character ( for transparent draw in world )
  sf::FloatRect bounding_box() const { return s_[curr_frame_]->getGlobalBounds(); }
};

// Class which holding the players body, view, and cave status
class Player {

  const float zoom_factor_ = 25.f;
  std::unique_ptr<Body> body_;
  sf::View view_;

  // Range & Plane info for more efficient drawing to window
  std::pair<int, int> x_range_;
  std::pair<int, int> y_range_;
  Plane_enum curr_plane_;

public:

  // Noncopyable
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;

  // params : x_scale, tilesize, texture_obj holding animation, pos_x = 0, pos_y = 0
  Player(float, int, const Texture_Obj&, float = 0, float = 0);

  // Get Player info
  const sf::View& get_View() const { return view_; }
  sf::FloatRect bounding_box() const { return body_->bounding_box(); }
  const std::pair<int, int>& x_range() const { return x_range_; }
  const std::pair<int, int>& y_range() const { return y_range_; }
  Plane_enum current_plane() const { return curr_plane_; }

  // Change Player curr_plane_
  void set_curr_plane(Plane_enum p) { curr_plane_ = p; }

  // TO DO : angle
  // Calls body_->update(...) & updates drawing ranges
  // params : vel_x, vel_y, angle_x, angle_y, world - for collisions
  void update(float, float, float, float, const World&);
 
  void draw(sf::RenderWindow& window) const { body_->draw(window); }

  friend Body;

  // TO DO : Debug
  void pos() {
    std::cout << body_->x() << " " << body_->y() << std::endl;
  }
};

#endif
