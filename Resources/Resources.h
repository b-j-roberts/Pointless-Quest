#ifndef __RESOURCES_H_INCLUDED__
#define __RESOURCES_H_INCLUDED__

#include <memory>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

class Sprite_Obj;
class Texture_Obj;

// Store texture info from a png file inside Resources/
class Texture_Obj {
 
  //NOTES: Texture file should be a single row of all textures of a given type, all with the
  //       same size (ie width and height)

  //Disallow default constuction, copy constuction, and copy assignment
  Texture_Obj() = delete;
  Texture_Obj(const Texture_Obj&);
  Texture_Obj& operator= (const Texture_Obj&);

  const size_t height_, width_;
  const size_t num_;
  std::vector<sf::Texture> t_;

  friend class Sprite_Obj;
  
public:
    
    //Create a texture object with parameters 
    //  (height, width, num, name of file w/o .png, height offset (def 0), width offset (def 0))
    Texture_Obj(const size_t, const size_t, const size_t, std::string, 
                const size_t = 0, const size_t = 0);

};

// Holds sprites of provided textures
class Sprite_Obj {

  //NOTE: This class is a friend of Texture_Obj and holds sprites of provided textures
  //      Origin should be the connection position, if it has one

  //Disallow default constuction, copy constuction, and copy assignment
  Sprite_Obj() = delete;
  Sprite_Obj(const Sprite_Obj&);
  Sprite_Obj& operator= (const Sprite_Obj&);

  std::vector<std::shared_ptr<sf::Sprite>> s_;

public:
  //Create a sprite object with parameters (origin x, origin y, scale x, scale y, texture object)
  Sprite_Obj(const size_t, const size_t, const double, const double, const Texture_Obj&);

  //Create a sprite object with origin at (0,0) and no scale with parameter (texture object)
  Sprite_Obj(const Texture_Obj&);

  //Method to get sprite in position (param)
  std::shared_ptr<sf::Sprite> get_Ptr(const int); // TO DO : change to size_t

  size_t size() { return s_.size(); }

};

class Resource {

  public:

    Resource(float pos_x, float pos_y):
      pos_x_(pos_x),
      pos_y_(pos_y) { }

    const float x() { return pos_x_; }
    const float y() { return pos_y_; }
    void move(float x, float y) { pos_x_ += x; pos_y_ += y; } // TO DO : Make negative y?

    virtual void draw(sf::RenderWindow& window) { }

  protected:

    float pos_x_, pos_y_;

};

#endif
