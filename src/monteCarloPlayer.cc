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
        scores.push_back(simulatePI(moves[i], currentPoints));
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
int MonteCarloPlayerPI::simulatePI(int move, int currentPoints){
    int totalAddedPoints = 0;
    for(int sim = 0; sim < 100; sim++){
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
        // Calculate points for this trick
        Trick simulatedTrick(currentTrick, currentPlayedBy, currentSuit, simulatedPlayers);
        simulatedTrick.calculatePoints();

        // Play addidional tricks
        for (int i = 0; i < 8; i++){
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
    }

    return totalAddedPoints/100;
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