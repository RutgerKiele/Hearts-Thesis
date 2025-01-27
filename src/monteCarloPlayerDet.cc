/**
* @author Rutger Kiele (s2979128)
* @file monteCarloPlayerDet.cc
**/

#include "../include/monteCarloPlayerDet.h"

MonteCarloPlayerDet::MonteCarloPlayerDet(){
    points = 0;
    totalScore = 0;
    maxPoints = 26;
    pointsPlayed = false;
    isTurn = false;
    numSims = 10;
    additionalTricks = 10;
    sampleSize = 3;
}

MonteCarloPlayerDet::MonteCarloPlayerDet(int numSims, int additionalTricks, int sampleSize){
    this -> numSims = numSims;
    this -> additionalTricks = additionalTricks;
    this -> sampleSize = sampleSize;
    points = 0;
    totalScore = 0;
    maxPoints = 26;
    pointsPlayed = false;
    isTurn = false;
}

Card MonteCarloPlayerDet::playCard(std::string suit, std::vector<Card> trick, std::vector<int> playedBy, int currentPlayer, int /*nPlayers*/, int maxPoints){
    this -> trick = trick;
    this -> playedBy = playedBy;
    this -> suit = suit;
    this -> currentPlayer = currentPlayer;
    this -> maxPoints = maxPoints;
    this -> cannotHaveSuit = std::vector<std::unordered_set<std::string>>(nPlayers);
    std::vector<int> moves = possibleMoves(suit);
    std::vector<int> scores;
    for(unsigned i = 0; i < moves.size(); i++){
        scores.push_back(simulateDet(moves[i]));
    }
    int bestMove = 0;
    for(unsigned i = 1; i < scores.size(); i++){
        if(scores[i] <= scores[bestMove]){
            bestMove = i;
        }
        // else if (scores[i] >= scores[bestMove] && points >= 20){
        //     bestMove = i;
        // }
    }
    playerPoints.clear();
    Card cardPlayed = hand[moves[bestMove]];
    removeCard(moves[bestMove]);
    return cardPlayed;
}

int MonteCarloPlayerDet::simulateDet(int move){
    int totalAddedPoints = 0;
    std::vector<std::vector<std::vector<Card>>> hands = generatePossibleHands(cardsInGame, sampleSize);
    for (int sample = 0; sample < sampleSize; sample++) {
        for(int sim = 0; sim < numSims; sim++){
            std::vector<Player*> simulatedPlayers;
            for (int j = 0; j < nPlayers; j++) {
                simulatedPlayers.push_back(new RandomPlayer());
                simulatedPlayers[j]->setHand(hands[sample][j]);
                simulatedPlayers[j]->setPointsPlayed(pointsPlayed); 
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
                simulatedCurrentPlayer = simulatedTrick.getWinner();
                if (simulatedPlayers[simulatedCurrentPlayer] -> getHandSize() == 0) {
                    break;
                }
                currentTrick.clear();
                currentPlayedBy.clear();
                currentSuit = "none";
                while (currentTrick.size() < unsigned(nPlayers)) {
                    currentTrick.push_back(simulatedPlayers[simulatedCurrentPlayer] -> playCard(currentSuit, currentTrick, currentPlayedBy, simulatedCurrentPlayer, nPlayers, maxPoints));
                    currentSuit = currentTrick[0].getSuit();
                    currentPlayedBy.push_back(simulatedCurrentPlayer);
                    simulatedCurrentPlayer = (simulatedCurrentPlayer + 1) % nPlayers;
                }
                Trick simulatedTrick(currentTrick, currentPlayedBy, currentSuit, simulatedPlayers, nPlayers);
                simulatedTrick.calculatePoints(true);
            }

            totalAddedPoints += simulatedPlayers[currentPlayer] -> getPoints();

            for (int j = 0; j < nPlayers; j++) {
                if (simulatedPlayers[j] -> getHandSize() == 0 && (simulatedPlayers[j]->getPoints() + playerPoints[j]) == maxPoints && j != currentPlayer){
                    totalAddedPoints += maxPoints;
                }
                delete simulatedPlayers[j];
            }
        }
    }

    return totalAddedPoints / numSims / sampleSize;
}
// Returns multiple possible hand for all players
std::vector<std::vector<std::vector<Card>>> MonteCarloPlayerDet::generatePossibleHands(Deck possibleCards, int sampleSize){
    std::vector<std::vector<std::vector<Card>>> possibleHands(sampleSize, std::vector<std::vector<Card>>(nPlayers));
    for (const Card& card : playedCards) {
        possibleCards.removeCard(card);
    }
    for (const Card& card : trick) {
        possibleCards.removeCard(card);
    }

    for (int sample = 0; sample < sampleSize; sample++) {
        possibleHands[sample][currentPlayer] = hand;
        possibleCards.shuffle();
        std::vector<Card> remainingCards = possibleCards.getCards();
        for (int i = 0; i < nPlayers; i++) {
            if (i != currentPlayer) {
                int handSize = hand.size() - hasPlayedCard(i);
                int addedCards = 0;
                auto it = remainingCards.begin();
                while (addedCards < handSize && it != remainingCards.end()) {
                    if (cannotHaveSuit[i].find(it->getSuit()) == cannotHaveSuit[i].end()) {
                        possibleHands[sample][i].push_back(*it);
                        it = remainingCards.erase(it);
                        addedCards++;
                    } else {
                        it++;
                    }
                }
            
                // If not enough valid cards were found, assign the remaining cards ignoring the restrictions
                it = remainingCards.begin();
                while (addedCards < handSize && it != remainingCards.end()) {
                    possibleHands[sample][i].push_back(*it);
                    it = remainingCards.erase(it);
                    ++addedCards;
                }
            }
        }
    }

    
    return possibleHands;
}

bool MonteCarloPlayerDet::hasPlayedCard(int player){
    return std::find(playedBy.begin(), playedBy.end(), player) != playedBy.end();
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

void MonteCarloPlayerDet::getPlayerPoints(std::vector<Player*> players, int nPlayers){
    this -> nPlayers = nPlayers;
    for(int i = 0; i < nPlayers; i++){
        playerPoints.push_back(players[i] -> getPoints());
    }
    otherHand = players[1] -> getHand();
}
