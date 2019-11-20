//NEED TO ZERO OUT GAME STRUCTS AFTER USING THEM!!
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "custom_assert.h"

/*
    test 1: get rid of estate and have one in hand
    test 2: get rid of estate, but not have one in hand
    test 3: gain an estate
    test 4: try to gain an estate, but negative amount of estates in supply
*/

int universalTest(struct gameState *pre, struct gameState *post, int discarded, int cardsGained, int buysGained, int coinsGained, int actionsGained, int player)
{
    printf("Number buys:\n");
    ASSERT((pre->numBuys + buysGained) == post->numBuys);
    printf("\texpected = %d, actual = %d\n", pre->numBuys + buysGained, post->numBuys);

    printf("Number Actions:\n");
    ASSERT(post->numActions == pre->numActions + actionsGained);
    printf("\texpected = %d, actual = %d\n", pre->numActions + actionsGained, post->numActions);

    printf("Number coins:\n");
    ASSERT((pre->coins + coinsGained) == post->coins);
    printf("\texpected = %d, actual = %d\n", pre->coins + coinsGained, post->coins);

    printf("Hand count:\n");
    ASSERT(post->handCount[player] == pre->handCount[player] - discarded + cardsGained);
    printf("\texpected = %d, actual = %d\n", pre->handCount[player] - discarded + cardsGained, post->handCount[player]);

    return 0;
}

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

    printf("\n\n-------------Testing Baron---------\n\n");
    initializeGame(numPlayers, k, seed, &preG);

/* 
    test 1: get rid of estate and have one in hand
    expect: to get rid of estate and gain +4 coins 
*/
    printf("\n\nTest 1:\n");

    //set players hand
    preG.hand[thisPlayer][0] = steward;
	preG.hand[thisPlayer][1] = copper;
	preG.hand[thisPlayer][2] = duchy;
	preG.hand[thisPlayer][3] = estate;
	preG.hand[thisPlayer][4] = feast;

    memcpy(&postG, &preG, sizeof(struct gameState));
	choice1 = 1;
    discarded = 1;
    buysGained = 1;
    coinsGained = 4;
    actionsGained = 0;
    cardsGained = 0;
	card_baron(choice1, &postG, thisPlayer, nextPlayer);

    universalTest(&preG, &postG, discarded, cardsGained, buysGained, coinsGained, actionsGained, thisPlayer);
    for(int i = 0; i < postG.handCount[thisPlayer]; i++)
    {
        ASSERT(postG.hand[thisPlayer][i] != estate);
        if(postG.hand[thisPlayer][i] == estate)
        {
            printf("estate found in hand at %d\n", i);
        }
    }

/* 
    test 2: get rid of estate, but not have one in hand
    expect: gain an estate
*/
    printf("\n\nTest 2:\n");

    //set player hand with no estate
    preG.hand[thisPlayer][0] = steward;
	preG.hand[thisPlayer][1] = copper;
	preG.hand[thisPlayer][2] = duchy;
	preG.hand[thisPlayer][3] = feast;
    preG.handCount[thisPlayer] = 4;

    memcpy(&postG, &preG, sizeof(struct gameState));
	choice1 = 1;
    discarded = 0;
    buysGained = 1;
    coinsGained = 0;
    actionsGained = 0;
    cardsGained = 1;
	card_baron(choice1, &postG, thisPlayer, nextPlayer);
    printf("postG: %d\n", postG.numBuys);

    universalTest(&preG, &postG, discarded, cardsGained, buysGained, coinsGained, actionsGained, thisPlayer);

    //the player should gain an estate at the highest hand pos
    ASSERT(postG.hand[thisPlayer][preG.handCount[thisPlayer] + 1] == estate);

/* 
    test 3:
    to what happens when player chooses to gain an estate 
*/
    printf("\n\nTest 3:\n");

    //set players hand
    preG.hand[thisPlayer][0] = steward;
	preG.hand[thisPlayer][1] = copper;
	preG.hand[thisPlayer][2] = duchy;
	preG.hand[thisPlayer][3] = feast;

    memcpy(&postG, &preG, sizeof(struct gameState));
	choice1 = 0;
    discarded = 0;
    buysGained = 1;
    coinsGained = 0;
    actionsGained = 0;
    cardsGained = 1;
	card_baron(choice1, &postG, thisPlayer, nextPlayer);

    universalTest(&preG, &postG, discarded, cardsGained, buysGained, coinsGained, actionsGained, thisPlayer);

    ASSERT(postG.hand[thisPlayer][postG.handCount[thisPlayer]] == estate);

/*
    test 4:
    expected: to not gain an estate card, everything stays the same, except you get +1 buys
*/
    printf("\n\nTest 4:\n");

    preG.hand[thisPlayer][0] = steward;
	preG.hand[thisPlayer][1] = copper;
	preG.hand[thisPlayer][2] = duchy;
	preG.hand[thisPlayer][3] = estate;
	preG.hand[thisPlayer][4] = feast;
    preG.supplyCount[estate] = -1;
    preG.handCount[thisPlayer] = 5;

    memcpy(&postG, &preG, sizeof(struct gameState));
	choice1 = 0;
    discarded = 0;
    buysGained = 1;
    coinsGained = 0;
    actionsGained = 0;
    cardsGained = 0;
	card_baron(choice1, &postG, thisPlayer, nextPlayer);

    universalTest(&preG, &postG, discarded, cardsGained, buysGained, coinsGained, actionsGained, thisPlayer);

    ASSERT(postG.supplyCount[estate] == preG.supplyCount[estate]);

    printf("\n\n-------------End Testing Baron---------------\n\n");

    return 0;
}