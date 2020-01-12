#ifndef __TUNDRA_H_INCLUDED__
#define __TUNDRA_H_INCLUDED__

#include "../Resources/Structures.h"
#include "Biome.h"


// Forest's Resource Forward Declaration
class Tundra_Shrub;
class Tundra_Tree;
class Tundra_Ice;

// Class containing all Forest Resource Textures & Sprites
// Contains overriden functions to properly build Forest biome ( perlins_needed & get_Resources )
class Tundra : public Biome {

  public:
	
    Tundra():
      tundra_shrub_t_(64, 64, 2, "Biomes/tundra/snowShrub"),
      tundra_tree_t_(160, 64, 2, "Biomes/tundra/snowTrees"),
      tundra_ice_t_(32, 32, 6, "Biomes/tundra/ice"),
      tundra_shrub_(std::make_shared<Sprite_Obj>(32, 60, 1, 1, tundra_shrub_t_)),
      tundra_tree_(std::make_shared<Sprite_Obj>(32, 146, 1, 1, tundra_tree_t_)),
      tundra_ice_(std::make_shared<Sprite_Obj>(tundra_ice_t_)) { }
    
    // 1 - Plantlife (density)
    const size_t perlins_needed() override { return 1; }

    void get_Resources(const std::vector<std::vector<std::vector<state>>>&, size_t,
                       const std::vector<std::vector<Biome_enum>>&, 
                       const std::vector<std::shared_ptr<Sprite_Obj>>&,
                       std::vector<std::vector<std::shared_ptr<Tile>>>&,
                       const std::vector<std::vector<state>>&,
                       std::vector<std::vector<std::shared_ptr<Resource>>>&) override;

  private:

    Tundra(const Tundra&);
    Tundra& operator= (const Tundra&);

    Texture_Obj tundra_shrub_t_;
    Texture_Obj tundra_tree_t_;
    Texture_Obj tundra_ice_t_;

    std::shared_ptr<Sprite_Obj> tundra_shrub_;
    std::shared_ptr<Sprite_Obj> tundra_tree_;
    std::shared_ptr<Sprite_Obj> tundra_ice_;

    friend Tundra_Shrub;
    friend Tundra_Tree;
    friend Tundra_Ice;
};

// Resource Class used to construct resource in world & 
// Overriden Resource functions for this specific type ( generation_range & collision_radius )
class Tundra_Shrub : public One_Piece {

  public:

    Tundra_Shrub(const float pos_x, const float pos_y, const Tundra& tundra):
      One_Piece(pos_x, pos_y,
	              tundra.tundra_shrub_->get_Ptr(rand() % tundra.tundra_shrub_->size())) { }
 
    virtual const size_t generation_range() const override { return 2; } 
    virtual const float collision_radius() const override { return 8; }// TO DO : Test all of these 

};

// Resource Class used to construct resource in world & 
// Overriden Resource functions for this specific type ( generation_range & collision_radius )
class Tundra_Tree : public One_Piece {

  public:

    Tundra_Tree(const float pos_x, const float pos_y, const Tundra& tundra):
      One_Piece(pos_x, pos_y,
	              tundra.tundra_tree_->get_Ptr(rand() % tundra.tundra_tree_->size())) { }
 
    virtual const size_t generation_range() const override { return 2; } 
    virtual const float collision_radius() const override { return 20; } 

};

// Resource Class used to construct resource in world & 
// Overriden Resource functions for this specific type ( generation_range & collision_radius )
class Tundra_Ice : public One_Piece {

  public:

    Tundra_Ice(const float pos_x, const float pos_y, const Tundra& tundra):
      One_Piece(pos_x, pos_y,
	              tundra.tundra_ice_->get_Ptr(rand() % tundra.tundra_ice_->size())) { }
 
    virtual const size_t generation_range() const override { return 1; } 
    virtual const float collision_radius() const override { return 0; } 

};

#endif
