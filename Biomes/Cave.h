#ifndef __CAVE_H_INCLUDED__
#define __CAVE_H_INCLUDED__

#include "../Resources/Structures.h"
#include "Biome.h"


// Cave's Resource Forward Declaration
class Cave_Spike;
class Cave_Crystal;

// Class containing all Cave Resource Textures & Sprites
// Contains overriden functions to properly build Cave biome ( perlins_needed = 0 & get_Resources )
class Cave : public Biome {

  public:

    Cave():
      cave_spike_t_(32, 32, 4, "Biomes/cave/caveSpike"),
      cave_crystal_t_(32, 32, 4, "Biomes/cave/caveCrystals"),
      cave_spike_(std::make_shared<Sprite_Obj>(16, 26, 1, 1, cave_spike_t_)),
      cave_crystal_(std::make_shared<Sprite_Obj>(15, 29, 1, 1, cave_crystal_t_)) { }

     // new get_Resources function for caves so we dont have to include cave map in the other 
     // get resources for the overworld biomes
     // params : cave_bdd_region, tile_vec, cave_tile_map, cave_resource_map
     void get_Resources(const std::vector<std::vector<bool>>&,
                        const std::vector<std::shared_ptr<Sprite_Obj>>&,
                        std::vector<std::vector<std::shared_ptr<Tile>>>&,
                        std::vector<std::vector<std::shared_ptr<Resource>>>&);

  private:
    
    Cave(const Cave&);
    Cave& operator= (const Cave&);

    Texture_Obj cave_spike_t_;
    Texture_Obj cave_crystal_t_;

    std::shared_ptr<Sprite_Obj> cave_spike_; // TO DO : unique ptr?
    std::shared_ptr<Sprite_Obj> cave_crystal_;

    friend Cave_Spike;
    friend Cave_Crystal;
};

// Resource Class used to construct resource in world & 
// Overriden Resource functions for this specific type ( generation_range & collision_radius )
class Cave_Spike : public One_Piece {

  public:
    
    // TO DO : get rand ptr function to make smaller (repeating coade)
    Cave_Spike(const float pos_x, const float pos_y, const Cave& cave):
      One_Piece(pos_x, pos_y,
                cave.cave_spike_->get_Ptr(rand() % cave.cave_spike_->size())) { }

    virtual const size_t generation_range() const override { return 1; }// TO DO : get_resource part
    virtual const float collision_radius() const override { return 7; } 

};

// Resource Class used to construct resource in world & 
// Overriden Resource functions for this specific type ( generation_range & collision_radius )
class Cave_Crystal : public One_Piece {

  public:

    // TO DO : get rand ptr function to make smaller (repeating coade)
    Cave_Crystal(const float pos_x, const float pos_y, const Cave& cave):
      One_Piece(pos_x, pos_y,
                cave.cave_crystal_->get_Ptr(rand() % cave.cave_crystal_->size())) { }

    virtual const size_t generation_range() const override { return 1; } // TO DO : get_resource part
    virtual const float collision_radius() const override { return 5; }

};

#endif
