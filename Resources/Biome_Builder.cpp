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
//         layering of resources

void Forest::get_Resources(const std::vector<std::vector<std::vector<state>>>& all_perlin, 
                           size_t pos, const std::vector<std::vector<Biome_enum>>& biomes_map, 
                           std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map) {

  // TO DO : We skip one of the perlins because we are skipping the tile guy for now

  // Tree Layer
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Forest_ && resource_map[i][j] == nullptr) {
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
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
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
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
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
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          default: 
//            resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;
        }
      }
    }
  }

}

void Magic::get_Resources(const std::vector<std::vector<std::vector<state>>>& all_perlin,
                          size_t pos, const std::vector<std::vector<Biome_enum>>& biomes_map, 
                          std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map) {

  // Flower Layer
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Magic_ && resource_map[i][j] == nullptr) {
        int rnd = rand() % 100;
        switch(all_perlin[pos][i][j]) {
          case Top:
            if(rnd > 85) 
              resource_map[i][j] = std::make_shared<Magic_Flowers>(i * 32, j * 32, *this);
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          case Middle:
            if(rnd > 95) 
              resource_map[i][j] = std::make_shared<Magic_Flowers>(i * 32, j * 32, *this);
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          case Bottom:
            if(rnd > 98) 
              resource_map[i][j] = std::make_shared<Magic_Flowers>(i * 32, j * 32, *this);
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          default: 
//            resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;
        }
      }
    }
  }

  // Tree Layer
  // TO DO : Need to do nullptr checking to not override flowers ?
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Magic_ && resource_map[i][j] == nullptr) {
        int rnd = rand() % 100;
        switch(all_perlin[pos + 1][i][j]) {
          case Top:
            if(rnd > 90) 
              resource_map[i][j] = std::make_shared<Magic_Trees>(i * 32, j * 32, *this);
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          case Middle:
            if(rnd > 95) 
              resource_map[i][j] = std::make_shared<Magic_Trees>(i * 32, j * 32, *this);
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          case Bottom:
            if(rnd > 98) 
              resource_map[i][j] = std::make_shared<Magic_Trees>(i * 32, j * 32, *this);
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          default:
//            resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;
        }
      }
    }
  }

}

void Desert::get_Resources(const std::vector<std::vector<std::vector<state>>>& all_perlin, 
                           size_t pos, const std::vector<std::vector<Biome_enum>>& biomes_map, 
                           std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map) {

  // Cactus Layer
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Desert_ && resource_map[i][j] == nullptr) {
        int rnd = rand() % 100;
        switch(all_perlin[pos][i][j]) {
          case Top:
            if(rnd > 90) 
              resource_map[i][j] = std::make_shared<Desert_Cactus>(i * 32, j * 32, *this);
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          case Middle:
            if(rnd > 95) 
              resource_map[i][j] = std::make_shared<Desert_Cactus>(i * 32, j * 32, *this);
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          case Bottom:
            if(rnd > 98) 
              resource_map[i][j] = std::make_shared<Desert_Cactus>(i * 32, j * 32, *this);
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          default:
//            resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;
        }
      }
    }
  }

}

void Ocean::get_Resources(const std::vector<std::vector<std::vector<state>>>& all_perlin, 
                          size_t pos, const std::vector<std::vector<Biome_enum>>& biomes_map, 
                          std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map) {

  // There are currently no resources with this biome so just fill map with default resource objects
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Ocean_ && resource_map[i][j] == nullptr) {
//        resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
      }
    }
  }

}

void Old_Ocean::get_Resources(const std::vector<std::vector<std::vector<state>>>& all_perlin, 
                              size_t pos, const std::vector<std::vector<Biome_enum>>& biomes_map, 
                              std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map) {

  // Bones Layer (Note : does not use perlin)
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Unocean_ && resource_map[i][j] == nullptr) {
        int rnd = rand() % 100;
        if(rnd > 98) 
          resource_map[i][j] = std::make_shared<Old_Ocean_Large_Fish>(i * 32, j * 32, *this);
        else if(rnd > 95) 
          resource_map[i][j] = std::make_shared<Old_Ocean_Small_Fish>(i * 32, j * 32, *this);
//        else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
      }
    }
  }

}

void Swamp::get_Resources(const std::vector<std::vector<std::vector<state>>>& all_perlin, 
                          size_t pos, const std::vector<std::vector<Biome_enum>>& biomes_map, 
                          std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map) {

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
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          case Middle:
            if(rnd > 97)
              resource_map[i][j] = std::make_shared<Swamp_Tree>(i * 32, j * 32, *this);
            else if(rnd > 93)
              resource_map[i][j] = std::make_shared<Swamp_Spikes>(i * 32, j * 32, *this);
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          case Bottom:
            if(rnd > 98)
              resource_map[i][j] = std::make_shared<Swamp_Tree>(i * 32, j * 32, *this);
            else if(rnd > 95)
              resource_map[i][j] = std::make_shared<Swamp_Spikes>(i * 32, j * 32, *this);
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          default:
//            resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;
        }
      }
    }
  }
  

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
//            resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;
        }
      }
    }
  }

  // Reeds
  for(size_t i = 0; i < biomes_map.size(); ++i) {
    for(size_t j = 0; j < biomes_map[i].size(); ++j) {
      if(biomes_map[i][j] == Swamp_ && resource_map[i][j] == nullptr) {
        int rnd = rand() % 100;
        switch(all_perlin[pos + 2][i][j]) {
          case Top:
            if(rnd > 92) 
              resource_map[i][j] = std::make_shared<Swamp_Reeds>(i * 32, j * 32, *this);
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          case Middle:
            if(rnd > 96) 
              resource_map[i][j] = std::make_shared<Swamp_Reeds>(i * 32, j * 32, *this);
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          case Bottom:
            if(rnd > 98) 
              resource_map[i][j] = std::make_shared<Swamp_Reeds>(i * 32, j * 32, *this);
//            else resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;

          default:
//            resource_map[i][j] = std::make_shared<Resource>(i * 32, j * 32);
            break;
        }
      }
    }
  }

}
