#include <iostream> // TO DO : Change to logger

#include "Resources.h"

#include <algorithm> // transform
#include <iterator> // back_inserter

Texture_Obj::Texture_Obj(size_t height, size_t width, size_t num, std::string s, 
            		         size_t height_offset, size_t width_offset):
  height_(height),
  width_(width) {
  std::vector<sf::Texture> temp_t(num);
  std::string file_path("Resources/" + s + ".png");
  for(size_t i = 0; i < num; i++) {
    if(!temp_t[i].loadFromFile(file_path,sf::IntRect(width * i + width_offset, 
                               height_offset, width, height)))
      std::cout << "Error loading " << file_path << " resource in position " << i << std::endl;
  }
  t_.swap(temp_t);
}

Sprite_Obj::Sprite_Obj(const Texture_Obj& t_obj, size_t orig_x, size_t orig_y, 
                       float scale_x, float scale_y) {
  std::transform(t_obj.t_.begin(), t_obj.t_.end(), std::back_inserter(s_), [&](const auto& txtr){
    std::shared_ptr<sf::Sprite> ret = std::make_shared<sf::Sprite>(txtr);
    ret->setOrigin(orig_x, orig_y);
    ret->scale(scale_x, scale_y);
    return ret;
  });
}

std::shared_ptr<sf::Sprite> Sprite_Obj::get_Ptr(size_t i) const {
  if(i < s_.size())  return s_[i];
  else if(s_.size() != 0)  return s_[0];
  else { // TO DO : runtime_error
    std::cout << "IndexError: in get_Ptr(const int): index " << i 
              << " beyond size " << s_.size() << std::endl;
    return s_[i % s_.size()]; // TO DO
  }
}

std::shared_ptr<sf::Sprite> Sprite_Obj::get_rand_Ptr() const { 
  return s_[static_cast<size_t>(rand()) % s_.size()]; 
}
