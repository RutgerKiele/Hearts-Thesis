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

using namespace std;

void dealCards(Deck deck, Player** players){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            players[i] -> addCard(deck.draw());
        }
        players[i] -> sortHand();
    }
}

int main(){
    Deck deck;
    Player* players[4];
    for(int i = 0; i < 4; i++){
        players[i] = new RandomPlayer();
    }
    dealCards(deck, players);
    return 0;
}