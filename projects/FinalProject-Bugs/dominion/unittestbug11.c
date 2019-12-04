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
    int nextPlayer = 1;
	struct gameState preG, postG;
	int k[5] = {copper, silver, gold, ambassador, mine};

    printf("\n\n-------------Testing Bug 11--------------\n\n");
    initializeGame(numPlayers, k, seed, &preG);

/* 
    test 1: call ambassador case and select a duplicate card in hand
    expect: chosen card and duplicate to be copied into others' hands
*/
    printf("\n\nTest 1:\n");

    preG.handCount[thisPlayer] = 5;
    preG.hand[thisPlayer][0] = copper;
	preG.hand[thisPlayer][1] = copper;
	preG.hand[thisPlayer][2] = silver;
	preG.hand[thisPlayer][3] = gold;
	preG.hand[thisPlayer][4] = ambassador;

    preG.handCount[nextPlayer] = 1;
    preG.hand[nextPlayer][0] = gold;

    memcpy(&postG, &preG, sizeof(struct gameState));
	cardEffect(ambassador, 1, 1, 0, &postG, 1, 0);

    printf("\nHand Count (Next Player):\n");
    printf("before: %d, after: %d\n", preG.handCount[nextPlayer], postG.handCount[nextPlayer]); 
    ASSERT(preG.handCount[nextPlayer] + 1 == postG.handCount[nextPlayer]);

    printf("\nNext player has discarded card in hand:\n");
    printf("before: %d, after: %d\n", preG.hand[nextPlayer][0], postG.hand[nextPlayer][0]); 
    ASSERT(preG.hand[nextPlayer][0] != postG.hand[nextPlayer][1]); // received new card

    for(int i = 0; i < postG.handCount[nextPlayer]; i++)
    {
        printf("\ncard: %d", postG.hand[nextPlayer][i]);
    }

    printf("\n\n-------------End Testing Bug 11---------------\n\n");

    return 0;
}