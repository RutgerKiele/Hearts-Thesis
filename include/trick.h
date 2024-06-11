/**
* @author Rutger Kiele (s2979128)
* @file trick.h
**/

#ifndef TRICK_H
#define TRICK_H

#include <iostream>
#include <vector>
#include "card.h"
#include "player.h"
#include "monteCarloPlayerPI.h"

class Trick{
    public:
        Trick();
        ~Trick();
        Trick(Player* players[]);
        Trick(std::vector<Card> trick, std::vector<int> playedBy, std::string suit, Player* players[]);
        void addCard(Card card);
        void playTrick();
        int getWinner();
        void calculatePoints();
        void printTrick();
        void printPlayedBy();
    private:
        std::vector<Card> trick;
        std::vector<int> playedBy;
        std::string suit;
        Player* players[4];
};

#endif