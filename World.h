#ifndef __WORLD_H_INCLUDED__
#define __WORLD_H_INCLUDED__

#include <array>

#include <stdlib.h>

#include "Player.h"
#include "Biomes/Biomes.h"

class Sprite_Obj; // Forward Declaration
class Resource; // Forward Declaration (see into using with class template)
class Player;
class Body;
class Map; // Forward Declare friend

/*
 

enum Plane_enum { Overworld_, Underground_ };

// Maybe place struct inside World and make it a class
template <Plane_enum P>
struct World_Plane {
  
  static std::array possible_top_biomes{ Magic_, Tundra_ }; // TO DO : Volcano 
  static std::array possible_mid_biomes{ Forest_, Desert_ };
  static std::array possible_bot_biomes{ Swamp_ }; // TO DO : Beach, Rockys
  static std::array possible_liq_biomes{ Ocean_, Unocean_ }; // TO DO : Lava

  std::vector<Biome_enum> biome_enums_;
  std::vector<std::unique_ptr<Biome>> biomes_;

  std::vector<std::vector<std::shared_ptr<Tile>>> tile_map_;
  std::vector<std::vector<std::shared_ptr<Resource>>> resource_map_;

  // World_Plane():
    do biome_enums_,
    do biomes_,
    size tile_map_, (nullptrs)
    size resource_map_ (nullptrs) {
    
    if constexpr(std::equal_to(P, Overworld_) {
      get_Biomes(...)
      do river
      get_perlins needed for biomes_
      get_Resources
    } else if constexpr(std::equal_to(P, Underground_)) {
      get_bounded_region
      get_resources
    }   
    
  }

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

    const Biome_enum biomes_[4] = { Magic_, Tundra_, Swamp_, Ocean_ }; 
                                               // Top,    Mid,     Bot,    Liq
    std::unique_ptr<Biome> biomes[4];
    std::unique_ptr<Cave> cave_;

    //Index is map location divided by 32 (tile width) mapped to Tile object 
    //  (contains sprite and biome info) in that location
    // Layer 0 of resources
    std::vector<std::vector<std::shared_ptr<Tile>>> cave_tile_map_; // TO DO: Use shared_ptr?
    //location to mapped resource
    std::vector<std::vector<std::shared_ptr<Resource>>> cave_resource_map_;

    //Index is map location divided by 32 (tile width) mapped to Tile object 
    //  (contains sprite and biome info) in that location
    // Layer 0 of resources
    std::vector<std::vector<std::shared_ptr<Tile>>> tile_map_; // TO DO: Use shared_ptr?
    //location to mapped resource
    std::vector<std::vector<std::shared_ptr<Resource>>> resource_map_;

    friend Map;
    friend Player;
    friend Body;
};

#endif
