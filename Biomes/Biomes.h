#ifndef __BIOMES_H_INCLUDED__
#define __BIOMES_H_INCLUDED__

#include <memory> // TO DO

#include "Forest.h"
#include "Magic.h"
#include "Desert.h"
#include "Ocean.h"
#include "OldOcean.h"
#include "Swamp.h"
#include "Tundra.h"

#include "Cave.h"

static std::unique_ptr<Biome> get_Biome(const Biome_enum b) {
  switch(b) {
    case Forest_:
      return std::make_unique<Forest>();
    case Desert_:
      return std::make_unique<Desert>();
    case Magic_:
      return std::make_unique<Magic>();
    case Ocean_:
      return std::make_unique<Ocean>();
    case Swamp_:
      return std::make_unique<Swamp>();
    case Tundra_:
      return std::make_unique<Tundra>();
    case Unocean_:
      return std::make_unique<Old_Ocean>();
    case Cave_:
      return std::make_unique<Cave>();
    default:
      return std::make_unique<Biome>();
  }
}

#endif
