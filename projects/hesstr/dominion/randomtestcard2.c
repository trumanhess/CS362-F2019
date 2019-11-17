#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define MAX_HAND_COUNT 10

int printError(struct gameState *pre, struct gameState *post, int coinsGained, int discarded, 
    int cardsGained, int actionsGained, int player)
{
    if((pre->numActions + actionsGained) != post->numActions || post->handCount[player] != pre->handCount[player] - discarded + cardsGained || (pre->coins + coinsGained) != post->coins)
    {   
        printf("\t\tNumber of Actions:\n");
        printf("\t\t\tExpected: %d, Actual: %d\n", pre->numActions + actionsGained, post->numActions);

        printf("\t\tNumber coins:\n");
        printf("\t\t\tExpected = %d, Actual = %d\n", pre->coins + coinsGained, post->coins);

        printf("\t\tHand count:\n");
        printf("\t\t\tExpected = %d, Actual = %d\n", pre->handCount[player] - discarded + cardsGained, post->handCount[player]);
    }

    return 0;
}

int main()
{
    int cardsGainedP1 = 0;
    int discardedP1 = 0;
    int cardsGainedP2 = 0;
    int discardedP2 = 0;
    int coinsGained = 0;
    int actionsGained = 0;

    int choice1 = 0, choice2 = 0, handPos = 0;
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
        actionsGained = 0;
        cardsGainedP1 = 0;
        discardedP1 = 0;
        cardsGainedP2 = 0;
        discardedP2 = 0;
        coinsGained = 0;

        choice1 = rand() % (2 - 1 + (1)) + 1; //either 1 or 2
        
        preG.handCount[player1] = rand() % 6 + (1); //between 1 and 6
        preG.handCount[player2] = rand() % 6 + (1); //between 1 and 6

        for(int i = 0; i < preG.handCount[player1]; i++) //use player hand size to randomize player1s hand
        {
            preG.hand[player1][i] = rand() % 27; //how many cards there are in dominion.h
        }

        for(int i = 0; i < preG.handCount[player2]; i++) //use player hand size to randomize player2s hand
        {
            preG.hand[player2][i] = rand() % 27; //how many cards there are in dominion.h
        }

        for(int i = 0; i < preG.handCount[player1]; i++)
        {
            if(preG.hand[player1][i] == minion)
            {
                handPos = i;
            }
        }

        actionsGained = 1;

        if(choice1 == 1)
        {
            coinsGained = 2;
        }
        else
        {
            discardedP1 = preG.handCount[player1];
            discardedP2 = preG.handCount[player2];

            cardsGainedP1 = 4;
            if(preG.handCount[player2] >= 5)
            {
                cardsGainedP2 = 4;
            }
        }
        

        memcpy(&postG, &preG, sizeof(struct gameState));

        minionLogic(choice1, choice2, &postG, handPos, player1);

        printf("\nTest Number: %d\n", count);
        printf("\tPlayer 1:\n");
        printError(&preG, &postG, coinsGained, discardedP1, cardsGainedP1, actionsGained, player1);
        printf("\tPlayer 2:\n");
        printError(&preG, &postG, 0, discardedP2, cardsGainedP2, actionsGained, player2);

        count++;
    }

    return 0;
}