#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include <SFML/Graphics/View.hpp>

#include "Resources/Resources.h"

class Player;

class Body : public Resource {
  // TO DO : Create body class for player with draw function, include pos_x_ and pos_y_ members
  public:
    void draw(sf::RenderWindow& window) override { //Placeholder
      std::cout << "this is a placeholder, so i do not have an abstract class" << std::endl;
    }
    
    void update(float, float, float);

    Body(): Resource(0,0), angle_(0) { }

  private:
    float angle_;

  friend Player;
};

class Player {

  public:

    //Default, places body at position (0,0) with (x_scale, tilesize) by param
    explicit Player(float, int);
    //Constructor placing body at position and args (x_scale, tile_size, pos_x, pos_y), passed arguments
    Player(float, int, float, float);

    //Update function for state of player, for now just changes position and 
    //  angle based on the passed parameters (Lstick_x, Lstick_y, Rstick_x, Rstick_y)
    void update(float, float, float, float);
    void draw(sf::RenderWindow& window) const { body_->draw(window); }
    sf::View get_View() const { return view_; }


  private:
  
    std::unique_ptr<Body> body_;
    float vel_x_, vel_y_;
    float angle_;
    sf::View view_;

};

#endif
