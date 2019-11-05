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
    test 6: lose a silver, gain a gold
*/

int main()
{
    int cardsGained = 0;
    int cardsDiscarded = 1;
    int coinsGained = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState preG, postG;
	int k[10] = {adventurer, silver, copper, gold, mine, cutpurse,
			sea_hag, baron, smithy, council_room};

//REPLACE ALL //assertS WITH OWN IMPLEMENTATION
    initializeGame(numPlayers, k, seed, &postG);
/* test 1: lose a copper, gain a silver */

    cardsGained = 1;
    cardsDiscarded = 1;
    coinsGained = 3;//(?)
    //set players hand
    postG.hand[thisPlayer][0] = steward;
	postG.hand[thisPlayer][1] = copper;
	postG.hand[thisPlayer][2] = duchy;
	postG.hand[thisPlayer][3] = estate;
	postG.hand[thisPlayer][4] = mine;

    memcpy(&preG, &postG, sizeof(struct gameState));
	choice1 = 1;//or is it 2?
    choice2 = 1;//or is it 2?
	cardEffect(mine, choice1, choice2, choice3, &postG, handpos, &bonus);

    ASSERT(preG.handCount[thisPlayer] + cardsGained - cardsDiscarded == postG.handCount[thisPlayer]);
    ASSERT(preG.deckCount[thisPlayer] - cardsGained == postG.deckCount[thisPlayer]);
    ASSERT(preG.coins + coinsGained == postG.coins);

/* 
    test 2: lose a silver, try to gain a copper 
    no change expected
*/

    cardsGained = 0;
    cardsDiscarded = 0;
    coinsGained = 0;
    //set players hand
    postG.hand[thisPlayer][0] = steward;
	postG.hand[thisPlayer][1] = silver;
	postG.hand[thisPlayer][2] = duchy;
	postG.hand[thisPlayer][3] = estate;
	postG.hand[thisPlayer][4] = mine;

    memcpy(&preG, &postG, sizeof(struct gameState));
	choice1 = 1;//or is it 2?
    choice2 = 2;//or is it 3?
	cardEffect(mine, choice1, choice2, choice3, &postG, handpos, &bonus);

    ASSERT(preG.handCount[thisPlayer] + cardsGained - cardsDiscarded == postG.handCount[thisPlayer]);
    ASSERT(preG.deckCount[thisPlayer] - cardsGained == postG.deckCount[thisPlayer]);
    ASSERT(preG.coins + coinsGained == postG.coins);

/* 
    test 3: lose a copper, try to gain a gold 
    no change expected
*/
    cardsGained = 0;
    cardsDiscarded = 0;
    coinsGained = 0;
    //set players hand
    postG.hand[thisPlayer][0] = steward;
	postG.hand[thisPlayer][1] = copper;
	postG.hand[thisPlayer][2] = duchy;
	postG.hand[thisPlayer][3] = estate;
	postG.hand[thisPlayer][4] = mine;

    memcpy(&preG, &postG, sizeof(struct gameState));
	choice1 = 1;//or is it 2?
    choice2 = 3;//or is it 4?
	cardEffect(mine, choice1, choice2, choice3, &postG, handpos, &bonus);

    ASSERT(preG.handCount[thisPlayer] + cardsGained - cardsDiscarded == postG.handCount[thisPlayer]);
    ASSERT(preG.deckCount[thisPlayer] - cardsGained == postG.deckCount[thisPlayer]);
    ASSERT(preG.coins + coinsGained == postG.coins);

/* 
    test 4: lose a copper, try to gain a mine
    no change expected
*/
    cardsGained = 0;
    cardsDiscarded = 0;
    coinsGained = 0;
    //set players hand
    postG.hand[thisPlayer][0] = steward;
	postG.hand[thisPlayer][1] = copper;
	postG.hand[thisPlayer][2] = duchy;
	postG.hand[thisPlayer][3] = estate;
	postG.hand[thisPlayer][4] = mine;

    memcpy(&preG, &postG, sizeof(struct gameState));
	choice1 = 1;//or is it 2?
    choice2 = 4;//or is it 5?
	cardEffect(mine, choice1, choice2, choice3, &postG, handpos, &bonus);

    ASSERT(preG.handCount[thisPlayer] + cardsGained - cardsDiscarded == postG.handCount[thisPlayer]);
    ASSERT(preG.deckCount[thisPlayer] - cardsGained == postG.deckCount[thisPlayer]);
    ASSERT(preG.coins + coinsGained == postG.coins);

/* 
    test 5: lose a estate, try to gain a mine
    no change expected
*/
    cardsGained = 0;
    cardsDiscarded = 0;
    coinsGained = 0;
    //set players hand
    postG.hand[thisPlayer][0] = steward;
	postG.hand[thisPlayer][1] = copper;
	postG.hand[thisPlayer][2] = duchy;
	postG.hand[thisPlayer][3] = estate;
	postG.hand[thisPlayer][4] = mine;

    memcpy(&preG, &postG, sizeof(struct gameState));
	choice1 = 3;//or is it 4?
    choice2 = 4;//or is it 5?
	cardEffect(mine, choice1, choice2, choice3, &postG, handpos, &bonus);

    ASSERT(preG.handCount[thisPlayer] + cardsGained - cardsDiscarded == postG.handCount[thisPlayer]);
    ASSERT(preG.deckCount[thisPlayer] - cardsGained == postG.deckCount[thisPlayer]);
    ASSERT(preG.coins + coinsGained == postG.coins);

    return 0;
}