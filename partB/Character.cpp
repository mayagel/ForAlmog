#include "Character.h"

using std::shared_ptr;
using std::vector;

namespace mtm
{

Character::Character(int health, int ammo, int range, int power, Team team) : health(health),
                                                                              ammo(ammo),
                                                                              range(range),
                                                                              power(power),
                                                                              team(team) {} //constractor
Character::Character(const Character &copy_from) : health(copy_from.health),
                                                   ammo(copy_from.ammo),
                                                   range(copy_from.range),
                                                   power(copy_from.power),
                                                   team(copy_from.team) {} //copy constractor
//geters
int Character::getHealth() const
{
    return this->health;
}
int Character::getAmmo() const
{
    return this->ammo;
}
int Character::getRange() const
{
    return this->range;
}
int Character::getPower() const
{
    return this->power;
}
Team Character::getTeam() const
{
    return this->team;
}
//seters
void Character::setHealth(int health)
{
    this->health = this->health + health;
}
void Character::setAmmo(int ammo)
{
    this->ammo = this->ammo + ammo;
}

Character::~Character()
{
}

}