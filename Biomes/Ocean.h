#ifndef __OCEAN_H_INCLUDED__
#define __OCEAN_H_INCLUDED__

// Class containing all Ocean Resource Textures & Sprites
// Overriden Biome functions to properly build Ocean biome ( perlins_needed = 0 & get_Resources )
class Ocean : public Biome {

  // Ocean's Texture Objects
  const Texture_Obj ocean_tile_t_;

  // Ocean's Sprite Objects
  std::shared_ptr<Sprite_Obj> ocean_tile_;

public:

  Ocean(const Ocean&) = delete;
  Ocean& operator= (const Ocean&) = delete;

  Ocean():
    ocean_tile_t_(32, 32, 4, "Biomes/ocean/waterTiles"),
    ocean_tile_(std::make_shared<Sprite_Obj>(ocean_tile_t_)) { }

  // Biome function overrides
  // Implimented in ./Biome_Builder.cpp
  void get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>&,
                     std::vector<std::vector<std::shared_ptr<Resource>>>&,
                     const std::vector<std::vector<Biome_enum>>&,
                     const std::vector<std::vector<std::vector<state>>>&, size_t,
                     const std::vector<std::vector<state>>&) override;
};

#endif
