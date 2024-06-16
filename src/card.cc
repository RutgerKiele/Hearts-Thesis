/**
* @author Rutger Kiele (s2979128)
* @file card.cc
**/

#include <string>
#include "../include/card.h"


using namespace std;

Card::Card(){
    value = Two;
    suit = "clubs";
}

Card::Card(Value value, string suit){
    this->value = value;
    this->suit = suit;
}

int Card::getPoints(){
    return points;
}

void Card::setPoints(int points){
    this->points = points;
}

void Card::printCard(){
    cout << getValueName() << " of " << suit;
    if (points != 0){
        cout << " (" << points << " points)";
    }
    cout << endl;
}

Value Card::getValue(){
    return value;
}

std::string Card::getValueName(){
    switch(value){
        case Two: case Three: case Four: case Five: case Six: case Seven: case Eight: case Nine: case Ten:
            return to_string(value + 2); // +2 because the enum starts at 0
        case Jack:
            return "Jack";
        case Queen:
            return "Queen";
        case King:
            return "King";
        case Ace:
            return "Ace";
        default:
            return "Invalid";
    }
}

string Card::getSuit(){
    return suit;
}

bool Card::sameCard(Card card){
    return value == card.getValue() && suit == card.getSuit();
}