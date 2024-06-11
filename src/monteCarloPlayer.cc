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
    removeCard(moves[bestMove]);
    return cardPlayed;
}

// Simulate the game with the given move and return the average points of the player
int MonteCarloPlayerPI::simulatePI(int move){
    Player* simulatedPlayers[4];
    for (int j = 0; j < 4; j++) {
        simulatedPlayers[j] = new RandomPlayer(*players[j]);
    }

    // Play the move
    Card chosenCard = hand[move];
    simulatedPlayers[currentPlayer] -> removeCard(move);
    std::vector<Card> currentTrick = trick;
    currentTrick.push_back(chosenCard);
    std::vector<int> currentPlayedBy = playedBy;
    currentPlayedBy.push_back(currentPlayer);
    std::string currentSuit = currentTrick[0].getSuit();

    // Play rest of trick
    int simulatedCurrentPlayer = currentPlayer;
    while (currentTrick.size() < 4) {
        simulatedCurrentPlayer = (simulatedCurrentPlayer + 1) % 4;
        currentTrick.push_back(simulatedPlayers[simulatedCurrentPlayer] -> playCard(currentSuit));
        currentPlayedBy.push_back(simulatedCurrentPlayer);
    }

    // Calculate points
    Trick trick(currentTrick, currentPlayedBy, currentSuit, simulatedPlayers);
    trick.calculatePoints();
    int points = simulatedPlayers[currentPlayer] -> getPoints();

    // Clean up simulated players
    for (int j = 0; j < 4; j++) {
        delete simulatedPlayers[j];
    }

    return points;
}

void MonteCarloPlayerPI::giveInfo(std::vector<Card> trick, std::vector<int> playedBy, std::string suit, Player* players[], int currentPlayer){
    this -> trick = trick;
    this -> playedBy = playedBy;
    this -> suit = suit;
    for(int i = 0; i < 4; i++){
        this -> players[i] = players[i];
    }
    this -> currentPlayer = currentPlayer;
}