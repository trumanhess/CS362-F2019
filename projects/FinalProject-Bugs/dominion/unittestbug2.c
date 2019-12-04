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

    printf("\n\n-------------Testing Bug 2---------\n\n");
    initializeGame(numPlayers, k, seed, &preG);

/* 
    test 1: call mine case, trash silver and gain copper
    expect: to not gain the copper
*/
    printf("\n\nTest 1:\n");

    preG.handCount[thisPlayer] = 5;
    preG.hand[thisPlayer][0] = silver;
	preG.hand[thisPlayer][1] = mine;
	preG.hand[thisPlayer][2] = duchy;
	preG.hand[thisPlayer][3] = estate;
	preG.hand[thisPlayer][4] = feast;

    preG.discardCount[thisPlayer] = 0;
    preG.deckCount[thisPlayer] = 0;

    preG.playedCardCount = 0;

    memcpy(&postG, &preG, sizeof(struct gameState));
	cardEffect(11, 0, 4, 0, &postG, 1, 0);

    printf("\nCoins:\n");
    printf("before: %d, after: %d\n", preG.coins, postG.coins);
    ASSERT(preG.coins - getCost(silver) + getCost(copper) == postG.coins);

    printf("\n\n-------------End Testing Bug 2---------------\n\n");

    return 0;
}