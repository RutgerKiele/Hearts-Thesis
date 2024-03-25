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
        int getHandSize();
        void setPoints(int points);
        int getPoints();
        bool getIsTurn();
        void setTurn(bool isTurn);
        bool hasTwoOfClubs();

        virtual Card playCard(std::string suit) = 0;
    protected:
        int points;
        std::vector<Card> hand;
        bool isTurn;
    private:

};

#endif