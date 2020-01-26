#include <iostream> // TO DO : Change to logger

#include "Resources.h"

#include <algorithm> // transform
#include <iterator> // back_inserter

Texture_Obj::Texture_Obj(const size_t height, const size_t width, const size_t num, std::string s, 
            		         const size_t height_offset, const size_t width_offset):
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

Sprite_Obj::Sprite_Obj(const Texture_Obj& t_obj, const size_t orig_x, const size_t orig_y, 
                       const double scale_x, const double scale_y) {
  std::transform(t_obj.t_.begin(), t_obj.t_.end(), std::back_inserter(s_), [&](const auto& txtr){
    std::shared_ptr<sf::Sprite> ret = std::make_shared<sf::Sprite>(txtr);
    ret->setOrigin(orig_x, orig_y);
    ret->scale(scale_x, scale_y);
    return ret;
  });
}

std::shared_ptr<sf::Sprite> Sprite_Obj::get_Ptr(const size_t i) const {
  if(i < s_.size())  return s_[i];
  else if(s_.size() != 0)  return s_[0];
  else { // TO DO : runtime_error
    std::cout << "IndexError: in get_Ptr(const int): index " << i 
              << " beyond size " << s_.size() << std::endl;
  }
}
