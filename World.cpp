#include "World.h"

#include <algorithm>

#include <map> // TO DO
#include <iostream> // TO DO

//static members
constexpr Biome_enum World::biomes_[4];

//returns minumum power of mult greater than num
int get_Min_Power(int num, int mult) {
  int ret = mult;
  while(ret < num) {
    ret *= mult;
  }
  return ret;
}

struct point_3D {

  double x, y, z;

  point_3D(double x_, double y_, double z_): x(x_), y(-1 * y_), z(z_) { }

};

// return height of point at pos on line with points (start , height_1) & (end , height_2)
double line_calc(size_t pos, double start, double end, double height_1, double height_2) {

  double m = (height_2 - height_1) / (end - start);
  return m * ( pos - end ) + height_1;
}

// returns height of point (x , y) in 3D space on place with 3 points corner_1, 2, & 3
double height_calc(size_t x, size_t y, const point_3D& corner_1, 
                   const point_3D& corner_2, const point_3D& center) {

  double a = (corner_1.y - center.y) * (corner_2.z - center.z) - 
             (corner_2.y - center.y) * (corner_1.z - center.z);
  double b = (corner_1.z - center.z) * (corner_2.x - center.x) - 
             (corner_2.z - center.z) * (corner_1.x - center.x);
  double c = (corner_1.x - center.x) * (corner_2.y - center.y) - 
             (corner_2.x - center.x) * (corner_1.y - center.y);
  double d = -1 * (a * center.x + b * center.y + c * center.z);

  return -1 * (a * (double)x - b * (double)y + d) / c;
}

// returns true if (x , y) in bottom right triangle of square with bottom-left point bl
bool is_under(size_t x, size_t y, const point_3D& bl) {
  return (-1 * (double)y) < ((double)x + bl.y - bl.x);
}

// return a perlin-ish 2D vector with width and height as specified ( must be power of 2 )
std::vector<std::vector<double>> sudo_perlin_2D(size_t width, size_t height) {

  std::vector<double> empty_vec(width + 1, 0);
  std::vector<std::vector<double>> ret(height + 1, empty_vec);

  size_t factor = 4;

  while(factor < width / 4) {
    double scale = 1 / (double)factor;
    double shift_x = width * scale;
    double shift_y = height * scale;
    std::vector<std::vector<double>> curr(height + 1, empty_vec);
    // set corners of boxes to random #
    for(int i = 0; i < width; i += shift_x) {
      for(int j = 0; j < height; j += shift_y) {
        curr[i][j] = (double)(rand() % 100);
      }
    }
    // use plane to find all other value other than bottom and right edges
    for(int i = 0; i < width; i += shift_x) {
      for(int j = 0; j < height; j += shift_y) {
        point_3D TL(i, j, curr[i][j]);
        point_3D TR(i + shift_x, j, curr[i + shift_x][j]);
        point_3D BL(i, j + shift_y, curr[i][j + shift_y]);
        point_3D BR(i + shift_x, j  + shift_y, curr[i + shift_x][j + shift_y]);
        for(int k = i; k < i + shift_x; ++k) {
          for(int m = j; m < j + shift_y; ++m) {
            curr[k][m] = height_calc(k, m, TR, BL, (is_under(k, m, BL) ? BR : TL));
          }
        }
      }
    }
    // Bottom edge
    for(int i = 0; i < width; i += shift_x) {
      for(int j = i; j < i + shift_x; ++j) {
        curr[height][j] = line_calc(j, i, i + shift_x, curr[height][i], curr[height][i + shift_x]);
      }
    }
    // Right edge
    for(int i = 0; i < height; i += shift_y) {
      for(int j = i; j < i + shift_y; ++j) {
        curr[j][width] = line_calc(j, i, i + shift_y, curr[i][width - 1], curr[i + shift_y][width]);
      }
    }
    // Multiply by scale and add to ret
    for(int i = 0; i < width; ++i) {
      for(int j = 0; j < height; ++j) {
        ret[i][j] += curr[i][j] * scale;
      }
    }

    factor *= 2;
  }

  return ret;

}

// return max value in 2D vector
template <typename T>
T max_2D(const std::vector<std::vector<T>>& vec) {
  
  T max(0);
  if(vec.begin() == vec.end()) return max;
  size_t w = vec.size();
  for(int i = 0; i < w; ++i) {
    size_t h = vec[i].size(); 
    for(int j = 0; j < h; ++j) {
      if(vec[i][j] > max) max = vec[i][j];
    }
  }

  return max;
}

// normalizes 2D vector ( ie scales so max val is 1 ) using max_2D funtion
void normalize_2D(std::vector<std::vector<double>>& vec) {
  
  double max = max_2D(vec);
  size_t w = vec.size();
  for(int i = 0; i < w; ++i) {
    size_t h = vec[i].size();
    for(int j = 0; j < h; ++j) {
      vec[i][j] /= max;
    }
  }

}

// returns the avg value about vec[i][j] with square radius rad
double avg_abt_2D(const std::vector<std::vector<double>>& vec, size_t i, size_t j, size_t rad) {

  double avg = 0;
  size_t max_x = vec[i].size();
  size_t max_y = vec.size();
  size_t tot = 0;
  for(int k = min(0, i - rad), k_end = min(max_y, i + rad); k < k_end; ++k) {
    for(int m = min(0, j - rad), m_end = min(max_x, j + rad); m < m_end; ++m) {
      avg+=vec[k][j];
      ++tot;
    }
  }

  return avg / tot;

}

// smooths vec by making each value equal to the average about it with square radius smooth_rad
void smooth_2D(std::vector<std::vector<double>>& vec, size_t smooth_rad) {

  size_t w = vec.size();
  std::vector<std::vector<double>> smoother(w);
  for(int i = 0; i < w; ++i) {
    size_t h = vec[i].size();
    std::vector<double> tmp(h);
    for(int j = 0; j < h; ++j) {
      tmp[j] = avg_abt_2D(vec, i, j, smooth_rad);
    }
    std::swap(smoother[i], tmp);
  }

  std::swap(smoother, vec);

}

// adds random noise based on noise scale given to all items in vec
// ex: factor = 3, scale = 10 => noise added ranges [-3/10 , 3/10 ]
void add_noise(std::vector<std::vector<double>>& vec, int factor, int scale) {
  size_t w = vec.size();
  for(int i = 0; i < w; ++i) {
    size_t h = vec[i].size();
    for(int j = 0; j < h; ++j) {
      float noise = (rand() % (2 * factor + 1)) - factor;
      noise /= (float)scale; // TO DO : move cast out?
      vec[i][j] += noise;
    }
  }
}

// return generated biome 2D vector with biome_enum values for biome 
std::vector<std::vector<Biome_enum>> World::get_Biomes(size_t width, size_t height) {

  // TO DO : Use get_Min_Power on width and height

  std::vector<std::vector<double>> tile_heights = sudo_perlin_2D(width, height);
  normalize_2D(tile_heights);
  //smooth_2D(tile_heights, 3); TO DO : Super slow rn
  add_noise(tile_heights, 1, 300);

  double top_percent_cut = .75;
  double mid_percent_cut = .40;
  double bottom_percent_cut = .15;

  //get cutoff values
  std::vector<double> all_heights;
  for(size_t i = 0; i < width; ++i) {
    for(size_t j = 0; j < height; ++j) {
      all_heights.push_back(tile_heights[i][j]);
    }
  }
  std::sort(all_heights.begin(), all_heights.end());
  double top_cutoff = all_heights[width * height * top_percent_cut];
  double mid_cutoff = all_heights[width * height * mid_percent_cut];
  double bottom_cutoff = all_heights[width * height * bottom_percent_cut];

  std::vector<std::vector<Biome_enum>> ret;
  for(size_t i = 0; i < width; ++i) {
    std::vector<Biome_enum> temp;
    for(size_t j = 0; j < height; ++j) { // TO DO: Create a way to define these biome types
      if(tile_heights[i][j] > top_cutoff) temp.push_back(biomes_[0]);
      else if(tile_heights[i][j] > mid_cutoff) temp.push_back(biomes_[1]);
      else if(tile_heights[i][j] > bottom_cutoff) temp.push_back(biomes_[2]);
      else temp.push_back(biomes_[3]);
    }
    ret.push_back(temp);
  }

  /*
  std::map<Biome_enum, size_t> biome_counts;
  biome_counts[biomes_[0]] = 0;
  biome_counts[biomes_[1]] = 0;
  biome_counts[biomes_[2]] = 0;
  biome_counts[biomes_[3]] = 0;
  for(size_t i = 0; i < ret.size(); ++i) {
    for(size_t j = 0; j < ret[i].size(); ++j) {
      biome_counts[ret[i][j]] += 1; 
    }
  }
  std::cout << "Top : " << biome_counts[biomes_[0]] << std::endl;
  std::cout << "Mid : " << biome_counts[biomes_[1]] << std::endl;
  std::cout << "Bot : " << biome_counts[biomes_[2]] << std::endl;
  std::cout << "Liq : " << biome_counts[biomes_[3]] << std::endl;
  */  

  return ret;

}

// get a sudo perlin for states with cutoffs of state values specified 
std::vector<std::vector<state>> get_States(size_t width, size_t height, 
                                           double top_percent_cut, double bot_percent_cut) {

  std::vector<std::vector<double>> tile_heights = sudo_perlin_2D(width, height);
  normalize_2D(tile_heights);

  //get cutoff values
  std::vector<double> all_heights;
  for(size_t i = 0; i < width; ++i) {
    for(size_t j = 0; j < height; ++j) {
      all_heights.push_back(tile_heights[i][j]);
    }
  }
  std::sort(all_heights.begin(), all_heights.end());
  double top_cutoff = all_heights[width * height * top_percent_cut];
  double bot_cutoff = all_heights[width * height * bot_percent_cut];
  
  std::vector<std::vector<state>> ret;
  for(size_t i = 0; i < width; ++i) {
    std::vector<state> temp;
    for(size_t j = 0; j < height; ++j) {
      if(tile_heights[i][j] > top_cutoff) temp.push_back(Top);
      else if(tile_heights[i][j] > bot_cutoff) temp.push_back(Middle);
      else temp.push_back(Bottom);
    }
    ret.push_back(temp);
  }

  return ret;
}

// TO DO : Think about checking low_bound to make sure it is possible to have that many elems
// TO DO : Think about vector of bools
//
// create a 2d vector containing true if position in bounded region, and false otherwise
// makes sure that there are at least low_bound elements in bounded region
std::vector<std::vector<bool>> get_Bounded_Region(size_t width, size_t height, size_t low_bound) {

  // Initialize vector
  std::vector<bool> false_vec(width, false);
  std::vector<std::vector<bool>> ret(height, false_vec);

  // Pick random starting point
  int x = rand() % (width - 2) + 1; // NOTE : this stops corners ( see below note )
  int y = rand() % (height - 2) + 1;

  ret[y][x] = true;

  size_t bounded_count = 1;

  // Note : min 1 & max - 2 because we dont want to have to check for indexing errors
  int min_i = max(1, x - 1);
  int min_j = max(1, y - 1);
  int max_i = min(width - 2, x + 1);
  int max_j = min(height - 2, y + 1);

  while(bounded_count < low_bound) {
    for(size_t i = min_i; i <= max_i; ++i) {
      for(size_t j = min_j; j <= max_j; ++j) {
        if(!ret[j][i]) {
          size_t possible = 0;
          // Make more and more possible based on surrounding points ( 100% likely if enclosed )
          if(ret[j-1][i]) ++possible;
          if(ret[j+1][i]) ++possible;
          if(ret[j][i-1]) ++possible;
          if(ret[j][i+1]) ++possible;
          size_t chance = rand() % 4;
          if(chance < possible) {
            ret[j][i] = true;
            if(j == min_j) min_j = max(1, j - 1);
            else if(j == max_j) max_j = min(height - 2, j + 1);
            else if(i == min_i) min_i = max(1, i - 1);
            else if(i == max_i) max_i = min(width - 2, i + 1);
            ++bounded_count;
          }
        }
      }
    }
  }

  return ret;

}

// Generates the entire world [ biomes (tiles , resources)
void World::generate(size_t width, size_t height, 
                     const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec) {

  // Loading Biomes Sprites and Textures
  biomes[0] = std::make_unique<BiomeType<biomes_[0]>::type>();
  biomes[1] = std::make_unique<BiomeType<biomes_[1]>::type>();
  biomes[2] = std::make_unique<BiomeType<biomes_[2]>::type>();
  biomes[3] = std::make_unique<BiomeType<biomes_[3]>::type>();

  size_t state_perlins_needed = 0;
  state_perlins_needed += biomes[0]->perlins_needed();
  state_perlins_needed += biomes[1]->perlins_needed();
  state_perlins_needed += biomes[2]->perlins_needed();
  state_perlins_needed += biomes[3]->perlins_needed();

  typedef std::vector<std::vector<state>> state_perlin;
  std::vector<state_perlin> all_perlin;
  for(int i = 0; i < state_perlins_needed; ++i) {
    all_perlin.emplace_back(get_States(width, height, 0.75, 0.50)); // These cut_offs are temp
  }

  std::vector<std::vector<Biome_enum>> biomes_map = get_Biomes(width, height);

  state_perlin river = get_States(width, height, 0.70, 0.68); // TO DO : More than one river

  // TO DO : Do tile map with other resources so one can use perlin in case needed
  // TO DO : Noisy edges
  size_t h = biomes_map.size();

  // Layer 0 initialize
  tile_map_.resize(h);
  std::vector<std::shared_ptr<Tile>> null_tile_vec(biomes_map[0].size(), nullptr);
  for(size_t i = 0; i < h; ++i) {
    tile_map_[i] = null_tile_vec; 
  }

  // Layer 1 initialize
  resource_map_.resize(h);
  std::vector<std::shared_ptr<Resource>> null_rec_vec(biomes_map[0].size(), nullptr);
  for(int i = 0; i < h; ++i) {
    resource_map_[i] = null_rec_vec;
  }

  // TO DO : 
  // layers
  // Other ?

  size_t pos = 0; 
  biomes[0]->get_Resources(all_perlin, pos, biomes_map, tile_vec, tile_map_, river, resource_map_);
  pos += biomes[0]->perlins_needed();
  biomes[1]->get_Resources(all_perlin, pos, biomes_map, tile_vec, tile_map_, river, resource_map_);
  pos += biomes[1]->perlins_needed();
  biomes[2]->get_Resources(all_perlin, pos, biomes_map, tile_vec, tile_map_, river, resource_map_);
  pos += biomes[2]->perlins_needed();
  biomes[3]->get_Resources(all_perlin, pos, biomes_map, tile_vec, tile_map_, river, resource_map_);

  // TO DO : Temp
  resource_map_[1000][1000] = nullptr;


  // Create caves
  
  cave_ = std::make_unique<Cave>();

  // Cave Layer 0 initialize
  cave_tile_map_.resize(h);
  for(size_t i = 0; i < h; ++i) {
    cave_tile_map_[i] = null_tile_vec;
  }

  // Cave Layer 1 initialize
  cave_resource_map_.resize(h);
  for(int i = 0; i < h; ++i) {
    cave_resource_map_[i] = null_rec_vec;
  }
  
  // TO DO : Think about size
  std::vector<std::vector<bool>> cave = get_Bounded_Region(width, height, width * height * .2);
  cave_->get_Resources(cave, tile_vec, cave_tile_map_, cave_resource_map_);

  // TO DO : pick between 3 and 5 intrance points and place it on top biomes
  //   make sure no river tiles?
  size_t cave_entry_x = rand() % cave[0].size();
  size_t cave_entry_y = rand() % cave.size();
  while(!cave[cave_entry_y][cave_entry_x]) {
    cave_entry_x = rand() % cave[0].size();
    cave_entry_y = rand() % cave.size();
  }
  // TO DO : Something here is flipped with the indexes... fix this then fix width, heights...
  // clear cave resources & main resources
  for(size_t i = max(0, cave_entry_y - 2); i < min(width - 1, cave_entry_y + 2); ++i) {
    for(size_t j = max(0, cave_entry_x - 2); j < min(width - 1, cave_entry_x + 2); ++j) {
      resource_map_[j][i] = nullptr;   
      cave_resource_map_[j][i] = nullptr;
      tile_map_[j][i] = std::make_shared<Tile>(Unocean_, tile_vec[Unocean_]); // TO DO : Temp
      cave_tile_map_[j][i] = std::make_shared<Tile>(Unocean_, tile_vec[Unocean_]);
    }
  }
  std::cout << cave_entry_x * 32 << " " << cave_entry_y * 32 << std::endl;
  // TO DO : make tiles under and on surface special

}

// Draw part of world in view of player to window
void World::draw(sf::RenderWindow& window, const Player& player) {

  auto size = player.get_View().getSize();
  auto center = player.get_View().getCenter();

  const int world_size_i = tile_map_.size();
  const int world_size_j = tile_map_[0].size();

  int begin_i = max(0, center.x - (size.x / 2) - 512) / 32;
  int end_i = min(max(0, (center.x + (size.x / 2) + 512) / 32), world_size_i);

  int begin_j = max(0, center.y - (size.y / 2) - 512) / 32;
  int end_j = min(max(0, (center.y + (size.y / 2) + 512) / 32), world_size_j);

  bool in_cave = player.in_cave();

  // Draw Tiles in view
  for(int i = begin_i; i < end_i; ++i) {
    for(int j = begin_j; j < end_j; ++j) { 
      if(in_cave) { 
        // TO DO : Change this to selecting tile map and resource map by reference ?
        if(cave_tile_map_[i][j]) {
          cave_tile_map_[i][j]->sprite_->setPosition(i * 32, j * 32);
          window.draw(*(cave_tile_map_[i][j]->sprite_));
        }
      } else {
        tile_map_[i][j]->sprite_->setPosition(i * 32, j * 32);
        window.draw(*(tile_map_[i][j]->sprite_));
      }
    }
  }
  
  player.draw(window);

  sf::FloatRect player_box = player.bounding_box();

  //Draw Resources in view
  for(int j = begin_j; j < end_j; ++j) {
    for(int i = begin_i; i < end_i; ++i) {
      if(in_cave) {
        if(cave_resource_map_[i][j]) { // ignores nullptr
          if(cave_resource_map_[i][j]->is_overlapped(player_box)) { // make transparent
            cave_resource_map_[i][j]->transparent_draw(window);
          } else {
            cave_resource_map_[i][j]->draw(window);
          }
        }
      } else {
        if(resource_map_[i][j]) { // ignores nullptr
          if(resource_map_[i][j]->is_overlapped(player_box)) { // make transparent
            resource_map_[i][j]->transparent_draw(window);
          } else {
            resource_map_[i][j]->draw(window);
          }
        }
      }
    }
  }

}

bool collision(const Player& player) { 
	// TO DO ?
  return false;
  //run through resources close to player and return true if any resource returns true 
  //  on a call to Resource.collision(player)

}
