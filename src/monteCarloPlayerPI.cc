/**
* @author Rutger Kiele (s2979128)
* @file monteCarloPlayerPI.cc
**/

#include "../include/monteCarloPlayerPI.h"


MonteCarloPlayerPI::MonteCarloPlayerPI(){
    maxPoints = 26;
    numSims = 30;
    additionalTricks = 8;
    pointsPlayedThisRound = 0;
}

MonteCarloPlayerPI::MonteCarloPlayerPI(int numSims, int additionalTricks, bool allPoints){
    this -> numSims = numSims;
    this -> additionalTricks = additionalTricks;
    this -> allPoints = allPoints;
    maxPoints = 26;
    pointsPlayedThisRound = 0;
}

// Monte Carlo Player with perfect information plays the card that minimizes the expected points
Card MonteCarloPlayerPI::playCard(std::string suit, std::vector<Card> trick, std::vector<int> playedBy, int currentPlayer, int /*nPlayers*/, int maxPoints){
    this -> trick = trick;
    this -> playedBy = playedBy;
    this -> suit = suit;
    this -> currentPlayer = currentPlayer;
    this -> maxPoints = maxPoints;
    std::vector<int> moves = possibleMoves(suit);
    std::vector<int> scores;
    int currentPoints = points;
    for(unsigned i = 0; i < moves.size(); i++){
        scores.push_back(simulatePI(moves[i], currentPoints));
    }
    int bestMove = 0;
    bool shootTheMoon = false;
    if(allPoints){
        shootTheMoon = goForAllPoints();
    }
    for(unsigned i = 1; i < scores.size(); i++){
        if(scores[i] <= scores[bestMove] && !shootTheMoon){
            bestMove = i;
        }
        else if (scores[i] >= scores[bestMove] && shootTheMoon){
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
    for(int sim = 0; sim < numSims; sim++){
        std::vector<Player*> simulatedPlayers;
        for (int j = 0; j < nPlayers; j++) {
            simulatedPlayers.push_back(new RandomPlayer(*players[j]));
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
        while (currentTrick.size() < unsigned(nPlayers)) {
            simulatedCurrentPlayer = (simulatedCurrentPlayer + 1) % nPlayers;
            currentTrick.push_back(simulatedPlayers[simulatedCurrentPlayer] -> playCard(currentSuit, currentTrick, currentPlayedBy, simulatedCurrentPlayer, nPlayers, maxPoints));
            currentPlayedBy.push_back(simulatedCurrentPlayer);
        }
        // Calculate points for this trick
        Trick simulatedTrick(currentTrick, currentPlayedBy, currentSuit, simulatedPlayers, nPlayers);
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
            while (currentTrick.size() < unsigned(nPlayers)) {
                currentTrick.push_back(simulatedPlayers[simulatedCurrentPlayer] -> playCard(currentSuit, currentTrick, currentPlayedBy, simulatedCurrentPlayer, nPlayers, maxPoints));
                currentSuit = currentTrick[0].getSuit();
                currentPlayedBy.push_back(simulatedCurrentPlayer);
                simulatedCurrentPlayer = (simulatedCurrentPlayer + 1) % nPlayers;
            }
            Trick simulatedTrick(currentTrick, currentPlayedBy, currentSuit, simulatedPlayers, nPlayers);
            simulatedTrick.calculatePoints(true);
        }
        
        totalAddedPoints += simulatedPlayers[currentPlayer] -> getPoints() - currentPoints;
    
        for (int j = 0; j < nPlayers; j++) {
            if (simulatedPlayers[j] -> getHandSize() == 0 && simulatedPlayers[j] -> getPoints() == maxPoints && j != currentPlayer){
                totalAddedPoints += maxPoints;
            }
            delete simulatedPlayers[j];
        }
    }

    return totalAddedPoints / numSims;
}

void MonteCarloPlayerPI::giveInfo(std::vector<Player*> players, int nPlayers){
    this -> nPlayers = nPlayers;
    for(int i = 0; i < nPlayers; i++){
        this->players.push_back(players[i]);
    }
}

// Should the player go for all points
bool MonteCarloPlayerPI::goForAllPoints(){
    // This means that the someone else has got a points
    if (points - pointsPlayedThisRound != 0){return false;}
    // It is too risky to go for all points when you cannot afford it
    if (totalScore >= 75){return false;}
    if (points < 15) {return false;}
    return true;
}

void MonteCarloPlayerPI::addPointsPlayedThisRound(int points){
    pointsPlayedThisRound += points;
}

void MonteCarloPlayerPI::resetPointsPlayedThisRound(){
    pointsPlayedThisRound = 0;
}