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

        // Functions to determine hands
        std::vector<std::vector<Card>> generatePossibleHands(Deck cardsInGame);
        void removeOwnCards();
        void addPlayedCards(std::vector<Card> cards, std::vector<int> playedBy, std::string suit, int thisPlayer);
        void resetArrays();
    private:
        Card playCard(std::string suit, std::vector<Card> trick, std::vector<int> playedBy, int currentPlayer, int nPlayers);

        // Information to simulate the game
        std::vector<Card> trick;
        std::vector<int> playedBy;
        std::string suit;
        int currentPlayer;
        int nPlayers;

        // Information to determine hands
        Deck cardsInGame;
        std::vector<Card> playedCards;
        std::vector<std::unordered_set<std::string>> cannotHaveSuit;

};

#endif