/**
* @author Rutger (s2979128)
* @file randomPlayer.h
**/

#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include <iostream>
#include "player.h"

class RandomPlayer : public Player{
    public:
        RandomPlayer();
    private:
        void playCard();
};

#endif