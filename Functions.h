#ifndef __FUNCTIONS_H_INCLUDED__
#define __FUNCTIONS_H_INCLUDED__

#include <cmath>

static const double PI = 3.14159265;

template <typename T1, typename T2>
decltype(auto) max(T1 a, T2 b) {
  return (a < b ? b : a);
}

template <typename T1, typename T2>
decltype(auto) min(T1 a, T2 b) {
  return (a > b ? b : a);
}

// TO DO : Think about access to sfml class
// Return angle in degrees, in clockwise order
double angle2f(const sf::Vector2f& vec) {
  if(vec.x == 0) {
    return vec.y < 0 ? 90 : 270; 
  } else {
    return vec.x < 0 ? -1 * atan(vec.y / vec.x) * 180 / PI : 
                       (-1 * atan(vec.y / vec.y) * 180 / PI) + 180; 
  } 
}

#endif
