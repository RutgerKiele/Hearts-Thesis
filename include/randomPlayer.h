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
#include "monteCarloPlayerPI.h"

class RandomPlayer : public Player{
    public:
        RandomPlayer();
        RandomPlayer(const Player& other);
    private:
        Card playCard(std::string suit, std::vector<Card> trick, std::vector<int> playedBy, int currentPlayer, int nPlayers, int maxPoints);
};

#endif