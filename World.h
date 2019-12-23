#ifndef __WORLD_H_INCLUDED__
#define __WORLD_H_INCLUDED__

#include <stdlib.h>

#include "Player.h"
#include "Biomes/Biomes.h"

class Sprite_Obj; // Forward Declaration
class Resource; // Forward Declaration (see into using with class template)
class Player;
class Body;
class Map; // Forward Declare friend

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

    static constexpr Biome_enum biomes_[4] = { Magic_, Forest_, Swamp_, Ocean_ }; 
                                               // Top,    Mid,     Bot,    Liq
    std::unique_ptr<Biome> biomes[4];

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
