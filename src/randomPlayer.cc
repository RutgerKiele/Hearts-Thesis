/**
* @author Rutger Kiele (s2979128)
* @file randomPlayer.cc
**/

#include "../include/randomPlayer.h"

RandomPlayer::RandomPlayer(){
}

Card RandomPlayer::playCard(std::string suit){
    srand(time(0));
    std::vector<int> moves = possibleMoves(suit);
    int card = rand() % moves.size();
    Card cardPlayed = hand[card];
    hand.erase(hand.begin() + card);
    return cardPlayed;
}