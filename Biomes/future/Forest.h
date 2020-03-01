#ifndef __FOREST_H_INCLUDED__
#define __FOREST_H_INCLUDED__

#include "Biome.h"

// TO DO : Two_Piece_Vert structures show the top 
//           really oddly when they do their transparent draw funciton
// TO DO : Is transparent draw function being activated too graciously ?


// Forest's Resource Forward Declaration
class Forest_Bush;
class Forest_Moss;
class Forest_Small_Tree;
class Forest_Tree;

// Class containing all Forest Resource Textures & Sprites
// Overriden Biome functions to properly build Forest biome ( perlins_needed & get_Resources )
class Forest : public Biome {

  conf::Config_Reader cfg_;

  // Forest's Texture Objects
  const Texture_Obj forest_tile_t_;
  const Texture_Obj forest_water_t_;
  const Texture_Obj forest_bush_top_t_;
  const Texture_Obj forest_bush_bot_t_;
  const Texture_Obj forest_moss_t_;
  const Texture_Obj forest_s_tree_top_t_;
  const Texture_Obj forest_s_tree_bot_t_;
  const Texture_Obj forest_tree_top_t_;
  const Texture_Obj forest_tree_bot_t_;

  // Forest's Sprite Objects
  std::shared_ptr<Sprite_Obj> forest_tile_;
  std::shared_ptr<Sprite_Obj> forest_water_;
  std::shared_ptr<Sprite_Obj> forest_bush_top_; // TO DO : Unique_ptr?
  std::shared_ptr<Sprite_Obj> forest_bush_bot_;
  std::shared_ptr<Sprite_Obj> forest_moss_;
  std::shared_ptr<Sprite_Obj> forest_s_tree_top_;
  std::shared_ptr<Sprite_Obj> forest_s_tree_bot_;
  std::shared_ptr<Sprite_Obj> forest_tree_top_;
  std::shared_ptr<Sprite_Obj> forest_tree_bot_;

public:

  Forest(const Forest&) = delete;
  Forest& operator= (const Forest&) = delete;

  Forest():
    cfg_("Resources/Biomes/cfg/forest.cfg"),
    forest_tile_t_(cfg_["Tile::width"].as_int(), cfg_["Tile::height"].as_int(), 
                   cfg_["Tile::count"].as_int(), "Biomes/forest/Tiles"),
    forest_water_t_(cfg_["Water::width"].as_int(), cfg_["Water::height"].as_int(),
                    cfg_["Water::count"].as_int(), "Biomes/ocean/waterTiles"),
    forest_bush_top_t_(cfg_["Bush::Top::width"].as_int(), cfg_["Bush::Top::height"].as_int(), 
                       cfg_["Bush::Top::count"].as_int(), "Biomes/forest/forestBush", 
                       cfg_["Bush::Bot::height"].as_int()),
    forest_bush_bot_t_(cfg_["Bush::Bot::width"].as_int(), cfg_["Bush::Bot::height"].as_int(), 
                       cfg_["Bush::Bot::count"].as_int(), "Biomes/forest/forestBush"),
    forest_moss_t_(cfg_["Moss::width"].as_int(), cfg_["Moss::height"].as_int(),
                   cfg_["Moss::count"].as_int(), "Biomes/forest/forestMoss"),
    forest_s_tree_top_t_(cfg_["S_Tree::Top::width"].as_int(), cfg_["S_Tree::Top::height"].as_int(),
                         cfg_["S_Tree::Top::count"].as_int(), "Biomes/forest/forestSmallTree",
                         cfg_["S_Tree::Bot::height"].as_int()),
    forest_s_tree_bot_t_(cfg_["S_Tree::Bot::width"].as_int(), cfg_["S_Tree::Bot::height"].as_int(),
                         cfg_["S_Tree::Bot::count"].as_int(), "Biomes/forest/forestSmallTree"),
    forest_tree_top_t_(cfg_["Tree::Top::width"].as_int(), cfg_["Tree::Top::height"].as_int(),
                       cfg_["Tree::Top::count"].as_int(), "Biomes/forest/forestTree",
                       cfg_["Tree::Bot::height"].as_int()),
    forest_tree_bot_t_(cfg_["Tree::Bot::width"].as_int(), cfg_["Tree::Bot::height"].as_int(),
                       cfg_["Tree::Bot::count"].as_int(), "Biomes/forest/forestTree"),
    forest_tile_(std::make_shared<Sprite_Obj>(forest_tile_t_)),
    forest_water_(std::make_shared<Sprite_Obj>(forest_water_t_)),
    forest_bush_top_(std::make_shared<Sprite_Obj>(forest_bush_top_t_, 15, 25, 1.2, 1.2)),
    forest_bush_bot_(std::make_shared<Sprite_Obj>(forest_bush_bot_t_, 16, 25)),
    forest_moss_(std::make_shared<Sprite_Obj>(forest_moss_t_, 15, 15, 1.2, 1.2)),
    forest_s_tree_top_(std::make_shared<Sprite_Obj>(forest_s_tree_top_t_, 15, 54, 1.2, 1.2)),
    forest_s_tree_bot_(std::make_shared<Sprite_Obj>(forest_s_tree_bot_t_, 15, 52)),
    forest_tree_top_(std::make_shared<Sprite_Obj>(forest_tree_top_t_, 63, 89, 1.3, 1.3)),
    forest_tree_bot_(std::make_shared<Sprite_Obj>(forest_tree_bot_t_, 31, 110)) { }

  // Biome function overrides
  // 2 - Tiles (flowers) & Plantlife (density)
  const size_t perlins_needed() override { return 2; }
  // Implimented in ./Biome_Builder.cpp
  void get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>&,
                     std::vector<std::vector<std::shared_ptr<Resource>>>&,
                     const std::vector<std::vector<Biome_enum>>&,
                     const std::vector<std::vector<std::vector<state>>>&, size_t,
                     const std::vector<std::vector<state>>&) override;

  friend Forest_Bush;
  friend Forest_Moss;
  friend Forest_Small_Tree;
  friend Forest_Tree;
};

// Final Resource Class used to construct resource in world 
class Forest_Bush final : public Two_Piece_Vert {

public:

  Forest_Bush(const float pos_x, const float pos_y, const Forest& forest):
    Two_Piece_Vert(pos_x, pos_y, 0, 21, forest.forest_bush_bot_->get_rand_Ptr(),
                   forest.forest_bush_top_->get_rand_Ptr()) { }

  // Overridden Resource Functions
  const size_t generation_range() const override { return 1; }
  const float collision_radius() const override { return 10; } 
};

// Final Resource Class used to construct resource in world
class Forest_Moss final : public One_Piece {

public:

  Forest_Moss(const float pos_x, const float pos_y, const Forest& forest):
    One_Piece(pos_x, pos_y, forest.forest_moss_->get_rand_Ptr(), rand() % 360) { }

  // Overridden Resource Functions
  const size_t generation_range() const override { return 1; }
  const float collision_radius() const override { return 0; } 
};

// Final Resource Class used to construct resource in world
class Forest_Small_Tree final : public Two_Piece_Vert {

public:

  Forest_Small_Tree(const float pos_x, const float pos_y, const Forest& forest):
    Two_Piece_Vert(pos_x, pos_y, 0, 51, forest.forest_s_tree_bot_->get_rand_Ptr(),
                   forest.forest_s_tree_top_->get_rand_Ptr()) { }

  // Overriden Resource Functions
  const size_t generation_range() const override { return 1; }
  const float collision_radius() const override { return 12; } 
};

// Final Resource Class used to construct resource in world
class Forest_Tree : public Two_Piece_Vert {

public:

  Forest_Tree(const float pos_x, const float pos_y, const Forest& forest):
    Two_Piece_Vert(pos_x, pos_y, 0, 90, forest.forest_tree_bot_->get_rand_Ptr(),
                   forest.forest_tree_top_->get_rand_Ptr()) { }

  // Overriden Resource Functions
  const size_t generation_range() const override { return 2; }
  const float collision_radius() const override { return 19; } 
};

#endif
