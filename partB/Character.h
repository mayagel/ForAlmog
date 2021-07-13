#ifndef CHARACTER_H_
#define CHARACTER_H_
#include <iostream>
#include "Auxiliaries.h"
#include <memory>
#include <vector>

namespace mtm
{
    class Character
    {
    protected:
        int health;
        int ammo;
        int range;
        int power;
        Team team;

    public:
        Character(int health, int ammo, int range, int power, Team team); //constructor
        Character(const Character &copy_from);                            //copy constructor                                                                                                                      //copy constructor
        int getHealth() const;                                            //accessor function
        int getAmmo() const;                                              //accessor function
        int getRange() const;                                             //accessor function
        int getPower() const;                                             //accessor function
        Team getTeam() const;                                             //accessor function
        void setHealth(int health);                                       //accessor function
        void setAmmo(int ammo);                                           //accessor function
        virtual std::shared_ptr<Character> clone() const = 0;                  //virtual clone
        virtual void characterAttack(const GridPoint &src_coordinates,
                                     const GridPoint &dst_coordinates,
                                     std::vector<std::vector<std::shared_ptr<Character>>> board,
                                     int height, int width) = 0;        //virtual attack
        virtual void characterReload(const GridPoint &coordinates) = 0; //virtual reload
        virtual int getMovmentRange() const = 0;                        //virtual accessor function
        virtual int getAttackAmmoCost() const = 0;                      //virtual accessor function
        virtual char getChar() = 0;                                     // return the chae of the character
        virtual ~Character();                                           //virtual destructor
    };
}
#endif
