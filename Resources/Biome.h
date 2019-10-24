#ifndef __BIOME_H_INCLUDED__
#define __BIOME_H_INCLUDED__

enum state { Top, Middle, Bottom };

enum Biome_enum {  Forest_ = 0, Desert_ = 1, Magic_ = 2, Ocean_ = 3, Swamp_ = 4, Tundra_ = 5, Unocean_ = 6 };

class Biome {

public:

  Biome() { }

  virtual const size_t perlins_needed() { return 0; }
  virtual void get_Resources(const std::vector<std::vector<std::vector<state>>>&, size_t,
                       const std::vector<std::vector<Biome_enum>>&, std::vector<std::vector<std::shared_ptr<Resource>>>&) { }

};

#endif
