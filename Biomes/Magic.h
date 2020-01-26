#ifndef __MAGIC_H_INCLUDED__
#define __MAGIC_H_INCLUDED__

#include "../Resources/Structures.h"
#include "Biome.h"


// Magic's Resource Forward Declaration
class Magic_Flowers;
class Magic_Trees;

// Class containing all Magic Resource Textures & Sprites
// Contains overriden functions to properly build Magic biome ( perlins_needed & get_Resources )
class Magic : public Biome {

  public:

    Magic():
      magic_flowers_t_(32, 32, 5, "Biomes/magic/magicFlowers"),
      magic_trees_t_(160, 96, 2, "Biomes/magic/magicTrees"),
      magic_flowers_(std::make_shared<Sprite_Obj>(magic_flowers_t_, 15, 31, 1.2, 1.2)),
      magic_trees_(std::make_shared<Sprite_Obj>(magic_trees_t_, 47, 150)) { }

    // 2 - Flowers (density), Trees (density)
    const size_t perlins_needed() override { return 2; }

    void get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map_,
                             std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map_,
                             const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec,
                             const std::vector<std::vector<Biome_enum>>& biome_map,
                             const std::vector<std::vector<std::vector<state>>>& perlins = {{{}}},
                             size_t perlins_pos = 0,
                             const std::vector<std::vector<state>>& river = {{}}) override;
  private:
	
    Magic(const Magic&);
    Magic& operator= (const Magic&);

    Texture_Obj magic_flowers_t_;
    Texture_Obj magic_trees_t_;

    std::shared_ptr<Sprite_Obj> magic_flowers_;
    std::shared_ptr<Sprite_Obj> magic_trees_;

    friend Magic_Flowers;
    friend Magic_Trees;

};

// Resource Class used to construct resource in world & 
// Overriden Resource functions for this specific type ( generation_range & collision_radius )
class Magic_Flowers : public One_Piece {

  public:
	
    Magic_Flowers(const float pos_x, const float pos_y, const Magic& magic):
      One_Piece(pos_x, pos_y,
                magic.magic_flowers_->get_Ptr(rand() % magic.magic_flowers_->size())) { }

    virtual const size_t generation_range() const override { return 1; }
    virtual const float collision_radius() const override { return 3; } 

};

// Resource Class used to construct resource in world & 
// Overriden Resource functions for this specific type ( generation_range & collision_radius )
class Magic_Trees : public One_Piece {

  public:
	
    Magic_Trees(const float pos_x, const float pos_y, const Magic& magic):
      One_Piece(pos_x, pos_y,
                magic.magic_trees_->get_Ptr(rand() % magic.magic_trees_->size())) { }

    virtual const size_t generation_range() const override { return 2; }
    virtual const float collision_radius() const override { return 10; } 

};

#endif
