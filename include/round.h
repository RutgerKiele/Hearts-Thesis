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
        Round(Player* players[], Deck deck);
        ~Round();
        void playRound();
    private:
        void playTrick();
        void calculatePoints();
        void printScores();
        void dealCards(Deck deck, Player** players);
        void whoStarts(Player** players);
        int shootTheMoon();
        Player* players[4];
        Deck deck;
};

#endif