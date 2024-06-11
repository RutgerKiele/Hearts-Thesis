/**
* @author Rutger Kiele (s2979128)
* @file randomPlayer.cc
**/

#include "../include/randomPlayer.h"

RandomPlayer::RandomPlayer(){
}

RandomPlayer::RandomPlayer(const Player& other){
    hand = other.hand;
    points = other.points;
    totalScore = other.totalScore;
    pointsPlayed = other.pointsPlayed;
    isTurn = other.isTurn;
}

Card RandomPlayer::playCard(std::string suit){
    int card = pickRandomCard(suit);
    Card cardPlayed = hand[card];
    removeCard(card);
    return cardPlayed;
}