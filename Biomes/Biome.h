#ifndef BIOME_H
#define BIOME_H

#include "../Resources/Structures.h"

// Used for indexing particular biomes
enum Biome_enum {  Forest_ = 0, Desert_, Magic_, Ocean_, Swamp_, Tundra_, Old_Ocean_, Cave_, None_ };

// Used for indexing particular planes
enum Plane_enum { Overworld_ = 0, Underground_ };

// Layer 0 Resource - (32, 32) storing ( biome info, if water tile, pointer to tile's sprite )
struct Tile {

  const Biome_enum biome_;
  const bool is_water_;

  std::shared_ptr<sf::Sprite> sprite_;

  // Construct tile from random index in Sprite_Obj
  Tile(Biome_enum biome, std::shared_ptr<Sprite_Obj> sprite_obj, bool is_water = false):
    biome_(biome),
    is_water_(is_water),
    sprite_(sprite_obj->get_rand_Ptr()) { }

  // Construct tile from passed index in Sprite_Obj ( used when want specific tile subset )
  Tile(Biome_enum biome, size_t tile_id, 
       std::shared_ptr<Sprite_Obj> sprite_obj, bool is_water = false):
    biome_(biome),
    is_water_(is_water),
    sprite_(sprite_obj->get_Ptr(tile_id)) { }

};

// Virtual Base Class for Biomes
class Biome {

public:

  Biome() = default;
  virtual ~Biome() = default;

  // Returns number of perlins needed to generate this biome in World::generate function
  virtual size_t perlins_needed() { return 0; }

  // Builds biome ( tiles, resources, river, ... ) from perlins ( if needed )
  // params : World_Plane::tile_map_, World_Plane::resource_map_, biome_map, all perlins,
  //          position in all perlins vector, river ( stored in Mid state ) 
  virtual void get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>&,
                             std::vector<std::vector<std::shared_ptr<Resource>>>&,
                             const std::vector<std::vector<Biome_enum>>&,
                             const std::vector<std::vector<std::vector<state>>>&, size_t,
                             const std::vector<std::vector<state>>&) { }
};

#endif
