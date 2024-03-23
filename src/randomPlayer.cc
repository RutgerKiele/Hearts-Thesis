/**
* @author Rutger (s2979128)
* @file randomPlayer.cc
**/

#include "../include/randomPlayer.h"

RandomPlayer::RandomPlayer(){
}

void RandomPlayer::playCard(){
    int card = rand() % hand.size();
    hand[card].printCard();
    cout << endl;
    hand.erase(hand.begin() + card);
}