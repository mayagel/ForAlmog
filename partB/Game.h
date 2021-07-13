#ifndef GAME_H_
#define GAME_H_
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Character.h"
#include "Exceptions.h"
#include "Auxiliaries.h"
#include "Medic.h"
#include "Soldier.h"
#include "Sniper.h"

namespace mtm
{
    class Game
    {
    private:
        int height;
        int width;
        std::vector<std::vector<std::shared_ptr<Character>>> board;

    public:
        Game(int height, int width);                                                           //constructor
        Game(const Game &other);                                                               //copy constructor
        Game &operator=(const Game &other);                                                    //copy assignment
        void addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character); //Add Character
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                        units_t health, units_t ammo, units_t range, units_t power);
        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
        void attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
        void reload(const GridPoint &coordinates);
        std::ostream &printGameBoard(std::ostream &os, const char *begin,
                                     const char *end, unsigned int width) const;
        bool isOver(Team *winningTeam = NULL) const;
        friend std::ostream &operator<<(std::ostream &os, const Game &game); // operator <<
        ~Game();
    };
}
#endif
