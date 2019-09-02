#include "Structures.h"

One_Piece::One_Piece(const float pos_x, const float pos_y, std::shared_ptr<sf::Sprite> sprite):
  Resource(pos_x, pos_y),
  sprite_(sprite) { }
/*
One_Piece::One_Piece(const One_Piece& One_piece):
  pos_x_(One_piece.pos_x_),
  pos_y_(One_piece.pos_y_),
  sprite_(One_piece.sprite_) { }

One_Piece& One_Piece::operator= (const One_Piece& One_piece) {
  One_Piece temp(One_piece);
  Swap(temp);
  return *this;
}

void One_Piece::Swap(One_Piece& One_piece) {
  std::swap(this->pos_x_,One_piece.pos_x_);
  std::swap(this->pos_y_,One_piece.pos_y_);
  std::swap(this->sprite_,One_piece.sprite_);
}
*/
void One_Piece::draw(sf::RenderWindow& window) {
  sprite_->setPosition(pos_x_, pos_y_);
  window.draw(*sprite_);
}


Two_Piece_Vert::Two_Piece_Vert(const float pos_x, const float pos_y, const size_t bot_conn_x,
	               	   const size_t bot_conn_y, std::shared_ptr<sf::Sprite> bot, std::shared_ptr<sf::Sprite> top):
  Resource(pos_x, pos_y),
  top_pos_x_(static_cast<float>(bot_conn_x)),
  top_pos_y_(pos_y + static_cast<float>(bot_conn_y)),
  top_(top),
  bot_(bot) { }
/*
Two_Piece_Vert::Two_Piece_Vert(const Two_Piece_Vert& Two_piece):
  bot_pos_x_(Two_piece.bot_pos_x_),
  bot_pos_y_(Two_piece.bot_pos_y_),
  top_pos_x_(Two_piece.top_pos_x_),
  top_pos_y_(Two_piece.top_pos_y_),
  top_(Two_piece.top_),
  bot_(Two_piece.bot_) { }

Two_Piece_Vert& Two_Piece_Vert::operator= (const Two_Piece_Vert& Two_piece) {
  Two_Piece_Vert temp(Two_piece);
  Swap(temp);
  return *this;
}

void Two_Piece_Vert::Swap(Two_Piece_Vert& Two_piece) {
//change to this->... ?
  std::swap(this->bot_pos_x, Two_piece.bot_pos_x);
  std::swap(this->bot_pos_y, Two_piece.bot_pos_y);
  std::swap(this->top_pos_x, Two_piece.top_pos_x);
  std::swap(this->top_pos_y, Two_piece.top_pos_y);
  std::swap(this->top_, Two_piece.top_);
  std::swap(this->bot_, Two_piece.bot_);
}
*/
void Two_Piece_Vert::draw(sf::RenderWindow& window) {
  bot_->setPosition(pos_x_,pos_y_);
  top_->setPosition(top_pos_x_,top_pos_y_);
  window.draw(*bot_);
  window.draw(*top_); 
}
