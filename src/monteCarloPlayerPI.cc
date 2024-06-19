/**
* @author Rutger Kiele (s2979128)
* @file monteCarloPlayerPI.cc
**/

#include "../include/monteCarloPlayerPI.h"


MonteCarloPlayerPI::MonteCarloPlayerPI(){
}

// Monte Carlo Player with perfect information plays the card that minimizes the expected points
Card MonteCarloPlayerPI::playCard(std::string suit, std::vector<Card> trick, std::vector<int> playedBy, int currentPlayer){
    this -> trick = trick;
    this -> playedBy = playedBy;
    this -> suit = suit;
    this -> currentPlayer = currentPlayer;
    std::vector<int> moves = possibleMoves(suit);
    std::vector<int> scores;
    int currentPoints = points;
    for(unsigned i = 0; i < moves.size(); i++){
        scores.push_back(simulatePI(moves[i], currentPoints));
    }
    int bestMove = 0;
    for(unsigned i = 1; i < scores.size(); i++){
        if(scores[i] <= scores[bestMove]){
            bestMove = i;
        }
    }
    Card cardPlayed = hand[moves[bestMove]];
    removeCard(moves[bestMove]);
    return cardPlayed;
}

// Simulate the game with the given move and return the average points of the player
int MonteCarloPlayerPI::simulatePI(int move, int currentPoints){
    int totalAddedPoints = 0, numSims = 50, additionalTricks = 10;
    for(int sim = 0; sim < numSims; sim++){
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
            currentTrick.push_back(simulatedPlayers[simulatedCurrentPlayer] -> playCard(currentSuit, currentTrick, currentPlayedBy, simulatedCurrentPlayer));
            currentPlayedBy.push_back(simulatedCurrentPlayer);
        }
        // Calculate points for this trick
        Trick simulatedTrick(currentTrick, currentPlayedBy, currentSuit, simulatedPlayers);
        simulatedTrick.calculatePoints(true);

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
                currentTrick.push_back(simulatedPlayers[simulatedCurrentPlayer] -> playCard(currentSuit, currentTrick, currentPlayedBy, simulatedCurrentPlayer));
                currentSuit = currentTrick[0].getSuit();
                currentPlayedBy.push_back(simulatedCurrentPlayer);
                simulatedCurrentPlayer = (simulatedCurrentPlayer + 1) % 4;
            }
            Trick simulatedTrick(currentTrick, currentPlayedBy, currentSuit, simulatedPlayers);
            simulatedTrick.calculatePoints(true);
        }

        totalAddedPoints += simulatedPlayers[currentPlayer] -> getPoints() - currentPoints;

        for (int j = 0; j < 4; j++) {
            delete simulatedPlayers[j];
        }
    }

    return totalAddedPoints / numSims;
}

void MonteCarloPlayerPI::giveInfo(Player* players[]){
    for(int i = 0; i < 4; i++){
        this -> players[i] = players[i];
    }
}