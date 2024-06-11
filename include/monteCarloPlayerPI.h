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
#include "trick.h"

class MonteCarloPlayerPI : public Player{
    public:
        MonteCarloPlayerPI();
        int simulatePI(int move);

        // Function to give information to the Monte carlo player who has full information
        void giveInfo(std::vector<Card> trick, std::vector<int> playedBy, std::string suit, Player* players[]);
    private:
        Card playCard(std::string suit);

        // Information to simulate the game
        std::vector<Card> trick;
        std::vector<int> playedBy;
        std::string suit;
        Player* players[4];
};

#endif