#include "Player.h"
#include <cmath> // TO DO : Move

//Body tempbody;

void Body::update(float vel_x, float vel_y, Player& player, const World& world) {

  move(vel_x, vel_y);// TO DO

  // DETECT and Resolve collisions
  float shifted_x = 0;
  float shifted_y = 0;

  // TO DO : Make this calculate only once per frame
  auto size = player.get_View().getSize();
  auto center = player.get_View().getCenter();

  const int world_size_i = world.tile_map_.size();
  const int world_size_j = world.tile_map_[0].size();

  int begin_i = max(0, center.x - (size.x / 2) - 512) / 32;
  int end_i = min(max(0, (center.x + (size.x / 2) + 512) / 32), world_size_i);

  int begin_j = max(0, center.y - (size.y / 2) - 512) / 32;
  int end_j = min(max(0, (center.y + (size.y / 2) + 512) / 32), world_size_j);

  //const float player_radius = 15; // TO DO : Temp

  // TO DO : Issue : tunneling
  // TO DO : Issue : Error if spawn on top of resource
  // TO DO : Issue : no collisions in cave but always collisions from overworld
  for(int j = begin_j; j < end_j; ++j) {
    for(int i = begin_i; i < end_i; ++i) {
      if(world.resource_map_[i][j] && world.resource_map_[i][j]->collision_radius() != 0) { 
        const sf::Vector2f rec_pos = world.resource_map_[i][j]->get_pos();
        if((pos_x_ - rec_pos.x) * (pos_x_ - rec_pos.x) + 
            (pos_y_ - rec_pos.y) * (pos_y_ - rec_pos.y) <= 
            (body_size + world.resource_map_[i][j]->collision_radius()) * 
            (body_size + world.resource_map_[i][j]->collision_radius())) { // Collision
          //world.resource_map_[i][j]->collide();
          float center_distance = sqrt((pos_x_ - rec_pos.x) * (pos_x_ - rec_pos.x) + 
                                       (pos_y_ - rec_pos.y) * (pos_y_ - rec_pos.y));
          float overlap = center_distance - body_size - 
                          world.resource_map_[i][j]->collision_radius();
          shifted_x -= overlap * (pos_x_ - rec_pos.x) / center_distance;
          shifted_y -= overlap * (pos_y_ - rec_pos.y) / center_distance;
        }
      }
    }
  }

  move(shifted_x, shifted_y);

  set_frames();

  // somehow transmit movement back to player update?
  player.view_.move(vel_x + shifted_x, vel_y + shifted_y);

}

// Note : Change 25.f to zoom in and out
Player::Player(float x_scale, int tile_size, const Texture_Obj& texture):
body_(std::make_unique<Body>(texture)), // default body construct
  vel_x_(0),
  vel_y_(0),
  angle_(0), // TO DO : Move to body
  view_(sf::Vector2f(tile_size / 2 + body_->x(), tile_size / 2 + body_->y()), 
        sf::Vector2f(x_scale * 25.f * tile_size / 3, 25.f * tile_size / 3)),
  in_cave_(false) { }

Player::Player(float x_scale, int tile_size, float pos_x, float pos_y, const Texture_Obj& texture):
  body_(std::make_unique<Body>(texture)),
  vel_x_(0),
  vel_y_(0),
  angle_(0),
  view_(sf::Vector2f(tile_size / 2 + body_->x(), tile_size / 2 + body_->y()), 
        sf::Vector2f(x_scale * 25.f * tile_size / 3, 25.f * tile_size / 3)),
  in_cave_(false) { }

void Player::update(float l_stick_x, float l_stick_y, float r_stick_x, float r_stick_y, const World& world) {
  vel_x_ = l_stick_x;
  vel_y_ = l_stick_y; // TO DO : Add some slow down effect so no instant stops?
  angle_ = 0;//angle_2f(r_stick_x, r_stick_y); // TO DO : Create this function

  body_->update(vel_x_, vel_y_, *this, world); // TO DO

}
