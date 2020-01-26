#ifndef __RESOURCES_H_INCLUDED__
#define __RESOURCES_H_INCLUDED__

#include "../Functions.h"

#include <memory> // shared_ptr
#include <string>

class Sprite_Obj;

// Stores textures from a png file inside Resources/
class Texture_Obj {
 
  // NOTE: Texture file should be a single row of all textures of a given type, all with the
  //       same size (ie width and height)

  // height & width of textures
  const size_t height_, width_;
  // Each texture has its own vector element
  std::vector<sf::Texture> t_;
  
public:
    
  // Disallow default constuction, copy constuction, and copy assignment
  Texture_Obj() = delete;
  Texture_Obj(const Texture_Obj&) = delete;
  Texture_Obj& operator= (const Texture_Obj&) = delete;

  // params : height, width, num, name of file w/o .png, height offset(=0), width offset(=0)
  Texture_Obj(const size_t, const size_t, const size_t, std::string, 
              const size_t = 0, const size_t = 0);

  friend class Sprite_Obj;

};

// Stores actual sf::Sprite's of textures from a Texture_Obj
class Sprite_Obj {

  // NOTES: This class is a friend of Texture_Obj, so directly indexing Texture_Obj given
  //       
  //        Origin should be the connection position, if it has one

protected: // TO DO : Is this what I want?

  // Each sprite has a shared_ptr for ease of use
  std::vector<std::shared_ptr<sf::Sprite>> s_;

public:

  // Disallow default constuction, copy constuction, and copy assignment
  Sprite_Obj() = delete;
  Sprite_Obj(const Sprite_Obj&) = delete;
  Sprite_Obj& operator= (const Sprite_Obj&) = delete;

  // params : texture object, origin x (=0), origin y (=0), scale x (=1), scale y (=1)
  Sprite_Obj(const Texture_Obj&, const size_t = 0, const size_t = 0, 
             const double = 1, const double = 1);

  // param : Index position of sprite in s_
  // Returns this sprite
  std::shared_ptr<sf::Sprite> get_Ptr(const size_t) const;

  const size_t size() const { return s_.size(); }

};

// Virtual Class used for polymorphic use of draw, generation, collisions, ...
// Stores location of any resource in the world (actual pixel location ie not by tile)
class Resource {

  protected:

    float pos_x_, pos_y_;

  public:

    Resource(float pos_x, float pos_y):
      pos_x_(pos_x),
      pos_y_(pos_y) { }

    // Functions for getting resource info & moving resource
    const float x() const { return pos_x_; }
    const float y() const { return pos_y_; }
    void move(float x, float y) { pos_x_ += x; pos_y_ += y; }

    // Virtual functions for drawing normally & transparently to window
    virtual void draw(sf::RenderWindow& window) const { }
    virtual void transparent_draw(sf::RenderWindow& window) const { }

    // Returns width of space needed to place resource (to the left & up of generation position)
    virtual const size_t generation_range() const { return 1; }

    // Returns radius about origin (pos) of resource in which collisions occur (0=collisionless)
    virtual const float collision_radius() const { return 0.f; }
                                                   
    // Returns whether given FloatRect overlaps the resource ( used for transparent draw of resource)
    virtual const bool is_overlapped(const sf::FloatRect&) { return false; }
    
};

#endif
