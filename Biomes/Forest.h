#ifndef __FOREST_H_INCLUDED__
#define __FOREST_H_INCLUDED__

#include "../Resources/Structures.h"
#include "Biome.h"

// TO DO : Two_Piece_Vert structures show the top 
//           really oddly when they do their transparent draw funciton
// TO DO : Is transparent draw function being activated too graciously ?

class Forest_Bush;
class Forest_Moss;
class Forest_Small_Tree;
class Forest_Tree;

class Forest : public Biome {

  public:
	
    Forest():
      forest_bush_top_t_(32, 32, 3, "Biomes/forest/forestBush", 32),
      forest_bush_bot_t_(32, 32, 2, "Biomes/forest/forestBush"),
      forest_moss_t_(32, 32, 3, "Biomes/forest/forestMoss"),
      forest_small_tree_top_t_(64, 32, 2, "Biomes/forest/forestSmallTree", 64),
      forest_small_tree_bot_t_(64, 32, 3, "Biomes/forest/forestSmallTree"),
      forest_tree_top_t_(96, 128, 2, "Biomes/forest/forestTree", 128),
      forest_tree_bot_t_(128, 64, 3, "Biomes/forest/forestTree"),
      forest_bush_top_(std::make_shared<Sprite_Obj>(15, 25, 1.2, 1.2, forest_bush_top_t_)),
      forest_bush_bot_(std::make_shared<Sprite_Obj>(16, 25, 1, 1, forest_bush_bot_t_)),
      forest_moss_(std::make_shared<Sprite_Obj>(15, 15, 1.2, 1.2, forest_moss_t_)),
      forest_small_tree_top_(std::make_shared<Sprite_Obj>(15, 54, 1.2, 
                                                          1.2, forest_small_tree_top_t_)),
      forest_small_tree_bot_(std::make_shared<Sprite_Obj>(15, 52, 1, 1, forest_small_tree_bot_t_)),
      forest_tree_top_(std::make_shared<Sprite_Obj>(63, 89, 1.3, 1.3, forest_tree_top_t_)),
      forest_tree_bot_(std::make_shared<Sprite_Obj>(31, 110, 1, 1, forest_tree_bot_t_)) { }

    const size_t perlins_needed() override { return 2; }
    void get_Resources(const std::vector<std::vector<std::vector<state>>>&, size_t,
                       const std::vector<std::vector<Biome_enum>>&, 
                       const std::vector<std::shared_ptr<Sprite_Obj>>&,
                       std::vector<std::vector<std::shared_ptr<Tile>>>&,
                       const std::vector<std::vector<state>>&,
                       std::vector<std::vector<std::shared_ptr<Resource>>>&) override;

  private:

    Forest(const Forest&);
    Forest& operator= (const Forest&);

    Texture_Obj forest_bush_top_t_;
    Texture_Obj forest_bush_bot_t_;
    Texture_Obj forest_moss_t_;
    Texture_Obj forest_small_tree_top_t_;
    Texture_Obj forest_small_tree_bot_t_;
    Texture_Obj forest_tree_top_t_;
    Texture_Obj forest_tree_bot_t_;

    std::shared_ptr<Sprite_Obj> forest_bush_top_;
    std::shared_ptr<Sprite_Obj> forest_bush_bot_;
    std::shared_ptr<Sprite_Obj> forest_moss_;
    std::shared_ptr<Sprite_Obj> forest_small_tree_top_;
    std::shared_ptr<Sprite_Obj> forest_small_tree_bot_;
    std::shared_ptr<Sprite_Obj> forest_tree_top_;
    std::shared_ptr<Sprite_Obj> forest_tree_bot_;

    friend Forest_Bush;
    friend Forest_Moss;
    friend Forest_Small_Tree;
    friend Forest_Tree;
};

class Forest_Bush : public Two_Piece_Vert {

  public:

    Forest_Bush(const float pos_x, const float pos_y, const Forest& forest):
      Two_Piece_Vert(pos_x, pos_y, 0, 21, 
       	      	     forest.forest_bush_bot_->get_Ptr(rand() % forest.forest_bush_bot_->size()),
		                 forest.forest_bush_top_->get_Ptr(rand() % forest.forest_bush_top_->size())) { }

    virtual const size_t generation_range() const override { return 1; }
    virtual const float collision_radius() const override { return 10; } 

  // TO DO : Add interface for collisions and invisible when under
  // TO DO : Other interface ? 
};

class Forest_Moss : public One_Piece {

  public:

    Forest_Moss(const float pos_x, const float pos_y, const Forest& forest):
      One_Piece(pos_x, pos_y,
	              forest.forest_moss_->get_Ptr(rand() % forest.forest_moss_->size()),
                rand() % 360) { }
 
    virtual const size_t generation_range() const override { return 1; }
    virtual const float collision_radius() const override { return 0; } 

};

// TO DO : Fix these so there is a constant method of determining the center 
class Forest_Small_Tree : public Two_Piece_Vert {

  public:

    Forest_Small_Tree(const float pos_x, const float pos_y, const Forest& forest):
      Two_Piece_Vert(pos_x, pos_y, 0, 51,
		    forest.forest_small_tree_bot_->get_Ptr(rand() % forest.forest_small_tree_bot_->size()),
		    forest.forest_small_tree_top_->get_Ptr(rand() % forest.forest_small_tree_top_->size())) { }

    virtual const size_t generation_range() const override { return 1; }
    virtual const float collision_radius() const override { return 12; } 

};

class Forest_Tree : public Two_Piece_Vert {

  public:

    Forest_Tree(const float pos_x, const float pos_y, const Forest& forest):
      Two_Piece_Vert(pos_x, pos_y, 0, 90,
                     forest.forest_tree_bot_->get_Ptr(rand() % forest.forest_tree_bot_->size()),
                     forest.forest_tree_top_->get_Ptr(rand() % forest.forest_tree_top_->size())) { }

    virtual const size_t generation_range() const override { return 2; }
    virtual const float collision_radius() const override { return 19; } 

};

#endif
