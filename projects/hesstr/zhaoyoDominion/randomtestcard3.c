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
    int coinsGained = 0;
    int actionsGained = 0;
    int expectedTribReveal[2] = {-1, -1};
    int deckDiscard = 0;
    int discardDiscard = 0;

    int inputTrib[2] = {-1, -1};

    int seed = 1000;
    int numPlayers = 2;
    int player1 = 0, player2 = 1;
	struct gameState preG, postG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, baron, smithy, council_room};

    printf("\n\n-------------Randomly Testing Tribute---------\n\n");
    initializeGame(numPlayers, k, seed, &preG);

    srand(time(NULL));

    int count = 0;

    while(count <= 1000)
    {
        expectedTribReveal[0] = -1;
        expectedTribReveal[1] = -1;
        cardsGainedP1 = 0;
        discardedP1 = 0;
        coinsGained = 0;
        actionsGained = 0;
        deckDiscard = 0;
        discardDiscard = 0;

        preG.deckCount[player2] = rand() % 6; //between 0 and 5
        preG.discardCount[player2] = rand() % 6; //between 0 and 5

        for(int i = 0; i < preG.deckCount[player2]; i++) //use non-randomized player hand size to randomize player1s hand
        {
            preG.deck[player1][i] = rand() % 27; //0 to 26
        }

        for(int i = 0; i < preG.discardCount[player2]; i++) //use non-randomized player hand size to randomize player2s hand
        {
            preG.discard[player2][i] = rand() % 27; //0 to 26
        }

        if(preG.deckCount[player2] + preG.discardCount[player2] <= 1)
        {
            if(preG.deckCount[player2] > 0)
            {
                expectedTribReveal[0] = preG.deck[player2][preG.deckCount[player2] - 1];
                deckDiscard = 1;
            }
            else if(preG.discardCount[player2] > 0)
            {
                expectedTribReveal[0] = preG.discard[player2][preG.discardCount[player2] - 1];
                discardDiscard = 1;
            }
        }
        else
        {
            if(preG.deckCount[player2] == 0)
            {
                expectedTribReveal[0] = preG.discard[player2][preG.discardCount[player2]-1];
                expectedTribReveal[1] = preG.discard[player2][preG.discardCount[player2]-2];
            }
            else
            {            
                expectedTribReveal[0] = preG.deck[player2][preG.deckCount[player2]-1];
                expectedTribReveal[1] = preG.deck[player2][preG.deckCount[player2]-2];
                deckDiscard = 2;
            }
        }

        if(expectedTribReveal[0] == expectedTribReveal[1])
        {
            expectedTribReveal[1] = -1;
        }
                
        for(int i = 0; i < 2; i++)
        {
            if(expectedTribReveal[i] == copper || expectedTribReveal[i] == silver || expectedTribReveal[i] == gold)
            {
                coinsGained += 2;
            }
            else if(expectedTribReveal[i] == estate || expectedTribReveal[i] == duchy || expectedTribReveal[i] == province || expectedTribReveal[i] == gardens || expectedTribReveal[i] == great_hall)
            {
                cardsGainedP1 += 2;
            }
            else if(expectedTribReveal[i] != -1)
            {
                actionsGained += 2;
            }
        }

        memcpy(&postG, &preG, sizeof(struct gameState));

        card_tribute(&postG, player2, &inputTrib, player1);
        //void card_tribute(struct gameState *state,int nextPlayer,int *tributeRevealedCards,int currentPlayer){

        printf("\nTest Number: %d\n", count);
        printf("\tPlayer 1:\n");
        printError(&preG, &postG, coinsGained, discardedP1, cardsGainedP1, actionsGained, player1);
        printf("\tPlayer 2:\n");
        printf("\t\tDeck count:\n");
        printf("\t\t\tExpected: %d, After: %d\n", preG.deckCount[player2] - deckDiscard, postG.deckCount[player2]);
        printf("\t\tDiscard count:\n");
        printf("\t\t\tExpected: %d, After: %d\n", preG.discardCount[player2] - discardDiscard, postG.discardCount[player2]);

        count++;
    }

    return 0;
}