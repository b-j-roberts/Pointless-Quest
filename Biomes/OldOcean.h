#ifndef OLDOCEAN_H
#define OLDOCEAN_H

#include "Biome.h"


// Old Ocean's Resource Forward Declaration
class Old_Ocean_Large_Fish;
class Old_Ocean_Small_Fish;

// Class containing all Old Ocean Resource Textures & Sprites
// Overriden Biome functions to properly build Old Ocean biome ( perlins_needed = 0 & get_Resources )
class Old_Ocean : public Biome {

  // Old_Ocean Texture Objects
  const Texture_Obj old_ocean_tile_t_;
  const Texture_Obj old_ocean_water_t_;
  const Texture_Obj old_ocean_large_fish_t_;
  const Texture_Obj old_ocean_small_fish_t_;

  // Old_Ocean Sprite Objects
  std::shared_ptr<Sprite_Obj> old_ocean_tile_;
  std::shared_ptr<Sprite_Obj> old_ocean_water_;
  std::shared_ptr<Sprite_Obj> old_ocean_large_fish_;
  std::shared_ptr<Sprite_Obj> old_ocean_small_fish_;

public:

  Old_Ocean(const Old_Ocean&) = delete;
  Old_Ocean& operator= (const Old_Ocean&) = delete;

  Old_Ocean():
    old_ocean_tile_t_(32, 32, 10, "Biomes/old_ocean/oldoceanTiles"),
    old_ocean_water_t_(32, 32, 4, "Biomes/ocean/waterTiles"),
    old_ocean_large_fish_t_(32, 64, 2, "Biomes/old_ocean/largeFishBones"),
    old_ocean_small_fish_t_(32, 32, 2, "Biomes/old_ocean/smallFishBones"),
    old_ocean_tile_(std::make_shared<Sprite_Obj>(old_ocean_tile_t_)),
    old_ocean_water_(std::make_shared<Sprite_Obj>(old_ocean_water_t_)),
    old_ocean_large_fish_(std::make_shared<Sprite_Obj>(old_ocean_large_fish_t_, 31, 15, 1.2, 1.2)),
    old_ocean_small_fish_(std::make_shared<Sprite_Obj>(old_ocean_small_fish_t_, 15, 15)) { }

  ~Old_Ocean() = default;

  // Biome function overrides
  // Implimented in ./Biome_Builder.cpp
  void get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>&,
                     std::vector<std::vector<std::shared_ptr<Resource>>>&,
                     const std::vector<std::vector<Biome_enum>>&,
                     const std::vector<std::vector<std::vector<state>>>&, size_t,
                     const std::vector<std::vector<state>>&) override;

  friend Old_Ocean_Large_Fish;
  friend Old_Ocean_Small_Fish;
};

// Final Resource Class used to construct resource in world
class Old_Ocean_Large_Fish final : public One_Piece {

public:
  
  Old_Ocean_Large_Fish(const float pos_x, const float pos_y, const Old_Ocean& old_ocean):
    One_Piece(pos_x, pos_y, old_ocean.old_ocean_large_fish_->get_rand_Ptr(), rand() % 360) { }

  // Overridden Resource Functions
  size_t generation_range() const override { return 2; }
  float collision_radius() const override { return 0; } 
};

// Final Resource Class used to construct resource in world
class Old_Ocean_Small_Fish final : public One_Piece {

public:

  Old_Ocean_Small_Fish(const float pos_x, const float pos_y, const Old_Ocean& old_ocean):
    One_Piece(pos_x, pos_y, old_ocean.old_ocean_small_fish_->get_rand_Ptr(), rand() % 360) { }

  // Overridden Resource Functions
  size_t generation_range() const override { return 1; }
  float collision_radius() const override { return 0; } 
};

#endif
