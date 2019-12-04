#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "custom_assert.h"

int main()
{
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState preG, postG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, baron, smithy, council_room};

    printf("\n\n-------------Testing Bug 1---------\n\n");
    initializeGame(numPlayers, k, seed, &preG);

/* 
    test 1: call mine case, trash the chosen card
    expect: chosen card to be untrashed
*/
    printf("\n\nTest 1:\n");

    preG.handCount[thisPlayer] = 5;
    preG.hand[thisPlayer][0] = copper;
	preG.hand[thisPlayer][1] = mine;
	preG.hand[thisPlayer][2] = duchy;
	preG.hand[thisPlayer][3] = estate;
	preG.hand[thisPlayer][4] = feast;

    preG.discardCount[thisPlayer] = 0;
    preG.deckCount[thisPlayer] = 0;

    preG.playedCardCount = 0;

    memcpy(&postG, &preG, sizeof(struct gameState));
	cardEffect(11, 0, 5, 0, &postG, 1, 0);

    printf("\nDiscard Count:\n");
    printf("before: %d, after: %d\n", preG.discardCount[thisPlayer], postG.discardCount[thisPlayer]);
    ASSERT(preG.discardCount[thisPlayer] + 1 == postG.discardCount[thisPlayer]);

    printf("\nDeck Count:\n");
    printf("before: %d, after: %d\n", preG.deckCount[thisPlayer], postG.deckCount[thisPlayer]);
    ASSERT(preG.deckCount[thisPlayer] == postG.deckCount[thisPlayer]);

    printf("\nHand Count:\n");
    printf("before: %d, after: %d\n", preG.handCount[thisPlayer], postG.handCount[thisPlayer]); 
    ASSERT(preG.handCount[thisPlayer] - 2 + 1 == postG.handCount[thisPlayer]);

    printf("\nPlayed Card Count:\n");
    printf("before: %d, after: %d\n", preG.playedCardCount, postG.playedCardCount); 
    ASSERT(preG.playedCardCount + 1 == postG.playedCardCount); //only played one card

    for(int i = 0; i < postG.handCount[thisPlayer]; i++)
    {
        printf("\ncard: %d", postG.hand[thisPlayer][i]);
    }


    printf("\n\n-------------End Testing Bug 1---------------\n\n");

    return 0;
}