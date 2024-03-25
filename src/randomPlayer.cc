/**
* @author Rutger (s2979128)
* @file randomPlayer.cc
**/

#include "../include/randomPlayer.h"

RandomPlayer::RandomPlayer(){
}

Card RandomPlayer::playCard(std::string suit){
    int card = rand() % hand.size();
    Card cardPlayed = hand[card];
    cardPlayed.printCard();
    cout << endl;
    hand.erase(hand.begin() + card);
    return cardPlayed;
}