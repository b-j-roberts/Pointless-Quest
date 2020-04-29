#ifndef WORLD_H
#define WORLD_H

#include <map> 

#include "Biomes/Biomes.h"
#include "Player.h"
#include "City.h"

// Forward Declarations
class Player;
class Body;
class Map;
class City_Plane;

// Virtual Class for a Worlds Plane w/ Biome_emuns, Biomes, tile_map, & resource_map
struct World_Plane {

  std::vector<Biome_enum> biome_enums_;
  std::vector<std::unique_ptr<Biome>> biomes_;

  std::vector<std::vector<std::shared_ptr<Tile>>> tile_map_;
  std::vector<std::vector<std::shared_ptr<Resource>>> resource_map_;

  // Reserve size for tile_map_ & resource_map_
  World_Plane(const size_t width, const size_t height): 
    tile_map_(height, std::vector<std::shared_ptr<Tile>>(width, nullptr)),
    resource_map_(height, std::vector<std::shared_ptr<Resource>>(width, nullptr)) { }

  // Draw part of World_Plane (tile & resource map) inside player's range ( & draw player )
  void draw(sf::RenderWindow&, const Player&) const;
  // Generate whole plane by making biomes_ ( w/ get_Biome ) & calling get_Resources on these
  void generate(const size_t width, const size_t height);
    
  // Virtual functions for specific world plane
  // Determines which biomes are possible for this plane
  virtual const std::vector<std::vector<Biome_enum>>& possible_biomes() { };
  // Determines if a river is needed for this plane
  virtual bool need_river() { };
  // Determines how to generate biomes_map for get_Resource function call
  virtual std::vector<std::vector<Biome_enum>> get_Biome_Map(size_t width, size_t height) { };

  // TO DO : Layers
};

struct Overworld : public World_Plane {
  
  Overworld(const size_t width, const size_t height):
    World_Plane(width, height) { this->generate(width, height); }

  // World_Plane overrides
  const std::vector<std::vector<Biome_enum>>& possible_biomes() override {
    static const std::vector<std::vector<Biome_enum>> possible_biomes_ = {
      { Magic_, Tundra_ }, // TO DO : Volcano  // top
      { Forest_, Desert_}, // TO DO : Plains  // mid
      { Swamp_ }, // TO DO : Beach, Rockys     // bot
      { Ocean_, Old_Ocean_ } // TO DO : Lava   // liq
    };
    return possible_biomes_;
  }
  bool need_river() override { return true; }
  std::vector<std::vector<Biome_enum>> get_Biome_Map(size_t width, size_t height) override;
};

struct Underground : public World_Plane {

  // TO DO : Cave entry things ( do in world object ) 
  Underground(const size_t width, const size_t height):
    World_Plane(width, height) { this->generate(width, height); }   

  // World_Plane overrides
  const std::vector<std::vector<Biome_enum>>& possible_biomes() override {
    static const std::vector<std::vector<Biome_enum>> possible_biomes_ = {
      { Cave_ } // cave
    };
    return possible_biomes_;
  }
  bool need_river() override { return false; }
  std::vector<std::vector<Biome_enum>> get_Biome_Map(size_t width, size_t height) override;
};

// Builds & Returns World_Plane cooresponding to Plane_enum
// params : Plane_enum to generate, width, height
std::unique_ptr<World_Plane> get_Plane(Plane_enum, const size_t, const size_t);

// Stores alls the worlds info & allows interfacing for drawing the world
class World {
  
  std::map<Plane_enum, std::unique_ptr<World_Plane>> planes_;
  std::map<Plane_enum, std::unique_ptr<City_Plane>> cities_;
  
public:

  World(const World&) = delete;
  World& operator=(const World&) = delete;

  // params : width, height
  World(const size_t, const size_t);
   
  // Call draw for planes_[Player's current plane]
  void draw(sf::RenderWindow&, const Player&) const; 

  friend Map;
  friend Player;
  friend Body;
};

#endif
