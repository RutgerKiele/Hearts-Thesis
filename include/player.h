/**
* @author Rutger (s2979128)
* @file player.h
**/

#ifndef player_H
#define player_H

#include <iostream>
#include "card.h"
#include <vector>

using namespace std;

class Player{
    public:
        Player();
        void addCard(Card card);
        void sortHand();
        void printHand();
        void setPoints(int points);
        int getPoints();
    protected:
        int points;
        std::vector<Card> hand;
    private:
        virtual void playCard() = 0;

};

#endif