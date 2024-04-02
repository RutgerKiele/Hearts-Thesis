/**
* @author Rutger Kiele (s2979128)
* @file deck.h
**/

#ifndef DECK_H
#define DECK_H

#include <iostream>
#include "card.h"

using namespace std; 

class Deck{
    public:
        Deck();
        void printDeck();
        void shuffle();
        Card draw();
        int getSize();
        void assignPoints();
    private:
        Card cards[52];
        int size;
};

#endif