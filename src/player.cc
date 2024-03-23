/**
* @author Rutger (s2979128)
* @file player.cc
**/

#include <string>
#include "../include/player.h"

using namespace std;

Player::Player(){
    points = 0;
}

void Player::addCard(Card card){
    hand.push_back(card);
}

void Player::sortHand(){
    for(unsigned i = 0; i < hand.size(); i++){
        for(unsigned j = 0; j < hand.size(); j++){
            if(hand[i].getSuit() < hand[j].getSuit()){
                Card temp = hand[i];
                hand[i] = hand[j];
                hand[j] = temp;
            }
            else if(hand[i].getSuit() == hand[j].getSuit() && hand[i].getValue() < hand[j].getValue()){
                Card temp = hand[i];
                hand[i] = hand[j];
                hand[j] = temp;
            }
        }
    }
}

void Player::printHand(){
    for(unsigned i = 0; i < hand.size(); i++){
        hand[i].printCard();
        cout << endl;
    }
}

void Player::setPoints(int points){
    this->points = points;
}

int Player::getPoints(){
    return points;
}


