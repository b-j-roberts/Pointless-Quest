#ifndef __OLDOCEAN_H_INCLUDED__
#define __OLDOCEAN_H_INCLUDED__

#include "Structures.h"
#include "Biome.h"

class Old_Ocean_Large_Fish;
class Old_Ocean_Small_Fish;

class Old_Ocean : public Biome {

  public:

    Old_Ocean():
      old_ocean_large_fish_t_(32, 64, 2, "Biomes/old_ocean/largeFishBones"),
      old_ocean_small_fish_t_(32, 32, 2, "Biomes/old_ocean/smallFishBones"),
      old_ocean_large_fish_(std::make_shared<Sprite_Obj>(31, 15, 1.2, 1.2, old_ocean_large_fish_t_)),
      old_ocean_small_fish_(std::make_shared<Sprite_Obj>(15, 15, 1, 1, old_ocean_small_fish_t_)) { }

     const size_t perlins_needed() override { return 1; }
     void get_Resources(const std::vector<std::vector<std::vector<state>>>&, size_t,
                       const std::vector<std::vector<Biome_enum>>&, 
                       const std::vector<std::shared_ptr<Sprite_Obj>>&,
                       std::vector<std::vector<std::shared_ptr<Tile>>>&,
                       const std::vector<std::vector<state>>&,
                       std::vector<std::vector<std::shared_ptr<Resource>>>&) override;

  private:
    
    Old_Ocean(const Old_Ocean&);
    Old_Ocean& operator= (const Old_Ocean&);

    Texture_Obj old_ocean_large_fish_t_;
    Texture_Obj old_ocean_small_fish_t_;

    std::shared_ptr<Sprite_Obj> old_ocean_large_fish_;
    std::shared_ptr<Sprite_Obj> old_ocean_small_fish_;

    friend Old_Ocean_Large_Fish;
    friend Old_Ocean_Small_Fish;
};

class Old_Ocean_Large_Fish : public One_Piece {

  public:
    
    Old_Ocean_Large_Fish(const float pos_x, const float pos_y, const Old_Ocean& old_ocean):
      One_Piece(pos_x, pos_y,
      old_ocean.old_ocean_large_fish_->get_Ptr(rand() % old_ocean.old_ocean_large_fish_->size())) { }

};

class Old_Ocean_Small_Fish : public One_Piece {

  public:

    Old_Ocean_Small_Fish(const float pos_x, const float pos_y, const Old_Ocean& old_ocean):
      One_Piece(pos_x, pos_y,
      old_ocean.old_ocean_small_fish_->get_Ptr(rand() % old_ocean.old_ocean_small_fish_->size())) { }

};

#endif
