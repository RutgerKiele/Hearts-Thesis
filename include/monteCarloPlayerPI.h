/**
* @author Rutger Kiele (s2979128)
* @file monteCarloPlayer.h
**/

#ifndef MONTECARLOPLAYER_H
#define MONTECARLOPLAYER_H

#include <cstdlib> // Include the <cstdlib> header for the rand() function
#include <ctime>   // Include the <ctime> header for the time() function
#include <iostream>
#include "player.h"

class MonteCarloPlayerPI : public Player{
    public:
        MonteCarloPlayerPI();
    private:
        Card playCard(std::string suit);
};

#endif