#include "Player.h"

void Body::update(float vel_x, float vel_y, Player& player, const World& world) {

  // Move Resource into possibly colliding position
  move(vel_x, vel_y); // Move into possibly colliding space
  
  // Stores collision resolution shift vector
  float shifted_x = 0;
  float shifted_y = 0;

  // TO DO : Issue : tunneling
  // TO DO : Issue : Error if spawn on top of resource ( divide by 0 )
  // Collision resolution ( resolution vector calculated as (shifted_x, shifted_y) )
  const auto& rec_map = world.planes_.at(player.curr_plane_)->resource_map_;
  auto sq = [](float val){ return val * val; };
  for(size_t j = player.x_range_.first; j < player.x_range_.second; ++j) {
    for(size_t i = player.y_range_.first; i < player.y_range_.second; ++i) {
      if(rec_map[i][j] && rec_map[i][j]->collision_radius() != 0) { // Ignore nullptr & 0 radius
        const sf::Vector2f rec_pos = sf::Vector2f(rec_map[i][j]->x(), rec_map[i][j]->y());
        if(sq((pos_x_ - rec_pos.x)) + sq((pos_y_ - rec_pos.y)) <= 
           sq(body_size + rec_map[i][j]->collision_radius())) { // If is collision
          float center_distance = sqrt((pos_x_ - rec_pos.x) * (pos_x_ - rec_pos.x) + 
                                       (pos_y_ - rec_pos.y) * (pos_y_ - rec_pos.y));
          float overlap = center_distance - body_size - 
                          rec_map[i][j]->collision_radius();
          shifted_x -= overlap * (pos_x_ - rec_pos.x) / center_distance; // shift by x overlap
          shifted_y -= overlap * (pos_y_ - rec_pos.y) / center_distance; // shift by y overlap
        }
      }
    }
  }

  // Move out of colliding space
  move(shifted_x, shifted_y);

  // Move view same amount body moved
  player.view_.move(vel_x + shifted_x, vel_y + shifted_y);

  // Update animation frames
  set_frames();
}

// TO DO : Think about view size
Player::Player(float x_scale, int tile_size, const Texture_Obj& texture, float pos_x, float pos_y):
  body_(std::make_unique<Body>(texture, pos_x, pos_y)),
  view_(sf::Vector2f(pos_x, pos_y), 
        sf::Vector2f(x_scale * zoom_factor_ * tile_size / 3, zoom_factor_ * tile_size / 3)),
  curr_plane_(Overworld_) { }

void Player::update(float l_stick_x, float l_stick_y, 
                    float r_stick_x, float r_stick_y, const World& world) {

  body_->update(l_stick_x, l_stick_y, *this, world);

  // Calculate x_range & y_range
  auto size = view_.getSize();
  auto center = view_.getCenter();
  const int world_size_x = world.planes_.at(curr_plane_)->tile_map_[0].size();
  const int world_size_y = world.planes_.at(curr_plane_)->tile_map_.size();
  // Set draw range to be full view + 16 tiles in any direction ( accounting for boundaries )
  x_range_ = std::make_pair<size_t, size_t>(
                max(0, center.x - (size.x / 2) - 512) / 32,
                min(max(0, (center.x + (size.x / 2) + 512) / 32), world_size_x));
  y_range_ = std::make_pair<size_t, size_t>(
                max(0, center.y - (size.y / 2) - 512) / 32,
                min(max(0, (center.y + (size.y / 2) + 512) / 32), world_size_y));
}
