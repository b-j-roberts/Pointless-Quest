#include "Forest.h"
#include "Magic.h"
#include "Desert.h"
#include "Ocean.h"
#include "OldOcean.h"
#include "Swamp.h"
#include "Tundra.h"

#include "Cave.h"

// TO DO : Scaling and tuning
//         When is each state, ie cutoff values
//         River texture for each biome
//         layering of resources, (0 - tile, 1 - river) tile map, (2 - ground resource) below player
//                                (3 - other resources) above player, (-1 - cave) needs each type of
//                                layer itself 
//         cutoff bottom of resources in water, so they look submerged

// Impliments all get_Resources functions
// TO DO : Think about beter way to do this! So much repeated code

void Forest::get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map_,
                           std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map_,
                           const std::vector<std::vector<Biome_enum>>& biome_map,
                           const std::vector<std::vector<std::vector<state>>>& perlins,
                           size_t perlins_pos,
                           const std::vector<std::vector<state>>& river) {

  // Tiles
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Forest_) {
        if(river[i][j] == Middle) { // Do river
          tile_map_[i][j] = std::make_shared<Tile>(Forest_, forest_water_, true);
        } else { // Do normal tile
          switch(perlins[perlins_pos][i][j]) {
            case Top:
              tile_map_[i][j] = std::make_shared<Tile>(Forest_, forest_tile_); 
              break;

            case Middle:
              tile_map_[i][j] = std::make_shared<Tile>(Forest_, rand() % 9, forest_tile_);
              break;

            case Bottom:
              tile_map_[i][j] = std::make_shared<Tile>(Forest_, rand() % 5, forest_tile_);
              break;

            default: break;
          }
        }
      }
    }
  }

  // Tree Layer
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Forest_ && resource_map_[i][j] == nullptr && 
         !tile_map_[i][j]->is_water_) {
        int rnd = rand() % 100; // based on base 100 scale
        switch(perlins[perlins_pos + 1][i][j]) {
          case Top:
            if(rnd > 95)
              resource_map_[i][j] = std::make_shared<Forest_Tree>(j * 32, i * 32, *this);
            else if(rnd > 87) 
              resource_map_[i][j] = std::make_shared<Forest_Small_Tree>(j * 32, i * 32, *this);
            else if(rnd > 80) 
              resource_map_[i][j] = std::make_shared<Forest_Bush>(j * 32, i * 32, *this);
            else if(rnd > 70) 
              resource_map_[i][j] = std::make_shared<Forest_Moss>(j * 32, i * 32, *this);
            break;

          case Middle:
            if(rnd > 98) 
              resource_map_[i][j] = std::make_shared<Forest_Tree>(j * 32, i * 32, *this);
            else if(rnd > 95) 
              resource_map_[i][j] = std::make_shared<Forest_Small_Tree>(j * 32, i * 32, *this);
            else if(rnd > 90) 
              resource_map_[i][j] = std::make_shared<Forest_Bush>(j * 32, i * 32, *this);
            else if(rnd > 85) 
              resource_map_[i][j] = std::make_shared<Forest_Moss>(j * 32, i * 32, *this);
            break;

          case Bottom:
            if(rnd > 98) 
              resource_map_[i][j] = std::make_shared<Forest_Tree>(j * 32, i * 32, *this);
            else if(rnd > 97) 
              resource_map_[i][j] = std::make_shared<Forest_Small_Tree>(j * 32, i * 32, *this);
            else if(rnd > 96) 
              resource_map_[i][j] = std::make_shared<Forest_Bush>(j * 32, i * 32, *this);
            else if(rnd > 94) 
              resource_map_[i][j] = std::make_shared<Forest_Moss>(j * 32, i * 32, *this);
            break;

          default: break;
        }

        // generation range collision
        if(resource_map_[i][j] != nullptr) {
          size_t gen_rng = resource_map_[i][j]->generation_range();
          if(i + 1 >= gen_rng && j + 1 >= gen_rng) { // Prevents indexing outside of world
            for(size_t rng_x = j + 1 - gen_rng; rng_x < j + 1; ++rng_x) {
              for(size_t rng_y = i + 1 - gen_rng; rng_y < i + 1; ++rng_y) {
                if(resource_map_[i][j] == nullptr || rng_x == j && rng_y == i) continue;        
                if(resource_map_[rng_x][rng_y] != nullptr) resource_map_[i][j] = nullptr;
              }
            }
          } else {
            resource_map_[i][j] = nullptr;
          }
        }

      }
    }
  }
}

void Magic::get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map_,
                          std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map_,
                          const std::vector<std::vector<Biome_enum>>& biome_map,
                          const std::vector<std::vector<std::vector<state>>>& perlins,
                          size_t perlins_pos,
                          const std::vector<std::vector<state>>& river) {

  // Tiles
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Magic_) {
        if(river[i][j] == Middle) 
          tile_map_[i][j] = std::make_shared<Tile>(Magic_, magic_water_, true);
        else tile_map_[i][j] = std::make_shared<Tile>(Magic_, magic_tile_);
      }
    }
  }

  // Flower Layer
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Magic_ && resource_map_[i][j] == nullptr && 
         !tile_map_[i][j]->is_water_) {
        int rnd = rand() % 100;
        switch(perlins[perlins_pos][i][j]) {
          case Top:
            if(rnd > 85) 
              resource_map_[i][j] = std::make_shared<Magic_Flowers>(j * 32, i * 32, *this);
            break;

          case Middle:
            if(rnd > 95) 
              resource_map_[i][j] = std::make_shared<Magic_Flowers>(j * 32, i * 32, *this);
            break;

          case Bottom:
            if(rnd > 98) 
              resource_map_[i][j] = std::make_shared<Magic_Flowers>(j * 32, i * 32, *this);
            break;

          default: break;
        }

        // generation range collision
        if(resource_map_[i][j] != nullptr) {
          size_t gen_rng = resource_map_[i][j]->generation_range();
          if(i + 1 >= gen_rng && j + 1 >= gen_rng) { // Prevents generation outside of world
            for(size_t rng_x = j + 1 - gen_rng; rng_x < j + 1; ++rng_x) {
              for(size_t rng_y = i + 1 - gen_rng; rng_y < i + 1; ++rng_y) {
                if(resource_map_[i][j] == nullptr || rng_x == j && rng_y == i) continue;        
                if(resource_map_[rng_x][rng_y] != nullptr) resource_map_[i][j] = nullptr;
              }
            }
          } else {
            resource_map_[i][j] = nullptr;
          }
        }

      }
    }
  }

  // Tree Layer
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Magic_ && resource_map_[i][j] == nullptr && 
         !tile_map_[i][j]->is_water_) {
        int rnd = rand() % 100;
        switch(perlins[perlins_pos + 1][i][j]) {
          case Top:
            if(rnd > 90) 
              resource_map_[i][j] = std::make_shared<Magic_Trees>(j * 32, i * 32, *this);
            break;

          case Middle:
            if(rnd > 95) 
              resource_map_[i][j] = std::make_shared<Magic_Trees>(j * 32, i * 32, *this);
            break;

          case Bottom:
            if(rnd > 98) 
              resource_map_[i][j] = std::make_shared<Magic_Trees>(j * 32, i * 32, *this);
            break;

          default: break;
        }

        // generation range collision
        if(resource_map_[i][j] != nullptr) {
          size_t gen_rng = resource_map_[i][j]->generation_range();
          if(i + 1 >= gen_rng && j + 1 >= gen_rng) { // Prevents generation outside of world
            for(size_t rng_x = j + 1 - gen_rng; rng_x < j + 1; ++rng_x) {
              for(size_t rng_y = i + 1 - gen_rng; rng_y < i + 1; ++rng_y) {
                if(resource_map_[i][j] == nullptr || rng_x == j && rng_y == i) continue;        
                if(resource_map_[rng_x][rng_y] != nullptr) resource_map_[i][j] = nullptr;
              }
            }
          } else {
            resource_map_[i][j] = nullptr;
          }
        }

      }
    }
  }
}

void Desert::get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map_,
                           std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map_,
                           const std::vector<std::vector<Biome_enum>>& biome_map,
                           const std::vector<std::vector<std::vector<state>>>& perlins,
                           size_t perlins_pos,
                           const std::vector<std::vector<state>>& river) {

  // Tiles
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Desert_) {
        if(river[i][j] == Middle) 
          tile_map_[i][j] = std::make_shared<Tile>(Desert_, desert_water_, true);
        else tile_map_[i][j] = std::make_shared<Tile>(Desert_, desert_tile_);
      }
    }
  }

  // Cactus Layer
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Desert_ && resource_map_[i][j] == nullptr && 
         !tile_map_[i][j]->is_water_) {
        int rnd = rand() % 100;
        switch(perlins[perlins_pos][i][j]) {
          case Top:
            if(rnd > 90) 
              resource_map_[i][j] = std::make_shared<Desert_Cactus>(j * 32, i * 32, *this);
            break;

          case Middle:
            if(rnd > 95) 
              resource_map_[i][j] = std::make_shared<Desert_Cactus>(j * 32, i * 32, *this);
            break;

          case Bottom:
            if(rnd > 98) 
              resource_map_[i][j] = std::make_shared<Desert_Cactus>(j * 32, i * 32, *this);
            break;

          default: break;
        }

        // generation range collision
        if(resource_map_[i][j] != nullptr) {
          size_t gen_rng = resource_map_[i][j]->generation_range();
          if(i + 1 >= gen_rng && j + 1 >= gen_rng) { // Prevents generation outside of world
            for(size_t rng_x = j + 1 - gen_rng; rng_x < j + 1; ++rng_x) {
              for(size_t rng_y = i + 1 - gen_rng; rng_y < i + 1; ++rng_y) {
                if(resource_map_[i][j] == nullptr || rng_x == j && rng_y == i) continue;        
                if(resource_map_[rng_x][rng_y] != nullptr) resource_map_[i][j] = nullptr;
              }
            }
          } else {
            resource_map_[i][j] = nullptr;
          }
        }

      }
    }
  }
}

void Ocean::get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map_,
                          std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map_,
                          const std::vector<std::vector<Biome_enum>>& biome_map,
                          const std::vector<std::vector<std::vector<state>>>& perlins,
                          size_t perlins_pos,
                          const std::vector<std::vector<state>>& river) {

  // Tiles
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Ocean_) {
        tile_map_[i][j] = std::make_shared<Tile>(Ocean_, ocean_tile_);
      }
    }
  }

}

void Old_Ocean::get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map_,
                             std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map_,
                             const std::vector<std::vector<Biome_enum>>& biome_map,
                             const std::vector<std::vector<std::vector<state>>>& perlins,
                             size_t perlins_pos,
                             const std::vector<std::vector<state>>& river) {

  // Tiles 
  // TO DO : Use perlin?
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Old_Ocean_) {
        if(river[i][j] == Middle) 
          tile_map_[i][j] = std::make_shared<Tile>(Old_Ocean_, old_ocean_water_, true);
        else tile_map_[i][j] = std::make_shared<Tile>(Old_Ocean_, old_ocean_tile_);
      }
    }
  }

  // Bones
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Old_Ocean_ && resource_map_[i][j] == nullptr && 
         !tile_map_[i][j]->is_water_) {
        int rnd = rand() % 100;
        if(rnd > 98) 
          resource_map_[i][j] = std::make_shared<Old_Ocean_Large_Fish>(j * 32, i * 32, *this);
        else if(rnd > 95) 
          resource_map_[i][j] = std::make_shared<Old_Ocean_Small_Fish>(j * 32, i * 32, *this);
        
        // generation range collision
        if(resource_map_[i][j] != nullptr) {
          size_t gen_rng = resource_map_[i][j]->generation_range();
          if(i + 1 >= gen_rng && j + 1 >= gen_rng) { // Prevents generation outside of world
            for(size_t rng_x = j + 1 - gen_rng; rng_x < j + 1; ++rng_x) {
              for(size_t rng_y = i + 1 - gen_rng; rng_y < i + 1; ++rng_y) {
                if(resource_map_[i][j] == nullptr || rng_x == j && rng_y == i) continue;        
                if(resource_map_[rng_x][rng_y] != nullptr) resource_map_[i][j] = nullptr;
              }
            }
          } else {
            resource_map_[i][j] = nullptr;
          }
        }

      }
    }
  }
}

void Swamp::get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map_,
                          std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map_,
                          const std::vector<std::vector<Biome_enum>>& biome_map,
                          const std::vector<std::vector<std::vector<state>>>& perlins,
                          size_t perlins_pos,
                          const std::vector<std::vector<state>>& river) {

  // Tiles
  // TO DO : Perlin?
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Swamp_) {
        if(river[i][j] == Middle) 
          tile_map_[i][j] = std::make_shared<Tile>(Swamp_, swamp_water_, true);
        else tile_map_[i][j] = std::make_shared<Tile>(Swamp_, swamp_tile_);
      }
    }
  }

  // Trees Layer
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Swamp_ && resource_map_[i][j] == nullptr) {
        int rnd = rand() % 100;
        switch(perlins[perlins_pos][i][j]) {
          case Top:
            if(rnd > 95) 
              resource_map_[i][j] = std::make_shared<Swamp_Tree>(j * 32, i * 32, *this);
            else if(rnd > 91)
              resource_map_[i][j] = std::make_shared<Swamp_Spikes>(j * 32, i * 32, *this);
            break;

          case Middle:
            if(rnd > 97)
              resource_map_[i][j] = std::make_shared<Swamp_Tree>(j * 32, i * 32, *this);
            else if(rnd > 93)
              resource_map_[i][j] = std::make_shared<Swamp_Spikes>(j * 32, i * 32, *this);
            break;

          case Bottom:
            if(rnd > 98)
              resource_map_[i][j] = std::make_shared<Swamp_Tree>(j * 32, i * 32, *this);
            else if(rnd > 95)
              resource_map_[i][j] = std::make_shared<Swamp_Spikes>(j * 32, i * 32, *this);
            break;

          default: break;
        }

        // generation range collision
        if(resource_map_[i][j] != nullptr) {
          size_t gen_rng = resource_map_[i][j]->generation_range();
          if(i + 1 >= gen_rng && j + 1 >= gen_rng) { // Prevents generation outside of world
            for(size_t rng_x = j + 1 - gen_rng; rng_x < j + 1; ++rng_x) {
              for(size_t rng_y = i + 1 - gen_rng; rng_y < i + 1; ++rng_y) {
                if(resource_map_[i][j] == nullptr || rng_x == j && rng_y == i) continue;        
                if(resource_map_[rng_x][rng_y] != nullptr) resource_map_[i][j] = nullptr;
              }
            }
          } else {
            resource_map_[i][j] = nullptr;
          }
        }

      }
    }
  }
  
  // TO DO : Water ?

  // Reeds
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Swamp_ && resource_map_[i][j] == nullptr &&
         !tile_map_[i][j]->is_water_) {
        int rnd = rand() % 100;
        switch(perlins[perlins_pos + 1][i][j]) {
          case Top:
            if(rnd > 92) 
              resource_map_[i][j] = std::make_shared<Swamp_Reeds>(j * 32, i * 32, *this);
            break;

          case Middle:
            if(rnd > 96) 
              resource_map_[i][j] = std::make_shared<Swamp_Reeds>(j * 32, i * 32, *this);
            break;

          case Bottom:
            if(rnd > 98) 
              resource_map_[i][j] = std::make_shared<Swamp_Reeds>(j * 32, i * 32, *this);
            break;

          default: break;
        }

        // generation range collision
        if(resource_map_[i][j] != nullptr) {
          size_t gen_rng = resource_map_[i][j]->generation_range();
          if(i + 1 >= gen_rng && j + 1 >= gen_rng) { // Prevents generation outside of world
            for(size_t rng_x = j + 1 - gen_rng; rng_x < j + 1; ++rng_x) {
              for(size_t rng_y = i + 1 - gen_rng; rng_y < i + 1; ++rng_y) {
                if(resource_map_[i][j] == nullptr || rng_x == j && rng_y == i) continue;        
                if(resource_map_[rng_x][rng_y] != nullptr) resource_map_[i][j] = nullptr;
              }
            }
          } else {
            resource_map_[i][j] = nullptr;
          }
        }

      }
    }
  }
}

void Tundra::get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map_,
                           std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map_,
                           const std::vector<std::vector<Biome_enum>>& biome_map,
                           const std::vector<std::vector<std::vector<state>>>& perlins,
                           size_t perlins_pos,
                           const std::vector<std::vector<state>>& river) {

  // Tiles
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Tundra_) {
        if(river[i][j] == Middle)
          tile_map_[i][j] = std::make_shared<Tile>(Tundra_, tundra_ice_, true);
        else tile_map_[i][j] = std::make_shared<Tile>(Tundra_, tundra_tile_);
      }
    }
  }

  //Plantlife
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Tundra_ && resource_map_[i][j] == nullptr &&
         !tile_map_[i][j]->is_water_) {
        int rnd = rand() % 100; // based on base 100 scale
        switch(perlins[perlins_pos][i][j]) {
          case Top:
            if(rnd > 94)
              resource_map_[i][j] = std::make_shared<Tundra_Tree>(j * 32, i * 32, *this);
            else if(rnd > 90)
              resource_map_[i][j] = std::make_shared<Tundra_Shrub>(j * 32, i * 32, *this);
            break;

          case Middle:
            if(rnd > 97)
              resource_map_[i][j] = std::make_shared<Tundra_Tree>(j * 32, i * 32, *this);
            else if(rnd > 94)
              resource_map_[i][j] = std::make_shared<Tundra_Shrub>(j * 32, i * 32, *this);
            break;

          case Bottom:
            if(rnd > 98)
              resource_map_[i][j] = std::make_shared<Tundra_Tree>(j * 32, i * 32, *this);
            else if(rnd > 97)
              resource_map_[i][j] = std::make_shared<Tundra_Shrub>(j * 32, i * 32, *this);
            break;

          default: break;
        }

        // generation range collision
        if(resource_map_[i][j] != nullptr) {
          size_t gen_rng = resource_map_[i][j]->generation_range();
          if(i + 1 >= gen_rng && j + 1 >= gen_rng) { // Prevents generation outside of world
            for(size_t rng_x = j + 1 - gen_rng; rng_x < j + 1; ++rng_x) {
              for(size_t rng_y = i + 1 - gen_rng; rng_y < i + 1; ++rng_y) {
                if(resource_map_[i][j] == nullptr || rng_x == j && rng_y == i) continue;
                if(resource_map_[rng_x][rng_y] != nullptr) resource_map_[i][j] = nullptr;
              }
            }
          } else {
            resource_map_[i][j] = nullptr;
          }
        }

      }
    }
  }
}

void Cave::get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map_,
                         std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map_,
                         const std::vector<std::vector<Biome_enum>>& biome_map,
                         const std::vector<std::vector<std::vector<state>>>& perlins,
                         size_t perlins_pos,
                         const std::vector<std::vector<state>>& river) {

  // Tiles 
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Cave_) {
         tile_map_[i][j] = std::make_shared<Tile>(Cave_, cave_tile_);
      }
    }
  }

  // Resources
  for(size_t i = 0; i < biome_map.size(); ++i) {
    for(size_t j = 0; j < biome_map[i].size(); ++j) {
      if(biome_map[i][j] == Cave_) {
        int rnd = rand() % 100;
        if(rnd > 97) 
          resource_map_[i][j] = std::make_shared<Cave_Spike>(j * 32, i * 32, *this);
        else if(rnd > 95) 
          resource_map_[i][j] = std::make_shared<Cave_Crystal>(j * 32, i * 32, *this);
      }
    }
  }

  // TO DO : gen_rng checks, for now useless
}
