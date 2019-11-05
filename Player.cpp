#include "Player.h"

Body tempbody;

void Body::update(float vel_x, float vel_y) {

  move(vel_x, vel_y);// TO DO

}

// Note : Change 25.f to zoom in and out
Player::Player(float x_scale, int tile_size):
body_(std::make_unique<Body>(tempbody)), // default body construct
  vel_x_(0),
  vel_y_(0),
  angle_(0),
  view_(sf::Vector2f(tile_size / 2 + body_->x(), tile_size / 2 + body_->y()), 
        sf::Vector2f(x_scale * 25.f * tile_size / 3, 25.f * tile_size / 3)) { }

Player::Player(float x_scale, int tile_size, float pos_x, float pos_y):
  body_(std::make_unique<Body>(tempbody)),
  vel_x_(0),
  vel_y_(0),
  angle_(0),
  view_(sf::Vector2f(tile_size / 2 + body_->x(), tile_size / 2 + body_->y()), 
        sf::Vector2f(x_scale * 25.f * tile_size / 3, 25.f * tile_size / 3)) { }

void Player::update(float l_stick_x, float l_stick_y, float r_stick_x, float r_stick_y) {
  vel_x_ = l_stick_x;
  vel_y_ = l_stick_y; // TO DO : Add some slow down effect so no instant stops?
  angle_ = 0;//angle_2f(r_stick_x, r_stick_y); // TO DO : Create this function
  view_.move(vel_x_, vel_y_);

  body_->update(vel_x_, vel_y_); // TO DO
}
