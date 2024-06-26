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

bool gameDone(std::vector<Player*> players, int nPlayers){
    for(int i = 0; i < nPlayers; i++){
        if(players[i] -> getScore() >= 100){
            return true;
        }
    }
    return false;
}

void whoWon(std::vector<Player*> players, std::vector<int>& numberWins, int nPlayers){
    int min = players[0] -> getScore();
    int index = 0;
    for(int i = 1; i < nPlayers; i++){
        if(players[i] -> getScore() < min){
            min = players[i] -> getScore();
            index = i;
        }
    }
    numberWins[index]++;
    for(int i = 0; i < nPlayers; i++){
        players[i] -> resetScore();
    }
}

int main(){
    Deck deck;
    int nPlayers = 3;
    std::vector<Player*> players;;
    int numberOfGames = 100;
    bool manual = false;
    std::cout << "How many players do you want to play with?: ";
    std::cin >> nPlayers;
    std::vector<int> numberWins(nPlayers, 0);
    if (nPlayers == 2 || nPlayers == 4){
        std::cout << "Do you want to play manually? (Answer 'Yes' or 'No'): ";
        std::string answer;
        std::cin >> answer;
        manual = answer == "Yes";
    }
    players.push_back(new MonteCarloPlayerDet());
    players.push_back(new MonteCarloPlayerPI());
    players.push_back(new MonteCarloPlayerDet());
    players.push_back(new MonteCarloPlayerPI());
    for(int i = 4; i < nPlayers; i++){
        players.push_back(new RandomPlayer());
    }
    if(manual){
        players[0] =  new ManualPlayer(nPlayers);
        numberOfGames = 1;
    }
    else {cout << "Running games..." << endl;}
    for(int i = 0; i < numberOfGames; i++){
        while(!gameDone(players, nPlayers)){
            deck.shuffle();
            Round round(players, deck, manual, nPlayers);
            round.playRound();
            for (int i = 0; i < nPlayers; i++){
                players[i] -> setPointsPlayed(false);
            }
        }
        whoWon(players, numberWins, nPlayers);
    }
    for(int i = 0; i < nPlayers; i++){
        std::cout << "Player " << i << " has " << numberWins[i] << " wins" << std::endl;
    }
    players.clear();

    return 0;
}