/**
* @author Rutger Kiele (s2979128)
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
#include "../include/round.h"

using namespace std;

bool gameDone(Player** players){
    for(int i = 0; i < 4; i++){
        if(players[i] -> getScore() >= 100){
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
    while(!gameDone(players)){
        deck.shuffle();
        Round round(players, deck);
        round.playRound();
    }
    for(int i = 0; i < 4; i++){
        cout << "Player " << i << " has " << players[i] -> getScore() << " points" << endl;
    }

    return 0;
}