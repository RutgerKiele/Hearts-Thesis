/**
* @author Rutger Kiele (s2979128)
* @file monteCarloPlayer.cc
**/

#include "../include/monteCarloPlayerPI.h"

MonteCarloPlayerPI::MonteCarloPlayerPI(){
}

// Monte Carlo Player with perfect information plays the card that minimizes the expected points
Card MonteCarloPlayerPI::playCard(std::string suit){
    std::vector<int> moves = possibleMoves(suit);
    std::vector<int> scores;
    int currentPoints = points;
    for(unsigned i = 0; i < moves.size(); i++){
        scores.push_back(simulatePI(moves[0]) - currentPoints);
    }
    int bestMove = 0;
    for(unsigned i = 1; i < scores.size(); i++){
        if(scores[i] < scores[bestMove]){
            bestMove = i;
        }
    }
    Card cardPlayed = hand[moves[bestMove]];
    hand.erase(hand.begin() + moves[bestMove]);
    return cardPlayed;
}

int MonteCarloPlayerPI::simulatePI(int move){
    for (int i = 0; i < 4; i++){
        cout << players[i] -> getPoints() << " ";
    }
    cout << endl;
    Trick firstTrick(trick, playedBy, suit, players);

    for (int i = 0; i < 4; i++){
        cout << players[i] -> getPoints() << " ";
    }
    cout << endl;
    cout << endl;
    return 0;
}

void MonteCarloPlayerPI::giveInfo(std::vector<Card> trick, std::vector<int> playedBy, std::string suit, Player* players[]){
    this -> trick = trick;
    this -> playedBy = playedBy;
    this -> suit = suit;
    for(int i = 0; i < 4; i++){
        this -> players[i] = players[i];
    }
}