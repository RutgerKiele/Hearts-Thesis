/**
* @author Rutger Kiele (s2979128)
* @file monteCarloPlayerDet.h
**/

#ifndef MONTECARLOPLAYERDET_H
#define MONTECARLOPLAYERDET_H

#include <iostream>
#include <unordered_set>
#include "player.h"
#include "randomPlayer.h"
#include "deck.h"

class MonteCarloPlayerDet : public Player{
    public:
        MonteCarloPlayerDet();
        int simulateDet(int move, int currentPoints);

        // Function to give information to the Monte carlo player whithout perfect information. so the hands of the other players are not known
        void giveInfo(std::vector<Card> trick, std::vector<int> playedBy, std::string suit, int currentPlayer);

        // Functions to determine hands
        std::vector<std::vector<Card>> generatePossibleHands(Deck cardsInGame);
        void removeOwnCards();
        void addPlayedCards(std::vector<Card> cards);
        void resetArrays();
    private:
        Card playCard(std::string suit);

        // Information to simulate the game
        std::vector<Card> trick;
        std::vector<int> playedBy;
        std::string suit;
        int currentPlayer;

        // Information to determine hands
        Deck cardsInGame;
        std::vector<Card> playedCards;
        std::vector<std::unordered_set<std::string>> cannotHaveSuit;

};

#endif