#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include <SFML/Graphics/View.hpp>

#include "Resources/Resources.h"

class Player;

class Body : public Resource {
  // TO DO : Create body class for player with draw function
  public:
    
    void draw(sf::RenderWindow& window) const override { // Placholder
      sf::CircleShape body(15);
      body.setPosition(pos_x_, pos_y_);
      window.draw(body);
    }

    sf::FloatRect bounding_box() const { //Placeholder
      sf::CircleShape body(15);
      body.setPosition(pos_x_, pos_y_);
      return body.getGlobalBounds();
    }
    
    void update(float, float, Player&);

    Body(): Resource(1000 * 32, 1000 * 32), angle_(0) { } // TO DO : Set default position

  private:

    float angle_;

//  friend Player;
};

class Player {

  public:

    //Default, places body at position (0,0) with (x_scale, tilesize) by param
    explicit Player(float, int);
    //Constructor placing body at position and args 
    //  (x_scale, tile_size, pos_x, pos_y), passed arguments
    Player(float, int, float, float);

    //Update function for state of player, for now just changes position and 
    //  angle based on the passed parameters (Lstick_x, Lstick_y, Rstick_x, Rstick_y)
    void update(float, float, float, float);
    void draw(sf::RenderWindow& window) const { body_->draw(window); }
    
    sf::View get_View() const { return view_; }
    sf::FloatRect bounding_box() const { return body_->bounding_box(); }

  private:
  
    std::unique_ptr<Body> body_;
    float vel_x_, vel_y_;
    float angle_;
    sf::View view_;

    friend Body;

};

#endif
