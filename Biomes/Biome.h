#ifndef __BIOME_H_INCLUDED__
#define __BIOME_H_INCLUDED__

#include "../Functions.h"

// level - used for perlin splitting of biomes and resource density areas
//enum state { Top, Middle, Bottom };

// enum used to map to biome & store biome info in objects
// maps to location in tile_vec (TO DO : This will change)
// TO DO : change Unocean_
enum Biome_enum {  Forest_ = 0, Desert_ = 1, Magic_ = 2, Ocean_ = 3, 
                   Swamp_ = 4, Tundra_ = 5, Unocean_ = 6, Cave_ = 7,
                   None_};

enum Plane_enum { Overworld_ = 0, Underground_ };

// Layer 0 Resource - (32, 32) storing ( biome info, if water tile, tiles sprite )
struct Tile {

  const Biome_enum biome_;
  const bool is_water_;

  std::shared_ptr<sf::Sprite> sprite_;

  // Construct tile from random index in Sprite_Obj
  Tile(Biome_enum biome, std::shared_ptr<Sprite_Obj> sprite_obj, bool is_water = false):
    biome_(biome),
    is_water_(is_water),
    sprite_(sprite_obj->get_Ptr(rand() % sprite_obj->size())) { }

  // Construct tile from passed index in Sprite_Obj ( used when want specific tile subset )
  Tile(Biome_enum biome, size_t tile_id, 
       std::shared_ptr<Sprite_Obj> sprite_obj, bool is_water = false):
    biome_(biome),
    is_water_(is_water),
    sprite_(sprite_obj->get_Ptr(tile_id)) { }

};

// Virtual Base Class for Biomes
// Contains : perlins_needed , which is number of perlins needed to properly generate biome
//            get_Resources  , which builds the biome ( tiles, resources, river ) from perlins*
//                             * - some biomes dont use perlins
class Biome {

public:

  Biome() { }

  virtual const size_t perlins_needed() { return 0; }
  // TO DO : Remove default args
  virtual void get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map_,
                             std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map_,
                             const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec,
                             const std::vector<std::vector<Biome_enum>>& biome_map,
                             const std::vector<std::vector<std::vector<state>>>& perlins = {{{}}}, 
                             size_t perlins_pos = 0,
                             const std::vector<std::vector<state>>& river = {{}}) { }
};

#endif
