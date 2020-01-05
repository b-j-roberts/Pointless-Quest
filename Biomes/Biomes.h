#ifndef __BIOMES_H_INCLUDED__
#define __BIOMES_H_INCLUDED__

#include "Forest.h"
#include "Magic.h"
#include "Desert.h"
#include "Ocean.h"
#include "OldOcean.h"
#include "Swamp.h"
// TO DO : Include the tundra

#include "Cave.h"

template<Biome_enum T> // Primary template
struct BiomeType;

template<> struct BiomeType<Forest_> { typedef Forest type; };
template<> struct BiomeType<Desert_> { typedef Desert type; };
template<> struct BiomeType<Magic_> { typedef Magic type; };
template<> struct BiomeType<Ocean_> { typedef Ocean type; };
template<> struct BiomeType<Swamp_> { typedef Swamp type; };
//template<> struct BiomeType<Tundra> { typedef Tundra type; };
template<> struct BiomeType<Unocean_> { typedef Old_Ocean type; };
template<> struct BiomeType<Cave_> { typedef Cave type; };

#endif
