/**
* @author Rutger Kiele (s2979128)
* @file trick.cc
**/

#include "../include/trick.h"


Trick::Trick(){
    suit = "none";
    manual = false;
}

Trick::~Trick(){
}

Trick::Trick(Player* players[], bool manual){
    for (int i = 0; i < 4; i++){
        this -> players[i] = players[i];
    }
    suit = "none";
    this -> manual = manual;
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
                    mcPlayer -> giveInfo(players);
                } // if player is perfect montecarlo player, give perfect information
                if(dynamic_cast<ManualPlayer*>(players[i])){showPoints();}
                addCard(players[i] -> playCard(suit, trick, playedBy, i));
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
            mcPlayer -> addPlayedCards(trick, playedBy, suit, i);
        }
    }
    calculatePoints(false);
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

void Trick::calculatePoints(bool simulation){
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
    if(manual && !simulation){printTrick(addedPoints);}
    if(addedPoints > 0){
        for (int i = 0; i < 4; i++){
            players[i] -> setPointsPlayed(true);
        }
    }
}

void Trick::showPoints(){
    std::cout << "Current points:" << std::endl;
    std::cout << " Player 0: " << players[0]->getPoints() << " (you)" << std::endl;
    std::cout << " Player 1: " << players[1]->getPoints()  << std::endl;
    std::cout << " Player 2: " << players[2]->getPoints()  << std::endl;
    std::cout << " Player 3: " << players[3]->getPoints()  << std::endl << std::endl;
}

void Trick::printTrick(int addedPoints){
    std::string yourCard;
    std::string player1Card;
    std::string player2Card;
    std::string player3Card;
    for (unsigned i = 0; i < trick.size(); i++) {
        if (playedBy[i] == 1) {
            player1Card = trick[i].getShortName();
        } else if (playedBy[i] == 2) {
            player2Card = trick[i].getShortName();
        } else if (playedBy[i] == 3) {
            player3Card = trick[i].getShortName();
        } else if (playedBy[i] == 0) {
            yourCard = trick[i].getShortName();
        }
    }
    int winner = getWinner();
    std::cout << "The trick is over. ";
    if(winner == 0){
        std::cout << "You";
    }
    else{
        std::cout << "Player " << winner;
    }
    std::cout << " won the trick and got " << addedPoints << " points." << std::endl << std::endl;
    std::cout << "         Player 2" << std::endl;
    std::cout << "            " << player2Card << std::endl;
    std::cout << "Player 1: "<< player1Card << "   " << player3Card << " :Player 3" << std::endl;
    std::cout << "            " << yourCard << std::endl;
    std::cout << "           You" << std::endl << std::endl;
}

void Trick::printPlayedBy(){
    for(unsigned i = 0; i < playedBy.size(); i++){
        std::cout << playedBy[i] << " ";
    }
    std::cout << std::endl;
}
