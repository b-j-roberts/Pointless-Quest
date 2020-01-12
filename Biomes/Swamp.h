#ifndef __SWAMP_H_INCLUDED__
#define __SWAMP_H_INCLUDED__

#include "../Resources/Structures.h"
#include "Biome.h"

// TO DO : Make circle and rectangle collision and use that for flowers 
//         and reeds and think about using it for the desert cactuses


// Swamp's Resource Forward Declaration
class Swamp_Reeds;
class Swamp_Spikes;
class Swamp_Tree;
class Swamp_Water;

// Class containing all Forest Swamp Textures & Sprites
// Contains overriden functions to properly build Swamp biome ( perlins_needed & get_Resources )
class Swamp : public Biome {

  public:
 
    Swamp():
      swamp_reeds_t_(32, 32, 2, "Biomes/swamp/SwampReeds"),
      swamp_spikes_t_(32, 32, 3, "Biomes/swamp/SwampSpikes"),
      swamp_tree_bot_t_(128, 64, 3, "Biomes/swamp/SwampTreeBottom"),
      swamp_tree_top_t_(128, 64, 2, "Biomes/swamp/SwampTreeTop"),
      swamp_water_t_(32, 32, 10, "Biomes/swamp/SwampWater"),
      swamp_reeds_(std::make_shared<Sprite_Obj>(15, 28, 1.2, 1.2, swamp_reeds_t_)),
      swamp_spikes_(std::make_shared<Sprite_Obj>(15, 28, 1, 1, swamp_spikes_t_)),
      swamp_tree_bot_(std::make_shared<Sprite_Obj>(31, 110, 1, 1, swamp_tree_bot_t_)),
      swamp_tree_top_(std::make_shared<Sprite_Obj>(31, 110, 1, 1, swamp_tree_top_t_)),
      swamp_water_(std::make_shared<Sprite_Obj>(swamp_water_t_)) {}

    // 2 - Trees (density), Reeds (density) 
    const size_t perlins_needed() override { return 2; }

    void get_Resources(const std::vector<std::vector<std::vector<state>>>&, size_t,
                       const std::vector<std::vector<Biome_enum>>&, 
                       const std::vector<std::shared_ptr<Sprite_Obj>>&,
                       std::vector<std::vector<std::shared_ptr<Tile>>>&,
                       const std::vector<std::vector<state>>&,
                       std::vector<std::vector<std::shared_ptr<Resource>>>&) override;

  private:

    Swamp(const Swamp&);
    Swamp& operator= (const Swamp&);

    Texture_Obj swamp_reeds_t_;
    Texture_Obj swamp_spikes_t_;
    Texture_Obj swamp_tree_bot_t_;
    Texture_Obj swamp_tree_top_t_;
    Texture_Obj swamp_water_t_;

    std::shared_ptr<Sprite_Obj> swamp_reeds_;
    std::shared_ptr<Sprite_Obj> swamp_spikes_;
    std::shared_ptr<Sprite_Obj> swamp_tree_bot_;
    std::shared_ptr<Sprite_Obj> swamp_tree_top_;
    std::shared_ptr<Sprite_Obj> swamp_water_;

    friend Swamp_Reeds;
    friend Swamp_Spikes;
    friend Swamp_Tree;
    friend Swamp_Water;

};

// Resource Class used to construct resource in world & 
// Overriden Resource functions for this specific type ( generation_range & collision_radius )
class Swamp_Reeds : public One_Piece {

  public:

    Swamp_Reeds(const float pos_x, const float pos_y, const Swamp& swamp):
      One_Piece(pos_x, pos_y,
                swamp.swamp_reeds_->get_Ptr(rand() % swamp.swamp_reeds_->size())) { }

    virtual const size_t generation_range() const override { return 1; }
    virtual const float collision_radius() const override { return 4; } 

};

// Resource Class used to construct resource in world & 
// Overriden Resource functions for this specific type ( generation_range & collision_radius )
class Swamp_Spikes : public One_Piece {

  public:

    Swamp_Spikes(const float pos_x, const float pos_y, const Swamp& swamp):
      One_Piece(pos_x, pos_y,
                swamp.swamp_spikes_->get_Ptr(rand() % swamp.swamp_spikes_->size())) { }

    virtual const size_t generation_range() const override { return 1; }
    virtual const float collision_radius() const override { return 5; } 

};

// Resource Class used to construct resource in world & 
// Overriden Resource functions for this specific type ( generation_range & collision_radius )
class Swamp_Tree : public Two_Piece_Vert {

  public:

    Swamp_Tree(const float pos_x, const float pos_y, const Swamp& swamp):
      Two_Piece_Vert(pos_x, pos_y, 0, 120,
                     swamp.swamp_tree_bot_->get_Ptr(rand() % swamp.swamp_tree_bot_->size()),
                     swamp.swamp_tree_top_->get_Ptr(rand() % swamp.swamp_tree_top_->size())) { }

    virtual const size_t generation_range() const override { return 2; }
    virtual const float collision_radius() const override { return 17; } 

};

// Resource Class used to construct resource in world & 
// Overriden Resource functions for this specific type ( generation_range & collision_radius )
class Swamp_Water : public One_Piece {

  public:

    Swamp_Water(const float pos_x, const float pos_y, const Swamp& swamp):
      One_Piece(pos_x, pos_y,
                swamp.swamp_water_->get_Ptr(rand() % swamp.swamp_water_->size())) { }

    virtual const size_t generation_range() const override { return 1; }
    virtual const float collision_radius() const override { return 0; } 

};

#endif
