#ifndef __DESERT_H_INCLUDED__
#define __DESERT_H_INCLUDED__

#include "Biome.h"

// TO DO : Add circular base to cactus or Create collision for rectangles and circles


// Desert's Resource Forward Declaration
class Desert_Cactus;

// Class containing all Desert Resource Textures & Sprites
// Overriden Biome functions to properly build Desert biome ( perlins_needed & get_Resources )
class Desert : public Biome {

  // Desert's Texture Objects
  const Texture_Obj desert_tile_t_;
  const Texture_Obj desert_water_t_;
  const Texture_Obj desert_cactus_t_;

  // Desert's Sprite Objects
  std::shared_ptr<Sprite_Obj> desert_tile_;
  std::shared_ptr<Sprite_Obj> desert_water_;
  std::shared_ptr<Sprite_Obj> desert_cactus_;

public:

  Desert(const Desert&) = delete;
  Desert& operator= (const Desert&) = delete;

  Desert():
    desert_tile_t_(32, 32, 10, "Biomes/desert/sandTiles"),
    desert_water_t_(32, 32, 4, "Biomes/ocean/waterTiles"),
    desert_cactus_t_(64, 32, 3, "Biomes/desert/Cactus"),
    desert_tile_(std::make_shared<Sprite_Obj>(desert_tile_t_)),
    desert_water_(std::make_shared<Sprite_Obj>(desert_water_t_)),
    desert_cactus_(std::make_shared<Sprite_Obj>(desert_cactus_t_, 15, 57)) { }

  // Biome function overrides
  // 1 - Cactus (density)
  const size_t perlins_needed() override { return 1; }
  // Implimented in ./Biome_Builder.cpp
  void get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>&,
                     std::vector<std::vector<std::shared_ptr<Resource>>>&,
                     const std::vector<std::vector<Biome_enum>>&,
                     const std::vector<std::vector<std::vector<state>>>&, size_t,
                     const std::vector<std::vector<state>>&) override;

  friend Desert_Cactus;
};

// Final Resource Class used to construct resource in world
class Desert_Cactus final : public One_Piece {

public:

  Desert_Cactus(const float pos_x, const float pos_y, const Desert& desert):
    One_Piece(pos_x, pos_y, desert.desert_cactus_->get_rand_Ptr()) { }

  // Overridden Resource Functions
  const size_t generation_range() const override { return 1; }
  const float collision_radius() const override { return 8; } 
};


#endif
