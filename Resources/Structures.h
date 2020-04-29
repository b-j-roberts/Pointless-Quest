#ifndef STRUCTURES_H_
#define STRUCTURES_H

#include "Resources.h"

// Resource which has single Sprite and angle for particular item in world
class One_Piece : public Resource {
  
  // Sprite shared by all other One_Piece with the same sprite
  std::shared_ptr<sf::Sprite> sprite_;

  // Rotation of sprite_
  float angle_;

public:

  // Disallowed Constructors
  One_Piece() = delete;
  One_Piece(const One_Piece&) = delete;
  One_Piece& operator= (const One_Piece&) = delete;

  // params : pos_x, pos_y, shared_ptr to sprite, angle of resource (clockwise?)
  One_Piece(const float, const float, std::shared_ptr<sf::Sprite>, const float angle = 0);

  // Resource Overrides
  void draw(sf::RenderWindow&) const override;
  void transparent_draw(sf::RenderWindow&) const override;
  bool is_overlapped(const sf::FloatRect&) override; // TO DO : Make const (so do update)

};

// Resource which has 2 ("stacked") Sprites based on offset value for particular item in world
class Two_Piece_Vert : public Resource {
  
  // Sprites shared by all other Two_Piece with the same sprites
  std::shared_ptr<sf::Sprite> top_;
  std::shared_ptr<sf::Sprite> bot_;

  // Offset of top_ origin from bot_ origin ( flipped y )
  const float top_offset_x_, top_offset_y_;

public:

  // Disallowed Constructors
  Two_Piece_Vert() = delete;
  Two_Piece_Vert(const Two_Piece_Vert&);
  Two_Piece_Vert& operator= (const Two_Piece_Vert&);

  // params : pos_x, pos_y, top_offset_x, top_offset_y, bot sprite, top sprite 
  Two_Piece_Vert(const float, const float, const float, const float, 
                 std::shared_ptr<sf::Sprite>, std::shared_ptr<sf::Sprite>);
    
  // Resource Overrides
  void draw(sf::RenderWindow&) const override;
  void transparent_draw(sf::RenderWindow&) const override;
  bool is_overlapped(const sf::FloatRect&) override;

};


// Resource and Sprite_Obj (which holds animation in sequence over its vector) with interface
// for animating Sprite_Obj
class Animation : public Resource, public Sprite_Obj {

  // TO DO : Think about using percents instead of overrall frame counting in case
  //         one needs to skip frames to get timing right (if runs super slow)
  
  // Holds how many set_frames called since last curr_frame update, range : [0, (framerate/fps) - 1]
  size_t frame_inc_;  
  // Stores desired fps of Animation
  const size_t fps_;
  // Framerate of overall system (ie based on number of calls to set_frames() / second)
  static const size_t framerate_ = 60; // TO DO

protected:
  
  // Current drawn frame, range : [0, s_.size() - 1]
  size_t curr_frame_;

public:

  // params : pos x , pos y , constructor from Sprite Object
  Animation(const float, const float, 
            const Texture_Obj&, const float=0, const float=0, const double=1, const double=1);

  // Update animation frame info
  void set_frames();

  // Resource overrides
  void draw(sf::RenderWindow&) const override;
  void transparent_draw(sf::RenderWindow&) const override;
  bool is_overlapped(const sf::FloatRect&) override;

};

#endif
