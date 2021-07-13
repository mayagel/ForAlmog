
#include "Medic.h"
using std::vector;
using std::shared_ptr;

namespace mtm
{
    Medic::Medic(int health, int ammo, int range, int power, Team team) : Character(health, ammo, range, power, team) {} //constructor
    Medic::Medic(const Medic &copy_from) : Character(copy_from) {}                                                       //copy constructor

    Medic &Medic::operator=(const Medic &copy_from)
    {
        Character::operator=(copy_from);
        return *this;
    }

    std::shared_ptr<Character> Medic::clone() const
    {
        shared_ptr<Character> ptr(new Medic(*this));
        return ptr;
    }

    //geters
    int Medic::getMovmentRange() const
    {
        return movment_range;
    }
    int Medic::getAttackAmmoCost() const
    {
        return attack_ammo_cost;
    }

    void Medic::characterAttack(const GridPoint &src_coordinates,
                                const GridPoint &dst_coordinates,
                                vector<vector<std::shared_ptr<Character>>> board,
                                int height, int width)
    {
        if (board[src_coordinates.row][src_coordinates.col]->getRange() < mtm::GridPoint::distance(src_coordinates, dst_coordinates))
        {
            throw OutOfRange();
        }
        if (ammo < attack_ammo_cost)
        {
            throw OutOfAmmo();
        }
        if ((src_coordinates == dst_coordinates) || (board[dst_coordinates.row][dst_coordinates.col] == nullptr))
        {
            throw IllegalTarget();
        }
        if (board[dst_coordinates.row][dst_coordinates.col]->getTeam() != this->getTeam())
        {
            board[dst_coordinates.row][dst_coordinates.col]->setHealth(-power);
            ammo--;
        }
        else
        {
            board[dst_coordinates.row][dst_coordinates.col]->setHealth(power);
        }
    }

    void Medic::characterReload(const GridPoint &coordinates)
    {
        ammo = ammo + load_ammo;
    }
    char Medic::getChar()
    {
        return 'm';
    }
    Medic::~Medic()
    {
    }

}
