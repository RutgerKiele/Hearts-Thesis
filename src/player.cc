/**
* @author Rutger Kiele (s2979128)
* @file player.cc
**/

#include <string>
#include "../include/player.h"

using namespace std;

Player::Player(){
    points = 0;
    totalScore = 0;
    pointsPlayed = false;
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

int Player::getHandSize(){
    return hand.size();
}

void Player::addPoints(int points){
    this->points += points;
}

int Player::getPoints(){
    return points;
}

void Player::resetPoints(){
    points = 0;
}

void Player::addScore(int points){
    totalScore += points;
}

int Player::getScore(){
    return totalScore;
}

void Player::resetScore(){
    totalScore = 0;
}

bool Player::getIsTurn(){
    return isTurn;
}

void Player::setTurn(bool turn){
    isTurn = turn;
}

bool Player::hasTwoOfClubs(){
    if(hand[0].getSuit() == "clubs" && hand[0].getValue() == 0){
        return true;
    }
    return false;
}

void Player::setPointsPlayed(bool pointsPlayed){
    this->pointsPlayed = pointsPlayed;
}

bool Player::hasSuit(std::string suit){
    for(unsigned i = 0; i < hand.size(); i++){
        if(hand[i].getSuit() == suit){
            return true;
        }
    }
    return false;
}

std::vector<int> Player::possibleMoves(std::string suit){
    std::vector<int> moves;
    if(hasTwoOfClubs()){
        moves.push_back(0);
        return moves;
    }
    for(unsigned i = 0; i < hand.size(); i++){
        if(suit == "none"){
            if(pointsPlayed){
                moves.push_back(i);
            }
            else {
                if(hand[i].getPoints() == 0){
                    moves.push_back(i);
                }
            }
                
        }
        else if(!hasSuit(suit)){
            moves.push_back(i);
        }
        else{
            if(hand[i].getSuit() == suit){
                moves.push_back(i);
            }
        }
    }
    if(moves.size() == 0){
        for(unsigned i = 0; i < hand.size(); i++){
            moves.push_back(i);
        }
    }
    return moves;
}


