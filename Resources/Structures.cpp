#include "Structures.h"

One_Piece::One_Piece(const float pos_x, const float pos_y, 
                     std::shared_ptr<sf::Sprite> sprite, const float angle):
  Resource(pos_x, pos_y),
  sprite_(sprite),
  angle_(angle) { }

void One_Piece::draw(sf::RenderWindow& window) const {
//  if(get_collide()) { sprite_->setColor(sf::Color(200, 0, 0)); }
  window.draw(*sprite_);
//  sprite_->setColor(sf::Color(255, 255, 255, 255));
}

const bool One_Piece::is_overlapped(const sf::FloatRect& rect) {
  sprite_->setPosition(pos_x_, pos_y_);
  sprite_->setRotation(angle_); 
  return sprite_->getGlobalBounds().intersects(rect);
}

//const sf::Vector2f One_Piece::get_pos() const { 
//  return sf::Vector2f(pos_x_, pos_y_) - sprite_->getOrigin(); 
//}

void One_Piece::transparent_draw(sf::RenderWindow& window) const {
//  if(get_collide()) { sprite_->setColor(sf::Color(200, 0, 0)); }
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
//  if(get_collide()) { bot_->setColor(sf::Color(200, 0, 0)); top_->setColor(sf::Color(200, 0, 0));}
  window.draw(*bot_);
  window.draw(*top_); 
//  bot_->setColor(sf::Color(255, 255, 255, 255));
//  top_->setColor(sf::Color(255, 255, 255, 255));
}

const bool Two_Piece_Vert::is_overlapped(const sf::FloatRect& rect) {
  bot_->setPosition(pos_x_, pos_y_);
  top_->setPosition(pos_x_ + top_pos_x_, pos_y_ - top_pos_y_);
  return top_->getGlobalBounds().intersects(rect) || bot_->getGlobalBounds().intersects(rect);
}

//const sf::Vector2f Two_Piece_Vert::get_pos() const { 
//  return sf::Vector2f(pos_x_, pos_y_) - bot_->getOrigin(); 
//}

void Two_Piece_Vert::transparent_draw(sf::RenderWindow& window) const {
//  if(get_collide()) { bot_->setColor(sf::Color(200, 0, 0)); top_->setColor(sf::Color(200, 0, 0));}
  bot_->setColor(sf::Color(255, 255, 255, 100));
  top_->setColor(sf::Color(255, 255, 255, 100));
  window.draw(*bot_);
  window.draw(*top_); 
  bot_->setColor(sf::Color(255, 255, 255, 255));
  top_->setColor(sf::Color(255, 255, 255, 255));
}

// TO DO : Maybe change these to take a sprite object instead so we dont need to duplicate
Animation::Animation(const float pos_x, const float pos_y, 
                     const size_t orig_x, const size_t orig_y, const double scale_x, 
                     const double scale_y, const Texture_Obj& t_obj):
  Resource(pos_x, pos_y),
  Sprite_Obj(orig_x, orig_y, scale_x, scale_y, t_obj),
  frames(size()),
  curr_frame(0),
  frame_inc(0),
  fps(5) // TO DO
  { }

Animation::Animation(const float pos_x, const float pos_y, const Texture_Obj& t_obj):
  Resource(pos_x, pos_y),
  Sprite_Obj(t_obj),
  frames(size()),
  curr_frame(0),
  frame_inc(0), 
  fps(5) // TO DO
  { }

void Animation::set_frames() {
  if(++frame_inc == framerate / fps) {
    frame_inc = 0;
    ++curr_frame;
  } 
  if(curr_frame == frames) curr_frame = 0;
}

void Animation::draw(sf::RenderWindow& window) const {
  s_[curr_frame]->setPosition(pos_x_, pos_y_); 
  window.draw(*s_[curr_frame]);
}

void Animation::transparent_draw(sf::RenderWindow& window) const {
  s_[curr_frame]->setPosition(pos_x_, pos_y_);
  s_[curr_frame]->setColor(sf::Color(255, 255, 255, 100));
  window.draw(*s_[curr_frame]);
  s_[curr_frame]->setColor(sf::Color(255, 255, 255, 255));
}

const bool Animation::is_overlapped(const sf::FloatRect& rect) {
  return s_[curr_frame]->getGlobalBounds().intersects(rect);
}
