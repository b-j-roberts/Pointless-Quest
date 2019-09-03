#include "World.h"

// TO DO : THIS IS TEMP
Biome Top_Biome = Magic;
Biome Mid_Biome = Forest;
Biome Bot_Biome = Desert;
Biome Liq_Biome = Ocean;


int get_Min_Power(int num, int mult) {
  int ret = mult;
  while(ret < num) {
    ret *= mult;
  }
  return ret;
}

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

template <typename T>
T max_2D(std::vector<std::vector<T>> vec) {
  
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

std::vector<std::vector<double>> normalize_2D (std::vector<std::vector<double>> vec) {
  
  double max = max_2D(vec);
  size_t w = vec.size();
  for(int i = 0; i < w; ++i) {
    size_t h = vec[i].size();
    for(int j = 0; j < h; ++j) {
      vec[i][j] /= max;
    }
  }

  return vec;

}

std::vector<std::vector<Biome>> get_Biomes(size_t width, size_t height) {

  std::vector<std::vector<double>> tile_heights = normalize_2D(get_Perlin_2D(width, height));
  // TO DO : Include average about function to 'smooth out' tile_heights

  double top_cutoff = .80;
  double mid_cutoff = .40;
  double bottom_cutoff = .15;

  std::vector<std::vector<Biome>> ret;
  for(size_t i = 0; i < width; ++i) {
    std::vector<Biome> temp;
    for(size_t j = 0; j < height; ++j) { // TO DO: Create a way to define these biome types
      if(tile_heights[i][j] > top_cutoff) temp.push_back(Top_Biome);
      else if(tile_heights[i][j] > mid_cutoff) temp.push_back(Mid_Biome);
      else if(tile_heights[i][j] > bottom_cutoff) temp.push_back(Bot_Biome);
      else temp.push_back(Liq_Biome);
    }
    ret.push_back(temp);
  }

  return ret;

}

void World::generate(size_t width, size_t height, const std::vector<std::shared_ptr<Sprite_Obj>> tile_vec) {

  std::vector<std::vector<Biome>> biomes = get_Biomes(width, height);
  size_t h = biomes.size();
  tile_map_.resize(h);
  for(size_t i = 0; i < h; ++i) {
    size_t w = biomes[i].size();
    std::vector<std::shared_ptr<Tile>> temp;
    for(size_t j = 0; j < w; ++j) {
      temp.emplace_back(std::make_shared<Tile>(biomes[i][j], tile_vec[biomes[i][j]]));
    }
    tile_map_[i].swap(temp); 
  }

  // TO DO : 
  // Resources ? 
  // Other ?

}

// TO DO : Move this to an include function file somewhere in the future
template <typename T1, typename T2>
decltype(auto) max(T1 a, T2 b) {
  return (a < b ? b : a);
}

void World::draw(sf::RenderWindow& window, const Player& player) {

  auto size = player.get_View().getSize();
  auto center = player.get_View().getCenter();

  for(int i = max(0, center.x - (size.x / 2) - 320) / 32, end_i = max(0, center.x + (size.x / 2) + 320) / 32; i < end_i; ++i) {// TO DO : Catch min for right and bottom
    for(int j = max(0, center.y - (size.y / 2) - 320) / 32, end_j = max(0, center.y + (size.y / 2) + 320) / 32; j < end_j; ++j) { 
      tile_map_[i][j]->sprite_->setPosition(i * 32, j * 32);
      window.draw(*(tile_map_[i][j]->sprite_));
    }
  }
  
  player.draw(window);

  //Draw Resources in view

}

bool collision(const Player& player) { 
	// TO DO
  return false;
  //run through resources close to player and return true if any resource returns true on a call to Resource.collision(player)

}
