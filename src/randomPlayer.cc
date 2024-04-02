/**
* @author Rutger Kiele (s2979128)
* @file randomPlayer.cc
**/

#include "../include/randomPlayer.h"

RandomPlayer::RandomPlayer(){
}

Card RandomPlayer::playCard(std::string suit){
    srand(time(0));
    int card = rand() % hand.size();
    Card cardPlayed = hand[card];
    if(hasTwoOfClubs()){
      card = 0;
      cardPlayed = hand[card];
    }
    else{
      if(cardPlayed.getSuit() != suit && suit != "none"){
          if(hasSuit(suit)){
            while (cardPlayed.getSuit() != suit){
                card = rand() % hand.size();
                cardPlayed = hand[card];
            }
          }
      }
    }
    hand.erase(hand.begin() + card);
    return cardPlayed;
}