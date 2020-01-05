#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include <SFML/Graphics/View.hpp>

#include "Functions.h"

#include "Resources/Structures.h"
#include "World.h"

#include <iostream> // TO DO

class Player; // Forward Declaration
class World; // Forward Declaration

class Body : public Animation {
  // TO DO : Create body class for player with draw function
  public:

    const size_t body_size = 5; // TO DO : Temp

    /*void draw(sf::RenderWindow& window) const override { // Placholder
      sf::CircleShape body(body_size);
      sf::CircleShape body_2(1);
      body.setPosition(pos_x_, pos_y_);
      body.setOrigin(body_size, body_size);
      body_2.setOrigin(1, 1);
      body_2.setFillColor(sf::Color::Red);
      body_2.setPosition(pos_x_, pos_y_);
      window.draw(body);
      window.draw(body_2);
    }*/
    
    sf::FloatRect bounding_box() const { //Placeholder
      sf::CircleShape body(body_size);
      body.setPosition(pos_x_, pos_y_);
      return body.getGlobalBounds();
    }
    
    void update(float, float, Player&, const World&);

    //Body(): Resource(1000 * 32, 1000 * 32), angle_(0) { } // TO DO : Set default position
    Body(const Texture_Obj& player_text): Animation(1000 * 32, 1000 * 32, player_text) { }

  private:

    float angle_;

//  friend Player;
};

class Player {

  public:

    //Default, places body at position (0,0) with (x_scale, tilesize) by param
    Player(float, int, const Texture_Obj&);
    //Constructor placing body at position and args 
    //  (x_scale, tile_size, pos_x, pos_y), passed arguments
    Player(float, int, float, float, const Texture_Obj&);

    //Update function for state of player, for now just changes position and 
    //  angle based on the passed parameters (Lstick_x, Lstick_y, Rstick_x, Rstick_y)
    void update(float, float, float, float, const World&);
    void draw(sf::RenderWindow& window) const { body_->draw(window); }
    
    sf::View get_View() const { return view_; }
    sf::FloatRect bounding_box() const { return body_->bounding_box(); }

    // TO DO : Debug
    void pos() {
      std::cout << body_->get_pos().x << " " << body_->get_pos().y << std::endl;
    }    

    void cross() { in_cave_ = !in_cave_; }
    bool in_cave() const { return in_cave_; }

  private:
  
    std::unique_ptr<Body> body_;
    float vel_x_, vel_y_;
    float angle_; // TO DO : Remove?
    sf::View view_;

    bool in_cave_;

    friend Body;

};

#endif
