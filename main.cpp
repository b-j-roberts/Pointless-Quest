#include <SFML/Window/Joystick.hpp>

#include "Map.h"

#include <iostream> // TO DO : debug

int main(int argc, char** argv) {

  srand(time(nullptr));

  // Window
  sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
  sf::RenderWindow window(desktop, "Pointless Quest");
  window.setFramerateLimit(60);

  const sf::Vector2u window_size(window.getSize());
  const float x_scale(window_size.x * 1.f / window_size.y);


  // World Generation & Resource Loading
  size_t world_scale = 2;
  // TO DO : TEMP
  if(argc > 1) world_scale = std::stoul(argv[1]);
  sf::Vector2u world_size(world_scale * 1024, world_scale * 1024);
  World world(world_size.x, world_size.y);

  // Player Creation & Resource Loading
  // TO DO : This is a temporary texture loading for player
  const Texture_Obj player_texture(32, 32, 4, "Biomes/ocean/waterTiles");
  Player player(x_scale, 32 /* tile_size */, player_texture, 
                world_size.x * 32 / 2, world_size.y * 32 / 2);

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
      if(l_stick.x < .07f && l_stick.x > -0.07f) l_stick.x = 0;
    }
    if(is_l_y) {
      l_stick.y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
      if(l_stick.y < .07f && l_stick.y > -0.07f) l_stick.y = 0;
    }
    if(is_r_x) {
      r_stick.x = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);
      if(r_stick.x < .07f && r_stick.x > -0.07f) r_stick.x = 0;
    }
    if(is_r_y) {
      r_stick.y = sf::Joystick::getAxisPosition(0, sf::Joystick::R);
      if(r_stick.y < .07f && r_stick.y > -0.07f) r_stick.y = 0;
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
