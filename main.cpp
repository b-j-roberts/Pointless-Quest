#include <SFML/Window/Joystick.hpp>

#include "World.h"
#include "Resources/Structures.h"
#include "Player.h"

size_t frame = 0;

int main() {

  sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
  sf::RenderWindow window(desktop, "Pointless Quest");

  window.setFramerateLimit(60);

  //Window Size & Scale
  const sf::Vector2u window_size(window.getSize());
  const float x_scale(window_size.x * 1.f / window_size.y);

  const size_t tile_size(32);

  srand(time(NULL));

  /*
   *
   * LOADING TEXTURES AND SPRITES ( TO DO : CHANGE TO ONLY LOAD ONES NEEDED FOR BIOME )
   *
   *
   */

  std::vector<std::shared_ptr<Sprite_Obj>> tile_vec; // TO DO : reserve 4 for the 4 loaded lile textures (in some standardized order, ie bottom to top)

  // TO DO : Check if number of tiles in each biome is correct

  //Load Forest Tiles
  const Texture_Obj forest_tile_t(tile_size, tile_size, 10, "forest/Tiles");
  tile_vec.push_back(std::make_shared<Sprite_Obj>(forest_tile_t));
  
  //Load Desert Tiles
  const Texture_Obj desert_tile_t(tile_size, tile_size, 10, "desert/sandTiles");
  tile_vec.push_back(std::make_shared<Sprite_Obj>(desert_tile_t));

  //Load Magic Tiles
  const Texture_Obj magic_tile_t(tile_size, tile_size, 7, "magic/magicTiles");
  tile_vec.push_back(std::make_shared<Sprite_Obj>(magic_tile_t));

  //Load Ocean Tiles
  const Texture_Obj ocean_tile_t(tile_size, tile_size, 4, "ocean/waterTiles");
  tile_vec.push_back(std::make_shared<Sprite_Obj>(ocean_tile_t));

  //Load Swamp Tiles
  const Texture_Obj swamp_tile_t(tile_size, tile_size, 10, "swamp/SwampTiles");
  tile_vec.push_back(std::make_shared<Sprite_Obj>(swamp_tile_t));

  //Load Tundra Tiles
  //const Texture_Obj tundra_tile_t(tile_size, tile_size, 10, "tundra/snowTiles");
  //tile_vec.push_back(std::make_shared<Sprite_Obj>(tundra_tile_t));

  //Load Old Ocean Tiles
  const Texture_Obj old_ocean_tile_t(tile_size, tile_size, 10, "old_ocean/oldoceanTiles");
  tile_vec.push_back(std::make_shared<Sprite_Obj>(old_ocean_tile_t));

  // TO DO : Make each block load all resources of that biome

  
  /*
   *
   *
   * Generate World
   *
   *
   */

  sf::Vector2u world_size(2048, 2048);

  World world;
  world.generate(world_size.x, world_size.y, tile_vec); 

  Player player(x_scale, tile_size);

  // TO DO : LOG WORLD COMPLETION
  
  /*
   *
   *
   * JOYSTICK
   *
   *
   */
   
  sf::Joystick::update();
  bool is_gamepad, is_l_x, is_l_y, is_r_x, is_r_y;
  is_gamepad = sf::Joystick::isConnected(0);
  if(!is_gamepad) std::cout << "No gamepad" << std::endl;// TO DO : LOG NO GAMEPAD
  is_l_x = sf::Joystick::hasAxis(0, sf::Joystick::X);
  is_l_y = sf::Joystick::hasAxis(0, sf::Joystick::Y);
  is_r_x = sf::Joystick::hasAxis(0, sf::Joystick::Z);
  is_r_y = sf::Joystick::hasAxis(0, sf::Joystick::R);

  /*
   *
   *
   * GAME LOOP
   *
   *
   */

  sf::Event event;

  while(window.isOpen()) {

    //Get Joystick State
    sf::Joystick::update();                
    sf::Vector2f r_stick, l_stick;
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

    //Other Input (Keyboard or window)
    while(window.pollEvent(event)) {
      switch(event.type) {

        case sf::Event::KeyPressed:
          if(event.key.code == sf::Keyboard::W) {
            l_stick.y = -100;
          }
          if(event.key.code == sf::Keyboard::S) {
            l_stick.y = 100;
          }
          if(event.key.code == sf::Keyboard::A) {
            l_stick.x = -100;
          }
          if(event.key.code == sf::Keyboard::D) {
            l_stick.x = 100;
          }
          break;

        case sf::Event::Closed:
      	  window.close();
	        break;
	
      	default: break;
      }
    }

    /*
     *
     * 
     * UPDATE STEP
     *
     *
     */

    player.update(l_stick.x / 10, l_stick.y / 10, r_stick.x, r_stick.y);


    /*
     *
     *
     * DRAW STEP
     *
     *
     */

    window.clear();

    world.draw(window, player); // TO DO : Make player (also view?)

    window.setView(player.get_View()); // TO DO : Need player view
    window.display();
    std::cout << "Frame : " << frame++ << std::endl;
  }
  // Closed Game Loop

  return 0;

}
