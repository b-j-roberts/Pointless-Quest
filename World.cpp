#include "World.h"

#include <numeric> // accumulate

#include <future>

void World_Plane::draw(sf::RenderWindow& window, const Player& player) const {
  
  // TILES
  for(size_t i = player.x_range().first; i < player.x_range().second; ++i) {
    for(size_t j = player.y_range().first; j < player.y_range().second; ++j) {
      tile_map_[j][i]->sprite_->setPosition(i * 32, j * 32);
      window.draw(*(tile_map_[j][i]->sprite_));
    }
  }

  // PLAYER
  player.draw(window);
  sf::FloatRect player_box = player.bounding_box();
  
  // RESOURCES
  for(size_t j = player.y_range().first; j < player.y_range().second; ++j) {
    for(size_t i = player.x_range().first; i < player.x_range().second; ++i) {
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

void World_Plane::generate(const size_t width, const size_t height) {

  // Create biome_enums_ vector by selecting random biomes in each section
  std::transform(possible_biomes().begin(), possible_biomes().end(),
                 std::back_inserter(biome_enums_), [](std::vector<Biome_enum> bv){ 
                   return bv[static_cast<size_t>(rand()) % bv.size()];
                 });

  // Create biomes_ vector
  std::transform(biome_enums_.begin(), biome_enums_.end(), std::back_inserter(biomes_),
                 [](Biome_enum b) { return get_Biome(b); });


  // Create 2D vector holding Biome_enum of the specific biome in that position
  auto biomes_map = get_Biome_Map(width, height);

  // Generate all Planes perlins needed
  typedef std::vector<std::vector<state>> state_perlin;
  state_perlin river;
  if(need_river()) river = get_States(width, height, 0.70f, 0.68f); 
  //std::future<state_perlin> fut_riv;
  //if(need_river()) fut_riv = std::async(std::launch::async, get_States, width, height, 0.70, 0.68); 
  size_t state_perlins_needed = std::accumulate(biomes_.begin(), biomes_.end(), 0ul,
                                [&](size_t a, const auto& b){ return a + b->perlins_needed(); });
  /*std::vector<state_perlin> all_perlin;
  for(int i = 0; i < state_perlins_needed; ++i) {
    all_perlin.emplace_back(get_States(width, height, 0.75, 0.50)); // TO DO : cut_offs are temp
  }*/
  // TO DO : Think about this
  std::vector<state_perlin> all_perlin;
  std::vector<std::future<state_perlin>> fut_perlin;
  for(size_t i = 0; i < state_perlins_needed; ++i) {
    fut_perlin.emplace_back(std::async(std::launch::async, get_States, width, height, .75, .5));
  }
  for(size_t i = 0; i < state_perlins_needed; ++i) {
    all_perlin.emplace_back(fut_perlin[i].get()); // TO DO : cut_offs are temp
  }
  //if(need_river()) river = fut_riv.get();

  // Call get_Resources ( fill tile_map_ & resource_map_ ) on each of biomes_ w/ info generated above
  size_t pos = 0;
  for(auto& biome : biomes_) {
    biome->get_Resources(tile_map_, resource_map_, biomes_map, all_perlin, pos, river);
    pos += biome->perlins_needed();
  }
  /*size_t pos = 0;
  std::future<void> resource_gen[4];
  size_t gen_pos = 0;
  for(auto& biome : biomes_) {
    resource_gen[gen_pos++] = std::async(std::launch::async, &Biome::get_Resources, *biome, tile_map_, resource_map_, biomes_map, all_perlin, pos, river);
    pos += biome->perlins_needed();
  }
  for(int i = 0; i < gen_pos; ++i) resource_gen[i].get();*/
 // auto a = std::async(std::launch::async, &Biome::get_Resources, *biomes_[0], tile_map_, resource_map_, biomes_map, all_perlin, 0, river);
 // a.get();

  // TO DO : Temp
  resource_map_[height / 2][width / 2] = nullptr;
}


std::vector<std::vector<Biome_enum>> Overworld::get_Biome_Map(size_t width, size_t height) {

  // TO DO : Use get_Min_Power on width and height

  // Generate tile_heights map ( used to determine biomes in position )
  auto tile_heights = sudo_perlin_2D(width, height);
  normalize_2D(tile_heights);
  add_noise(tile_heights, 1, 300);

  // Percent cuts for each biome 'level'
  float top_percent_cut = .75f;
  float mid_percent_cut = .40f;
  float bottom_percent_cut = .15f;

  //get cutoff values ( flatten, sort, index percent cut )
  std::vector<float> all_heights;
  for(const auto& row : tile_heights) {
    all_heights.insert(all_heights.end(), row.begin(), row.end());
  }
  std::sort(all_heights.begin(), all_heights.end());
  float top_cutoff = all_heights[static_cast<size_t>(width * height * top_percent_cut)];
  float mid_cutoff = all_heights[static_cast<size_t>(width * height * mid_percent_cut)];
  float bottom_cutoff = all_heights[static_cast<size_t>(width * height * bottom_percent_cut)];

  // Build return Biome_Map ( transform tile_heights based on cutoffs
  std::vector<std::vector<Biome_enum>> ret(height);
  size_t row_num = 0;
  for(const auto& row : tile_heights) {
    std::transform(row.begin(), row.end(), std::back_inserter(ret[row_num]), [&](float val){
      if(val > top_cutoff) return biome_enums_[0];
      else if(val > mid_cutoff) return biome_enums_[1];
      else if(val > bottom_cutoff) return biome_enums_[2];
      else return biome_enums_[3];
    });
    ++row_num;
  }

  return ret;
}

std::vector<std::vector<Biome_enum>> Underground::get_Biome_Map(size_t width, size_t height) {

  // Generate Bounded Cave region & transform into returned Biome_Map
  auto cave_region = get_Bounded_Region(width, height, width * height / 5); // TO DO : Think #
  std::vector<std::vector<Biome_enum>> ret(height);
  size_t row_num = 0;
  for(const auto& row : cave_region) {
    std::transform(row.begin(), row.end(), std::back_inserter(ret[row_num]), [](bool val){
      return val ? Cave_ : None_;
    });
    ++row_num;
  }

  return ret;
}

std::unique_ptr<World_Plane> get_Plane(Plane_enum p, const size_t width, const size_t height) {
  switch(p) {
    case Overworld_:
      return std::make_unique<Overworld>(width, height);
    case Underground_:
      return std::make_unique<Underground>(width, height);
  }
}

World::World(const size_t width, const size_t height) {
 
  // Generate Planes
  planes_[Overworld_] = get_Plane(Overworld_, width, height);
  planes_[Underground_] = get_Plane(Underground_, width, height);

  cities_[Overworld_] = std::make_unique<City_Plane>(width, height);

  // Cave entry
/*  // TO DO : Fix all of this
  //         More than one entrance, no river tiles
  size_t cave_entry_x = rand() % cave[0].size();
  size_t cave_entry_y = rand() % cave.size();
  while(!cave[cave_entry_y][cave_entry_x]) {
    cave_entry_x = rand() % cave[0].size();
    cave_entry_y = rand() % cave.size();
  }
  // TO DO : Fix index flip wherever in this codebase it may be
  for(size_t i = max(0, cave_entry_y - 2); i < min(width - 1, cave_entry_y + 2); ++i) {
    for(size_t j = max(0, cave_entry_x - 2); j < min(width - 1, cave_entry_x + 2); ++j) {
      resource_map_[j][i] = nullptr;
      cave_resource_map_[j][i] = nullptr;
      tile_map_[j][i] = std::make_shared<Tile>(Old_Ocean_, tile_vec[Old_Ocean_]); // TO DO : Temp
      cave_tile_map_[j][i] = std::make_shared<Tile>(Old_Ocean_, tile_vec[Old_Ocean_]);
    }
  }
*/
}

// Call draw function for correct plane
void World::draw(sf::RenderWindow& window, const Player& player) const {
  planes_.at(player.current_plane())->draw(window, player);
  cities_.at(player.current_plane())->draw(window, player);
}
