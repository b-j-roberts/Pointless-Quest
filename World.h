#ifndef __WORLD_H_INCLUDED__
#define __WORLD_H_INCLUDED__

#include <stdlib.h>

#include "Player.h"
#include "Resources/Biomes.h"

class Sprite_Obj; // Forward Declaration
class Resource; // Forward Declaration (see into using with class template)

// TO DO : Make tile a resource and combine tile map with resource map ? 

struct Tile {

  const Biome_enum biome_;

  const size_t tile_id_;

  std::shared_ptr<sf::Sprite> sprite_;
 
  Tile(Biome_enum biome, std::shared_ptr<Sprite_Obj> sprite_obj):
    biome_(biome),
    tile_id_(rand() % sprite_obj->size()),
    sprite_(sprite_obj->get_Ptr(tile_id_)) { } 	
 
};

class World {
  
  public:
    
    World() = default;
     
    //Generate world of (width, height, vector of tile sprite objects)
    void generate(size_t, size_t, const std::vector<std::shared_ptr<Sprite_Obj>>&);
    std::vector<std::vector<Biome_enum>> get_Biomes(size_t width, size_t height);

    //Draws tiles, the player, and then resources (in that order) inside of vi  const Player&); // TO DO: Create View and Player
    void draw(sf::RenderWindow&, const Player&);

    //Returns true if collision with Resource & player
    bool collision(const Player&); // TO DO: Create player 
  
  private:

    //Disallow copy constuction and assignment
    World(const World&);
    World& operator=(const World&);

    static constexpr Biome_enum biomes_[4] = { Magic_, Forest_, Desert_, Ocean_ }; // In order Top, Mid, Bot, Liq
    std::unique_ptr<Biome> biomes[4];

    //Index is map location divided by 32 (tile width) mapped to Tile object (contains sprite and biome info) in that location
    std::vector<std::vector<std::shared_ptr<Tile>>> tile_map_; // TO DO: Use shared_ptr?
    //location to mapped resource which 
    std::vector<std::vector<std::shared_ptr<Resource>>> resource_map_;
};

#endif
