#ifndef __MAGIC_H_INCLUDED__
#define __MAGIC_H_INCLUDED__

#include "Structures.h"
#include "Biome.h"

class Magic_Flowers;
class Magic_Trees;

class Magic : public Biome {

  public:

    Magic():
      magic_flowers_t_(32, 32, 5, "Biomes/magic/magicFlowers"),
      magic_trees_t_(160, 96, 2, "Biomes/magic/magicTrees"),
      magic_flowers_(std::make_shared<Sprite_Obj>(15, 31, 1.2, 1.2, magic_flowers_t_)),
      magic_trees_(std::make_shared<Sprite_Obj>(47, 159, 1, 1, magic_trees_t_)) { }

    const size_t perlins_needed() override { return 2; }
    void get_Resources(const std::vector<std::vector<std::vector<state>>>&, size_t,
                       const std::vector<std::vector<Biome_enum>>&, 
                       std::vector<std::vector<std::shared_ptr<Resource>>>&) override;

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

class Magic_Flowers : public One_Piece {

  public:
	
    Magic_Flowers(const float pos_x, const float pos_y, const Magic& magic):
      One_Piece(pos_x, pos_y,
                magic.magic_flowers_->get_Ptr(rand() % magic.magic_flowers_->size())) { }

};

class Magic_Trees : public One_Piece {

  public:
	
    Magic_Trees(const float pos_x, const float pos_y, const Magic& magic):
      One_Piece(pos_x, pos_y,
                magic.magic_trees_->get_Ptr(rand() % magic.magic_trees_->size())) { }

};

#endif
