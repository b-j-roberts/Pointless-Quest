#ifndef __SWAMP_H_INCLUDED__
#define __SWAMP_H_INCLUDED__

#include "Structures.h"

class Swamp_Reeds;
class Swamp_Spikes;
class Swamp_Tree;
class Swamp_Water;

class Swamp {

  public:
 
    Swamp():
      swamp_reeds_t_(32, 32, 2, "swamp/SwampReeds.png"),
      swamp_spikes_t_(32, 32, 3, "swamp/SwampSpikes.png"),
      swamp_tree_bot_t_(128, 64, 3, "swamp/SwampTreeBottom.png"),
      swamp_tree_top_t_(128, 64, 2, "swamp/SwampTreeTop.png"),
      swamp_water_t_(32, 32, 10, "swamp/SwampWater.png"),
      swamp_reeds_(std::make_shared<Sprite_Obj>(swamp_reeds_t_)),
      swamp_spikes_(std::make_shared<Sprite_Obj>(swamp_spikes_t_)),
      swamp_tree_bot_(std::make_shared<Sprite_Obj>(swamp_tree_bot_t_)),
      swamp_tree_top_(std::make_shared<Sprite_Obj>(swamp_tree_top_t_)),
      swamp_water_(std::make_shared<Sprite_Obj>(swamp_water_t_)) {}

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

class Swamp_Reeds : One_Piece {

  public:

    Swamp_Reeds(const float pos_x, const float pos_y, const Swamp& swamp):
      One_Piece(pos_x, pos_y,
                swamp.swamp_reeds_->get_Ptr(rand() % swamp.swamp_reeds_->size())) { }

};

class Swamp_Spikes : One_Piece {

  public:

    Swamp_Spikes(const float pos_x, const float pos_y, const Swamp& swamp):
      One_Piece(pos_x, pos_y,
                swamp.swamp_spikes_->get_Ptr(rand() % swamp.swamp_spikes_->size())) { }

};

class Swamp_Tree : Two_Piece_Vert {

  public:

    Swamp_Tree(const float pos_x, const float pos_y, const Swamp& swamp):
      Two_Piece_Vert(pos_x, pos_y, 0, 0,
                     swamp.swamp_tree_bot_->get_Ptr(rand() % swamp.swamp_tree_bot_->size()),
                     swamp.swamp_tree_top_->get_Ptr(rand() % swamp.swamp_tree_top_->size())) { }

};

class Swamp_Water : One_Piece {

  public:

    Swamp_Water(const float pos_x, const float pos_y, const Swamp& swamp):
      One_Piece(pos_x, pos_y,
                swamp.swamp_water_->get_Ptr(rand() % swamp.swamp_water_->size())) { }

};

#endif
