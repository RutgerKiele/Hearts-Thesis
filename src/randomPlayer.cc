/**
* @author Rutger Kiele (s2979128)
* @file randomPlayer.cc
**/

#include "../include/randomPlayer.h"

RandomPlayer::RandomPlayer(){
}

Card RandomPlayer::playCard(std::string suit){
    int card = pickRandomCard(suit);
    Card cardPlayed = hand[card];
    hand.erase(hand.begin() + card);
    return cardPlayed;
}