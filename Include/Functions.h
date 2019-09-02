#ifndef __FUNCTIONS_H_INCLUDED__
#define __FUNCTIONS_H_INCLUDED__

#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

float length(sf::Vector2f vec);
float angleBetween(sf::Vector2f vec1, sf::Vector2f vec2);
float dotProd(sf::Vector2f vec1, sf::Vector2f vec2);
float angle2f(sf::Vector2f vec);
float sq(float num);
sf::Vector2f getConnector(std::string currentLine);
std::vector<std::vector<float>> perlin2D(int size);
float interPointLine(float heightI, float heighF, int pos, int length);
float interPointTriangleTL(float heightOne, float heightTwo, float heightThree, sf::Vector2u pos, int legLength);
float interPointTriangleBR(float heightOne, float heightTwo, float heightThree, sf::Vector2u pos, int legLength);
float averageAbout(int row, int column, std::vector<std::vector<float>> &arr, int radius);
int max(int a, int b);
float percentBound(float percent, std::vector<std::vector<float>> &arr);
int min(int a, int b);

#endif