#include "Player.h"

void Body::update(float vel_x, float vel_y, Player& player, const World& world) {

  // DETECT and Resolve collisions

  move(vel_x, vel_y); // Move into possibly colliding space
  
  float shifted_x = 0;
  float shifted_y = 0;

  // TO DO : Issue : tunneling
  // TO DO : Issue : Error if spawn on top of resource
  // TO DO : Issue : no collisions in cave but always collisions from overworld
  // Collision resolution ( resolution vector calculated as (shifted_x, shifted_y) )
  for(int j = player.x_range_.first; j < player.x_range_.second; ++j) {
    for(int i = player.y_range_.first; i < player.y_range_.second; ++i) {
      if(world.resource_map_[i][j] && world.resource_map_[i][j]->collision_radius() != 0) { 
        const sf::Vector2f rec_pos = world.resource_map_[i][j]->get_pos();
        if((pos_x_ - rec_pos.x) * (pos_x_ - rec_pos.x) + 
            (pos_y_ - rec_pos.y) * (pos_y_ - rec_pos.y) <= 
            (body_size + world.resource_map_[i][j]->collision_radius()) * 
            (body_size + world.resource_map_[i][j]->collision_radius())) { // Is collision
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

  move(shifted_x, shifted_y); // Move out of colliding space

  // Move view same amount body moved
  player.view_.move(vel_x + shifted_x, vel_y + shifted_y);

  // Update animation frames
  set_frames();
}


Player::Player(float x_scale, int tile_size, const Texture_Obj& texture):
  body_(std::make_unique<Body>(texture)), // default position
  view_(sf::Vector2f(tile_size / 2 + body_->x(), tile_size / 2 + body_->y()), 
        sf::Vector2f(x_scale * zoom_factor_ * tile_size / 3, zoom_factor_ * tile_size / 3)),
  in_cave_(false) { }
//curr_plane_(Overworld_) { }

Player::Player(float x_scale, int tile_size, float pos_x, float pos_y, const Texture_Obj& texture):
  body_(std::make_unique<Body>(texture, pos_x, pos_y)),
  view_(sf::Vector2f(tile_size / 2 + body_->x(), tile_size / 2 + body_->y()), 
        sf::Vector2f(x_scale * zoom_factor_ * tile_size / 3, zoom_factor_ * tile_size / 3)),
  in_cave_(false) { }
//curr_plane_(Overworld_) { }

// Calls body update, which does all necessary updates ( including players view )
// & calculate new ranges
void Player::update(float l_stick_x, float l_stick_y, 
                    float r_stick_x, float r_stick_y, const World& world) {

  body_->update(l_stick_x, l_stick_y, *this, world);

  // Calculate x_range & y_range
  auto size = view_.getSize();
  auto center = view_.getCenter();

  const int world_size_x = world.tile_map_.size();
  const int world_size_y = world.tile_map_[0].size();

  x_range_ = std::make_pair<int, int>(
                max(0, center.x - (size.x / 2) - 512) / 32,
                min(max(0, (center.x + (size.x / 2) + 512) / 32), world_size_x));

  y_range_ = std::make_pair<int, int>(
                max(0, center.y - (size.y / 2) - 512) / 32,
                min(max(0, (center.y + (size.y / 2) + 512) / 32), world_size_y));

}
