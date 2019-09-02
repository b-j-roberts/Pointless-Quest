#ifndef __MAGIC_H_INCLUDED__
#define __MAGIC_H_INCLUDED__

#include "Structures.h"

class Magic_Flowers;
class Magic_Trees;

class Magic {

  public:

    Magic():
      magic_flowers_t_(32, 32, 5, "magic/magicFlowers"),
      magic_trees_t_(160, 96, 2, "magic/magicTrees"),
      magic_flowers_(std::make_shared<Sprite_Obj>(magic_flowers_t_)),
      magic_trees_(std::make_shared<Sprite_Obj>(magic_trees_t_)) { }

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

class Magic_Flowers : One_Piece {

  public:
	
    Magic_Flowers(const float pos_x, const float pos_y, const Magic& magic):
      One_Piece(pos_x, pos_y,
              magic.magic_flowers_->get_Ptr(rand() % magic.magic_flowers_->size())) { }

};

class Magic_Trees : One_Piece {

  public:
	
    Magic_Trees(const float pos_x, const float pos_y, const Magic& magic):
      One_Piece(pos_x, pos_y,
              magic.magic_trees_->get_Ptr(rand() % magic.magic_trees_->size())) { }

};

#endif
