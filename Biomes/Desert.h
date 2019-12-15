#ifndef __DESERT_H_INCLUDED__
#define __DESERT_H_INCLUDED__

#include "../Resources/Structures.h"
#include "Biome.h"

class Desert_Cactus;

class Desert : public Biome {

  public:

    Desert():
      desert_cactus_t_(64, 32, 3, "Biomes/desert/Cactus"),
      desert_cactus_(std::make_shared<Sprite_Obj>(15, 47, 1, 1, desert_cactus_t_)) { }

    const size_t perlins_needed() override { return 1; }
    void get_Resources(const std::vector<std::vector<std::vector<state>>>&, size_t,
                       const std::vector<std::vector<Biome_enum>>&, 
                       const std::vector<std::shared_ptr<Sprite_Obj>>&,
                       std::vector<std::vector<std::shared_ptr<Tile>>>&,
                       const std::vector<std::vector<state>>&,
                       std::vector<std::vector<std::shared_ptr<Resource>>>&) override;

  private:

    Desert(const Desert&);
    Desert& operator= (const Desert&);

    Texture_Obj desert_cactus_t_;

    std::shared_ptr<Sprite_Obj> desert_cactus_;

    friend Desert_Cactus;

};

class Desert_Cactus : public One_Piece {

  public:

    Desert_Cactus(const float pos_x, const float pos_y, const Desert& desert):
      One_Piece(pos_x, pos_y,
	              desert.desert_cactus_->get_Ptr(rand() % desert.desert_cactus_->size())) { }

    virtual const size_t generation_range() const override { return 1; }
    virtual const float collision_radius() const override { return 15; } 

};


#endif
