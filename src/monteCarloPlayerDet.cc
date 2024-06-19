/**
* @author Rutger Kiele (s2979128)
* @file monteCarloPlayerDet.cc
**/

#include "../include/monteCarloPlayerDet.h"

MonteCarloPlayerDet::MonteCarloPlayerDet(){
    points = 0;
    totalScore = 0;
    pointsPlayed = false;
    isTurn = false;
}

Card MonteCarloPlayerDet::playCard(std::string suit, std::vector<Card> trick, std::vector<int> playedBy, int currentPlayer, int nPlayers){
    this -> trick = trick;
    this -> playedBy = playedBy;
    this -> suit = suit;
    this -> currentPlayer = currentPlayer;
    this -> nPlayers = nPlayers;
    this -> cannotHaveSuit = std::vector<std::unordered_set<std::string>>(nPlayers);
    std::vector<int> moves = possibleMoves(suit);
    std::vector<int> scores;
    int currentPoints = points;
    for(unsigned i = 0; i < moves.size(); i++){
        scores.push_back(simulateDet(moves[i], currentPoints));
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

int MonteCarloPlayerDet::simulateDet(int move, int currentPoints){
    int totalAddedPoints = 0, numSims = 10, additionalTricks = 7;
    for(int sim = 0; sim < numSims; sim++){
        std::vector<std::vector<Card>> hands = generatePossibleHands(cardsInGame);
        
        std::vector<Player*> simulatedPlayers(nPlayers);
        for (int j = 0; j < nPlayers; j++) {
            simulatedPlayers[j] = new RandomPlayer();
            simulatedPlayers[j]->setHand(hands[j]); 
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
            currentTrick.push_back(simulatedPlayers[simulatedCurrentPlayer] -> playCard(currentSuit, currentTrick, currentPlayedBy, simulatedCurrentPlayer, nPlayers));
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
                currentTrick.push_back(simulatedPlayers[simulatedCurrentPlayer] -> playCard(currentSuit, currentTrick, currentPlayedBy, simulatedCurrentPlayer, nPlayers));
                currentSuit = currentTrick[0].getSuit();
                currentPlayedBy.push_back(simulatedCurrentPlayer);
                simulatedCurrentPlayer = (simulatedCurrentPlayer + 1) % nPlayers;
            }
            Trick simulatedTrick(currentTrick, currentPlayedBy, currentSuit, simulatedPlayers, nPlayers);
            simulatedTrick.calculatePoints(true);
        }

        totalAddedPoints += simulatedPlayers[currentPlayer] -> getPoints() - currentPoints;

        for (int j = 0; j < nPlayers; j++) {
            delete simulatedPlayers[j];
        }
    }

    return totalAddedPoints / numSims;
}

std::vector<std::vector<Card>> MonteCarloPlayerDet::generatePossibleHands(Deck possibleCards){
    std::vector<std::vector<Card>> possibleHands(nPlayers);
    possibleHands[currentPlayer] = hand;

    for (const Card& card : playedCards) {
        possibleCards.removeCard(card);
    }

    possibleCards.shuffle();
    std::vector<Card> remainingCards = possibleCards.getCards();
    for (int i = 0; i < nPlayers; i++) {
        if (i != currentPlayer) {
            int handSize = hand.size();
            int addedCards = 0;

            auto it = remainingCards.begin();
            while (addedCards < handSize && it != remainingCards.end()) {
                if (cannotHaveSuit[i].find(it->getSuit()) == cannotHaveSuit[i].end()) {
                    possibleHands[i].push_back(*it);
                    it = remainingCards.erase(it);
                    addedCards++;
                } else {
                    it++;
                }
            }

            // If not enough valid cards were found, assign the remaining cards ignoring the restrictions
            it = remainingCards.begin();
            while (addedCards < handSize && it != remainingCards.end()) {
                possibleHands[i].push_back(*it);
                it = remainingCards.erase(it);
                ++addedCards;
            }
        }
    }
    
    return possibleHands;
}

void MonteCarloPlayerDet::removeOwnCards(){
    for(unsigned i = 0; i < hand.size(); i++){
        cardsInGame.removeCard(hand[i]);
    }
}

void MonteCarloPlayerDet::addPlayedCards(std::vector<Card> cards, std::vector<int> playedBy, std::string suit, int thisPlayer){
    for(unsigned i = 0; i < cards.size(); i++){
        playedCards.push_back(cards[i]);
        int player = playedBy[i];
        if (cards[i].getSuit() != suit && player != thisPlayer) {
            cannotHaveSuit[player].insert(suit);
        }
    }
}

void MonteCarloPlayerDet::resetArrays(){
    playedCards.clear();
    cardsInGame = Deck();
    cannotHaveSuit = std::vector<std::unordered_set<std::string>>(nPlayers);
}
