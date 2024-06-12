/**
* @author Rutger Kiele (s2979128)
* @file monteCarloPlayerDet.cc
**/

#include "../include/monteCarloPlayerDet.h"

MonteCarloPlayerDet::MonteCarloPlayerDet(){
}


Card MonteCarloPlayerDet::playCard(std::string suit){
    std::vector<int> moves = possibleMoves(suit);
    std::vector<int> scores;
    int currentPoints = points;
    for(unsigned i = 0; i < moves.size(); i++){
        scores.push_back(simulateDet(moves[i], currentPoints));
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

int MonteCarloPlayerDet::simulateDet(int move, int currentPoints){
    int totalAddedPoints = 0, numSims = 1, additionalTricks = 5;

    Player* simulatedPlayers[4];
    simulatedPlayers[currentPlayer] = new RandomPlayer(*this);

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
    // Calculate points for this trick
    Trick simulatedTrick(currentTrick, currentPlayedBy, currentSuit, simulatedPlayers);
    simulatedTrick.calculatePoints();

    // Play addidional tricks
    for (int i = 0; i < additionalTricks; i++){
        if (simulatedPlayers[currentPlayer] -> getHandSize() == 0) {
            break;
        }
        currentTrick.clear();
        currentPlayedBy.clear();
        currentSuit = "none";
        simulatedCurrentPlayer = simulatedTrick.getWinner();
        while (currentTrick.size() < 4) {
            currentTrick.push_back(simulatedPlayers[simulatedCurrentPlayer] -> playCard(currentSuit));
            currentSuit = currentTrick[0].getSuit();
            currentPlayedBy.push_back(simulatedCurrentPlayer);
            simulatedCurrentPlayer = (simulatedCurrentPlayer + 1) % 4;
        }
        Trick simulatedTrick(currentTrick, currentPlayedBy, currentSuit, simulatedPlayers);
        simulatedTrick.calculatePoints();
    }

    totalAddedPoints += simulatedPlayers[currentPlayer] -> getPoints() - currentPoints;

    return totalAddedPoints / numSims;
}

void MonteCarloPlayerDet::giveInfo(std::vector<Card> trick, std::vector<int> playedBy, std::string suit, int currentPlayer){
    this -> trick = trick;
    this -> playedBy = playedBy;
    this -> suit = suit;
    this -> currentPlayer = currentPlayer;
}
