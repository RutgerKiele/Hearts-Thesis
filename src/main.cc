/**
* @author Rutger Kiele (s2979128)
* @file main.cc
**/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../include/monteCarloPlayerPI.h"
#include "../include/monteCarloPlayerDet.h"
#include "../include/randomPlayer.h"
#include "../include/manualPlayer.h"	
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

void whoWon(Player** players, int numberWins[]){
    int min = players[0] -> getScore();
    int index = 0;
    for(int i = 1; i < 4; i++){
        if(players[i] -> getScore() < min){
            min = players[i] -> getScore();
            index = i;
        }
    }
    numberWins[index]++;
    for(int i = 0; i < 4; i++){
        players[i] -> resetScore();
    }
}

int main(){
    Deck deck;
    Player* players[4];
    int numberWins[4] = {0, 0, 0, 0};
    int numberOfGames = 100;
    bool manual = false;
    std::cout << "Do you want to play manually? (Answer 'Yes' or 'No'): ";
    std::string answer;
    std::cin >> answer;
    manual = answer == "Yes";
    players[0] = new RandomPlayer();
    players[1] = new MonteCarloPlayerPI();
    players[2] = new MonteCarloPlayerDet();
    players[3] = new MonteCarloPlayerPI();
    if(manual){
        players[0] = new ManualPlayer();
        numberOfGames = 1;
    }
    else {cout << "Running games..." << endl;}
    for(int i = 0; i < numberOfGames; i++){
        while(!gameDone(players)){
            deck.shuffle();
            Round round(players, deck, manual);
            round.playRound();
            for (int i = 0; i < 4; i++){
                players[i] -> setPointsPlayed(false);
            }
        }
        whoWon(players, numberWins);
    }
    for(int i = 0; i < 4; i++){
        std::cout << "Player " << i << " has " << numberWins[i] << " wins" << std::endl;
    }

    return 0;
}