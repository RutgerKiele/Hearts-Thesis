/**
* @author Rutger Kiele (s2979128)
* @file trick.cc
**/

#include "../include/trick.h"


Trick::Trick(){
    suit = "none";
    manual = false;
    maxPoints = 26;
}

Trick::~Trick(){
}

Trick::Trick(std::vector<Player*> players, bool manual, int nPlayers, int maxPoints){
    for (int i = 0; i < nPlayers; i++){
        this -> players.push_back(players[i]);
    }
    suit = "none";
    this -> manual = manual;
    this -> nPlayers = nPlayers;
    this -> maxPoints = maxPoints;
}

Trick::Trick(std::vector<Card> trick, std::vector<int> playedBy, std::string suit, std::vector<Player*> players, int nPlayers){
    this -> trick = trick;
    this -> playedBy = playedBy;
    this -> suit = suit;
    for (int i = 0; i < nPlayers; i++){
        this -> players.push_back(players[i]);
    }
    this -> nPlayers = nPlayers;
}

void Trick::addCard(Card card){
    trick.push_back(card);
}

void Trick::playTrick(){
    int cardsPlayed = 0;
    while(cardsPlayed < nPlayers){
        for(int i = 0; i < nPlayers; i++){
            if(players[i] -> getIsTurn()){
                if (MonteCarloPlayerPI* mcPlayer = dynamic_cast<MonteCarloPlayerPI*>(players[i])) {
                    mcPlayer -> giveInfo(players, nPlayers);
                } // if player is perfect montecarlo player, give perfect information
                if(dynamic_cast<ManualPlayer*>(players[i])){showPoints();}
                addCard(players[i] -> playCard(suit, trick, playedBy, i, nPlayers, maxPoints));
                playedBy.push_back(i);
                cardsPlayed++;
                players[i] -> setTurn(false);
                if (cardsPlayed == nPlayers){
                    break;
                }
                players[(i + 1) % nPlayers] -> setTurn(true);
                suit = trick[0].getSuit();
            }
        }
    }
    
    // Add played cards to deterministic montecarlo players
    for (int i = 0; i < nPlayers; i++){
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
        for (int i = 0; i < nPlayers; i++){
            players[i] -> setPointsPlayed(true);
        }
    }
}

void Trick::showPoints(){
    std::cout << "Current points:" << std::endl;
    for (int i = 0; i < nPlayers; i++){
        std::cout << "Player " << i << ": " << players[i] -> getPoints();
        if (i == 0){ std::cout << " (You)";}
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Trick::printTrick(int addedPoints){
    int winner = getWinner();
    std::cout << "The trick is over. ";
    if(winner == 0){
        std::cout << "You";
    }
    else{
        std::cout << "Player " << winner;
    }
    std::cout << " won the trick and got " << addedPoints << " points." << std::endl << std::endl;
    if (nPlayers == 4){
        printFourCards();
    } else if (nPlayers == 2){
        printTwoCards();
    } else {
        std::cout << "Error: invalid number of players" << std::endl;
    }
}

void Trick::printFourCards(){
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
    std::cout << "         Player 2" << std::endl;
    std::cout << "            " << player2Card << std::endl;
    std::cout << "Player 1: "<< player1Card << "   " << player3Card << " :Player 3" << std::endl;
    std::cout << "            " << yourCard << std::endl;
    std::cout << "           You" << std::endl << std::endl;
}

void Trick::printTwoCards(){
    std::string yourCard;
    std::string player1Card;
    for (unsigned i = 0; i < trick.size(); i++) {
        if (playedBy[i] == 1) {
            player1Card = trick[i].getShortName();
        } else if (playedBy[i] == 0) {
            yourCard = trick[i].getShortName();
        }
    }
    std::cout << "Player 1: " << player1Card << std::endl;
    std::cout << "You: " << yourCard << std::endl << std::endl;
}

void Trick::printPlayedBy(){
    for(unsigned i = 0; i < playedBy.size(); i++){
        std::cout << playedBy[i] << " ";
    }
    std::cout << std::endl;
}
