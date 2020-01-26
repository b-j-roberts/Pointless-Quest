#include "World.h"

//#include <algorithm> // std::sort

// return generated biome 2D vector with biome_enum values for biome 
std::vector<std::vector<Biome_enum>> Overworld::get_Biome_Map(size_t width, size_t height) {

  // TO DO : Use get_Min_Power on width and height

  std::vector<std::vector<double>> tile_heights = sudo_perlin_2D(width, height);
  normalize_2D(tile_heights);
  add_noise(tile_heights, 1, 300);

  double top_percent_cut = .75;
  double mid_percent_cut = .40;
  double bottom_percent_cut = .15;

  //get cutoff values
  std::vector<double> all_heights;
  for(size_t i = 0; i < width; ++i) {
    for(size_t j = 0; j < height; ++j) {
      all_heights.push_back(tile_heights[j][i]);
    }
  }
  std::sort(all_heights.begin(), all_heights.end());
  double top_cutoff = all_heights[width * height * top_percent_cut];
  double mid_cutoff = all_heights[width * height * mid_percent_cut];
  double bottom_cutoff = all_heights[width * height * bottom_percent_cut];

  std::vector<std::vector<Biome_enum>> ret;
  for(size_t i = 0; i < width; ++i) {
    std::vector<Biome_enum> temp;
    for(size_t j = 0; j < height; ++j) {
      if(tile_heights[j][i] > top_cutoff) temp.push_back(biome_enums_[0]);
      else if(tile_heights[j][i] > mid_cutoff) temp.push_back(biome_enums_[1]);
      else if(tile_heights[j][i] > bottom_cutoff) temp.push_back(biome_enums_[2]);
      else temp.push_back(biome_enums_[3]);
    }
    ret.push_back(temp);
  }

  
  return ret;

}

std::vector<std::vector<Biome_enum>> Underground::get_Biome_Map(size_t width, size_t height) {

  auto cave_region = get_Bounded_Region(width, height, width * height * .2); // TO DO : Think #
  std::vector<std::vector<Biome_enum>> ret;
  for(size_t i = 0; i < width; ++i) {
    std::vector<Biome_enum> temp;
    for(size_t j = 0; j < height; ++j) {
      if(cave_region[j][i]) temp.push_back(Cave_);
      else temp.push_back(None_); 
    }
    ret.push_back(temp);
  }

  return ret;
}

std::unique_ptr<World_Plane> get_Plane(Plane_enum p, const size_t width, const size_t height,
                                       const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec) {
  switch(p) {
    case Overworld_:
      return std::make_unique<Overworld>(width, height, tile_vec);
    case Underground_:
      return std::make_unique<Underground>(width, height, tile_vec);
    default:
      return std::make_unique<World_Plane>(width, height);
  }
}

// Draw part of world in view of the player to window
void World_Plane::draw(sf::RenderWindow& window, const Player& player) {
  
  // TILES
  for(int i = player.x_range().first; i < player.x_range().second; ++i) {
    for(int j = player.y_range().first; j < player.y_range().second; ++j) {
      tile_map_[j][i]->sprite_->setPosition(i * 32, j * 32);
      window.draw(*(tile_map_[j][i]->sprite_));
    }
  }

  player.draw(window);
  sf::FloatRect player_box = player.bounding_box();
  
  //RESOURCES
  for(int j = player.y_range().first; j < player.y_range().second; ++j) {
    for(int i = player.x_range().first; i < player.x_range().second; ++i) {
      if(resource_map_[j][i]) { // ignores nullptr
        if(resource_map_[j][i]->is_overlapped(player_box)) { // make transparent
          resource_map_[j][i]->transparent_draw(window);
        } else {
          resource_map_[j][i]->draw(window);
        }
      }
    }
  }

}

// Call draw function for correct plane
void World::draw(sf::RenderWindow& window, const Player& player) {
  world_[player.current_plane()]->draw(window, player);
}
