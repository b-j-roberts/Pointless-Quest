#include <SFML/Graphics.hpp>

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>

struct point_3D {

  double x, y, z;

  point_3D(double x_, double y_, double z_): x(x_), y(-1 * y_), z(z_) { }

};

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

int main() {
/*
  sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
  sf::RenderWindow window(desktop, "Perlin Analysis");
  window.setFramerateLimit(30);
*/
  srand(time(NULL));

  int width = 2048;
  int height = 2048;

//  sf::Event event;

  std::vector<double> zeros(width, 0);
  std::vector<std::vector<double>> perlin_avg(height, zeros);


  for(int i = 0; i < 5000; ++i) {
    std::cout << i << std::endl;    
    std::vector<std::vector<double>> perlin = sudo_perlin_2D(width, height);
    normalize_2D(perlin);
    for(int j = 0; j < width; ++j) {
      for(int k = 0; k < height; ++k) {
        perlin_avg[j][k] += perlin[j][k]; 
      }
    }
  }

  for(int j = 0; j < width; ++j) {
    for(int k = 0; k < height; ++k) {
      perlin_avg[j][k] /= 5000;
      std::cout << perlin_avg[j][k] << std::endl;
    }
  }

//  bool new_map = true;

/*  while(window.isOpen()) {
    while(window.pollEvent(event)) {
      switch(event.type) {

        case sf::Event::KeyPressed:
          if(event.key.code == sf::Keyboard::Space) {
            new_map = true;
          }
          break;

        case sf::Event::Closed:
          window.close();
          break;

        default: break;
      }
    }

    if(new_map) {
      perlin = sudo_perlin_2D(width, height);
      normalize_2D(perlin);
      new_map = false;
    }

    window.clear();
    
    sf::RectangleShape pixel;
    pixel.setSize(sf::Vector2f(1, 1));
    for(int i = 0; i < perlin.size(); ++i) {
      for(int j = 0; j < perlin[i].size(); ++j) {
        pixel.setPosition(sf::Vector2f(i, j));
        pixel.setFillColor(sf::Color(0, 0, 255 * perlin[i][j]));
        window.draw(pixel);
      }
    } 
    
    window.display();

  }
*/

  

  return 0;

}
