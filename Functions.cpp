#include "Functions.h"

#include <algorithm> // sort, transform, max_element
#include <iterator> // back_inserter

#include <stdexcept> // runtime_error
#include <string> // string ( used for runtime_error )

static const double PI = 3.14159265;

int get_Min_Power(int num, int mult) {
  int ret = mult;
  while(ret < num) {
    ret *= mult;
  }
  return ret;
}

double angle2f(const sf::Vector2f& vec) {
  if(vec.x == 0) {
    return vec.y < 0 ? 90 : 270; 
  } else {
    return vec.x < 0 ? -1 * atan(vec.y / vec.x) * 180 / PI : 
                       (-1 * atan(vec.y / vec.y) * 180 / PI) + 180; 
  } 
}
/*
// helper : struct to hold 3D point with flipped y ( for logical reasons )
struct point_3D {

  double x, y, z;

  point_3D(double x_, double y_, double z_): x(x_), y(-1 * y_), z(z_) { }

};

// helper : return height of point at pos on line with points (start , height_1) & (end , height_2)
double line_calc(size_t pos, double start, double end, double height_1, double height_2) {
  double m = (height_2 - height_1) / (end - start);
  return m * ( pos - end ) + height_1;
}

// helper : returns height of point (x , y) in on plane with 3 points corner_1, _2, & center
double plane_calc(double x, double y, const point_3D& corner_1,
                   const point_3D& corner_2, const point_3D& center) {
  double a = (corner_1.y - center.y) * (corner_2.z - center.z) -
             (corner_2.y - center.y) * (corner_1.z - center.z);
  double b = (corner_1.z - center.z) * (corner_2.x - center.x) -
             (corner_2.z - center.z) * (corner_1.x - center.x);
  double c = (corner_1.x - center.x) * (corner_2.y - center.y) -
             (corner_2.x - center.x) * (corner_1.y - center.y);
  double d = -1 * (a * center.x + b * center.y + c * center.z);

  return -1 * (a * x - b * y + d) / c;
}

// helper : returns true if (x , y) in bottom right triangle of square with bottom-left point bl
// *---*
// |F /|
// | / |  : On diagonal counts as False (ie top left) 
// |/ T|
// bl--*
bool is_under(double x, double y, const point_3D& bl) {
  return (-1 * y) < (x + bl.y - bl.x);
}

// TO DO : Test & possibly replace this not so great perlin generator
std::vector<std::vector<double>> old_perlin_2D(size_t width, size_t height) {

  std::vector<double> empty_vec(width, 0);
  std::vector<std::vector<double>> ret(height, empty_vec);

  double factor = 4;

  while(factor < width / 4) {
    double scale = 1 / factor;
    double shift_x = width * scale;
    double shift_y = height * scale;
    std::vector<std::vector<double>> curr(height + 1, empty_vec);
    // set corners of boxes to random #
    for(int i = 0; i < width; i += shift_x) {
      for(int j = 0; j < height; j += shift_y) {
        curr[j][i] = (double)(rand() % 100);
      }
    }
    // use plane to find all other value other than bottom and right edges
    for(int i = 0; i < width; i += shift_x) {
      for(int j = 0; j < height; j += shift_y) {
        point_3D TL(i, j, curr[j][i]);
        point_3D TR(i + shift_x, j, curr[j][i + shift_x]);
        point_3D BL(i, j + shift_y, curr[j + shift_y][i]);
        point_3D BR(i + shift_x, j  + shift_y, curr[j + shift_y][i + shift_x]);
        for(int k = i; k < i + shift_x; ++k) {
          for(int m = j; m < j + shift_y; ++m) {
            curr[k][m] = plane_calc(k, m, TR, BL, (is_under(k, m, BL) ? BR : TL)); // TO DO
          }
        }
      }
    }
    // Bottom edge
    for(int i = 0; i < width; i += shift_x) {
      for(int j = i; j < i + shift_x; ++j) {
        curr[height][j] = line_calc(j, i, i + shift_x, 
                                    curr[height][i], curr[height][i + shift_x]);
      }
    }
    // Right edge
    for(int i = 0; i < height; i += shift_y) {
      for(int j = i; j < i + shift_y; ++j) {
        curr[j][width] = line_calc(j, i, i + shift_y,// TO DO 
                                   curr[i][width - 1], curr[i + shift_y][width]);
      }
    }
    // Multiply by scale and add to ret
    for(int i = 0; i < width; ++i) {
      for(int j = 0; j < height; ++j) {
        ret[j][i] += curr[j][i] * scale;
      }
    }

    factor *= 2;
  }

  return ret;

}*/

std::vector<std::vector<double>> sudo_perlin_2D(int width, int height) {

  // TO DO : Test this with viewer
  // Note : Requires square & power of 2?

  std::vector<std::vector<double>> ret(height, std::vector<double>(width, 0));
  
  // Create random seed 2d vector
  // TO DO : Transform?
  std::vector<std::vector<double>> seed(height, std::vector<double>(width, 0.f));
  for(int i = 0; i < height; ++i) {
    for(int j = 0; j < width; ++j) {
      seed[i][j] = (rand() % 100);
    }
  }


  for(int i = 0; i < height; ++i) {
    for(int j = 0; j < width; ++j) {
      float scale = 1.f;
      int pitch = width;
      while(pitch > 0) { // TO DO : Change this min to some variable for biasing
        // Take advantage of int rounding to get boundary values for interpolation
        int x_1 = (j / pitch) * pitch;
        int y_1 = (i / pitch) * pitch;
        int x_2 = (x_1 + pitch) % width; // wrapping
        int y_2 = (y_1 + pitch) % height;
        // Get relative position in each coordinate of current point
        float curr_x = (float)(j - x_1) / (float)pitch;
        float curr_y = (float)(i - y_1) / (float)pitch;
        // Interpolate 'top' and 'bottom' x values for y interpolation
        float x_top = (1.f - curr_x) * seed[y_1][x_1] + curr_x * seed[y_1][x_2];
        float x_bot = (1.f - curr_x) * seed[y_2][x_1] + curr_x * seed[y_2][x_2];
        // Increase return by scaled Interpolated y value
        ret[i][j] += (curr_y * (x_bot - x_top) +  x_top) * scale;
        // TO DO : Scale accumulator for making max val 1?
        scale /= 2; // TO DO : Change this to some bias variable
        pitch /= 2;
      }
    }
  }

  return ret;

}

// helper : return max value in 2D vector
template <typename T>
T max_2D(const std::vector<std::vector<T>>& vec) {
  T max(0);
  for(const auto& v : vec) {
    auto v_max = std::max_element(v.begin(), v.end());
    if(*v_max > max) max = *v_max;
  }
  return max;
}

void normalize_2D(std::vector<std::vector<double>>& vec) {
  double max = max_2D(vec);
  for(auto& v : vec) {
    std::transform(v.begin(), v.end(), v.begin(), [max](auto val){ return val / max; });
  }
}

void add_noise(std::vector<std::vector<double>>& vec, int factor, int scale) {
  int rand_mod = 2 * factor + 1;
  for(auto& v : vec) {
    std::transform(v.begin(), v.end(), v.begin(), [&](auto val){ 
        return val + ((float)(rand() % rand_mod) - factor) / scale; 
    });
  }
}

std::vector<std::vector<state>> get_States(size_t width, size_t height,
                                           double top_percent_cut, double bot_percent_cut) {

  // Create Normalized 2D perlin
  auto tile_heights = sudo_perlin_2D(width, height);
  normalize_2D(tile_heights);

  // Get cutoff values by flattening, sorting, and indexing percent cuts
  std::vector<double> all_heights;
  for(const auto& v : tile_heights) {
    all_heights.insert(all_heights.end(), v.begin(), v.end());
  }
  std::sort(all_heights.begin(), all_heights.end());
  double top_cutoff = all_heights[width * height * top_percent_cut];
  double bot_cutoff = all_heights[width * height * bot_percent_cut];

  // Create return vector from tile_heights, states based on cutoff values
  std::vector<std::vector<state>> ret(height);
  int top_count = 0;
  int mid_count = 0;
  int bot_count = 0;
  for(size_t i = 0; i < height; ++i) {
    std::transform(tile_heights[i].begin(), tile_heights[i].end(), std::back_inserter(ret[i]),
        [&](auto val){
          if(val > top_cutoff) { ++top_count; return Top; }
          else if(val > bot_cutoff) { ++mid_count; return Middle; }
          else { ++bot_count; return Bottom; }
        });
  }

  return ret;
}

std::vector<std::vector<bool>> get_Bounded_Region(size_t width, size_t height, size_t low_bound) {

  // Check if low_bound achievable
  if(low_bound > width * height) {
    throw std::runtime_error("In get_Bounded_Region : cannot bound " + 
                             std::to_string(low_bound) + " within vec : ( width : " + 
                             std::to_string(width) + ", height : " + 
                             std::to_string(height) + " )");
  }

  // Initialize vector
  std::vector<bool> false_vec(width, false);
  std::vector<std::vector<bool>> ret(height, false_vec);

  // Pick random starting point
  int x = rand() % (width - 2) + 1; // NOTE : this prevents corners ( see below note )
  int y = rand() % (height - 2) + 1;

  ret[y][x] = true;

  size_t bounded_count = 1;

  // Note : min 1 & max -2 because we dont want to have to check for indexing errors
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

// helper : returns true if there is only one true element adjacent to vec[i][j]
bool one_adjacent(const std::vector<std::vector<bool>>& vec, int i, int j) {
  int count = 0;
  if(vec[i-1][j]) ++count;
  if(vec[i+1][j]) ++count;
  if(vec[i][j-1]) ++count;
  if(vec[i][j+1]) ++count;
  return count < 2;
}

void smooth_Bounded_Edges(std::vector<std::vector<bool>>& vec) {
  // Comes at shoots on all 4 angles so that no matter which way they face they will be removed
  for(int i = 1; i < vec.size() - 1; ++i) {
    for(int j = 1; j < vec[i].size() - 1; ++j) {
      if(vec[i][j] && one_adjacent(vec, i, j)) vec[i][j] = false; 
    }
  }
  for(int i = vec.size(); i > 0; --i) {
    for(int j = vec[i].size(); j > 0; --j) {
      if(vec[i][j] && one_adjacent(vec, i, j)) vec[i][j] = false; 
    }
  }
  for(int i = 1; i < vec[0].size() - 1; ++i) {
    for(int j = 1; j < vec.size() - 1; ++j) {
      if(vec[j][i] && one_adjacent(vec, j, i)) vec[j][i] = false; 
    }
  }
  for(int i = vec[0].size() - 1; i > 0; --i) {
    for(int j = vec.size() - 1; j > 0; --j) {
      if(vec[j][i] && one_adjacent(vec, j, i)) vec[j][i] = false; 
    }
  }
}

bool is_Bounded_Edge(const std::vector<std::vector<bool>>& vec, size_t i, size_t j) {
  if(!vec[i-1][j] || !vec[i][j-1] || !vec[i+1][j] || !vec[i][j+1]) return true;
  else return false;
}

