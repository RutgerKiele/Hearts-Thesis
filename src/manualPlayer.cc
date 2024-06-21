/**
* @author Rutger Kiele (s2979128)
* @file manualPlayer.cc
**/

#include "../include/manualPlayer.h"

ManualPlayer::ManualPlayer(int nPlayers){
    this -> nPlayers = nPlayers;
}

Card ManualPlayer::playCard(std::string suit, std::vector<Card> trick, std::vector<int> playedBy, int /*currentPlayer*/, int /*nPlayers*/, int /*maxPoints*/){
    std::string chosenCard;
    if (nPlayers == 4) fourPlayerHand(trick, playedBy);
    else if (nPlayers == 2) twoPlayerHand(trick, playedBy);
    else throw "Invalid number of players";
    std::cout << "Your hand: ";
    for (auto& card : hand) {
        std::cout << card.getShortName();
        if (&card != &hand.back()) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Enter the card you want to play ('2c' for '2 of clubs'): ";
    std::cin >> chosenCard;
    int card = correctInput(chosenCard, suit);
    while (card == -1) {
        std::cout << "Please give a playable card:";;
        cin >> chosenCard;
        card = correctInput(chosenCard, suit);
    }
    std::cout << std::endl;
    Card cardPlayed = hand[card];
    removeCard(card);
    return cardPlayed;
}

void ManualPlayer::fourPlayerHand(std::vector<Card> trick, std::vector<int> playedBy){
    std::string player1Card = "-";
    std::string player2Card = "-";
    std::string player3Card = "-";
    for (unsigned i = 0; i < trick.size(); i++) {
        if (playedBy[i] == 1) {
            player1Card = trick[i].getShortName();
        } else if (playedBy[i] == 2) {
            player2Card = trick[i].getShortName();
        } else if (playedBy[i] == 3) {
            player3Card = trick[i].getShortName();
        }
    }
    std::cout << "         Player 2" << std::endl;
    std::cout << "            " << player2Card << std::endl;
    std::cout << "Player 1: "<< player1Card << "   " << player3Card << " :Player 3" << std::endl;
    std::cout << "            -" << std::endl;
    std::cout << "           You" << std::endl;
}

void ManualPlayer::twoPlayerHand(std::vector<Card> trick, std::vector<int> playedBy){
    std::string player1Card = "-";
    for (unsigned i = 0; i < trick.size(); i++) {
        if (playedBy[i] == 1) {
            player1Card = trick[i].getShortName();
        }
    }
    std::cout << "Player 1: " << player1Card << std::endl;
    std::cout << "You: -" << std::endl;
}

int ManualPlayer::correctInput(std::string input, std::string suit){
    if (input.length() != 2){
        std::cout << "Incorrect input length. ";
        return -1;
    }
    char value = input[0];
    char suitInput = input[1];
    if (value != '2' && value != '3' && value != '4' && value != '5' && value != '6' && value != '7' && value != '8' && value != '9' && value != 'T' && value != 'J' && value != 'Q' && value != 'K' && value != 'A'){
        std::cout << "Incorrect value. ";
        return -1;
    }
    if (suitInput != 'c' && suitInput != 'd' && suitInput != 'h' && suitInput != 's'){
        std::cout << "Incorrect suit. ";
        return -1;
    }
    Value chosenValue;
    if (value >= '2' && value <= '9') {
        chosenValue = static_cast<Value>(value - '2');
    } else {
        switch (value) {
            case 'T':
                chosenValue = Value::Ten;
                break;
            case 'J':
                chosenValue = Value::Jack;
                break;
            case 'Q':
                chosenValue = Value::Queen;
                break;
            case 'K':
                chosenValue = Value::King;
                break;
            case 'A':
                chosenValue = Value::Ace;
                break;
            default:
                throw "Invalid value";
        }
    }
    std::string chosenSuit;
    switch (suitInput) {
        case 'c':
            chosenSuit = "clubs";
            break;
        case 'd':
            chosenSuit = "diamonds";
            break;
        case 'h':
            chosenSuit = "hearts";
            break;
        case 's':
            chosenSuit = "spades";
            break;
        default:
            throw "Invalid suit";
    }
    Card chosenCard = Card(chosenValue, chosenSuit);
    int index = -1;
    for (unsigned i = 0; i < hand.size(); i++){
        if (hand[i].sameCard(chosenCard)) {
            index = i;
            break;
        }
    }
    if (index == -1) {cout << "Card is not in your hand. ";return -1;}
    std::vector<int> moves = possibleMoves(suit);
    for (unsigned i = 0; i < moves.size(); i++){
        if (moves[i] == index) {return index;}
    }
    std::cout << "This card can not be played now. ";
    return -1;
}