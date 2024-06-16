/**
* @author Rutger Kiele (s2979128)
* @file deck.h
**/

#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include "card.h"

using namespace std; 

class Deck{
    public:
        Deck();
        void printDeck();
        void shuffle();
        Card draw();
        void removeCard(Card card);
        int getSize();
        void assignPoints();
        std::vector<Card> getCards();
    private:
        std::vector<Card> cards;
        int size;
};

#endif