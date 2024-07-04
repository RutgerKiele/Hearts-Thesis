/**
* @author Rutger Kiele (s2979128)
* @file monteCarloPlayerPI.h
**/

#ifndef MONTECARLOPLAYER_H
#define MONTECARLOPLAYER_H

#include <iostream>
#include "player.h"
#include "randomPlayer.h"
#include "trick.h"

class MonteCarloPlayerPI : public Player{
    public:
        MonteCarloPlayerPI();
        MonteCarloPlayerPI(int numSims, int additionalTricks, bool allPoints);
        int simulatePI(int move, int currentPoints);

        // Function to give information to the Monte carlo player who has full information
        void giveInfo(std::vector<Player*> players, int nPlayers);
        void addPointsPlayedThisRound(int points);
        void resetPointsPlayedThisRound();
    private:
        Card playCard(std::string suit, std::vector<Card> trick, std::vector<int> playedBy, int currentPlayer, int nPlayers, int maxPoints);

        // Should the player go for all points
        bool allPoints;
        bool goForAllPoints();

        // Information to simulate the game
        std::vector<Card> trick;
        std::vector<int> playedBy;
        std::string suit;
        std::vector<Player*> players;
        int currentPlayer;
        int nPlayers;
        int maxPoints;
        int pointsPlayedThisRound;
        int numSims;
        int additionalTricks;
};

#endif