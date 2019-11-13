#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
//#include "custom_assert.h"


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

    int choice1 = 0, choice2 = 0, handPos = 0; //randomize player1 choice1
    int seed = 1000;
    int numPlayers = 2;
    int player1 = 0, player2 = 1;
	struct gameState preG, postG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, baron, smithy, council_room};

    printf("\n\n-------------Randomly Testing Mininon---------\n\n");
    initializeGame(numPlayers, k, seed, &preG);

    srand(time(NULL));

    int count = 0;

    while(count <= 1000)
    {
        choice1 = rand() % (2 - 1 + (1)) + 1; //either 1 or 2
        //choice1 = 1;
        
        preG.handCount[player1] = rand() % 6 + (1); //between 0 and 5
        preG.handCount[player2] = rand() % 6 + (1); //between 0 and 5

        for(int i = 0; i < preG.handCount[player1]; i++) //use non-randomized player hand size to randomize player1s hand
        {
            preG.hand[player1][i] = rand() % 27; //or is it 23? 0 to 26
        }

        for(int i = 0; i < preG.handCount[player2]; i++) //use non-randomized player hand size to randomize player2s hand
        {
            preG.hand[player2][i] = rand() % 27; //or is it 23? 0 to 26
        }

        for(int i = 0; i < preG.handCount[player1]; i++)
        {
            if(preG.hand[player1][i] == minion)
            {
                handPos = i;
            }
        }

        memcpy(&postG, &preG, sizeof(struct gameState));

        minionLogic(choice1, choice2, &postG, handPos, player1);

        count++;
    }

    return 0;
}