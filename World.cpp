#include "World.h"

//static members
constexpr Biome_enum World::biomes_[4];

int get_Min_Power(int num, int mult) {
  int ret = mult;
  while(ret < num) {
    ret *= mult;
  }
  return ret;
}

/*
double inter_Point_Triangle_TL(double height_one, double height_two, double height_three, int pos_x, int pos_y, int leg_length) {
  return height_one + ((height_two - height_one) / leg_length) * pos_x + ((height_three - height_one) / leg_length) * pos_y;
}

double inter_Point_Triangle_BR(double height_one, double height_two, double height_three, int pos_x, int pos_y, int leg_length) {
  return height_three + height_two - height_one + ((height_one - height_two) / leg_length) * pos_x + ((height_one - height_three) / leg_length) * pos_y;
}

std::vector<std::vector<double>> get_Perlin_2D (size_t width, size_t height) {

  size_t maximum = (width < height ? height : width);
  int two_mult = get_Min_Power(maximum, 2);

  std::vector<std::vector<double>> rand_noise(two_mult);
  for(size_t i = 0; i < two_mult; ++i) {
    std::vector<double> rand_row(two_mult);
    for(size_t j = 0; j < two_mult; ++j) {
      rand_row[j] = static_cast<double>(rand() % 100);
    }
    rand_noise[i].swap(rand_row);
  }

  std::vector<double> zero_vec(two_mult, 0);
  std::vector<std::vector<double>> perlin(two_mult, zero_vec);

  
  for(int i = 2; i <= two_mult; i*=2) {
    int sub_div = two_mult / i;
    for(int j = 0; j < two_mult; j += sub_div) {
      for(int k = 0; k < two_mult; k += sub_div) {
        perlin[j][k] += (1.f / i) * rand_noise[j][k];
      	for(int l = k - sub_div; l < k && k > 0 && j > 0; l++) {
          for(int m = j - sub_div; m < j; m++) {
            int current_x = m - j + sub_div;
	          int current_y = l - k - sub_div;
	          if(current_x <= sub_div - current_y) perlin[m][l] += inter_Point_Triangle_TL(rand_noise[j - sub_div][k - sub_div], rand_noise[j - sub_div][k],
			                                                                                   rand_noise[j][k - sub_div], current_x, current_y, sub_div);
	          else perlin[m][l] += inter_Point_Triangle_BR(rand_noise[j][k], rand_noise[j][k - sub_div], rand_noise[j - sub_div][k], current_x, current_y, sub_div);
	        }
       	}
      }
    } 
  } 

  return perlin;
}
*/

struct point_3D {

  double x, y, z;

  point_3D(double x_, double y_, double z_): x(x_), y(-1 * y_), z(z_) { }

};

double line_calc(size_t pos, double start, double end, double height_1, double height_2) {

  double m = (height_2 - height_1) / (end - start);
  return m * ( pos - end ) + height_1;
}

double height_calc(size_t x, size_t y, const point_3D& corner_1, const point_3D& corner_2, const point_3D& center) {

  double a = (corner_1.y - center.y) * (corner_2.z - center.z) - (corner_2.y - center.y) * (corner_1.z - center.z);
  double b = (corner_1.z - center.z) * (corner_2.x - center.x) - (corner_2.z - center.z) * (corner_1.x - center.x);
  double c = (corner_1.x - center.x) * (corner_2.y - center.y) - (corner_2.x - center.x) * (corner_1.y - center.y);
  double d = -1 * (a * center.x + b * center.y + c * center.z);

  return -1 * (a * (double)x - b * (double)y + d) / c;
}

bool is_under(size_t x, size_t y, const point_3D& bl) {

  return (-1 * (double)y) < ((double)x + bl.y - bl.x);
}

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

// TO DO : Move this to an include function file somewhere in the future
template <typename T1, typename T2>
decltype(auto) max(T1 a, T2 b) {
  return (a < b ? b : a);
}

template <typename T1, typename T2>
decltype(auto) min(T1 a, T2 b) {
  return (a > b ? b : a);
}

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

};

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

};

std::vector<std::vector<Biome_enum>> World::get_Biomes(size_t width, size_t height) {

  std::vector<std::vector<double>> tile_heights = sudo_perlin_2D(width, height);
  normalize_2D(tile_heights);
  //smooth_2D(tile_heights, 3); TO DO : Super slow rn

  double top_cutoff = .80;
  double mid_cutoff = .40;
  double bottom_cutoff = .15;

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

  return ret;

}

std::vector<std::vector<state>> get_States(size_t width, size_t height, double top_cutoff, double bot_cutoff) {

  std::vector<std::vector<double>> tile_heights = sudo_perlin_2D(width, height);
  normalize_2D(tile_heights);

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

void World::generate(size_t width, size_t height, const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec) {

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

  size_t h = biomes_map.size();
  tile_map_.resize(h);
  for(size_t i = 0; i < h; ++i) {
    size_t w = biomes_map[i].size();
    std::vector<std::shared_ptr<Tile>> temp;
    for(size_t j = 0; j < w; ++j) {
      temp.emplace_back(std::make_shared<Tile>(biomes_map[i][j], tile_vec[biomes_map[i][j]]));
    }
    tile_map_[i].swap(temp); 
  }

  // TO DO : 
  // Resources ? 
  // Other ?

  resource_map_.resize(h);
  for(int i = 0; i < h; ++i) {
    resource_map_[i].resize(biomes_map[i].size());
  }

  size_t pos = 0; 
  biomes[0]->get_Resources(all_perlin, pos, biomes_map, resource_map_);
  pos += biomes[0]->perlins_needed();
  biomes[1]->get_Resources(all_perlin, pos, biomes_map, resource_map_);
  pos += biomes[1]->perlins_needed();
  biomes[2]->get_Resources(all_perlin, pos, biomes_map, resource_map_);
  pos += biomes[2]->perlins_needed();
  biomes[3]->get_Resources(all_perlin, pos, biomes_map, resource_map_);

}

void World::draw(sf::RenderWindow& window, const Player& player) {

  auto size = player.get_View().getSize();
  auto center = player.get_View().getCenter();

  int world_size_i = tile_map_.size();
  int world_size_j = tile_map_[0].size();

  int begin_i = max(0, center.x - (size.x / 2) - 64) / 32;
  int end_i = min(max(0, (center.x + (size.x / 2) + 64) / 32), world_size_i);

  int begin_j = max(0, center.y - (size.y / 2) - 64) / 32;
  int end_j = min(max(0, (center.y + (size.y / 2) + 64) / 32), world_size_j);

  // Draw Tiles in view
  for(int i = begin_i; i < end_i; ++i) {
    for(int j = begin_j; j < end_j; ++j) { 
      tile_map_[i][j]->sprite_->setPosition(i * 32, j * 32);
      window.draw(*(tile_map_[i][j]->sprite_));
    }
  }
  
  player.draw(window);

  //Draw Resources in view
  for(int i = begin_i; i < end_i; ++i) {
    for(int j = begin_j; j < end_j; ++j) {                                                                                       
      resource_map_[i][j]->draw(window);
    }
  }

}

bool collision(const Player& player) { 
	// TO DO
  return false;
  //run through resources close to player and return true if any resource returns true on a call to Resource.collision(player)

}
