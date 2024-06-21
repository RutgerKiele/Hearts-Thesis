/**
* @author Rutger Kiele (s2979128)
* @file manualPlayer.h
**/

#ifndef MANUALPLAYER_H
#define MANUALPLAYER_H

#include <iostream>
#include "player.h"
#include "card.h"

class ManualPlayer : public Player{
    public:
        ManualPlayer(int nPlayers);
        int correctInput(std::string input, std::string suit);
        void fourPlayerHand(std::vector<Card> trick, std::vector<int> playedBy);
        void twoPlayerHand(std::vector<Card> trick, std::vector<int> playedBy);
    private:
        Card playCard(std::string suit, std::vector<Card> trick, std::vector<int> playedBy, int currentPlayer, int nPlayers, int maxPoints);
        int nPlayers;
};

#endif