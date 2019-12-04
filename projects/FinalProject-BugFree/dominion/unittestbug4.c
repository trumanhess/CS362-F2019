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
	struct gameState preG, postG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, baron, smithy, council_room};

    printf("\n\n-------------Testing Bug 4---------\n\n");
    initializeGame(numPlayers, k, seed, &preG);

/* 
    test 1: call isGameOver function with three things set to zero
    expect: to not get a gameover
*/
    printf("\n\nTest 1:\n");

    for(int i = 0; i < sizeof(preG.supplyCount); i++)
    {
        preG.supplyCount[i] = 10;
    }

    preG.supplyCount[26] = 0;
    preG.supplyCount[0] = 0;
    preG.supplyCount[1] = 0;

    memcpy(&postG, &preG, sizeof(struct gameState));
    
	ASSERT(isGameOver(&postG) == 1);

    printf("\n\n-------------End Testing Bug 4---------------\n\n");

    return 0;
}