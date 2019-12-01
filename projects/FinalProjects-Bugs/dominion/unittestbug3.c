#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "custom_assert.h"

int main()
{
    int cardsGained = 0;
    int discarded = 0;
    int coinsGained = 0;
    int buysGained = 0;
    int actionsGained = 0;

    int choice1 = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int nextPlayer = 1;
	struct gameState preG, postG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, baron, smithy, council_room};

    printf("\n\n-------------Testing Bug 3---------\n\n");
    initializeGame(numPlayers, k, seed, &preG);

/* 
    test 1: call remodel case, trash adventurer and gain feast
    expect: to not gain the feast
*/
    printf("\n\nTest 1:\n");

    preG.handCount[thisPlayer] = 5;
    preG.hand[thisPlayer][0] = adventurer;
	preG.hand[thisPlayer][1] = remodel;
	preG.hand[thisPlayer][2] = duchy;
	preG.hand[thisPlayer][3] = estate;
	preG.hand[thisPlayer][4] = copper;

    preG.discardCount[thisPlayer] = 0;
    preG.deckCount[thisPlayer] = 0;

    preG.playedCardCount = 0;

    memcpy(&postG, &preG, sizeof(struct gameState));
	cardEffect(12, 0, 9, 0, &postG, 1, 0);

    printf("\nCards in Discard pile:\n");
    printf("before: %d, after: %d\n", preG.discardCount[thisPlayer], postG.discardCount[thisPlayer]);
    ASSERT(preG.discardCount[thisPlayer] + 1 == postG.discardCount[thisPlayer]);

    printf("\n\n-------------End Testing Bug 3---------------\n\n");

    return 0;
}