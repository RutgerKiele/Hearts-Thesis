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
#include "monteCarloPlayerDet.h"
#include "manualPlayer.h"

class Trick{
    public:
        Trick();
        ~Trick();
        Trick(Player* players[], bool manual);
        Trick(std::vector<Card> trick, std::vector<int> playedBy, std::string suit, Player* players[]);
        void addCard(Card card);
        void playTrick();
        int getWinner();
        void calculatePoints(bool simulation);
        void showPoints();
        void printTrick(int addedPoints);
        void printPlayedBy();
    private:
        std::vector<Card> trick;
        std::vector<int> playedBy;
        std::string suit;
        Player* players[4];
        bool manual;
};

#endif