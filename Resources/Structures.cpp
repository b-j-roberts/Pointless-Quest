#include "Structures.h"

One_Piece::One_Piece(const float pos_x, const float pos_y, std::shared_ptr<sf::Sprite> sprite):
  Resource(pos_x, pos_y),
  sprite_(sprite) { }

void One_Piece::draw(sf::RenderWindow& window) {
  sprite_->setPosition(pos_x_, pos_y_);
  window.draw(*sprite_);
}

Two_Piece_Vert::Two_Piece_Vert(const float pos_x, const float pos_y, const size_t bot_conn_x,
	               	             const size_t bot_conn_y, std::shared_ptr<sf::Sprite> bot, 
                               std::shared_ptr<sf::Sprite> top):
  Resource(pos_x, pos_y),
  top_pos_x_(static_cast<float>(bot_conn_x)),
  top_pos_y_(static_cast<float>(bot_conn_y)),
  top_(top),
  bot_(bot) { }

void Two_Piece_Vert::draw(sf::RenderWindow& window) {
  bot_->setPosition(pos_x_,pos_y_);
  top_->setPosition(pos_x_ + top_pos_x_, pos_y_ - top_pos_y_);
  window.draw(*bot_);
  window.draw(*top_); 
}
