#ifndef __STRUCTURES_H_INCLUDED__
#define __STRUCTURES_H_INCLUDED__

#include "Resources.h"

//Inherit from Resource class to allow polymorphism

class Two_Piece_Vert;
class One_Piece;

class One_Piece : public Resource {
  
  public:

    //Create a 1 piece object with parameters (position x, position y, sprite pointer)
    One_Piece(const float, const float, std::shared_ptr<sf::Sprite>);

    void draw(sf::RenderWindow&); // TO DO : Override

  private:

    //Disallow default constuction
    One_Piece() = delete;

    // TO DO : Do I want to be able to copy these?
    //Private Swap function
    //void Swap(One_Piece&);
    //Copy construction and Copy assignment
    One_Piece(const One_Piece&);
    One_Piece& operator= (const One_Piece&);

    std::shared_ptr<sf::Sprite> sprite_;

};

class Two_Piece_Vert : public Resource {
  
  public:

    //Create a 2 piece vertically connected object with parameters (position x, position y, bot to top connector position x,
    //                                                              bot to top connector position y, sprite pointer bot, sprite pointer top)
    Two_Piece_Vert(const float, const float, const size_t, const size_t, std::shared_ptr<sf::Sprite>, std::shared_ptr<sf::Sprite>);
    
    void draw(sf::RenderWindow&);

  private:

    //Disallow default construction
    Two_Piece_Vert() = delete;

    // TO DO : Do I want to copy ? if so need to use pimpl idiom bc const members
    //Private Swap function
    //void Swap(Two_Piece_Vert&);
    //Copy constuctor and Copy assignment
    Two_Piece_Vert(const Two_Piece_Vert&);
    Two_Piece_Vert& operator= (const Two_Piece_Vert&);


    const float top_pos_x_, top_pos_y_;
    std::shared_ptr<sf::Sprite> top_;
    std::shared_ptr<sf::Sprite> bot_;

};

#endif
