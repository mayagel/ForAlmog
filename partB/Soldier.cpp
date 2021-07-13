#include "Soldier.h"

using std::vector;
using std::shared_ptr;

namespace mtm
{
    Soldier::Soldier(int health, int ammo, int range, int power, Team team) : Character(health, ammo, range, power, team) {} //constructor

    Soldier::Soldier(const Soldier &copy_from) : Character(copy_from) {} //copy constructor

    Soldier &Soldier::operator=(const Soldier &copy_from)
    {
        Character::operator=(copy_from);
        return *this;
    }

    shared_ptr<Character> Soldier::clone() const
    {
        shared_ptr<Character> ptr(new Soldier(*this));
        return ptr;
    }

    //geters
    int Soldier::getMovmentRange() const
    {
        return movment_range;
    }
    int Soldier::getAttackAmmoCost() const
    {
        return attack_ammo_cost;
    }
    void Soldier::characterAttack(const GridPoint &src_coordinates,
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
        if ((src_coordinates.row != dst_coordinates.row) && (src_coordinates.col != dst_coordinates.col))
        {
            throw IllegalTarget();
        }

        if (board[dst_coordinates.row][dst_coordinates.col] != nullptr && this != nullptr)
        {
            if (board[dst_coordinates.row][dst_coordinates.col]->getTeam() != this->getTeam())
            {
                board[dst_coordinates.row][dst_coordinates.col]->setHealth(-power);
            }
        }
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (board[i][j] != nullptr)
                {
                    shared_ptr<GridPoint> ptr(new mtm::GridPoint(i, j));
                    if (mtm::GridPoint::distance(dst_coordinates, *ptr) <= (range + 2) / 3)
                    {
                        if (dst_coordinates.row != i || dst_coordinates.col != j)
                        {
                            if (board[i][j]->getTeam() != this->getTeam())
                            {
                                board[i][j]->setHealth(-((power + 1) / 2));
                            }
                        }
                    }
                }
            }
        }
        ammo--;
    }
    void Soldier::characterReload(const GridPoint &coordinates)
    {
        ammo = ammo + load_ammo;
    }
    char Soldier::getChar()
    {
        return 's';
    }
    Soldier::~Soldier()
    {
    }

} //namespace mtm