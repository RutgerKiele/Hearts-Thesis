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
        void removeCard(int card);
        void sortHand();
        void printHand();
        int getHandSize();
        void addPoints(int points);
        int getPoints();
        void resetPoints();
        void addScore(int points);
        int getScore();
        void resetScore();
        bool getIsTurn();
        void setTurn(bool isTurn);
        void setPointsPlayed(bool pointsPlayed);
        bool hasTwoOfClubs();
        bool hasSuit(std::string suit);
        std::vector<int> possibleMoves(std::string suit);
        int pickRandomCard(std::string suit);

        virtual Card playCard(std::string suit) = 0;

        //TODO: protected hier en getters voor waardes
        int points;
        int totalScore;
        std::vector<Card> hand;
        bool isTurn;
        bool pointsPlayed;
    private:

};

#endif