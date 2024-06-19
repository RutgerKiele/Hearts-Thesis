/**
* @author Rutger Kiele (s2979128)
* @file monteCarloPlayerPI.h
**/

#ifndef MONTECARLOPLAYER_H
#define MONTECARLOPLAYER_H

#include <iostream>
#include "player.h"
#include "randomPlayer.h"
#include "trick.h"

class MonteCarloPlayerPI : public Player{
    public:
        MonteCarloPlayerPI();
        int simulatePI(int move, int currentPoints);

        // Function to give information to the Monte carlo player who has full information
        void giveInfo(std::vector<Player*> players, int nPlayers);
    private:
        Card playCard(std::string suit, std::vector<Card> trick, std::vector<int> playedBy, int currentPlayer, int nPlayers);

        // Information to simulate the game
        std::vector<Card> trick;
        std::vector<int> playedBy;
        std::string suit;
        std::vector<Player*> players;
        int currentPlayer;
        int nPlayers;
};

#endif