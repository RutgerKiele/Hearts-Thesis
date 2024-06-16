/**
* @author Rutger Kiele (s2979128)
* @file deck.cc
**/

#include <cstdlib> // Include the <cstdlib> header for the rand() function
#include <ctime>   // Include the <ctime> header for the time() function
#include "../include/deck.h"

Deck::Deck(){
    size = 52;
    for(int i = 0; i < 13; i++){
        cards.push_back(Card(static_cast<Value>(i), "hearts"));
    }
    for(int i = 0; i < 13; i++){
        cards.push_back(Card(static_cast<Value>(i), "diamonds"));
    }
    for(int i = 0; i < 13; i++){
        cards.push_back(Card(static_cast<Value>(i), "clubs"));
    }
    for(int i = 0; i < 13; i++){
        cards.push_back(Card(static_cast<Value>(i), "spades"));
    }
    assignPoints();
}

void Deck::assignPoints(){
    for(int i = 0; i < size; i++){
        if(cards[i].getSuit() == "hearts"){
            cards[i].setPoints(1);
        }
        else if(cards[i].getSuit() == "spades" && cards[i].getValue() == Queen){
            cards[i].setPoints(13);
        }
        else{
            cards[i].setPoints(0);
        }
    }
}

void Deck::printDeck(){
    for(int i = 0; i < size; i++){
        cards[i].printCard();
    }
    cout << endl;
}

void Deck::shuffle(){
    // Seed the random number generator with the current time
    srand(time(0));

    for(int i = 0; i < size; i++){
        int randomIndex = rand() % size;
        Card temp = cards[i];
        cards[i] = cards[randomIndex];
        cards[randomIndex] = temp;
    }
}

Card Deck::draw(){
    Card card = cards[size - 1];
    size--;
    return card;
}

void Deck::removeCard(Card card){
    for(int i = 0; i < size; i++){
        if(cards[i].sameCard(card)){
            cards.erase(cards.begin() + i);
            size--;
            break;
        }
    }
}

int Deck::getSize(){
    return size;
}

std::vector<Card> Deck::getCards(){
    return cards;
}
