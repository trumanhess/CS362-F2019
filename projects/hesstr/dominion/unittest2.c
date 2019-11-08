#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "custom_assert.h"

/*
    test 1: lose a copper, gain a silver
    test 2: lose a silver, try to gain a copper
    test 3: lose a copper, try to gain a gold
    test 4: lose a copper, try to gain a mine
    test 5: lose a estate, try to gain a mine
    test 6: lose a silver, try to gain a gold
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
}

int main()
{
    int cardsGained = 0;
    int discarded = 0;
    int coinsGained = 0;
    int buysGained = 0;
    int actionsGained = 0;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState preG, postG;
	int k[10] = {adventurer, silver, copper, gold, mine, cutpurse,
			sea_hag, baron, smithy, council_room};

    printf("\n\n--------------------Testing Mine----------------------\n\n");

    initializeGame(numPlayers, k, seed, &preG);
/* test 1: lose a copper, gain a silver */

    printf("\n\nTest 1:\n");
    //cardsGained = 1;
    //cardsDiscarded = 1;
    //coinsGained = 3;//(?)
    //set players hand
    preG.hand[thisPlayer][0] = steward;
	preG.hand[thisPlayer][1] = copper;
	preG.hand[thisPlayer][2] = duchy;
	preG.hand[thisPlayer][3] = estate;
	preG.hand[thisPlayer][4] = mine;
    updateCoins(thisPlayer, &preG, 4);

    memcpy(&postG, &preG, sizeof(struct gameState));
	choice1 = 1;
    choice2 = 5;
    discarded = 1;
    buysGained = 0;
    coinsGained = 2;
    actionsGained = 0;
    cardsGained = 1;
	mineLogic(choice1, choice2, &postG, handpos, thisPlayer);
    //updateCoins(thisPlayer, &postG, 4); //need to update coins to be accurate

    /*ASSERT(preG.handCount[thisPlayer] + cardsGained - cardsDiscarded == postG.handCount[thisPlayer]);
    //ASSERT(preG.deckCount[thisPlayer] - cardsGained == postG.deckCount[thisPlayer]);
    ASSERT(preG.coins + coinsGained == postG.coins);*/
    universalTest(&preG, &postG, discarded, cardsGained, buysGained, coinsGained, actionsGained, thisPlayer);

/* 
    test 2: lose a silver, try to gain a copper 
    no change expected
*/

    printf("\n\nTest 2:\n");

    //cardsGained = 0;
    //cardsDiscarded = 0;
    //coinsGained = 0;
    //set players hand
    preG.hand[thisPlayer][0] = steward;
	preG.hand[thisPlayer][1] = silver;
	preG.hand[thisPlayer][2] = duchy;
	preG.hand[thisPlayer][3] = estate;
	preG.hand[thisPlayer][4] = mine;
    preG.handCount[thisPlayer] = 5;
    updateCoins(thisPlayer, &preG, 4);

    memcpy(&postG, &preG, sizeof(struct gameState));
	choice1 = 1;
    choice2 = 4;
    discarded = 0;
    buysGained = 0;
    coinsGained = 0;
    actionsGained = 0;
    cardsGained = 0;
	mineLogic(choice1, choice2, &postG, handpos, thisPlayer);
    //updateCoins(thisPlayer, &postG, 4);

    universalTest(&preG, &postG, discarded, cardsGained, buysGained, coinsGained, actionsGained, thisPlayer);
    /*ASSERT(preG.handCount[thisPlayer] + cardsGained  == postG.handCount[thisPlayer]);
    ASSERT(preG.deckCount[thisPlayer] - cardsGained == postG.deckCount[thisPlayer]);
    ASSERT(preG.coins + coinsGained == postG.coins);*/


/* 
    test 3: lose a copper, try to gain a gold 
    no change expected
*/
    printf("\n\nTest 3:\n");

    //cardsGained = 0;
    //cardsDiscarded = 0;
    //coinsGained = 0;
    //set players hand
    preG.hand[thisPlayer][0] = steward;
	preG.hand[thisPlayer][1] = copper;
	preG.hand[thisPlayer][2] = duchy;
	preG.hand[thisPlayer][3] = estate;
	preG.hand[thisPlayer][4] = mine;
    updateCoins(thisPlayer, &preG, 4);

    memcpy(&postG, &preG, sizeof(struct gameState));
	choice1 = 1;
    choice2 = 6;
    discarded = 0;
    buysGained = 0;
    coinsGained = 0;
    actionsGained = 0;
    cardsGained = 0;
	mineLogic(choice1, choice2, &postG, handpos, thisPlayer);
    //updateCoins(thisPlayer, &postG, 4);

    universalTest(&preG, &postG, discarded, cardsGained, buysGained, coinsGained, actionsGained, thisPlayer);
    /*ASSERT(preG.handCount[thisPlayer] + cardsGained  == postG.handCount[thisPlayer]);
    ASSERT(preG.deckCount[thisPlayer] - cardsGained == postG.deckCount[thisPlayer]);
    ASSERT(preG.coins + coinsGained == postG.coins);*/

/* 
    test 4: lose a copper, try to gain a mine
    no change expected
*/

    printf("\n\nTest 4:\n");
    //set players hand
    preG.hand[thisPlayer][0] = steward;
	preG.hand[thisPlayer][1] = copper;
	preG.hand[thisPlayer][2] = duchy;
	preG.hand[thisPlayer][3] = estate;
	preG.hand[thisPlayer][4] = mine;
    updateCoins(thisPlayer, &preG, 4);

    memcpy(&postG, &preG, sizeof(struct gameState));
	choice1 = 1;
    choice2 = 11;
    discarded = 0;
    buysGained = 0;
    coinsGained = 0;
    actionsGained = 0;
    cardsGained = 0;
	mineLogic(choice1, choice2, &postG, handpos, thisPlayer);
    //updateCoins(thisPlayer, &postG, 4);

    universalTest(&preG, &postG, discarded, cardsGained, buysGained, coinsGained, actionsGained, thisPlayer);
    /*
    ASSERT(preG.handCount[thisPlayer] + cardsGained  == postG.handCount[thisPlayer]);
    ASSERT(preG.deckCount[thisPlayer] - cardsGained == postG.deckCount[thisPlayer]);
    ASSERT(preG.coins + coinsGained == postG.coins);*/

/* 
    test 5: lose a estate, try to gain a mine
    no change expected
*/

    printf("\n\nTest 5:\n");
    //set players hand
    preG.hand[thisPlayer][0] = steward;
	preG.hand[thisPlayer][1] = copper;
	preG.hand[thisPlayer][2] = duchy;
	preG.hand[thisPlayer][3] = estate;
	preG.hand[thisPlayer][4] = copper;
    updateCoins(thisPlayer, &preG, 4);

    memcpy(&postG, &preG, sizeof(struct gameState));
	choice1 = 3;
    choice2 = 11;
    discarded = 0;
    buysGained = 0;
    coinsGained = 0;
    actionsGained = 0;
    cardsGained = 0;
	mineLogic(choice1, choice2, &postG, handpos, thisPlayer);

    universalTest(&preG, &postG, discarded, cardsGained, buysGained, coinsGained, actionsGained, thisPlayer);

    for(int i = 0; i < postG.handCount[thisPlayer]; i++)
    {
        ASSERT(postG.hand[thisPlayer][i] != estate);
        if(postG.hand[thisPlayer][i] == estate)
        {
            printf("estate found in hand at position: %d\n", i);
        }
        
    }

/*
    test 6:
*/
    printf("\n\nTest 6:\n");
    preG.hand[thisPlayer][0] = steward;
	preG.hand[thisPlayer][1] = silver;
	preG.hand[thisPlayer][2] = duchy;
	preG.hand[thisPlayer][3] = estate;
	preG.hand[thisPlayer][4] = mine;
    updateCoins(thisPlayer, &preG, 4);

    memcpy(&postG, &preG, sizeof(struct gameState));
	choice1 = 1;
    choice2 = 6;
    discarded = 1;
    buysGained = 0;
    coinsGained = 2;
    actionsGained = 0;
    cardsGained = 1;
	mineLogic(choice1, choice2, &postG, handpos, thisPlayer);
    //updateCoins(thisPlayer, &postG, 4); //need to update coins to be accurate

    universalTest(&preG, &postG, discarded, cardsGained, buysGained, coinsGained, actionsGained, thisPlayer);

    printf("\n\n-----------------------------------End Testing Mine--------------------------------\n\n");

    return 0;
}