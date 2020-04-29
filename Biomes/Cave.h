#ifndef CAVE_H_
#define CAVE_H

#include "Biome.h"


// Cave's Resource Forward Declaration
class Cave_Spike;
class Cave_Crystal;

// Class containing all Cave Resource Textures & Sprites
// Overriden Biome functions to properly build Cave biome ( perlins_needed = 0 & get_Resources )
class Cave : public Biome {

  // Cave's Texture Objects
  const Texture_Obj cave_tile_t_;
  const Texture_Obj cave_spike_t_;
  const Texture_Obj cave_crystal_t_;

  // Cave's Sprite Objects
  std::shared_ptr<Sprite_Obj> cave_tile_;
  std::shared_ptr<Sprite_Obj> cave_spike_;
  std::shared_ptr<Sprite_Obj> cave_crystal_;

public:

  Cave(const Cave&) = delete;
  Cave& operator= (const Cave&) = delete;

  Cave():
    cave_tile_t_(32, 32, 10, "Biomes/cave/caveTiles"),
    cave_spike_t_(32, 32, 4, "Biomes/cave/caveSpike"),
    cave_crystal_t_(32, 32, 4, "Biomes/cave/caveCrystals"),
    cave_tile_(std::make_shared<Sprite_Obj>(cave_tile_t_)),
    cave_spike_(std::make_shared<Sprite_Obj>(cave_spike_t_, 16, 26)),
    cave_crystal_(std::make_shared<Sprite_Obj>(cave_crystal_t_, 15, 29)) { }

  ~Cave() override = default;

  // Biome function overrides
  // Implimented in ./Biome_Builder.cpp
  void get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>&,
                     std::vector<std::vector<std::shared_ptr<Resource>>>&,
                     const std::vector<std::vector<Biome_enum>>&,
                     const std::vector<std::vector<std::vector<state>>>&, size_t,
                     const std::vector<std::vector<state>>&) override;

  friend Cave_Spike;
  friend Cave_Crystal;
};

// Final Resource Class used to construct resource in world 
class Cave_Spike final : public One_Piece {

public:
  
  Cave_Spike(const float pos_x, const float pos_y, const Cave& cave):
    One_Piece(pos_x, pos_y, cave.cave_spike_->get_rand_Ptr()) { }

  // Overriden Resource Functions
  size_t generation_range() const override { return 1; }
  // TO DO : Test this
  float collision_radius() const override { return 7; } 
};

// Final Resource Class used to construct resource in world 
class Cave_Crystal final : public One_Piece {

public:

  Cave_Crystal(const float pos_x, const float pos_y, const Cave& cave):
    One_Piece(pos_x, pos_y, cave.cave_crystal_->get_rand_Ptr()) { }

  // Overriden Resource Functions
  size_t generation_range() const override { return 1; }
  // TO DO : Test this
  float collision_radius() const override { return 5; }
};

#endif
