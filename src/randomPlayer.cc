/**
* @author Rutger Kiele (s2979128)
* @file randomPlayer.cc
**/

#include "../include/randomPlayer.h"

RandomPlayer::RandomPlayer(){
}

RandomPlayer::RandomPlayer(const Player& other){
    hand = other.getHand();
    points = other.getPoints();
    totalScore = other.getScore();
    pointsPlayed = other.getPointsPlayed();
    isTurn = other.getIsTurn();
}

Card RandomPlayer::playCard(std::string suit, std::vector<Card> /*trick*/, std::vector<int> /*playedBy*/, int /*currentPlayer*/, int /*nPlayers*/){
    int card = pickRandomCard(suit);
    Card cardPlayed = hand[card];
    removeCard(card);
    return cardPlayed;
}