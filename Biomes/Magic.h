#ifndef __MAGIC_H_INCLUDED__
#define __MAGIC_H_INCLUDED__

#include "Biome.h"


// Magic's Resource Forward Declaration
class Magic_Flowers;
class Magic_Trees;

// Class containing all Magic Resource Textures & Sprites
// Overriden Biome functions to properly build Magic biome ( perlins_needed & get_Resources )
class Magic : public Biome {

  // Magic's Texture Objects
  const Texture_Obj magic_tile_t_;
  const Texture_Obj magic_water_t_;
  const Texture_Obj magic_flowers_t_;
  const Texture_Obj magic_trees_t_;

  // Magic's Sprite Objects
  std::shared_ptr<Sprite_Obj> magic_tile_;
  std::shared_ptr<Sprite_Obj> magic_water_;
  std::shared_ptr<Sprite_Obj> magic_flowers_;
  std::shared_ptr<Sprite_Obj> magic_trees_;

public:

  Magic(const Magic&) = delete;
  Magic& operator= (const Magic&) = delete;

  Magic():
    magic_tile_t_(32, 32, 7, "Biomes/magic/magicTiles"),
    magic_water_t_(32, 32, 4, "Biomes/ocean/waterTiles"),
    magic_flowers_t_(32, 32, 5, "Biomes/magic/magicFlowers"),
    magic_trees_t_(160, 96, 2, "Biomes/magic/magicTrees"),
    magic_tile_(std::make_shared<Sprite_Obj>(magic_tile_t_)),
    magic_water_(std::make_shared<Sprite_Obj>(magic_water_t_)),
    magic_flowers_(std::make_shared<Sprite_Obj>(magic_flowers_t_, 15, 31, 1.2, 1.2)),
    magic_trees_(std::make_shared<Sprite_Obj>(magic_trees_t_, 47, 150)) { }

  // Biome function overrides
  // 2 - Flowers (density), Trees (density)
  const size_t perlins_needed() override { return 2; }
  // Implimented in ./Biome_Builder.cpp
  void get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>&,
                     std::vector<std::vector<std::shared_ptr<Resource>>>&,
                     const std::vector<std::vector<Biome_enum>>&,
                     const std::vector<std::vector<std::vector<state>>>&, size_t,
                     const std::vector<std::vector<state>>&) override;

  friend Magic_Flowers;
  friend Magic_Trees;
};

// Final Resource Class used to construct resource in world
class Magic_Flowers final : public One_Piece {

public:

  Magic_Flowers(const float pos_x, const float pos_y, const Magic& magic):
    One_Piece(pos_x, pos_y, magic.magic_flowers_->get_rand_Ptr()) { }

  // Overridden Resource Functions
  const size_t generation_range() const override { return 1; }
  const float collision_radius() const override { return 3; } 
};

// Final Resource Class used to construct resource in world
class Magic_Trees final : public One_Piece {

public:

  Magic_Trees(const float pos_x, const float pos_y, const Magic& magic):
    One_Piece(pos_x, pos_y, magic.magic_trees_->get_rand_Ptr()) { }

  // Overridden Resource Functions
  const size_t generation_range() const override { return 2; }
  const float collision_radius() const override { return 10; } 
};

#endif
