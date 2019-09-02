#include "Resources.h"

Texture_Obj::Texture_Obj(const size_t height, const size_t width, const size_t num, std::string s, 
		         const size_t height_offset, const size_t width_offset):
  height_(height),
  width_(width),
  num_(num)
{
  std::vector<sf::Texture> temp_t(num);
  std::string file_path("Resources/" + s + ".png");
  for(size_t i = 0; i < num; i++) {
    if(!temp_t[i].loadFromFile(file_path,sf::IntRect(width * i + width_offset, height_offset, width, height)))
      std::cout << "Error loading " << file_path << " resource in position " << i << std::endl;
  }
  t_.swap(temp_t);
}



Sprite_Obj::Sprite_Obj(const size_t orig_x, const size_t orig_y, const double scale_x, const double scale_y, const Texture_Obj& t_obj) {
  std::vector<std::shared_ptr<sf::Sprite>> temp_s(t_obj.num_);
  for(int i = 0; i < t_obj.num_; i++) {
    temp_s[i] = std::make_shared<sf::Sprite>(t_obj.t_[i]);
    temp_s[i]->setOrigin(orig_x,orig_y);
    temp_s[i]->scale(scale_x, scale_y);
  }
  s_.swap(temp_s);
}

Sprite_Obj::Sprite_Obj(const Texture_Obj& t_obj) {
  std::vector<std::shared_ptr<sf::Sprite>> temp_s(t_obj.num_);
  for(int i = 0; i < t_obj.num_; i++) {
    temp_s[i] = std::make_shared<sf::Sprite>(t_obj.t_[i]);
    temp_s[i]->setOrigin(0,0);
  }
  s_.swap(temp_s);
}

std::shared_ptr<sf::Sprite> Sprite_Obj::get_Ptr(const int i) {
  if(i < s_.size())  return s_[i];
  else if(s_.size() != 0)  return s_[0];
  else {
    std::cout << "IndexError: in get_Ptr(const int): index " << i << " beyond size " << size() << std::endl;
  }
}
