#ifndef __WORLD_H_INCLUDED__
#define __WORLD_H_INCLUDED__

#include <array>
#include <map> // TO DO 

#include <numeric>

//#include <cstdlib>

#include "Biomes/Biomes.h"
#include "City.h"
#include "Player.h"

#include <iostream> // TO DO

class Sprite_Obj; // Forward Declaration
class Resource; // Forward Declaration (see into using with class template)
class Player;
class Body;
class Map; // Forward Declare friend


struct World_Plane {

  std::vector<Biome_enum> biome_enums_;
  std::vector<std::unique_ptr<Biome>> biomes_;

  std::vector<std::vector<std::shared_ptr<Tile>>> tile_map_;
  std::vector<std::vector<std::shared_ptr<Resource>>> resource_map_;

  void draw(sf::RenderWindow&, const Player&);

  virtual const std::vector<std::vector<Biome_enum>>& possible_biomes() { };
  virtual bool need_river() { };
  virtual std::vector<std::vector<Biome_enum>> get_Biome_Map(size_t width, size_t height) { };

  World_Plane(const size_t width, const size_t height): 
    tile_map_(height, std::vector<std::shared_ptr<Tile>>(width, nullptr)),
    resource_map_(height, std::vector<std::shared_ptr<Resource>>(width, nullptr)) { }

  void generate(const size_t width, const size_t height,
                const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec) {
    
    std::transform(possible_biomes().begin(), possible_biomes().end(), 
                   std::back_inserter(biome_enums_),
                   [](std::vector<Biome_enum> bv) { return bv[rand() % bv.size()]; });
    
    std::transform(biome_enums_.begin(), biome_enums_.end(), std::back_inserter(biomes_),
                   [](Biome_enum b) { return get_Biome(b); }); 
  
  
    auto biomes_map = get_Biome_Map(width, height);
    std::vector<std::vector<state>> river;
    if(need_river()) { river = get_States(width, height, 0.70, 0.68); }

    size_t state_perlins_needed = std::accumulate(biomes_.begin(), biomes_.end(), 0,
                   [&](size_t a, const auto& b){ return a + b->perlins_needed(); });
    typedef std::vector<std::vector<state>> state_perlin;
    std::vector<state_perlin> all_perlin;
    for(int i = 0; i < state_perlins_needed; ++i) {
      // TO DO : Shorten this
      all_perlin.emplace_back(get_States(width, height, 0.75, 0.50)); // These cut_offs are temp
    }

    size_t pos = 0;
    for(auto& biome : biomes_) {
      biome->get_Resources(tile_map_, resource_map_, tile_vec, biomes_map, all_perlin, pos, river);
      pos += biome->perlins_needed();
    }

    // TO DO : Temp
    resource_map_[1000][1000] = nullptr;
  }

    // TO DO : Layers
 
};
    
struct Overworld : public World_Plane {
  
  const std::vector<std::vector<Biome_enum>>& possible_biomes() override {
    static const std::vector<std::vector<Biome_enum>> possible_biomes_ = {
      { Magic_, Tundra_ }, // TO DO : Volcano  // top
      { Forest_, Desert_ }, // TO DO : Plains  // mid
      { Swamp_ }, // TO DO : Beach, Rockys     // bot
      { Ocean_, Unocean_ } // TO DO : Lava     // liq
    };
    return possible_biomes_;
  }

  bool need_river() override { return true; }

  std::vector<std::vector<Biome_enum>> get_Biome_Map(size_t width, size_t height) override;

  // TO DO : Use transform and other things to clean this
  Overworld(const size_t width, const size_t height,
            const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec):
    World_Plane(width, height) { this->generate(width, height, tile_vec); }

};

struct Underground : public World_Plane {

  const std::vector<std::vector<Biome_enum>>& possible_biomes() override {
    static const std::vector<std::vector<Biome_enum>> possible_biomes_ = {
      { Cave_ } // cave
    };
    return possible_biomes_;
  }

  bool need_river() override { return false; }

  std::vector<std::vector<Biome_enum>> get_Biome_Map(size_t width, size_t height) override;

  Underground(const size_t width, const size_t height,
            const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec):
    World_Plane(width, height) { this->generate(width, height, tile_vec); }   
    // TO DO : Cave entry things to planes ( do in world object ) 
};

std::unique_ptr<World_Plane> get_Plane(Plane_enum p, const size_t width, const size_t height,
                                       const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec);


class World {
  
  std::map<Plane_enum, std::unique_ptr<World_Plane>> world_; // TO DO : Name -> planes_

  std::map<Plane_enum, std::unique_pt<City>> cities_;
  
public:

  World(const World&) = delete;
  World& operator=(const World&) = delete;

  
  World(const size_t width, const size_t height, 
        const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec) {
    // Generate Tiles & Resources for planes
    world_[Overworld_] = get_Plane(Overworld_, width, height, tile_vec);
    world_[Underground_] = get_Plane(Underground_, width, height, tile_vec);

    // Cave entry
  /*  // TO DO : Fix all of this
    //         More than one entrance, no river tiles
    size_t cave_entry_x = rand() % cave[0].size();
    size_t cave_entry_y = rand() % cave.size();
    while(!cave[cave_entry_y][cave_entry_x]) {
      cave_entry_x = rand() % cave[0].size();
      cave_entry_y = rand() % cave.size();
    }
    // TO DO : Fix index flip wherever in this codebase it may be
    for(size_t i = max(0, cave_entry_y - 2); i < min(width - 1, cave_entry_y + 2); ++i) {
      for(size_t j = max(0, cave_entry_x - 2); j < min(width - 1, cave_entry_x + 2); ++j) {
        resource_map_[j][i] = nullptr;
        cave_resource_map_[j][i] = nullptr;
        tile_map_[j][i] = std::make_shared<Tile>(Unocean_, tile_vec[Unocean_]); // TO DO : Temp
        cave_tile_map_[j][i] = std::make_shared<Tile>(Unocean_, tile_vec[Unocean_]);
      }
    }
*/
  }
   
  //Draws tiles, the player, and then resources (in that order)
  void draw(sf::RenderWindow&, const Player&);

  friend Map;
  friend Player;
  friend Body;

};

#endif
