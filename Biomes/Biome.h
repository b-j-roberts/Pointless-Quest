#ifndef __BIOME_H_INCLUDED__
#define __BIOME_H_INCLUDED__

enum state { Top, Middle, Bottom };

enum Biome_enum {  Forest_ = 0, Desert_ = 1, Magic_ = 2, Ocean_ = 3, 
                   Swamp_ = 4, Unocean_ = 5, Cave_ = 6};

struct Tile { // Layer 0 Resource

  const Biome_enum biome_;

  const size_t tile_id_; // TO DO : Currently dont need, maybe use for rotatable tiles later
  const bool is_water_;

  std::shared_ptr<sf::Sprite> sprite_;

  Tile(Biome_enum biome, std::shared_ptr<Sprite_Obj> sprite_obj, bool is_water = false):
    biome_(biome),
    tile_id_(rand() % sprite_obj->size()),
    is_water_(is_water),
    sprite_(sprite_obj->get_Ptr(tile_id_)) { }

  Tile(Biome_enum biome, size_t tile_id, 
       std::shared_ptr<Sprite_Obj> sprite_obj, bool is_water = false):
    biome_(biome),
    tile_id_(tile_id),
    is_water_(is_water),
    sprite_(sprite_obj->get_Ptr(tile_id)) { }

};

class Biome {

public:

  Biome() { }

  virtual const size_t perlins_needed() { return 0; }
  virtual void get_Resources(const std::vector<std::vector<std::vector<state>>>&, size_t,
                             const std::vector<std::vector<Biome_enum>>&,
                             const std::vector<std::shared_ptr<Sprite_Obj>>&,
                             std::vector<std::vector<std::shared_ptr<Tile>>>&,
                             const std::vector<std::vector<state>>&,
                             std::vector<std::vector<std::shared_ptr<Resource>>>&) { }

};

#endif
