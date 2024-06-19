/**
* @author Rutger Kiele (s2979128)
* @file round.h
**/

#ifndef ROUND_H
#define ROUND_H

#include <iostream>
#include "deck.h"
#include "player.h"

class Round{
    public:
        Round();
        Round(std::vector<Player*> players, Deck deck, bool manual, int nPlayers);
        ~Round();
        void playRound();
    private:
        void calculatePoints();
        void printScores();
        void dealCards(Deck deck, std::vector<Player*> players);
        int shootTheMoon();
        Deck deck;
        bool manual;
        int nPlayers;
        std::vector<Player*> players;
};

#endif