#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define MAX_HAND_COUNT 10

int printError(struct gameState *pre, struct gameState *post, int coinsGained, int discarded, int cardsGained, int buysGained, int player, int testNum)
{
    if((pre->numBuys + buysGained) != post->numBuys || post->handCount[player] != pre->handCount[player] - discarded + cardsGained || (pre->coins + coinsGained) != post->coins)
    {
        //print out player state, expected and actual as well as test number
        printf("\nTest Number: %d\n", testNum);

        printf("\tNumber of Buys:\n");
        printf("\t\tExpected: %d, Actual: %d\n", pre->numBuys + buysGained, post->numBuys);

        printf("\tNumber coins:\n");
        printf("\t\tExpected = %d, Actual = %d\n", pre->coins + coinsGained, post->coins);

        printf("\tHand count:\n");
        printf("\t\tExpected = %d, Actual = %d\n", pre->handCount[player] - discarded + cardsGained, post->handCount[player]);
    }

    return 0;
}

int main()
{
    int cardsGained = 0;
    int discarded = 0;
    int coinsGained = 0;
    int buysGained = 0;

    int choice1 = 0;
    int seed = 1000;
    int numPlayers = 2;
    int player1 = 0;
    int player2 = 1;
	struct gameState preG, postG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, baron, smithy, council_room};

    printf("\n\n-------------Randomly Testing Baron---------\n\n");
    initializeGame(numPlayers, k, seed, &preG);

    srand(time(NULL));

    int count = 0;

    while(count <= 1000)
    {
        coinsGained = 0;
        buysGained = 0;
        discarded = 0;
        cardsGained = 0;

        choice1 = rand() % 2; //choose to either get rid of an estate or not

        for(int i = 0; i < preG.handCount[player1]; i++) //use non-randomized player hand size to randomize the players hand
        {
            preG.hand[player1][i] = rand() % 27; //0 to 26
        }

        //randomize supply count for estates
        preG.supplyCount[estate] = rand() % 12 + (-5); //generate random numbers between -5 and 6

        buysGained = 1;
        if(choice1 == 1)
        {
            coinsGained = 4;
            discarded = 1;
        }
        else
        {
            cardsGained = 1;
        }
        
        memcpy(&postG, &preG, sizeof(struct gameState));

        card_baron(choice1, &postG, player1, player2);

        printError(&preG, &postG, coinsGained, discarded, cardsGained, buysGained, player1, count);

        count++;
    }

    return 0;
}

//how do we want to catch errors in a random tester?