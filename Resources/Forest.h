#ifndef __FOREST_H_INCLUDED__
#define __FOREST_H_INCLUDED__

#include "Structures.h"
#include "Biome.h"

class Forest_Bush;
class Forest_Moss;
class Forest_Small_Tree;
class Forest_Tree;

class Forest : public Biome {

  public:
	
    Forest():
      forest_bush_top_t_(32, 32, 3, "forest/forestBush", 32),
      forest_bush_bot_t_(32, 32, 2, "forest/forestBush"),
      forest_moss_t_(32, 32, 3, "forest/forestMoss"),
      forest_small_tree_top_t_(64, 32, 2, "forest/forestSmallTree", 64),
      forest_small_tree_bot_t_(64, 32, 3, "forest/forestSmallTree"),
      forest_tree_top_t_(96, 128, 2, "forest/forestTree", 128),
      forest_tree_bot_t_(128, 64, 3, "forest/forestTree"),
      forest_bush_top_(std::make_shared<Sprite_Obj>(forest_bush_top_t_)),
      forest_bush_bot_(std::make_shared<Sprite_Obj>(forest_bush_bot_t_)),
      forest_moss_(std::make_shared<Sprite_Obj>(forest_moss_t_)),
      forest_small_tree_top_(std::make_shared<Sprite_Obj>(forest_small_tree_top_t_)),
      forest_small_tree_bot_(std::make_shared<Sprite_Obj>(forest_small_tree_bot_t_)),
      forest_tree_top_(std::make_shared<Sprite_Obj>(63, 0, 1.f, 1.f, forest_tree_top_t_)),
      forest_tree_bot_(std::make_shared<Sprite_Obj>(forest_tree_bot_t_)) { }

    const size_t perlins_needed() override { return 2; }
    void get_Resources(const std::vector<std::vector<std::vector<state>>>&, size_t,
                       const std::vector<std::vector<Biome_enum>>&, std::vector<std::vector<std::shared_ptr<Resource>>>&) override;

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
      Two_Piece_Vert(pos_x, pos_y, 0, 32, 
	      	     forest.forest_bush_bot_->get_Ptr(rand() % forest.forest_bush_bot_->size()),
		     forest.forest_bush_top_->get_Ptr(rand() % forest.forest_bush_top_->size())) { }
  // TO DO : Add interface for collisions and invisible when under
  // TO DO : Other interface ? 
};

class Forest_Moss : public One_Piece {

  public:

    Forest_Moss(const float pos_x, const float pos_y, const Forest& forest):
      One_Piece(pos_x, pos_y,
	        forest.forest_moss_->get_Ptr(rand() % forest.forest_moss_->size())) { }
 
};
// TO DO : Fix these so there is a constant method of determining the center 
class Forest_Small_Tree : public Two_Piece_Vert {

  public:

    Forest_Small_Tree(const float pos_x, const float pos_y, const Forest& forest):
      Two_Piece_Vert(pos_x, pos_y, 0, 64,
		   forest.forest_small_tree_bot_->get_Ptr(rand() % forest.forest_small_tree_bot_->size()),
		   forest.forest_small_tree_top_->get_Ptr(rand() % forest.forest_small_tree_top_->size())) { }

};

class Forest_Tree : public Two_Piece_Vert {

  public:

    Forest_Tree(const float pos_x, const float pos_y, const Forest& forest):
      Two_Piece_Vert(pos_x, pos_y, 31, 96,
                   forest.forest_tree_bot_->get_Ptr(rand() % forest.forest_tree_bot_->size()),
                   forest.forest_tree_top_->get_Ptr(rand() % forest.forest_tree_top_->size())) { }

};

#endif
