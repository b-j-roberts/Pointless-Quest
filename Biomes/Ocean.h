#ifndef __OCEAN_H_INCLUDED__
#define __OCEAN_H_INCLUDED__

// This is blank for now because I dont have any ocean resources!!

class Ocean : public Biome {

  public:

    Ocean() { }

    void get_Resources(const std::vector<std::vector<std::vector<state>>>&, size_t,
                       const std::vector<std::vector<Biome_enum>>&, 
                       const std::vector<std::shared_ptr<Sprite_Obj>>&,
                       std::vector<std::vector<std::shared_ptr<Tile>>>&,
                       const std::vector<std::vector<state>>&,
                       std::vector<std::vector<std::shared_ptr<Resource>>>&) override;

  private:

    Ocean(const Ocean&);
    Ocean& operator= (const Ocean&);

};

#endif
