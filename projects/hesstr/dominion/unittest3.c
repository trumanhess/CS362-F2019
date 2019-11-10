#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "custom_assert.h"
#include "rngs.h"

/*
    check player has +1 action in all of these
    test 1: first option, gain +2 coins
    test 2: second option, have 5 cards and try to gain a new set, check new set of cards (?)
            player 2 will have 4 cards and should not gain a new set
    test 3: second option, have 3 cards and check new set of cards (?)
            player 2 will have 5 cards and should gain a new set
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
    int cardsDiscarded = 0;
    int coinsGained = 0;
    int buysGained = 0;
    int actionsGained = 0;

    int handpos = 0, choice1 = 0, choice2 = 0;
    int seed = 1000;
    int numPlayers = 2;
    int player1 = 0;
    int player2 = 1;
	struct gameState preG, postG;
	int k[10] = {adventurer, silver, copper, gold, mine, minion,
			sea_hag, baron, smithy, council_room};

    printf("\n\n-----------------------------Testing Minion------------------------\n\n");
    initializeGame(numPlayers, k, seed, &preG);

/*
    test 1: first option, gain +2 coins
    expect to gain +2 coins
*/
    printf("\n\nTest 1:\n");

    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = steward;
	preG.hand[player1][2] = duchy;
	preG.hand[player1][3] = estate;
	preG.hand[player1][4] = mine;

    preG.hand[player2][0] = minion;
	preG.hand[player2][1] = copper;
	preG.hand[player2][2] = duchy;
	preG.hand[player2][3] = estate;
	preG.hand[player2][4] = mine;
    preG.handCount[player2] = 5;

    memcpy(&postG, &preG, sizeof(struct gameState));
    choice1 = 1; //choose to gain +2 coins
    choice2 = 0;
    cardsDiscarded = 0;
    buysGained = 0;
    coinsGained = 2;
    actionsGained = 1;
    cardsGained = 0;
    minionLogic(choice1, choice2, &postG, handpos, player1);

    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);
    ASSERT(preG.discardCount[player1] == postG.discardCount[player1]);

    ASSERT(preG.handCount[player2] + 0 - 0 == postG.handCount[player2]);
    ASSERT(preG.deckCount[player2] - 0 == postG.deckCount[player2]);

/*
    test 2: second option, have 5 cards and check new set of cards (?)
    player 2 will have 4 cards and should not gain a new set
    expect for player 1 to have a new hand and player 2 to keep hand
*/

    printf("\n\nTest 2:\n");

    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = copper;
	preG.hand[player1][2] = duchy;
	preG.hand[player1][3] = estate;
	preG.hand[player1][4] = mine;

    preG.hand[player2][0] = minion;
	preG.hand[player2][1] = copper;
	preG.hand[player2][2] = duchy;
	preG.hand[player2][3] = estate;

    memcpy(&postG, &preG, sizeof(struct gameState));
    choice1 = 2;
    cardsDiscarded = 5;
    buysGained = 0;
    coinsGained = 0;
    actionsGained = 1;
    cardsGained = 4;
	minionLogic(choice1, choice2, &postG, handpos, player1);

    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);

    ASSERT(preG.handCount[player2] + 0 - 0 == postG.handCount[player2]);
    ASSERT(preG.deckCount[player2] - 0 == postG.deckCount[player2]);

/*
    test 3: second option, have 3 cards and check new set of cards (?)
    player 2 will have 5 cards and should gain a new set
    expect player one to gain a new hand and player 2 to gain a new hand
*/

    printf("\n\nTest 3:\n");


    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = copper;
	preG.hand[player1][2] = duchy;
    preG.handCount[player1] = 3;

    preG.hand[player2][0] = minion;
	preG.hand[player2][1] = copper;
	preG.hand[player2][2] = duchy;
	preG.hand[player2][3] = estate;
    preG.hand[player2][4] = mine;

    memcpy(&postG, &preG, sizeof(struct gameState));
    choice1 = 2; //choose to gain a new hand
    cardsDiscarded = 3;
    buysGained = 0;
    coinsGained = 0;
    actionsGained = 1;
    cardsGained = 4;
	minionLogic(choice1, choice2, &postG, handpos, player1);

    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);

    ASSERT(preG.handCount[player2] + 4 == postG.handCount[player2]);
    ASSERT(preG.deckCount[player2] - 4 == postG.deckCount[player2]);

    printf("\n\n--------------------------------End Testing Minion---------------------------------\n\n");

    return 0;
}