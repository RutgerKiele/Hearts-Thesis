/**
* @author Rutger Kiele (s2979128)
* @file randomPlayer.h
**/

#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include <cstdlib> // Include the <cstdlib> header for the rand() function
#include <ctime>   // Include the <ctime> header for the time() function
#include <iostream>
#include "player.h"

class RandomPlayer : public Player{
    public:
        RandomPlayer();
    private:
        Card playCard(std::string suit);
};

#endif