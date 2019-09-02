#ifndef __DESERT_H_INCLUDED__
#define __DESERT_H_INCLUDED__

#include "Structures.h"

class Desert_Cactus;

class Desert {

  public:

    Desert():
      desert_cactus_t_(64, 32, 3, "desert/Cactus"),
      desert_cactus_(std::make_shared<Sprite_Obj>(desert_cactus_t_)) { }

  private:

    Desert(const Desert&);
    Desert& operator= (const Desert&);

    Texture_Obj desert_cactus_t_;

    std::shared_ptr<Sprite_Obj> desert_cactus_;

    friend Desert_Cactus;

};

class Desert_Cactus : One_Piece {

  public:

    Desert_Cactus(const float pos_x, const float pos_y, const Desert& desert):
      One_Piece(pos_x, pos_y,
	      desert.desert_cactus_->get_Ptr(rand() % desert.desert_cactus_->size())) { }

};


#endif
