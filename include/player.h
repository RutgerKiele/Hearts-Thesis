/**
* @author Rutger Kiele (s2979128)
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
        void addPoints(int points);
        int getPoints();
        void resetPoints();
        void addScore(int points);
        int getScore();
        bool getIsTurn();
        void setTurn(bool isTurn);
        bool hasTwoOfClubs();
        bool hasSuit(std::string suit);

        virtual Card playCard(std::string suit) = 0;
    protected:
        int points;
        int totalScore;
        std::vector<Card> hand;
        bool isTurn;
    private:

};

#endif