#include "Structures.h"

One_Piece::One_Piece(float pos_x, float pos_y, 
                     std::shared_ptr<sf::Sprite> sprite, float angle):
  Resource(pos_x, pos_y),
  sprite_(sprite),
  angle_(angle) { }

void One_Piece::draw(sf::RenderWindow& window) const {
  window.draw(*sprite_);
}

void One_Piece::transparent_draw(sf::RenderWindow& window) const {
  // Make sprite transparent
  sprite_->setColor(sf::Color(255, 255, 255, 100));
  window.draw(*sprite_);
  // Reset
  sprite_->setColor(sf::Color(255, 255, 255, 255));
}

bool One_Piece::is_overlapped(const sf::FloatRect& rect) {
  // TO DO : Move position and rotation to a set_sprite function?
  //         => make this function const
  sprite_->setPosition(pos_x_, pos_y_);
  sprite_->setRotation(angle_); 

  return sprite_->getGlobalBounds().intersects(rect);
}


Two_Piece_Vert::Two_Piece_Vert(float pos_x, float pos_y, float top_offset_x,
	               	             float top_offset_y, std::shared_ptr<sf::Sprite> bot, 
                               std::shared_ptr<sf::Sprite> top):
  Resource(pos_x, pos_y),
  top_(top),
  bot_(bot),
  top_offset_x_(top_offset_x),
  top_offset_y_(top_offset_y) { }

void Two_Piece_Vert::draw(sf::RenderWindow& window) const {
  window.draw(*bot_);
  window.draw(*top_); 
}

void Two_Piece_Vert::transparent_draw(sf::RenderWindow& window) const {
  // Make sprites transparent
  bot_->setColor(sf::Color(255, 255, 255, 100));
  top_->setColor(sf::Color(255, 255, 255, 100));
  window.draw(*bot_);
  window.draw(*top_); 
  // Reset
  bot_->setColor(sf::Color(255, 255, 255, 255));
  top_->setColor(sf::Color(255, 255, 255, 255));
}

bool Two_Piece_Vert::is_overlapped(const sf::FloatRect& rect) {
  // TO DO : Move position to a set_sprite function?
  //         => make this function const
  bot_->setPosition(pos_x_, pos_y_);
  top_->setPosition(pos_x_ + top_offset_x_, pos_y_ - top_offset_y_);

  return top_->getGlobalBounds().intersects(rect) || bot_->getGlobalBounds().intersects(rect);
}


Animation::Animation(float pos_x, float pos_y, const Texture_Obj& t_obj, 
                     size_t orig_x, size_t orig_y, float scale_x, float scale_y):  
  Resource(pos_x, pos_y),
  Sprite_Obj(t_obj, orig_x, orig_y, scale_x, scale_y),
  frame_inc_(0),
  fps_(5), // TO DO
  curr_frame_(0)
  { }

void Animation::set_frames() {
  if(++frame_inc_ == framerate_ / fps_) {
    frame_inc_ = 0;
    ++curr_frame_;
  } 
  if(curr_frame_ == s_.size()) curr_frame_ = 0;
}

void Animation::draw(sf::RenderWindow& window) const {
  // TO DO : Move this position setter into new Resource function
  s_[curr_frame_]->setPosition(pos_x_, pos_y_); 

  window.draw(*s_[curr_frame_]);

  // TO DO : Temp for collision circles
  sf::CircleShape body(15);
  body.setOrigin(15, 15);
  body.setPosition(pos_x_, pos_y_);
  body.setFillColor(sf::Color(255, 0, 0, 100));
  window.draw(body);
  sf::CircleShape loc(2);
  loc.setOrigin(1, 1);
  loc.setPosition(pos_x_, pos_y_);
  loc.setFillColor(sf::Color(255, 255, 0, 150));
  window.draw(loc);
}

void Animation::transparent_draw(sf::RenderWindow& window) const {
  // TO DO : Move this position setter into new Resource function
  s_[curr_frame_]->setPosition(pos_x_, pos_y_);

  // Make Transparent
  s_[curr_frame_]->setColor(sf::Color(255, 255, 255, 100));
  window.draw(*s_[curr_frame_]);
  // Reset
  s_[curr_frame_]->setColor(sf::Color(255, 255, 255, 255));
}

bool Animation::is_overlapped(const sf::FloatRect& rect) {
  return s_[curr_frame_]->getGlobalBounds().intersects(rect);
}
