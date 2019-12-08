#include "Forest.h"
#include "Magic.h"
#include "Desert.h"
#include "Ocean.h"
#include "OldOcean.h"
#include "Swamp.h"

#include <iostream> // TO DO : Debug

// TO DO : Scaling and tuning
//         When is each state
//         Some random ones outside of perlin range
//         stacking resources checks
//         rough biome edges
//         River for each biome
//         Resources over water
//         layering of resources

void Forest::get_Resources(const std::vector<std::vector<std::vector<state>>>& all_perlin, 
                           size_t pos, const std::vector<std::vector<Biome_enum>>& biomes_map, 
                           const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec,
                           std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map,
                           const std::vector<std::vector<state>>& river,
                           std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map) {

  // Tiles
  for(size_t i = 0; i < biomes_map.size(); ++i) { // TO DO : Resize tile file
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Forest_) {
        if(river[i][j] == Middle) { // Do river
          tile_map[i][j] = std::make_shared<Tile>(Forest_, tile_vec[Ocean_], true);
        } else { // Do normal tile
          switch(all_perlin[pos][i][j]) {
            case Top:
              tile_map[i][j] = std::make_shared<Tile>(Forest_, tile_vec[Forest_]); 
              break;

            case Middle:
              tile_map[i][j] = std::make_shared<Tile>(Forest_, rand() % 9, tile_vec[Forest_]);
              break;

            case Bottom:
              tile_map[i][j] = std::make_shared<Tile>(Forest_, rand() % 5, tile_vec[Forest_]);
              break;

            default: break;
          }
        }
      }
    }
  }

  // Tree Layer
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Forest_ && resource_map[i][j] == nullptr && 
         !tile_map[i][j]->is_water_) {
        int rnd = rand() % 100; // based on base 100 scale
        switch(all_perlin[pos + 1][i][j]) {
          case Top:
            if(rnd > 95)
              resource_map[i][j] = std::make_shared<Forest_Tree>(i * 32, j * 32, *this);
            else if(rnd > 87) 
              resource_map[i][j] = std::make_shared<Forest_Small_Tree>(i * 32, j * 32, *this);
            else if(rnd > 80) 
              resource_map[i][j] = std::make_shared<Forest_Bush>(i * 32, j * 32, *this);
            else if(rnd > 70) 
              resource_map[i][j] = std::make_shared<Forest_Moss>(i * 32, j * 32, *this);
            break;

          case Middle:
            if(rnd > 98) 
              resource_map[i][j] = std::make_shared<Forest_Tree>(i * 32, j * 32, *this);
            else if(rnd > 95) 
              resource_map[i][j] = std::make_shared<Forest_Small_Tree>(i * 32, j * 32, *this);
            else if(rnd > 90) 
              resource_map[i][j] = std::make_shared<Forest_Bush>(i * 32, j * 32, *this);
            else if(rnd > 85) 
              resource_map[i][j] = std::make_shared<Forest_Moss>(i * 32, j * 32, *this);
            break;

          case Bottom:
            if(rnd > 98) 
              resource_map[i][j] = std::make_shared<Forest_Tree>(i * 32, j * 32, *this);
            else if(rnd > 97) 
              resource_map[i][j] = std::make_shared<Forest_Small_Tree>(i * 32, j * 32, *this);
            else if(rnd > 96) 
              resource_map[i][j] = std::make_shared<Forest_Bush>(i * 32, j * 32, *this);
            else if(rnd > 94) 
              resource_map[i][j] = std::make_shared<Forest_Moss>(i * 32, j * 32, *this);
            break;

          default: break;
        }

        // generation range collision
        if(resource_map[i][j] != nullptr) {
          size_t gen_rng = resource_map[i][j]->generation_range();
          if(i + 1 >= gen_rng && j + 1 >= gen_rng) {
            for(size_t rng_x = i + 1 - gen_rng; rng_x < i + 1; ++rng_x) {
              for(size_t rng_y = j + 1 - gen_rng; rng_y < j + 1; ++rng_y) {
                if(resource_map[i][j] == nullptr || rng_x == i && rng_y == j) continue;        
                if(resource_map[rng_x][rng_y] != nullptr) resource_map[i][j] = nullptr;
              }
            }
          } else {
            resource_map[i][j] = nullptr;
          }
        }

      }
    }
  }

}

void Magic::get_Resources(const std::vector<std::vector<std::vector<state>>>& all_perlin,
                          size_t pos, const std::vector<std::vector<Biome_enum>>& biomes_map, 
                          const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec,
                          std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map,
                          const std::vector<std::vector<state>>& river,
                          std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map) {

  // Tiles
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Magic_) {
        if(river[i][j] == Middle) 
          tile_map[i][j] = std::make_shared<Tile>(Magic_, tile_vec[Ocean_], true);
        else tile_map[i][j] = std::make_shared<Tile>(Magic_, tile_vec[Magic_]);
      }
    }
  }

  // Flower Layer
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Magic_ && resource_map[i][j] == nullptr && !tile_map[i][j]->is_water_) {
        int rnd = rand() % 100;
        switch(all_perlin[pos][i][j]) {
          case Top:
            if(rnd > 85) 
              resource_map[i][j] = std::make_shared<Magic_Flowers>(i * 32, j * 32, *this);
            break;

          case Middle:
            if(rnd > 95) 
              resource_map[i][j] = std::make_shared<Magic_Flowers>(i * 32, j * 32, *this);
            break;

          case Bottom:
            if(rnd > 98) 
              resource_map[i][j] = std::make_shared<Magic_Flowers>(i * 32, j * 32, *this);
            break;

          default: break;
        }

        // generation range collision
        if(resource_map[i][j] != nullptr) {
          size_t gen_rng = resource_map[i][j]->generation_range();
          if(i + 1 >= gen_rng && j + 1 >= gen_rng) {
            for(size_t rng_x = i + 1 - gen_rng; rng_x < i + 1; ++rng_x) {
              for(size_t rng_y = j + 1 - gen_rng; rng_y < j + 1; ++rng_y) {
                if(resource_map[i][j] == nullptr || rng_x == i && rng_y == j) continue;        
                if(resource_map[rng_x][rng_y] != nullptr) resource_map[i][j] = nullptr;
              }
            }
          } else {
            resource_map[i][j] = nullptr;
          }
        }

      }
    }
  }

  // Tree Layer
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Magic_ && resource_map[i][j] == nullptr && !tile_map[i][j]->is_water_) {
        int rnd = rand() % 100;
        switch(all_perlin[pos + 1][i][j]) {
          case Top:
            if(rnd > 90) 
              resource_map[i][j] = std::make_shared<Magic_Trees>(i * 32, j * 32, *this);
            break;

          case Middle:
            if(rnd > 95) 
              resource_map[i][j] = std::make_shared<Magic_Trees>(i * 32, j * 32, *this);
            break;

          case Bottom:
            if(rnd > 98) 
              resource_map[i][j] = std::make_shared<Magic_Trees>(i * 32, j * 32, *this);
            break;

          default: break;
        }

        // generation range collision
        if(resource_map[i][j] != nullptr) {
          size_t gen_rng = resource_map[i][j]->generation_range();
          if(i + 1 >= gen_rng && j + 1 >= gen_rng) {
            for(size_t rng_x = i + 1 - gen_rng; rng_x < i + 1; ++rng_x) {
              for(size_t rng_y = j + 1 - gen_rng; rng_y < j + 1; ++rng_y) {
                if(resource_map[i][j] == nullptr || rng_x == i && rng_y == j) continue;        
                if(resource_map[rng_x][rng_y] != nullptr) resource_map[i][j] = nullptr;
              }
            }
          } else {
            resource_map[i][j] = nullptr;
          }
        } // TO DO : Think about avoiding doing this twice

      }
    }
  }

}

void Desert::get_Resources(const std::vector<std::vector<std::vector<state>>>& all_perlin, 
                           size_t pos, const std::vector<std::vector<Biome_enum>>& biomes_map, 
                           const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec,
                           std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map,
                           const std::vector<std::vector<state>>& river,
                           std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map) {

  // Tiles
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Desert_) {
        if(river[i][j] == Middle) 
          tile_map[i][j] = std::make_shared<Tile>(Desert_, tile_vec[Ocean_], true);
        else tile_map[i][j] = std::make_shared<Tile>(Desert_, tile_vec[Desert_]);
      }
    }
  }

  // Cactus Layer
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Desert_ && resource_map[i][j] == nullptr && 
         !tile_map[i][j]->is_water_) {
        int rnd = rand() % 100;
        switch(all_perlin[pos][i][j]) {
          case Top:
            if(rnd > 90) 
              resource_map[i][j] = std::make_shared<Desert_Cactus>(i * 32, j * 32, *this);
            break;

          case Middle:
            if(rnd > 95) 
              resource_map[i][j] = std::make_shared<Desert_Cactus>(i * 32, j * 32, *this);
            break;

          case Bottom:
            if(rnd > 98) 
              resource_map[i][j] = std::make_shared<Desert_Cactus>(i * 32, j * 32, *this);
            break;

          default: break;
        }

        // generation range collision
        if(resource_map[i][j] != nullptr) {
          size_t gen_rng = resource_map[i][j]->generation_range();
          if(i + 1 >= gen_rng && j + 1 >= gen_rng) {
            for(size_t rng_x = i + 1 - gen_rng; rng_x < i + 1; ++rng_x) {
              for(size_t rng_y = j + 1 - gen_rng; rng_y < j + 1; ++rng_y) {
                if(resource_map[i][j] == nullptr || rng_x == i && rng_y == j) continue;        
                if(resource_map[rng_x][rng_y] != nullptr) resource_map[i][j] = nullptr;
              }
            }
          } else {
            resource_map[i][j] = nullptr;
          }
        }

      }
    }
  }

}

void Ocean::get_Resources(const std::vector<std::vector<std::vector<state>>>& all_perlin, 
                          size_t pos, const std::vector<std::vector<Biome_enum>>& biomes_map, 
                          const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec,
                          std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map,
                          const std::vector<std::vector<state>>& river,
                          std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map) {

  // Tiles
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Ocean_) {
        tile_map[i][j] = std::make_shared<Tile>(Ocean_, tile_vec[Ocean_], true);
      }
    }
  }

  // There are currently no resources with this biome so just fill map with default resource objects
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Ocean_ && resource_map[i][j] == nullptr) {
      }
    }
  }

}

void Old_Ocean::get_Resources(const std::vector<std::vector<std::vector<state>>>& all_perlin, 
                              size_t pos, const std::vector<std::vector<Biome_enum>>& biomes_map, 
                              const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec,
                              std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map,
                              const std::vector<std::vector<state>>& river,
                              std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map) {

  // Tiles 
  // TO DO : Use perlin?
  for(size_t i = 0; i < biomes_map.size(); ++i) { // TO DO : Fix miscolored old_ocean tile
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Unocean_) {
        if(river[i][j] == Middle) 
          tile_map[i][j] = std::make_shared<Tile>(Unocean_, tile_vec[Ocean_], true);
        else tile_map[i][j] = std::make_shared<Tile>(Unocean_, tile_vec[Unocean_]);
      }
    }
  }

  // Bones Layer (Note : does not use perlin)
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Unocean_ && resource_map[i][j] == nullptr && 
         !tile_map[i][j]->is_water_) {
        int rnd = rand() % 100;
        if(rnd > 98) 
          resource_map[i][j] = std::make_shared<Old_Ocean_Large_Fish>(i * 32, j * 32, *this);
        else if(rnd > 95) 
          resource_map[i][j] = std::make_shared<Old_Ocean_Small_Fish>(i * 32, j * 32, *this);
        
        // generation range collision
        if(resource_map[i][j] != nullptr) {
          size_t gen_rng = resource_map[i][j]->generation_range();
          if(i + 1 >= gen_rng && j + 1 >= gen_rng) {
            for(size_t rng_x = i + 1 - gen_rng; rng_x < i + 1; ++rng_x) {
              for(size_t rng_y = j + 1 - gen_rng; rng_y < j + 1; ++rng_y) {
                if(resource_map[i][j] == nullptr || rng_x == i && rng_y == j) continue;        
                if(resource_map[rng_x][rng_y] != nullptr) resource_map[i][j] = nullptr;
              }
            }
          } else {
            resource_map[i][j] = nullptr;
          }
        }

      }
    }
  }

}

void Swamp::get_Resources(const std::vector<std::vector<std::vector<state>>>& all_perlin, 
                          size_t pos, const std::vector<std::vector<Biome_enum>>& biomes_map, 
                          const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec,
                          std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map,
                          const std::vector<std::vector<state>>& river,
                          std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map) {

  // Tiles
  // TO DO : Perlin?
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Swamp_) {
        if(river[i][j] == Middle) 
          tile_map[i][j] = std::make_shared<Tile>(Swamp_, swamp_water_, true);
        else tile_map[i][j] = std::make_shared<Tile>(Swamp_, tile_vec[Swamp_]);
      }
    }
  }

  // Trees Layer
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Swamp_ && resource_map[i][j] == nullptr) {
        int rnd = rand() % 100;
        switch(all_perlin[pos][i][j]) {
          case Top:
            if(rnd > 95) 
              resource_map[i][j] = std::make_shared<Swamp_Tree>(i * 32, j * 32, *this);
            else if(rnd > 91)
              resource_map[i][j] = std::make_shared<Swamp_Spikes>(i * 32, j * 32, *this);
            break;

          case Middle:
            if(rnd > 97)
              resource_map[i][j] = std::make_shared<Swamp_Tree>(i * 32, j * 32, *this);
            else if(rnd > 93)
              resource_map[i][j] = std::make_shared<Swamp_Spikes>(i * 32, j * 32, *this);
            break;

          case Bottom:
            if(rnd > 98)
              resource_map[i][j] = std::make_shared<Swamp_Tree>(i * 32, j * 32, *this);
            else if(rnd > 95)
              resource_map[i][j] = std::make_shared<Swamp_Spikes>(i * 32, j * 32, *this);
            break;

          default: break;
        }

        // generation range collision
        if(resource_map[i][j] != nullptr) {
          size_t gen_rng = resource_map[i][j]->generation_range();
          if(i + 1 >= gen_rng && j + 1 >= gen_rng) {
            for(size_t rng_x = i + 1 - gen_rng; rng_x < i + 1; ++rng_x) {
              for(size_t rng_y = j + 1 - gen_rng; rng_y < j + 1; ++rng_y) {
                if(resource_map[i][j] == nullptr || rng_x == i && rng_y == j) continue;        
                if(resource_map[rng_x][rng_y] != nullptr) resource_map[i][j] = nullptr;
              }
            }
          } else {
            resource_map[i][j] = nullptr;
          }
        }

      }
    }
  }
  
/*
  // Water Layer TO DO : Do an overall river and use tile for corresponding biome in that position
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Swamp_ && resource_map[i][j] == nullptr) {
        switch(all_perlin[pos + 1][i][j]) {
          case Top:
            resource_map[i][j] = std::make_shared<Swamp_Water>(i * 32, j * 32, *this);
            break;
//
//          case Middle:
//            break;
//
//          case Bottom:
//            break;
//
          default: 
            break;
        }
      }
    }
  }
*/
  // Reeds
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Swamp_ && resource_map[i][j] == nullptr && !tile_map[i][j]->is_water_) {
        int rnd = rand() % 100;
        switch(all_perlin[pos + 2][i][j]) {
          case Top:
            if(rnd > 92) 
              resource_map[i][j] = std::make_shared<Swamp_Reeds>(i * 32, j * 32, *this);
            break;

          case Middle:
            if(rnd > 96) 
              resource_map[i][j] = std::make_shared<Swamp_Reeds>(i * 32, j * 32, *this);
            break;

          case Bottom:
            if(rnd > 98) 
              resource_map[i][j] = std::make_shared<Swamp_Reeds>(i * 32, j * 32, *this);
            break;

          default: break;
        }

        // generation range collision
        if(resource_map[i][j] != nullptr) {
          size_t gen_rng = resource_map[i][j]->generation_range();
          if(i + 1 >= gen_rng && j + 1 >= gen_rng) {
            for(size_t rng_x = i + 1 - gen_rng; rng_x < i + 1; ++rng_x) {
              for(size_t rng_y = j + 1 - gen_rng; rng_y < j + 1; ++rng_y) {
                if(resource_map[i][j] == nullptr || rng_x == i && rng_y == j) continue;        
                if(resource_map[rng_x][rng_y] != nullptr) resource_map[i][j] = nullptr;
              }
            }
          } else {
            resource_map[i][j] = nullptr;
          }
        } // TO DO : Think about not doing this twice

      }
    }
  }

}
