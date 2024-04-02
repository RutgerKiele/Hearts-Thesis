/**
* @author Rutger Kiele (s2979128)
* @file card.h
**/

#ifndef CARD_H
#define CARD_H

#include <iostream>

enum Value {Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace};

class Card{
    public:
        Card();
        Card(Value value, std::string suit);
        void printCard();
        int getPoints();
        void setPoints(int points);
        Value getValue();
        std::string getSuit();
        std::string getValueName();

    private:
        Value value;
        std::string suit;
        int points = 0;

};

#endif