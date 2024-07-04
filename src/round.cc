/**
* @author Rutger Kiele (s2979128)
* @file round.cc
**/

#include "../include/round.h"
#include "../include/trick.h"
#include "../include/monteCarloPlayerDet.h" 

Round::Round(){
    manual = false;
    maxPoints = 26;
}

Round::~Round(){
}

Round::Round(std::vector<Player*> players, Deck deck, bool manual, int nPlayers){
    for (int i = 0; i < nPlayers; i++){
        this -> players.push_back(players[i]);
    }
    this -> deck = deck;
    this -> manual = manual;
    this -> nPlayers = nPlayers;
    maxPoints = 26;
}

void Round::playRound(){
    dealCards(deck, players);
    while(players[0] -> getHandSize() > 0){
        Trick trick(players, manual, nPlayers, maxPoints);
        trick.playTrick();
    }
    calculatePoints();
    if(manual){
        printScores();
    }
    for (int i = 0; i < nPlayers; i++){
        if(MonteCarloPlayerDet *p = dynamic_cast<MonteCarloPlayerDet*>(players[i])){
            p -> resetArrays();
        }
        else if(MonteCarloPlayerPI *p = dynamic_cast<MonteCarloPlayerPI*>(players[i])){
            p -> resetPointsPlayedThisRound();
        }
    }
}

void Round::calculatePoints(){
    int allPoints = shootTheMoon();
    // if (allPoints != -1){
    //     std::cout << "Player " << allPoints << " has shot the moon!" << std::endl;
    // }
    if(allPoints == -1){
        for (int i = 0; i < nPlayers; i++){
            players[i] -> addScore(players[i] -> getPoints());
            players[i] -> resetPoints();
        }
    }
    else {
        for (int i = 0; i < nPlayers; i++){
            if(i == allPoints){
                players[i] -> addScore(0);
                players[i] -> resetPoints();
            }
            else{
                players[i] -> addScore(maxPoints);
                players[i] -> resetPoints();
            }
        }
    }
}

void Round::printScores(){
    std::cout << "The round is over. The scores after this round:" << std::endl;
    for(int i = 0; i < nPlayers; i++){
        std::cout << "Player " << i << " now has " << players[i] -> getScore() << " total points" << std::endl;
    }
    std::cout << std::endl << "Next trick:" << std::endl << std::endl;

}

void Round::dealCards(Deck deck, std::vector<Player*> players){
    for(int i = 0; i < nPlayers; i++){
        for(int j = 0; j < 52/nPlayers; j++){
            players[i] -> addCard(deck.draw());
        }
        players[i] -> sortHand();
        if(MonteCarloPlayerDet *p = dynamic_cast<MonteCarloPlayerDet*>(players[i])){
            p -> removeOwnCards();
        }
    }
    for(int i = 0; i < deck.getSize(); i++){
        int points = deck.draw().getPoints();
        if(points > 0){
            maxPoints -= points;
        }
    }
}

int Round::shootTheMoon(){
    for (int i = 0; i < nPlayers; i++){
        if(players[i] -> getPoints() == maxPoints){
            return i;
        }
    }
    return -1;
}
