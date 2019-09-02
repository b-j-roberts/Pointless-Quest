#ifndef __WORLD_H_INCLUDED__
#define __WORLD_H_INCLUDED__

#include <stdlib.h>

#include "Player.h"
#include "Resources/Biomes.h"

class Sprite_Obj; // Forward Declaration
class Resource; // Forward Declaration (see into using with class template)

enum Biome {  Forest = 0, Desert = 1, Magic = 2, Ocean = 3, Swamp = 4, Tundra = 5, Unocean = 6 };

// TO DO : Make tile a resource and combine tile map with resource map ? 

struct Tile {

  const Biome biome_;

  const size_t tile_id_;

  std::shared_ptr<sf::Sprite> sprite_;
 
  Tile(Biome biome, std::shared_ptr<Sprite_Obj> sprite_obj):
    biome_(biome),
    tile_id_(rand() % sprite_obj->size()),
    sprite_(sprite_obj->get_Ptr(tile_id_)) { } 	
 
};

class World {
  
  public:
    
    World() = default;
     
    //Generate world of (width, height, vector of tile sprite objects)
    void generate(size_t, size_t, const std::vector<std::shared_ptr<Sprite_Obj>>);

    //Draws tiles, the player, and then resources (in that order) inside of vi  const Player&); // TO DO: Create View and Player
    void draw(sf::RenderWindow&, const Player&);

    //Returns true if collision with Resource & player
    bool collision(const Player&); // TO DO: Create player 
  
  private:

    //Disallow copy constuction and assignment
    World(const World&);
    World& operator=(const World&);

    //Index is map location divided by 32 (tile width) mapped to Tile object (contains sprite and biome info) in that location
    std::vector<std::vector<std::shared_ptr<Tile>>> tile_map_; // TO DO: Use shared_ptr?
    //location to mapped resource which 
    //std::map<std::pair<uint32_t,uint32_t>, Resource> resource_loc_map_; // TO DO: Create Resource class and change this to pointers for polymorphism?

};

#endif
