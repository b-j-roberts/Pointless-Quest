#ifndef __WORLD_H_INCLUDED__
#define __WORLD_H_INCLUDED__

#include <stdlib.h>

#include "Functions.h"

#include "Player.h"
#include "Resources/Biomes.h"

class Sprite_Obj; // Forward Declaration
class Resource; // Forward Declaration (see into using with class template)
class Map; // Forward Declare friend
/*
struct Tile { // Layer 0 Resource

  const Biome_enum biome_;

  const size_t tile_id_;
  // TO DO : Is water variable?
  
  std::shared_ptr<sf::Sprite> sprite_;
 
  Tile(Biome_enum biome, std::shared_ptr<Sprite_Obj> sprite_obj):
    biome_(biome),
    tile_id_(rand() % sprite_obj->size()),
    sprite_(sprite_obj->get_Ptr(tile_id_)) { } 	
 
};
*/
class World {
  
  public:
    
    World() = default;
     
    //Generate world of (width, height, vector of tile sprite objects)
    void generate(size_t, size_t, const std::vector<std::shared_ptr<Sprite_Obj>>&);

    //Draws tiles, the player, and then resources (in that order) inside of vi  const Player&)
    void draw(sf::RenderWindow&, const Player&);

    //Returns true if collision with Resource & player
    bool collision(const Player&); // TO DO: Create player 
  
  private:

    //Disallow copy constuction and assignment
    World(const World&);
    World& operator=(const World&);

    std::vector<std::vector<Biome_enum>> get_Biomes(size_t width, size_t height);

    static constexpr Biome_enum biomes_[4] = { Swamp_, Unocean_, Desert_, Ocean_ }; 
                                               // Top,    Mid,     Bot,    Liq
    std::unique_ptr<Biome> biomes[4];

    //Index is map location divided by 32 (tile width) mapped to Tile object 
    //  (contains sprite and biome info) in that location
    // Layer 0 of resources
    std::vector<std::vector<std::shared_ptr<Tile>>> tile_map_; // TO DO: Use shared_ptr?
    //location to mapped resource
    std::vector<std::vector<std::shared_ptr<Resource>>> resource_map_;

    friend Map;
};

#endif
