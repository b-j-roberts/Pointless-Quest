#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include <SFML/Graphics/View.hpp>

#include "Functions.h"

#include "Resources/Structures.h"
#include "World.h"

#include <iostream> // TO DO

class Player; // Forward Declaration
class World; // Forward Declaration

// Body class that puts special interface on animation objects related to the player,
// these include collision detection, player view updating, and the bounding_box
class Body : public Animation {
  public:

    // Noncopyable
    Body(const Body&) = delete;
    Body& operator=(const Body&) = delete;

    // Constructs body animation resource at position specified - default (0, 0)
    // params : (texture_obj holding animation, pos_x, pos_y)
    Body(const Texture_Obj& player_text, float x = 0, float y = 0): Animation(x, y, player_text) { }

    // Update the state of the body ( position, collisions, animation, & even Player view )
    // params : ( vel_x, vel_y, player - with this body, World - for collisions )
    void update(float, float, Player&, const World&);

    const size_t body_size = 15; // TO DO : Temp

    // Return FloatRect box which bounds the character ( for transparent draw in world )
    sf::FloatRect bounding_box() const {
      sf::CircleShape body(body_size); // placeholder
      body.setPosition(pos_x_ + 15, pos_y_ + 15);
      return body.getGlobalBounds();
    }
    
  private:

    float angle_ = 0; // TO DO : Useless atm

};

// Class which holding the players body, view, and cave status
class Player {

  public:

    // Noncopyable
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    // Constructs player at position (0, 0)
    // params : (x_scale, tilesize, texture_obj holding animation)
    Player(float, int, const Texture_Obj&);

    // Constructs player at position specified
    // params : (x_scale, tile_size, pos_x, pos_y, texture_obj holding animation)
    Player(float, int, float, float, const Texture_Obj&);

    // TO DO : angle
    // Update the state of the player ( position, collisions, view, animation frames ) 
    // params : ( vel_x, vel_y, angle_x, angle_y, world - for collisions )
    void update(float, float, float, float, const World&);
    
    void draw(sf::RenderWindow& window) const { body_->draw(window); }

    const sf::View& get_View() const { return view_; }
    sf::FloatRect bounding_box() const { return body_->bounding_box(); }

    // TO DO : Debug
    void pos() {
      std::cout << body_->get_pos().x << " " << body_->get_pos().y << std::endl;
    }    

    const std::pair<int, int>& x_range() const { return x_range_; }
    const std::pair<int, int>& y_range() const { return y_range_; }

    // Cave interface for player 
    // cross() - toggle cave state & in_cave() - if currently in cave
    void cross() { in_cave_ = !in_cave_; }
    bool in_cave() const { return in_cave_; }
    // void set_curr_plane_(Plane p) { curr_plane_ = p; }
    //Plane current_plane() const { return curr_plane_; }

  private:
  
    const float zoom_factor_ = 25.f;

    std::pair<int, int> x_range_;
    std::pair<int, int> y_range_;

    std::unique_ptr<Body> body_;
    sf::View view_;

    bool in_cave_;
    // Plane curr_plane_;
 
    friend Body;

};

#endif
