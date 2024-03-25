/**
* @author Rutger (s2979128)
* @file trick.cc
**/

#include "../include/trick.h"


Trick::Trick(){
    suit = "none";
}

Trick::Trick(Player* players[]){
    for (int i = 0; i < 4; i++){
        this -> players[i] = players[i];
    }
    suit = "none";
}

void Trick::addCard(Card card){
    trick.push_back(card);
}

void Trick::playTrick(){
    int cardsPlayed = 0;
    while(cardsPlayed < 4){
        for(int i = 0; i < 4; i++){
            if(players[i] -> getIsTurn()){
                addCard(players[i] -> playCard(suit));
                cout << "test1" << std::endl;
                playedBy.push_back(i);
                cardsPlayed++;
                players[i] -> setTurn(false);
                if (cardsPlayed == 4){
                    break;
                }
                if(i == 3){
                    players[0] -> setTurn(true);
                }
                else{
                    players[i + 1] -> setTurn(true);
                }
                suit = trick[0].getSuit();
            }
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
    int points = 0;
    for(unsigned i = 0; i < trick.size(); i++){
        if(trick[i].getSuit() == "hearts"){
            points++;
        }
        // Value of 10 is the Queen of spades
        if(trick[i].getSuit() == "spades" && trick[i].getValue() == 10){
            points += 13;
        }
    }
    players[getWinner()] -> setPoints(points);
}

void Trick::printTrick(){
    for(unsigned i = 0; i < trick.size(); i++){
        trick[i].printCard();
        cout << " / " ;
    }
    cout << std::endl;
}

void Trick::printPlayedBy(){
    for(unsigned i = 0; i < playedBy.size(); i++){
        cout << playedBy[i] << " ";
    }
    cout << std::endl;
}
