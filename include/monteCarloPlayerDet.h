/**
* @author Rutger Kiele (s2979128)
* @file monteCarloPlayerDet.h
**/

#ifndef MONTECARLOPLAYERDET_H
#define MONTECARLOPLAYERDET_H

#include <iostream>
#include "player.h"
#include "randomPlayer.h"

class MonteCarloPlayerDet : public Player{
    public:
        MonteCarloPlayerDet();
        int simulateDet(int move, int currentPoints);

        // Function to give information to the Monte carlo player whithout perfect information. so the hands of the other players are not known
        void giveInfo(std::vector<Card> trick, std::vector<int> playedBy, std::string suit, int currentPlayer);
    private:
        Card playCard(std::string suit);

        // Information to simulate the game
        std::vector<Card> trick;
        std::vector<int> playedBy;
        std::string suit;
        int currentPlayer;
};

#endif