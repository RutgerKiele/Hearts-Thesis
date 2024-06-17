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
        virtual ~Player() = default;	// Default destructor
        void addCard(Card card);
        void removeCard(int card);
        void sortHand();
        void printHand();
        void setHand(std::vector<Card> newHand);
        std::vector<Card> getHand() const;
        int getHandSize();
        void addPoints(int points);
        int getPoints() const;
        void resetPoints();
        void addScore(int points);
        int getScore() const;
        void resetScore();
        bool getIsTurn() const;
        void setTurn(bool isTurn);
        void setPointsPlayed(bool pointsPlayed);
        int getPointsPlayed() const;
        bool hasTwoOfClubs();
        bool hasSuit(std::string suit);
        std::vector<int> possibleMoves(std::string suit);
        int pickRandomCard(std::string suit);

        virtual Card playCard(std::string suit) = 0;

    protected:
        int playerID;
        int points;
        int totalScore;
        std::vector<Card> hand;
        bool isTurn;
        bool pointsPlayed;

};

#endif