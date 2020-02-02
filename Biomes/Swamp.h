#ifndef __SWAMP_H_INCLUDED__
#define __SWAMP_H_INCLUDED__

#include "Biome.h"


// Swamp's Resource Forward Declaration
class Swamp_Reeds;
class Swamp_Spikes;
class Swamp_Tree;
class Swamp_Water;

// Class containing all Forest Swamp Textures & Sprites
// Overriden Biome functions to properly build Swamp biome ( perlins_needed & get_Resources )
class Swamp : public Biome {

  // Swamp's Texture Objects
  const Texture_Obj swamp_tile_t_;
  const Texture_Obj swamp_reeds_t_;
  const Texture_Obj swamp_spikes_t_;
  const Texture_Obj swamp_tree_bot_t_;
  const Texture_Obj swamp_tree_top_t_;
  const Texture_Obj swamp_water_t_;

  // Swamp's Sprite Objects
  std::shared_ptr<Sprite_Obj> swamp_tile_;
  std::shared_ptr<Sprite_Obj> swamp_reeds_;
  std::shared_ptr<Sprite_Obj> swamp_spikes_;
  std::shared_ptr<Sprite_Obj> swamp_tree_bot_;
  std::shared_ptr<Sprite_Obj> swamp_tree_top_;
  std::shared_ptr<Sprite_Obj> swamp_water_;

public:

  Swamp(const Swamp&) = delete;
  Swamp& operator= (const Swamp&) = delete;

  Swamp():
    swamp_tile_t_(32, 32, 10, "Biomes/swamp/SwampTiles"),
    swamp_reeds_t_(32, 32, 2, "Biomes/swamp/SwampReeds"),
    swamp_spikes_t_(32, 32, 3, "Biomes/swamp/SwampSpikes"),
    swamp_tree_bot_t_(128, 64, 3, "Biomes/swamp/SwampTreeBottom"),
    swamp_tree_top_t_(128, 64, 2, "Biomes/swamp/SwampTreeTop"),
    swamp_water_t_(32, 32, 10, "Biomes/swamp/SwampWater"),
    swamp_tile_(std::make_shared<Sprite_Obj>(swamp_tile_t_)),
    swamp_reeds_(std::make_shared<Sprite_Obj>(swamp_reeds_t_, 15, 28, 1.2, 1.2)),
    swamp_spikes_(std::make_shared<Sprite_Obj>(swamp_spikes_t_, 15, 28)),
    swamp_tree_bot_(std::make_shared<Sprite_Obj>(swamp_tree_bot_t_, 31, 110)),
    swamp_tree_top_(std::make_shared<Sprite_Obj>(swamp_tree_top_t_, 31, 110)),
    swamp_water_(std::make_shared<Sprite_Obj>(swamp_water_t_)) {}

  // Biome function overrides
  // 2 - Trees (density), Reeds (density) 
  const size_t perlins_needed() override { return 2; }
  // Implimented in ./Biome_Builder.cpp
  void get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>&,
                     std::vector<std::vector<std::shared_ptr<Resource>>>&,
                     const std::vector<std::vector<Biome_enum>>&,
                     const std::vector<std::vector<std::vector<state>>>&, size_t,
                     const std::vector<std::vector<state>>&) override;

  friend Swamp_Reeds;
  friend Swamp_Spikes;
  friend Swamp_Tree;
  friend Swamp_Water;
};

// Final Resource Class used to construct resource in world
class Swamp_Reeds final : public One_Piece {

public:

  Swamp_Reeds(const float pos_x, const float pos_y, const Swamp& swamp):
    One_Piece(pos_x, pos_y, swamp.swamp_reeds_->get_rand_Ptr()) { }

  // Overridden Resource Functions
  const size_t generation_range() const override { return 1; }
  const float collision_radius() const override { return 4; } 
};

// Final Resource Class used to construct resource in world
class Swamp_Spikes final : public One_Piece {

public:

  Swamp_Spikes(const float pos_x, const float pos_y, const Swamp& swamp):
    One_Piece(pos_x, pos_y, swamp.swamp_spikes_->get_rand_Ptr()) { }

  // Overridden Resource Functions
  const size_t generation_range() const override { return 1; }
  const float collision_radius() const override { return 5; } 
};

// Final Resource Class used to construct resource in world
class Swamp_Tree final : public Two_Piece_Vert {

public:

  Swamp_Tree(const float pos_x, const float pos_y, const Swamp& swamp):
    Two_Piece_Vert(pos_x, pos_y, 0, 120, swamp.swamp_tree_bot_->get_rand_Ptr(),
                   swamp.swamp_tree_top_->get_rand_Ptr()) { }

  // Overridden Resource Functions
  const size_t generation_range() const override { return 2; }
  const float collision_radius() const override { return 17; } 
};

// Final Resource Class used to construct resource in world
class Swamp_Water final : public One_Piece {

public:

  Swamp_Water(const float pos_x, const float pos_y, const Swamp& swamp):
    One_Piece(pos_x, pos_y, swamp.swamp_water_->get_rand_Ptr()) { }

  // Overridden Resource Functions
  const size_t generation_range() const override { return 1; }
  const float collision_radius() const override { return 0; } 
};

#endif
