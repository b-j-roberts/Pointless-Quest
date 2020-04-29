#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// TO DO : Learn make files so I can move all unneccesary header librarys into .cpp files
#include <cmath> // atan & sqrt ( in other translation units ) // TO DO
#include <vector>
#include <cstdlib> // size_t & rand

#include <SFML/Graphics.hpp> // sf::Vector2f & Graphics ( in other translation units )

/*
 * Utility Functions
 */

// max & min template functions
template <typename T1, typename T2>
decltype(auto) max(T1 a, T2 b) {
  return (a < b ? b : a);
}
template <typename T1, typename T2>
decltype(auto) min(T1 a, T2 b) {
  return (a > b ? b : a);
}

// Returns the minimum power of mult greater than num
int get_Min_Power(int num, int mult);

// Returns double angle (clockwise) created by Vector2f passed in
double angle2f(const sf::Vector2f& vec);


/*
 * Enums
 */

// Enum used to split areas into different categories , used in perlin & resources for density areas
enum state { Top, Middle, Bottom };


/*
 * Perlin Related Functions
 */

// TO DO : Must be a power of 2 as of now
// Return a perlin-ish 2D vector with width & height as specified
std::vector<std::vector<double>> sudo_perlin_2D(int width, int height);

// Linearly scale 2D vector, such that max value is 1
void normalize_2D(std::vector<std::vector<double>>& vec);
// Adds random noise to all elements in vec ranging from [-factor/scale , factor/scale]
void add_noise(std::vector<std::vector<double>>& vec, int factor, int scale);
// Creates a normalized perlin with states, how many of each state determined by cut percents
std::vector<std::vector<state>> get_States(size_t width, size_t height,
                                           double top_percent_cut, double bot_percent_cut);


/*
 * Bounded Region Related Functions
 */

// Create a 2D bounded region (true for inside region) with minimaly low_bound elements
// NOTE : No elements of bounded region are on an edge ( to prevent indexing errors )
std::vector<std::vector<bool>> get_Bounded_Region(size_t width, size_t height, size_t low_bound);

// Removes all single wide shoots off of a bounded region
void smooth_Bounded_Edges(std::vector<std::vector<bool>>& vec);
// Returns true if indexed element is an edge of bounded region
bool is_Bounded_Edge(const std::vector<std::vector<bool>>& vec, size_t i, size_t j);

#endif
