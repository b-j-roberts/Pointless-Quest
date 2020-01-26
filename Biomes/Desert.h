#ifndef __DESERT_H_INCLUDED__
#define __DESERT_H_INCLUDED__

#include "../Resources/Structures.h"
#include "Biome.h"

// TO DO : Add circular base to cactus


// Desert's Resource Forward Declaration
class Desert_Cactus;

// Class containing all Desert Resource Textures & Sprites
// Contains overriden functions to properly build Desert biome ( perlins_needed & get_Resources )
class Desert : public Biome {

  public:

    Desert():
      desert_cactus_t_(64, 32, 3, "Biomes/desert/Cactus"),
      desert_cactus_(std::make_shared<Sprite_Obj>(desert_cactus_t_, 15, 57)) { }

    // 1 - Cactus (density)
    const size_t perlins_needed() override { return 1; }
     void get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map_,
                             std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map_,
                             const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec,
                             const std::vector<std::vector<Biome_enum>>& biome_map,
                             const std::vector<std::vector<std::vector<state>>>& perlins = {{{}}},
                             size_t perlins_pos = 0,
                             const std::vector<std::vector<state>>& river = {{}}) override;

  private:

    Desert(const Desert&);
    Desert& operator= (const Desert&);

    Texture_Obj desert_cactus_t_;

    std::shared_ptr<Sprite_Obj> desert_cactus_;

    friend Desert_Cactus;

};

// Resource Class used to construct resource in world & 
// Overriden Resource functions for this specific type ( generation_range & collision_radius )
class Desert_Cactus : public One_Piece {

  public:

    Desert_Cactus(const float pos_x, const float pos_y, const Desert& desert):
      One_Piece(pos_x, pos_y,
	              desert.desert_cactus_->get_Ptr(rand() % desert.desert_cactus_->size())) { }

    virtual const size_t generation_range() const override { return 1; }
    virtual const float collision_radius() const override { return 8; } 

};


#endif
