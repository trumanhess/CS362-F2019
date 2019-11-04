//NEED TO ZERO OUT GAME STRUCTS AFTER USING THEM!!
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "custom_assert.h"

/*
    test 1: get rid of estate and have one in hand
    test 2: get rid of estate, but not have one in hand
    test 3: gain an estate
    test 4: try to gain an estate, but no estates in supply
    test 5: try to gain an estate, but negative amount of estates in supply
*/

int main()
{
    int cardsGained = 0;
    int discarded = 1;
    int coinsGained = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState preG, postG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, baron, smithy, council_room};

//REPLACE ALL ASSERTS WITH OWN IMPLEMENTATION
/* 
    test 1: 
    to get rid of estate and gain +4 coins 
*/
    //could make this test more robust by testing multiple estates
    //or estates in different positions in the hand

    initializeGame(numPlayers, k, seed, &postG);

    //set players hand
    postG.hand[thisPlayer][0] = steward;
	postG.hand[thisPlayer][1] = copper;
	postG.hand[thisPlayer][2] = duchy;
	postG.hand[thisPlayer][3] = estate;
	postG.hand[thisPlayer][4] = feast;
    postG.coins = 0;

    memcpy(&preG, &postG, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(baron, choice1, choice2, choice3, &postG, handpos, &bonus);

    //compare how many buys
    ASSERT((preG.numBuys + 1) == postG.numBuys);
    printf("expected = %d, actual = %d\n", preG.numBuys + 1, postG.numBuys);
    //compare old coins to new coins
    ASSERT((preG.coins + 4) == postG.coins);
    printf("expected = %d, actual = %d\n", preG.coins + 4, postG.coins);
    //compare that card is no longer in hand in both
    //should remove number 3 in hand
    for(i = 1; i < postG.handCount[thisPlayer]; i++)
    {
        //assert(postG.hand[thisPlayer][i] != estate); //in this case we can just write estate because there is only one estate in our hand
                                                     //might need to change this in the future
        ASSERT(postG.hand[thisPlayer][i] != estate);
        if(postG.hand[thisPlayer][i] == estate)
        {
            printf("estate found in hand at %d\n", i);
        }
    }
    ASSERT(postG.handCount[thisPlayer] == preG.handCount[thisPlayer] - 1);
    printf("Hand count: expected = %d, actual = %d\n", preG.handCount[thisPlayer] - 1, postG.handCount[thisPlayer]);
    //check to see if other stuff is unaffected, like other players and piles

/* 
    test 2:
     to see what happens when player wants to get rid of estate but doesn't have one 
*/

    //set player hand with no estate
    postG.hand[thisPlayer][0] = steward;
	postG.hand[thisPlayer][1] = copper;
	postG.hand[thisPlayer][2] = duchy;
	postG.hand[thisPlayer][3] = feast;

    memcpy(&preG, &postG, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(baron, choice1, choice2, choice3, &postG, handpos, &bonus);

    //compare how many buys
    ASSERT((preG.numBuys + 1) == postG.numBuys);
    printf("Number of Buys: expected: %d, actual: %d", (preG.numBuys + 1), postG.numBuys);
    //compare old coins to new coins
    ASSERT(preG.coins == postG.coins);

    //the player should gain an estate at the highest hand pos
    ASSERT(postG.hand[thisPlayer][preG.handCount[thisPlayer + 1]] == estate);

    //assert(postG.handCount[thisPlayer] == preG.handCount[thisPlayer]);
    ASSERT(postG.handCount[thisPlayer] == preG.handCount[thisPlayer] + 1);
    printf("Hand count: expected = %d, actual = %d\n", preG.handCount[thisPlayer] + 1, postG.handCount[thisPlayer]);
    //check that discard pile is unaffected?
    //amongest other things

/* 
    test 3:
    to what happens when player chooses to gain an estate 
*/

    //set players hand
    postG.hand[thisPlayer][0] = steward;
	postG.hand[thisPlayer][1] = copper;
	postG.hand[thisPlayer][2] = duchy;
	postG.hand[thisPlayer][3] = estate;
	postG.hand[thisPlayer][4] = feast;

    memcpy(&preG, &postG, sizeof(struct gameState));
	choice1 = 0;
	cardEffect(baron, choice1, choice2, choice3, &postG, handpos, &bonus);

    //compare how many buys
    //assert((preG.numBuys + 1) == postG.numBuys);
    //compare old coins to new coins
    //assert(preG.coins == postG.coins);

    int numEstates = 0;
    
    for(i = 0; i < postG.handCount[thisPlayer]; i++)
    {
        //assert(postG.hand[thisPlayer][i] != estate); //in this case we can just write estate because there is only one estate in our hand
        if(postG.hand[thisPlayer][i] == estate)
        {
            numEstates += 1;
        }
    }
    if(numEstates == 2)
    {
        //yeet
    }
    //assert(postG.handCount[thisPlayer] == preG.handCount[thisPlayer] + 1);

/*
    test 4:
*/

/*
    test 5:
    expected: to not gain an estate card, everything stays the same, except you get +1 buys
*/
    postG.hand[thisPlayer][0] = steward;
	postG.hand[thisPlayer][1] = copper;
	postG.hand[thisPlayer][2] = duchy;
	postG.hand[thisPlayer][3] = estate;
	postG.hand[thisPlayer][4] = feast;
    postG.coins = 0;

    memcpy(&preG, &postG, sizeof(struct gameState));
	choice1 = 0;
    postG.supplyCount[estate] = -1;
	cardEffect(baron, choice1, choice2, choice3, &postG, handpos, &bonus);

    //compare how many buys
    ASSERT((preG.numBuys + 1) == postG.numBuys);
    printf("expected = %d, actual = %d\n", preG.numBuys + 1, postG.numBuys);
    //compare old coins to new coins
    ASSERT(preG.coins == postG.coins);
    printf("expected = %d, actual = %d\n", preG.coins, postG.coins);
    
    ASSERT(postG.handCount[thisPlayer] == preG.handCount[thisPlayer]);
    printf("Hand count: expected = %d, actual = %d\n", preG.handCount[thisPlayer], postG.handCount[thisPlayer]);
    //check to see if other stuff is unaffected, like other players and piles

    return 0;
}