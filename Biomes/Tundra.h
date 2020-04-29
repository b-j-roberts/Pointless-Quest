#ifndef TUNDRA_H
#define TUNDRA_H

#include "Biome.h"


// Tundra's Resource Forward Declaration
class Tundra_Shrub;
class Tundra_Tree;
class Tundra_Ice;

// Class containing all Forest Resource Textures & Sprites
// Overriden Biome functions to properly build Forest biome ( perlins_needed & get_Resources )
class Tundra : public Biome {

  // Tundra's Texture Objects
  const Texture_Obj tundra_tile_t_;
  const Texture_Obj tundra_shrub_t_;
  const Texture_Obj tundra_tree_t_;
  const Texture_Obj tundra_ice_t_;

  // Tundra's Sprite Objects
  std::shared_ptr<Sprite_Obj> tundra_tile_;
  std::shared_ptr<Sprite_Obj> tundra_shrub_;
  std::shared_ptr<Sprite_Obj> tundra_tree_;
  std::shared_ptr<Sprite_Obj> tundra_ice_;

public:

  Tundra(const Tundra&) = delete;
  Tundra& operator= (const Tundra&) = delete;

  Tundra():
    tundra_tile_t_(32, 32, 10, "Biomes/tundra/snowTiles"),
    tundra_shrub_t_(64, 64, 2, "Biomes/tundra/snowShrub"),
    tundra_tree_t_(160, 64, 2, "Biomes/tundra/snowTrees"),
    tundra_ice_t_(32, 32, 6, "Biomes/tundra/ice"),
    tundra_tile_(std::make_shared<Sprite_Obj>(tundra_tile_t_)),
    tundra_shrub_(std::make_shared<Sprite_Obj>(tundra_shrub_t_, 32, 60)),
    tundra_tree_(std::make_shared<Sprite_Obj>(tundra_tree_t_, 32, 146)),
    tundra_ice_(std::make_shared<Sprite_Obj>(tundra_ice_t_)) { }
  
  // Biome function overrides
  // 1 - Plantlife (density)
  size_t perlins_needed() override { return 1; }
  // Implimented in ./Biome_Builder.cpp
  void get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>&,
                     std::vector<std::vector<std::shared_ptr<Resource>>>&,
                     const std::vector<std::vector<Biome_enum>>&,
                     const std::vector<std::vector<std::vector<state>>>&, size_t,
                     const std::vector<std::vector<state>>&) override;

  ~Tundra() = default;

  friend Tundra_Shrub;
  friend Tundra_Tree;
  friend Tundra_Ice;
};

// Final Resource Class used to construct resource in world
class Tundra_Shrub final : public One_Piece {

public:

  Tundra_Shrub(const float pos_x, const float pos_y, const Tundra& tundra):
    One_Piece(pos_x, pos_y, tundra.tundra_shrub_->get_rand_Ptr()) { }

  // Overridden Resource Functions
  size_t generation_range() const override { return 2; } 
  // TO DO : Test this
  float collision_radius() const override { return 8; } 
};

// Final Resource Class used to construct resource in world
class Tundra_Tree final : public One_Piece {

public:

  Tundra_Tree(const float pos_x, const float pos_y, const Tundra& tundra):
    One_Piece(pos_x, pos_y, tundra.tundra_tree_->get_rand_Ptr()) { }

  // Overridden Resource Functions
  size_t generation_range() const override { return 2; } 
  // TO DO : Test this
  float collision_radius() const override { return 16; } 
};

// Final Resource Class used to construct resource in world
class Tundra_Ice final : public One_Piece {

public:

  Tundra_Ice(const float pos_x, const float pos_y, const Tundra& tundra):
    One_Piece(pos_x, pos_y, tundra.tundra_ice_->get_rand_Ptr()) { }

  // Overridden Resource Functions
  size_t generation_range() const override { return 2; } 
  float collision_radius() const override { return 0; } 
};

#endif
