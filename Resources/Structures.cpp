#include "Structures.h"

One_Piece::One_Piece(const float pos_x, const float pos_y, 
                     std::shared_ptr<sf::Sprite> sprite, const float angle):
  Resource(pos_x, pos_y),
  sprite_(sprite),
  angle_(angle) { }

void One_Piece::draw(sf::RenderWindow& window) const {
  window.draw(*sprite_);
}

const bool One_Piece::is_overlapped(const sf::FloatRect& rect) {
  sprite_->setPosition(pos_x_, pos_y_);
  sprite_->setRotation(angle_); 
  return sprite_->getGlobalBounds().intersects(rect);
}

void One_Piece::transparent_draw(sf::RenderWindow& window) const {
  sprite_->setColor(sf::Color(255, 255, 255, 100));
  window.draw(*sprite_);
  sprite_->setColor(sf::Color(255, 255, 255, 255));
}


Two_Piece_Vert::Two_Piece_Vert(const float pos_x, const float pos_y, const size_t bot_conn_x,
	               	             const size_t bot_conn_y, std::shared_ptr<sf::Sprite> bot, 
                               std::shared_ptr<sf::Sprite> top):
  Resource(pos_x, pos_y),
  top_pos_x_(static_cast<float>(bot_conn_x)),
  top_pos_y_(static_cast<float>(bot_conn_y)),
  top_(top),
  bot_(bot) { }

void Two_Piece_Vert::draw(sf::RenderWindow& window) const {
  window.draw(*bot_);
  window.draw(*top_); 
}

const bool Two_Piece_Vert::is_overlapped(const sf::FloatRect& rect) {
  bot_->setPosition(pos_x_,pos_y_);
  top_->setPosition(pos_x_ + top_pos_x_, pos_y_ - top_pos_y_);
  return top_->getGlobalBounds().intersects(rect) || bot_->getGlobalBounds().intersects(rect);
}

void Two_Piece_Vert::transparent_draw(sf::RenderWindow& window) const {
  bot_->setColor(sf::Color(255, 255, 255, 100));
  top_->setColor(sf::Color(255, 255, 255, 100));
  window.draw(*bot_);
  window.draw(*top_); 
  bot_->setColor(sf::Color(255, 255, 255, 255));
  top_->setColor(sf::Color(255, 255, 255, 255));
}
