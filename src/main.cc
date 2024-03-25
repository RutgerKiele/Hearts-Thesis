/**
* @author Rutger (s2979128)
* @file main.cc
**/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../include/randomPlayer.h"
#include "../include/player.h"
#include "../include/deck.h"
#include "../include/card.h"
#include "../include/trick.h"

using namespace std;

void whoStarts(Player** players){
    for(int i = 0; i < 4; i++){
        if(players[i] -> hasTwoOfClubs()){
            players[i] -> setTurn(true);
        }
    }
}

void dealCards(Deck deck, Player** players){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            players[i] -> addCard(deck.draw());
        }
        players[i] -> sortHand();
    }
    whoStarts(players);
}

bool gameDone(Player** players){
    for(int i = 0; i < 4; i++){
        if(players[i] -> getPoints() >= 100){
            return true;
        }
    }
    return false;
}

int main(){
    Deck deck;
    Player* players[4];
    for(int i = 0; i < 4; i++){
        players[i] = new RandomPlayer();
    }
    // TODO: punten bij spelers optellen per spelronde
    //while(!gameDone(players)){
        dealCards(deck, players);
        int counter = 0;
        while(players[0] -> getHandSize() > 0){
            Trick trick(players);
            trick.playTrick();
            counter++;
            for(int i = 0; i < 4; i++){
                std::cout << "Player " << i << " has " << players[i] -> getPoints() << " points" << endl;
            }
            cout << "Round " << counter << " is done" << endl;
        }
    //}


    return 0;
}