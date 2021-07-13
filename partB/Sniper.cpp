#include "Sniper.h"

using std::vector;
using std::shared_ptr;

namespace mtm
{
    Sniper::Sniper(int health, int ammo, int range, int power, Team team) : Character(health, ammo, range, power, team), attack_counter(1) {} //constructor

    Sniper::Sniper(const Sniper &copy_from) : Character(copy_from) {} //copy constructor

    Sniper &Sniper::operator=(const Sniper &copy_from)
    {
        Character::operator=(copy_from);
        return *this;
    }

    shared_ptr<Character> Sniper::clone() const
    {
        shared_ptr<Character> ptr(new Sniper(*this));
        return ptr;
    }

    //geters
    int Sniper::getMovmentRange() const
    {
        return movment_range;
    }
    int Sniper::getAttackAmmoCost() const
    {
        return attack_ammo_cost;
    }
    void Sniper::characterAttack(const GridPoint &src_coordinates,
                                 const GridPoint &dst_coordinates,
                                 vector<vector<std::shared_ptr<Character>>> board,
                                 int height, int width)
    {
        if (board[src_coordinates.row][src_coordinates.col]->getRange() < mtm::GridPoint::distance(src_coordinates, dst_coordinates))
        {
            throw OutOfRange();
        }
        if (((board[src_coordinates.row][src_coordinates.col]->getRange() + 1) / 2) > mtm::GridPoint::distance(src_coordinates, dst_coordinates))
        {
            throw OutOfRange();
        }
        if (ammo < attack_ammo_cost)
        {
            throw OutOfAmmo();
        }
        if (board[dst_coordinates.row][dst_coordinates.col] == nullptr)
        {
            throw IllegalTarget();
        }
        else if (board[dst_coordinates.row][dst_coordinates.col]->getTeam() == this->getTeam())
        {
            throw IllegalTarget();
        }
        if (board[dst_coordinates.row][dst_coordinates.col]->getTeam() != this->getTeam())
        {
            if (this->attack_counter == 3)
            {
                board[dst_coordinates.row][dst_coordinates.col]->setHealth(-(power * 2));
                this->attack_counter = 1;
            }
            else
            {
                board[dst_coordinates.row][dst_coordinates.col]->setHealth(-power);
                this->attack_counter++;
            }
            // if (board[dst_coordinates.row][dst_coordinates.col]->getHealth() <= 0)
            // {
            //     board[dst_coordinates.row][dst_coordinates.col] = nullptr;
            // }
            ammo--;
        }
    }
    void Sniper::characterReload(const GridPoint &coordinates)
    {
        ammo = ammo + load_ammo;
    }
    char Sniper::getChar()
    {
        return 'n';
    }
    Sniper::~Sniper()
    {
    }

}