/**
* @author Rutger Kiele (s2979128)
* @file round.cc
**/

#include "../include/round.h"
#include "../include/trick.h"
#include "../include/monteCarloPlayerDet.h" 

Round::Round(){
    manual = false;
}

Round::~Round(){
}

Round::Round(Player* players[], Deck deck, bool manual){
    for (int i = 0; i < 4; i++){
        this -> players[i] = players[i];
    }
    this -> deck = deck;
    this -> manual = manual;
}

void Round::playRound(){
    dealCards(deck, players);
    while(players[0] -> getHandSize() > 0){
        Trick trick(players, manual);
        trick.playTrick();
    }
    calculatePoints();
    if(manual){
        printScores();
    }
    for (int i = 0; i < 4; i++){
        if(MonteCarloPlayerDet *p = dynamic_cast<MonteCarloPlayerDet*>(players[i])){
            p -> resetArrays();
        }
    }
}

void Round::calculatePoints(){
    int allPoints = shootTheMoon();
    if(allPoints == -1){
        for (int i = 0; i < 4; i++){
            players[i] -> addScore(players[i] -> getPoints());
            players[i] -> resetPoints();
        }
    }
    else {
        for (int i = 0; i < 4; i++){
            if(i == allPoints){
                players[i] -> addScore(0);
                players[i] -> resetPoints();
            }
            else{
                players[i] -> addScore(26);
                players[i] -> resetPoints();
            }
        }
    }
}

void Round::printScores(){
    std::cout << "The round is over. The scores after this round:" << std::endl;
    for(int i = 0; i < 4; i++){
        std::cout << "Player " << i << " now has " << players[i] -> getScore() << " total points" << std::endl;
    }
    std::cout << std::endl << "Next trick:" << std::endl << std::endl;

}

void Round::dealCards(Deck deck, Player** players){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            players[i] -> addCard(deck.draw());
        }
        players[i] -> sortHand();
        if(MonteCarloPlayerDet *p = dynamic_cast<MonteCarloPlayerDet*>(players[i])){
            p -> removeOwnCards();
        }
    }
}

int Round::shootTheMoon(){
    for (int i = 0; i < 4; i++){
        if(players[i] -> getPoints() == 26){
            return i;
        }
    }
    return -1;
}
