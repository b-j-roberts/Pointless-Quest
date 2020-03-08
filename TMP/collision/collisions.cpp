#include <SFML/Graphics.hpp>

#include <cmath> // sin, cos, sqrt
#include <algorithm> // min, max
#include <cfloat> // FLT_MIN, FLT_MAX

#include <memory> // TO DO
#include <iostream>

const float PI = 3.14159;

class Collidable {

protected:

  sf::ConvexShape shape_;

public:

  Collidable(size_t resolution): shape_(resolution) { }

  void move(const sf::Vector2f& move_vec) { shape_.move(move_vec); }

  size_t resolution() const { return shape_.getPointCount(); }
  const sf::Vector2f& origin() const { return shape_.getPosition(); }
  sf::Vector2f get_vertex(size_t idx) const { return shape_.getPoint(idx) + shape_.getPosition(); }

  // TO DO : DEBUG
  void draw(sf::RenderWindow& window) { window.draw(shape_); }
  void setColor(sf::Color c) { shape_.setFillColor(c); }
};

float dot(const sf::Vector2f& v_1, const sf::Vector2f& v_2) { return v_1.x * v_2.x + v_1.y * v_2.y; }

// Helper : Separated Axis Theorem
bool is_Collision_Half(const Collidable& c_1, const Collidable& c_2) {
  for(int i = 0; i < c_1.resolution(); ++i) {
    int next = (i + 1) % c_1.resolution();
    sf::Vector2f normal = sf::Vector2f( c_1.get_vertex(i).y - c_1.get_vertex(next).y,
                                        c_1.get_vertex(next).x - c_1.get_vertex(i).x);
    // Get minimum and maximum projection values for c_1
    float min_c_1 = FLT_MAX, max_c_1 = FLT_MIN; 
    for(int j = 0; j < c_1.resolution(); ++j) {
      float projection = dot(c_1.get_vertex(j), normal);
      min_c_1 = std::min(projection, min_c_1);
      max_c_1 = std::max(projection, max_c_1);
    }
    // Get minimum and maximum projection values for c_2
    float min_c_2 = FLT_MAX, max_c_2 = FLT_MIN;
    for(int j = 0; j < c_2.resolution(); ++j) {
      float projection = dot(c_2.get_vertex(j), normal);
      min_c_2 = std::min(projection, min_c_2);
      max_c_2 = std::max(projection, max_c_2);
    }
    // If they dont overlap => no collision
    if(!(min_c_1 <= max_c_2 && max_c_1 >= min_c_2)) return false;
  }
  return true;
}

float res_Collision_Half(const Collidable& c_1, const Collidable& c_2) {
  float displace = FLT_MAX;
  for(int i = 0; i < c_1.resolution(); ++i) {
    int next = (i + 1) % c_1.resolution();
    sf::Vector2f normal = sf::Vector2f( c_1.get_vertex(i).y - c_1.get_vertex(next).y,
                                        c_1.get_vertex(next).x - c_1.get_vertex(i).x);

    float normalize = sqrt(dot(normal, normal));
    normal /= normalize;

    // Get minimum and maximum projection values for c_1
    float min_c_1 = FLT_MAX, max_c_1 = FLT_MIN; 
    for(int j = 0; j < c_1.resolution(); ++j) {
      float projection = dot(c_1.get_vertex(j), normal);
      min_c_1 = std::min(projection, min_c_1);
      max_c_1 = std::max(projection, max_c_1);
    }
    // Get minimum and maximum projection values for c_2
    float min_c_2 = FLT_MAX, max_c_2 = FLT_MIN;
    for(int j = 0; j < c_2.resolution(); ++j) {
      float projection = dot(c_2.get_vertex(j), normal);
      min_c_2 = std::min(projection, min_c_2);
      max_c_2 = std::max(projection, max_c_2);
    }
    // We want to find minimum displacement to move out
    displace = std::min(std::min(max_c_1, max_c_2) - std::max(min_c_1, min_c_2), displace);
    
    // If they dont overlap => no collision
    if(!(min_c_1 <= max_c_2 && max_c_1 >= min_c_2)) return 0.f;
  }
  return displace;
}

void res_Collision(Collidable& c_1, const Collidable& c_2) {
  float displacement = res_Collision_Half(c_1, c_2);
  if(displacement != 0.f) {
    displacement = std::min(displacement, res_Collision_Half(c_2, c_1));
    sf::Vector2f dist(c_2.origin().x - c_1.origin().x, c_2.origin().y - c_1.origin().y);
    float scale = -1 * sqrt(dist.x*dist.x + dist.y*dist.y);
    c_1.move(dist * (displacement / scale));
  }
}

// REFERENCE : OLC Convex Polygon Collisions
// Detects if there is a collision between 2 collidables ( using Separated Axis Theorem )
bool is_Collision(const Collidable& c_1, const Collidable& c_2) {
  return is_Collision_Half(c_1, c_2) && is_Collision_Half(c_2, c_1);
}


bool is_Collision_Half_2(const Collidable& c_1, const Collidable& c_2) {
  // Diagonals in c_1 intersect edges in c_2 ?
  for(int i = 0; i < c_1.resolution(); ++i) {
    sf::Vector2f c_1_i = c_1.get_vertex(i); 
    for(int j = 0; j < c_2.resolution(); ++j) {
       sf::Vector2f c_2_j = c_2.get_vertex(j);
       sf::Vector2f c_2_next = c_2.get_vertex((j + 1) % c_2.resolution());
       // Get desired line intersection values ( scale to be 0 - 1 )
       float scale = (c_2_next.x - c_2_j.x) * (c_1.origin().y - c_1_i.y) -
                     (c_1.origin().x - c_1_i.x) * (c_2_next.y - c_2_j.y);
       float intersect_1 = ((c_2_j.y - c_2_next.y) * (c_1.origin().x - c_2_j.x) +
                            (c_2_next.x - c_2_j.x) * (c_1.origin().y - c_2_j.y)) / scale;
       float intersect_2 = ((c_1.origin().y - c_1_i.y) * (c_1.origin().x - c_2_j.x) +
                            (c_1_i.x - c_1.origin().x) * (c_1.origin().y - c_2_j.y)) / scale;
       if(intersect_1 >= 0.f && intersect_1 < 1.f && intersect_2 >= 0.f && intersect_2 < 1.f) {
         return true;
       }
    }
  }
  return false;
}

sf::Vector2f res_Collision_Half_2(const Collidable& c_1, const Collidable& c_2) {
  // Diagonals in c_1 intersect edges in c_2 ?
  sf::Vector2f displace(0,0);
  for(int i = 0; i < c_1.resolution(); ++i) {
    sf::Vector2f c_1_i = c_1.get_vertex(i);
    for(int j = 0; j < c_2.resolution(); ++j) {
       sf::Vector2f c_2_j = c_2.get_vertex(j);
       sf::Vector2f c_2_next = c_2.get_vertex((j + 1) % c_2.resolution());
       // Get desired line intersection values ( scale to be 0 - 1 )
       float scale = (c_2_next.x - c_2_j.x) * (c_1.origin().y - c_1_i.y) -
                     (c_1.origin().x - c_1_i.x) * (c_2_next.y - c_2_j.y);
       float intersect_1 = ((c_2_j.y - c_2_next.y) * (c_1.origin().x - c_2_j.x) +
                            (c_2_next.x - c_2_j.x) * (c_1.origin().y - c_2_j.y)) / scale;
       float intersect_2 = ((c_1.origin().y - c_1_i.y) * (c_1.origin().x - c_2_j.x) +
                            (c_1_i.x - c_1.origin().x) * (c_1.origin().y - c_2_j.y)) / scale;
       if(intersect_1 >= 0.f && intersect_1 < 1.f && intersect_2 >= 0.f && intersect_2 < 1.f) {
         displace += (c_1_i - c_1.origin()) * (1.f - intersect_1); 
       }
    }
  }
  return displace;
}

void res_Collision_2(Collidable& c_1, const Collidable& c_2) {
  sf::Vector2f displacement = res_Collision_Half_2(c_2, c_1) - res_Collision_Half_2(c_1, c_2);
  c_1.move(displacement);
}

// Detexts if there is a collision between 2 collidables ( using Line Segment Collision )
bool is_Collision_2(const Collidable& c_1, const Collidable& c_2) {
  return is_Collision_Half_2(c_1, c_2) || is_Collision_Half_2(c_2, c_1);
}

class Circle : public Collidable {

public:

  // params : radius, position, # of verticies for closed Circle polygon
  Circle(float radius, const sf::Vector2f& position, size_t resolution = 10):
    Collidable(resolution) {
    shape_.setOrigin(0, 0);
    float angle_increment = PI * 2.f / resolution;
    for(float i = 0; i < resolution; ++i) {
      shape_.setPoint(i, sf::Vector2f(cos(angle_increment * i), sin(angle_increment * i)) * radius); 
    }
    shape_.move(position);

    // TO DO : Debug
    shape_.setFillColor(sf::Color::Red);
  }
};

class Rectangle : public Collidable {

public:

  Rectangle(float width, float height, const sf::Vector2f& position):
    Collidable(4) {
    shape_.setOrigin(0, 0);
    shape_.setPoint(0, sf::Vector2f(width / 2, height / 2));
    shape_.setPoint(1, sf::Vector2f(-width / 2, height / 2));
    shape_.setPoint(2, sf::Vector2f(-width / 2, -height / 2));
    shape_.setPoint(3, sf::Vector2f(width / 2, -height / 2));
    shape_.move(position);

    // TO DO : Debug
    shape_.setFillColor(sf::Color::Green);
  }
};

int main() {

  sf::RenderWindow window(sf::VideoMode(1000, 1000), "Collisions");

  window.setFramerateLimit(60);

  sf::Event event;

  std::shared_ptr<Collidable> circle_1 = std::make_shared<Circle>(10, sf::Vector2f(10, 10));
  Circle circle_2(50, sf::Vector2f(70, 70), 4);
  Rectangle rect_1(200, 100, sf::Vector2f(420, 420));

  while(window.isOpen()) {

    // Input
    while(window.pollEvent(event)) {
      switch(event.type) {

        case sf::Event::Closed:
          window.close();
          break;

        default: break;
      }
    } // end event loop
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { circle_2.move(sf::Vector2f(0, -1)); }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { circle_2.move(sf::Vector2f(-1, 0)); }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { circle_2.move(sf::Vector2f(0, 1)); }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { circle_2.move(sf::Vector2f(1, 0)); }


    // Update
  //  if(is_Collision_2(*circle_1, circle_2)) { circle_2.setColor(sf::Color::Yellow); }
  //  else { circle_2.setColor(sf::Color::Red); }
    res_Collision_2(*circle_1, circle_2);
    res_Collision_2(*circle_1, rect_1);


    // Draw
    window.clear();

    circle_1->draw(window);
    circle_2.draw(window);
    rect_1.draw(window);

    window.display();

  }

  return 0;
}
