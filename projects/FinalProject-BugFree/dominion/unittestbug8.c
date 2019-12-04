#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "custom_assert.h"

int main()
{
    int coinsGained = 0;

    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int nextPlayer = 1;
	struct gameState preG, postG;
	int k[6] = {ambassador, tribute, minion, mine,
			sea_hag, baron};

    printf("\n\n-------------Testing Bug 8-------------\n\n");
    initializeGame(numPlayers, k, seed, &preG);

/* 
    test 1: call tribute case on duplicate card
    expect: player receives 2 coin
*/
    printf("\n\nTest 1:\n");

    preG.deckCount[thisPlayer] = 2;
    preG.deck[thisPlayer][0] = copper;
	preG.deck[thisPlayer][1] = baron;

    preG.playedCardCount = 0;

    memcpy(&postG, &preG, sizeof(struct gameState));
	cardEffect(baron, 0, 0, 0, &postG, 1, 0);

    printf("\nCoin Increase:\n");
    printf("before: %d, after: %d\n", preG.coins, postG.coins);
    ASSERT(preG.coins == postG.coins);
    updateCoins(thisPlayer, & postG, 4);
    ASSERT(preG.coins + 4 == postG.coins);

    printf("\n\n-------------End Testing Bug 8---------------\n\n");

    return 0;
}