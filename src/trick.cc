/**
* @author Rutger Kiele (s2979128)
* @file trick.cc
**/

#include "../include/trick.h"


Trick::Trick(){
    suit = "none";
}

Trick::~Trick(){
}

Trick::Trick(Player* players[]){
    for (int i = 0; i < 4; i++){
        this -> players[i] = players[i];
    }
    suit = "none";
}

Trick::Trick(std::vector<Card> trick, std::vector<int> playedBy, std::string suit, Player* players[]){
    this -> trick = trick;
    this -> playedBy = playedBy;
    this -> suit = suit;
    for (int i = 0; i < 4; i++){
        this -> players[i] = players[i];
    }
}

void Trick::addCard(Card card){
    trick.push_back(card);
}

void Trick::playTrick(){
    int cardsPlayed = 0;
    while(cardsPlayed < 4){
        for(int i = 0; i < 4; i++){
            if(players[i] -> getIsTurn()){
                if (MonteCarloPlayerPI* mcPlayer = dynamic_cast<MonteCarloPlayerPI*>(players[i])) {
                    mcPlayer -> giveInfo(trick, playedBy, suit, players, i);
                } // if player is perfect montecarlo player, give perfect information
                else if (MonteCarloPlayerDet* mcPlayer = dynamic_cast<MonteCarloPlayerDet*>(players[i])) {
                    mcPlayer -> giveInfo(trick, playedBy, suit, i);
                } // if player is imperfect montecarlo player, give imperfect information
                addCard(players[i] -> playCard(suit));
                playedBy.push_back(i);
                cardsPlayed++;
                players[i] -> setTurn(false);
                if (cardsPlayed == 4){
                    break;
                }
                players[(i + 1) % 4] -> setTurn(true);
                suit = trick[0].getSuit();
            }
        }
    }
    
    // Add played cards to deterministic montecarlo players
    for (int i = 0; i < 4; i++){
        if(MonteCarloPlayerDet* mcPlayer = dynamic_cast<MonteCarloPlayerDet*>(players[i])){
            mcPlayer -> addPlayedCards(trick);
        }
    }
    calculatePoints();
}

int Trick::getWinner(){
    int winner = 0;
    for(unsigned i = 1; i < trick.size(); i++){
        if(trick[i].getSuit() == suit && trick[i].getValue() > trick[winner].getValue()){
            winner = i;
        }
    }
    players[playedBy[winner]] -> setTurn(true);
    return playedBy[winner];
}

void Trick::calculatePoints(){
    int addedPoints = 0;
    for(unsigned i = 0; i < trick.size(); i++){
        if(trick[i].getSuit() == "hearts"){
            addedPoints++;
        }
        // Value of 10 is the Queen of spades
        if(trick[i].getSuit() == "spades" && trick[i].getValue() == 10){
            addedPoints += 13;
        }
    }
    players[getWinner()] -> addPoints(addedPoints);
    if(addedPoints > 0){
        for (int i = 0; i < 4; i++){
            players[i] -> setPointsPlayed(true);
        }
    }
}

void Trick::printTrick(){
    int point = 0;
    for(unsigned i = 0; i < trick.size(); i++){
        trick[i].printCard();
        cout << " / " ;
        point += trick[i].getPoints();
    }
    cout << point << std::endl;
}

void Trick::printPlayedBy(){
    for(unsigned i = 0; i < playedBy.size(); i++){
        cout << playedBy[i] << " ";
    }
    cout << std::endl;
}

