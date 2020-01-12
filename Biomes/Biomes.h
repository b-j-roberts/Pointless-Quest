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

// Meta Template Class for mapping Biome_enum -> Biome with typedef type
/* Issue : This requires constexpr knowledge of which biomes I want, unless I want to construct
 *         All Resources
// Primary Template
template<Biome_enum T>
struct BiomeType;

// Special Template instantiation for each type of biome
template<> struct BiomeType<Forest_> { typedef Forest type; };
template<> struct BiomeType<Desert_> { typedef Desert type; };
template<> struct BiomeType<Magic_> { typedef Magic type; };
template<> struct BiomeType<Ocean_> { typedef Ocean type; };
template<> struct BiomeType<Swamp_> { typedef Swamp type; };
template<> struct BiomeType<Tundra_> { typedef Tundra type; };
template<> struct BiomeType<Unocean_> { typedef Old_Ocean type; };
template<> struct BiomeType<Cave_> { typedef Cave type; };

static const std::map<Biome_enum, BiomeType> Biome_enum_to_BiomeType = {
  {Forest_, BiomeType<Forest_>},
  {Desert_, BiomeType<Desert_>},
  {Magic_, BiomeType<Magic_>},
  {Ocean_, BiomeType<Ocean_>},
  {Swamp_, Swamp},
  {Tundra_, Tundra},
  {Unocean_, Old_Ocean},
  {Cave_, Cave}
};
*/

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
