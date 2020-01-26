#ifndef __OCEAN_H_INCLUDED__
#define __OCEAN_H_INCLUDED__

// This is blank for now because I dont have any ocean resources!!

// Class containing all Ocean Resource Textures & Sprites
// Contains overriden functions to properly build Ocean biome ( perlins_needed = 0 & get_Resources )
class Ocean : public Biome {

  public:

    Ocean() { }

/*    void get_Resources(const std::vector<std::vector<std::vector<state>>>&, size_t,
                       const std::vector<std::vector<Biome_enum>>&, 
                       const std::vector<std::shared_ptr<Sprite_Obj>>&,
                       std::vector<std::vector<std::shared_ptr<Tile>>>&,
                       const std::vector<std::vector<state>>&,
                       std::vector<std::vector<std::shared_ptr<Resource>>>&) override;
*/
    void get_Resources(std::vector<std::vector<std::shared_ptr<Tile>>>& tile_map_,
                             std::vector<std::vector<std::shared_ptr<Resource>>>& resource_map_,
                             const std::vector<std::shared_ptr<Sprite_Obj>>& tile_vec,
                             const std::vector<std::vector<Biome_enum>>& biome_map,
                             const std::vector<std::vector<std::vector<state>>>& perlins = {{{}}},
                             size_t perlins_pos = 0,
                             const std::vector<std::vector<state>>& river = {{}}) override;
  private:

    Ocean(const Ocean&);
    Ocean& operator= (const Ocean&);

};

#endif
