#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "custom_assert.h"


/*
vars to consider for randomization:
    YES:
        player1 state vars
        randomize card locations and which cards are being used in the players hand
        supply deck numbers
        the number which the player inputs for getting rid of and estate

    NO:
        number players

*/


/*

struct gameState {
    int numPlayers; //number of players
    int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
    int embargoTokens[treasure_map+1];
    int outpostPlayed;
    int outpostTurn;
    int whoseTurn;
    int phase;
    int numActions; /* Starts at 1 each turn
    int coins; /* Use as you see fit!
    int numBuys; /* Starts at 1 each turn
    int hand[MAX_PLAYERS][MAX_HAND];
    int handCount[MAX_PLAYERS];
};

*/

#define MAX_HAND_COUNT 10

int main()
{
    int cardsGained = 0;
    int discarded = 0;
    int coinsGained = 0;
    int buysGained = 0;
    int actionsGained = 0;

    int choice1 = 0; //randomize player1 choice1
    int seed = 1000;
    int numPlayers = 2;
    int player1 = 0;
	struct gameState preG, postG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, baron, smithy, council_room};

    printf("\n\n-------------Randomly Testing Baron---------\n\n");
    initializeGame(numPlayers, k, seed, &preG);


    choice1 = rand() % preG.handCount[player1];

    //might randomize player hand count so it is bigger or smaller?
    for(int i = 0; i < preG.handCount[player1]; i++) //use non-randomized player hand size to randomize the players hand
    {
        preG.hand[player1][i] = rand() % 24; //or is it 23?
    }

    //randomize supply count for estates


    return 0;
}