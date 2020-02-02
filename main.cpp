#include <SFML/Window/Joystick.hpp>

#include "Map.h"

#include <iostream> // TO DO : debug

int main() {

  srand(time(NULL));

  // Window
  sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
  sf::RenderWindow window(desktop, "Pointless Quest");
  window.setFramerateLimit(60);

  const sf::Vector2u window_size(window.getSize());
  const float x_scale(window_size.x * 1.f / window_size.y);


  // World Generation & Resource Loading
  sf::Vector2u world_size(2048, 2048);
  //sf::Vector2u world_size(512, 512); //TO DO : Why is this seg fault?
  World world(world_size.x, world_size.y);

  // Player Creation & Resource Loading
  // TO DO : This is a temporary texture loading for player
  const Texture_Obj player_texture(32, 32, 4, "Biomes/ocean/waterTiles");
  Player player(x_scale, 32 /* tile_size */, player_texture, 1000 * 32, 1000 * 32);

  // GUI Creation
  Map map(player);
  

  // Joystick Initialization
  sf::Joystick::update();
  bool is_gamepad, is_l_x, is_l_y, is_r_x, is_r_y;
  is_gamepad = sf::Joystick::isConnected(0);
  if(!is_gamepad) std::cout << "No gamepad" << std::endl; // TO DO : LOG NO GAMEPAD
  is_l_x = sf::Joystick::hasAxis(0, sf::Joystick::X);
  is_l_y = sf::Joystick::hasAxis(0, sf::Joystick::Y);
  is_r_x = sf::Joystick::hasAxis(0, sf::Joystick::Z);
  is_r_y = sf::Joystick::hasAxis(0, sf::Joystick::R);


  // Game Loop
  sf::Event event;
  while(window.isOpen()) {

    // Get Joystick State
    sf::Joystick::update();                
    sf::Vector2f r_stick, l_stick;
    // Prevent slight joystick drift
    if(is_l_x) {
      l_stick.x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
      if(l_stick.x < .07 && l_stick.x > -0.07) l_stick.x = 0;
    }
    if(is_l_y) {
      l_stick.y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
      if(l_stick.y < .07 && l_stick.y > -0.07) l_stick.y = 0;
    }
    if(is_r_x) {
      r_stick.x = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);
      if(r_stick.x < .07 && r_stick.x > -0.07) r_stick.x = 0;
    }
    if(is_r_y) {
      r_stick.y = sf::Joystick::getAxisPosition(0, sf::Joystick::R);
      if(r_stick.y < .07 && r_stick.y > -0.07) r_stick.y = 0;
    }

    // Other Input (Keyboard or window)
    while(window.pollEvent(event)) {
      switch(event.type) {
        case sf::Event::Closed:
      	  window.close();
	        break;
	
      	default: break;
      }
    }

    // TO DO : Debug commands
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      l_stick.y = -70;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      l_stick.x = -70;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      l_stick.y = 70;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      l_stick.x = 70;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
      player.pos();
    }

    // Update Step
    player.update(l_stick.x / 10, l_stick.y / 10, r_stick.x, r_stick.y, world);

    // Draw Step
    window.clear();
    window.setView(player.get_View());

    world.draw(window, player);
    map.draw(window, world, player);

    window.display();
  } // Closed Game Loop

  return 0;
}
