#ifndef MEDIC_H_
#define MEDIC_H_
#include "Character.h"
#include "Exceptions.h"
#include "Auxiliaries.h"
#include <memory>
#include <vector>

namespace mtm
{
    class Medic : public Character
    {
    private:
        const int movment_range = 5;
        const int load_ammo = 5;
        const int attack_ammo_cost = 1;

    public:
        Medic(int health, int ammo, int range, int power, Team team); //constructor
        Medic(const Medic &copy_from);                                //copy constructor
        Medic &operator=(const Medic &copy_from);                     //copy assignment
        std::shared_ptr<Character> clone() const override;            // virtual clone
        void characterAttack(const GridPoint &src_coordinates,
                             const GridPoint &dst_coordinates,
                             std::vector<std::vector<std::shared_ptr<Character>>> board,
                             int height, int width) override;        //attack
        void characterReload(const GridPoint &coordinates) override; //virtual reload
        int getMovmentRange() const override;                                 // accessor function
        int getAttackAmmoCost() const override;                               // accessor function
        char getChar() override;                                     // virtual get char
        ~Medic() override;
    };
}
#endif
