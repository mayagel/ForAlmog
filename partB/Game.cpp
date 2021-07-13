#include "Game.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;

namespace mtm
{
    //constructor
    Game::Game(int height, int width)
    {
        if (height <= 0 || width <= 0)
        {
            throw mtm::IllegalArgument();
        }
        vector<vector<std::shared_ptr<Character>>> board(height, vector<std::shared_ptr<Character>>(width /*,initionlazation*/));
        this->board = board;
        this->height = height;
        this->width = width;
    }
    //copy constructor
    Game::Game(const Game &other)
    {
        board.resize(other.height);
        for (int i = 0; i < other.height; i++)
        {
            board[i].resize(other.width);
        }
        //this->board = other.board;
        for (int i = 0; i < other.height; i++)
        {
            for (int j = 0; j < other.width; j++)
            {
                if (other.board[i][j] != nullptr)
                {
                    board[i][j] = other.board[i][j]->clone();
                }
            }
        }
        this->height = other.height;
        this->width = other.width;
    }
    //copy assignment
    Game &Game::operator=(const Game &other)
    {
        /*if(this->board == other.board) //need == to character
    {
        return *this;
    }
    */
        // maby need to delet
        for (int i = 0; i < other.height; i++)
        {
            for (int j = 0; j < other.width; j++)
            {
                if (other.board[i][j] != nullptr)
                {
                    board[i][j] = other.board[i][j]->clone();
                }
            }
        }
        this->height = other.height;
        this->width = other.width;
        return *this;
    }

    void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character)
    {
        if (character == nullptr)
        {
            return;
        }
        if (coordinates.row > height || coordinates.col > width || coordinates.row < 0 || coordinates.col < 0)
        {
            throw mtm::IllegalCell();
        }
        if (board[coordinates.row][coordinates.col] != nullptr)
        {
            throw mtm::CellOccupied();
        }
        this->board[coordinates.row][coordinates.col] = character;
    }
    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team,
                                                   units_t health, units_t ammo, units_t range, units_t power)
    {
        if (health <= 0 || ammo < 0 || power < 0 || range <= 0)
        {
            throw mtm::IllegalArgument();
        }
        if (type == SOLDIER)
        {
            std::shared_ptr<Character> ptr(new Soldier(health, ammo, range, power, team));
            return ptr;
        }
        if (type == SNIPER)
        {
            std::shared_ptr<Character> ptr(new Sniper(health, ammo, range, power, team));
            return ptr;
        }

        std::shared_ptr<Character> ptr(new Medic(health, ammo, range, power, team));
        return ptr;
    }

    void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {

        if (src_coordinates.col < 0 || src_coordinates.row < 0 || dst_coordinates.col < 0 || dst_coordinates.row < 0 ||
            src_coordinates.col >= this->width || src_coordinates.row >= this->height || dst_coordinates.col >= this->width || dst_coordinates.row >= this->height)
        {
            throw mtm::IllegalCell();
        }
        if (this->board[src_coordinates.row][src_coordinates.col] == nullptr)
        {
            throw mtm::CellEmpty();
        }
        if (this->board[src_coordinates.row][src_coordinates.col]->getMovmentRange() < mtm::GridPoint::distance(src_coordinates, dst_coordinates))
        {
            throw mtm::MoveTooFar();
        }
        if (this->board[dst_coordinates.row][dst_coordinates.col] != nullptr)
        {
            throw mtm::CellOccupied();
        }
        board[dst_coordinates.row][dst_coordinates.col] = board[src_coordinates.row][src_coordinates.col];
        board[src_coordinates.row][src_coordinates.col] = nullptr;
    }

    void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        if (src_coordinates.col < 0 || src_coordinates.row < 0 || dst_coordinates.col < 0 || dst_coordinates.row < 0 ||
            src_coordinates.col >= this->width || src_coordinates.row >= this->height || dst_coordinates.col >= this->width || dst_coordinates.row >= this->height)
        {
            throw IllegalCell();
        }
        if (this->board[src_coordinates.row][src_coordinates.col] == nullptr)
        {
            throw CellEmpty();
        }

        this->board[src_coordinates.row][src_coordinates.col]->characterAttack(src_coordinates, dst_coordinates, board, height, width);
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (board[i][j] != nullptr)
                {
                    if (board[i][j]->getHealth() <= 0)
                    {
                        //out << i << j << endl;
                        this->board[i][j] = nullptr;
                    }
                }
            }
        }
    }

    //reload
    void Game::reload(const GridPoint &coordinates)
    {
        if (coordinates.row > height || coordinates.col > width || coordinates.row < 0 || coordinates.col < 0)
        {
            throw mtm::IllegalCell();
        }
        if (this->board[coordinates.row][coordinates.col] == nullptr)
        {
            throw mtm::CellEmpty();
        }
        board[coordinates.row][coordinates.col]->characterReload(coordinates);
    }

    bool Game::isOver(Team *winningTeam) const
    {
        bool powerlifters_left = false, crossfitters_left = false;
        for (int i = 0; i != height; ++i)
        {
            for (int j = 0; j != width; ++j)
            {
                if (board[i][j])
                {
                    if (board[i][j]->getTeam() == POWERLIFTERS)
                    {
                        powerlifters_left = true;
                        continue;
                    }
                    crossfitters_left = true;
                }
            }
        }
        if ((crossfitters_left && powerlifters_left) || (!crossfitters_left && !powerlifters_left))
        {
            return false;
        }
        if (powerlifters_left)
        {
            if (winningTeam)
            {
                *winningTeam = POWERLIFTERS;
            }
            return true;
        }
        if (winningTeam)
        {
            *winningTeam = CROSSFITTERS;
        }
        return true;
    }

    std::ostream &operator<<(std::ostream &os, const Game &game)
    {
        string board_formation;
        for (int i = 0; i < game.height; i++)
        {
            for (int j = 0; j < game.width; j++)
            {
                if (game.board[i][j] != nullptr)
                {
                    if (game.board[i][j]->getTeam() == CROSSFITTERS)
                    {
                        board_formation += game.board[i][j]->getChar();
                        continue;
                    }
                    board_formation += (game.board[i][j]->getChar() + ('A' - 'a'));
                    continue;
                }
                board_formation += ' ';
            }
        }
        const char *begin = board_formation.cbegin().base();
        const char *end_string = board_formation.cend().base();

        // const char *begin = board_formation.c_str();
        // const char *end_string = begin + board_formation.size();
        return printGameBoard(os, begin, end_string, (unsigned int)game.width);
    }

    Game::~Game()
    {
    }

} // namespace mtm
