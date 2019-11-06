#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "custom_assert.h"
#include "rngs.h"

//tribute card
/*
    test 1: reveal card, return 0 copy of it to supply
    test 2: reveal card, return 1 copy of it to supply
    test 3: reveal card, return 2 copies of it to supply
    test 4: reveal card, try to return 3 copies of it to supply
    test 5: reveal card, try to return 2 copies of it to supply even though you have one in hand
    test 6: reveal the ambassador card that was played and try to return 1 copy of it to supply
    test 7: reveal card, try to return 0 copies but supply has 0 of that card
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
    int cardsDiscarded = 0;
    int coinsGained = 0;
    int buysGained = 0;
    int actionsGained = 0;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int player1 = 0;
    int player2 = 1;
	struct gameState preG, postG;
	int k[10] = {adventurer, silver, steward, gold, mine, minion,
			sea_hag, baron, smithy, council_room};

//REPLACE ALL //assertS WITH OWN IMPLEMENTATION
    printf("\n\n---------------------------------Testing Ambassador--------------------------------\n\n");
    initializeGame(numPlayers, k, seed, &preG);

/*
    test 1: reveal card, return 0 copy of it to supply
    expect: nothing in supply or players hand to change, expect other players hand to change
*/
    printf("\n\nTest 1:\n");

    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = steward;
	preG.hand[player1][2] = ambassador;
	preG.hand[player1][3] = estate;
	preG.hand[player1][4] = mine;

    preG.hand[player2][0] = minion;
	preG.hand[player2][1] = steward;
	preG.hand[player2][2] = ambassador;
	preG.hand[player2][3] = estate;
	preG.hand[player2][4] = mine;
    preG.handCount[player2] = 5;

    handpos = 2;

    memcpy(&postG, &preG, sizeof(struct gameState));
    choice1 = 3;
    choice2 = 0; 
    cardsDiscarded = 1; //losing one card because tribute is discarded
    buysGained = 0;
    coinsGained = 0;
    actionsGained = 0;
    cardsGained = 0;
	ambassadorLogic(choice1, choice2, &postG, handpos, player1);

    ASSERT(postG.supplyCount[preG.hand[player1][choice1]] == preG.supplyCount[preG.hand[player1][choice1]] - 1);

    printf("Player 1:\n");
    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);

    printf("Player 2:\n");
    universalTest(&preG, &postG, 0, 0, buysGained, coinsGained, actionsGained, player2);
    ASSERT(preG.discardCount[player2] + 1 == postG.discardCount[player2]);



/*
    test 2: reveal card, return 1 copy of it to supply
    expect: player to lose one card, supply to gain one card, and players to gain a card
*/ 
    printf("\n\nTest 2:\n");

    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = steward;
	preG.hand[player1][2] = ambassador;
	preG.hand[player1][3] = estate;
	preG.hand[player1][4] = mine;

    preG.hand[player2][0] = minion;
	preG.hand[player2][1] = steward;
	preG.hand[player2][2] = ambassador;
	preG.hand[player2][3] = estate;
	preG.hand[player2][4] = mine;

    handpos = 2;

    memcpy(&postG, &preG, sizeof(struct gameState));
    choice1 = 3;
    choice2 = 1; 
    cardsDiscarded = 2;
    buysGained = 0;
    coinsGained = 0;
    actionsGained = 0;
    cardsGained = 0;
	ambassadorLogic(choice1, choice2, &postG, handpos, player1);

    ASSERT(postG.supplyCount[preG.hand[player1][choice1]] == preG.supplyCount[preG.hand[player1][choice1]]); //asserts true but for the wrong reasons

    printf("Player 1:\n");
    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);

    printf("Player 2:\n");
    universalTest(&preG, &postG, 0, 0, buysGained, coinsGained, actionsGained, player2);
    ASSERT(preG.discardCount[player2] + 1 == postG.discardCount[player2]);
/*
    test 3: reveal card, return 2 copies of it to supply
    expect: player to lose 2 cards, supply to gain two cards, expect other players to gain a card
*/ 
    printf("\n\nTest 3:\n");

    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = steward;
	preG.hand[player1][2] = ambassador;
	preG.hand[player1][3] = estate;
	preG.hand[player1][4] = estate;

    preG.hand[player2][0] = minion;
	preG.hand[player2][1] = steward;
	preG.hand[player2][2] = ambassador;
	preG.hand[player2][3] = estate;
	preG.hand[player2][4] = mine;

    handpos = 2;

    memcpy(&postG, &preG, sizeof(struct gameState));
    choice1 = 3;
    choice2 = 2; 
    cardsDiscarded = 3;
    buysGained = 0;
    coinsGained = 0;
    actionsGained = 0;
    cardsGained = 0;
	ambassadorLogic(choice1, choice2, &postG, handpos, player1);

    ASSERT(postG.supplyCount[preG.hand[player1][choice1]] == preG.supplyCount[preG.hand[player1][choice1]] + 1);

    printf("Player 1:\n");
    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);

    printf("Player 2:\n");
    universalTest(&preG, &postG, 0, 0, buysGained, coinsGained, actionsGained, player2);
    ASSERT(preG.discardCount[player2] + 1 == postG.discardCount[player2]);
/*
    test 4: reveal card, try to return 3 copies of it to supply
    expect: no change to occur
*/
    printf("\n\nTest 2:\n");

    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = steward;
	preG.hand[player1][2] = ambassador;
	preG.hand[player1][3] = estate;
	preG.hand[player1][4] = mine;

    handpos = 2;

    memcpy(&postG, &preG, sizeof(struct gameState));
    choice1 = 4;
    choice2 = 3; 
    cardsDiscarded = 0;
    buysGained = 0;
    coinsGained = 0;
    actionsGained = 0;
    cardsGained = 0;
	ambassadorLogic(choice1, choice2, &postG, handpos, player1);

    ASSERT(postG.supplyCount[preG.hand[player1][choice1]] == preG.supplyCount[preG.hand[player1][choice1]]);

    printf("Player 1:\n");
    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);

    printf("Player 2:\n");
    universalTest(&preG, &postG, cardsDiscarded, 0, buysGained, coinsGained, actionsGained, player2);

/*
    test 5: reveal card, try to return 2 cards even though you only have one card
    expect: nothing to change
*/
    printf("\n\nTest 5:\n");

    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = steward;
	preG.hand[player1][2] = ambassador;
	preG.hand[player1][3] = estate;
	preG.hand[player1][4] = mine;

    preG.hand[player2][0] = minion;
	preG.hand[player2][1] = steward;
	preG.hand[player2][2] = ambassador;
	preG.hand[player2][3] = estate;
	preG.hand[player2][4] = mine;

    handpos = 2;

    memcpy(&postG, &preG, sizeof(struct gameState));
    choice1 = 3;
    choice2 = 2; 
    cardsDiscarded = 0;
    buysGained = 0;
    coinsGained = 0;
    actionsGained = 0;
    cardsGained = 0;
	ambassadorLogic(choice1, choice2, &postG, handpos, player1);

    ASSERT(postG.supplyCount[preG.hand[player1][choice1]] == preG.supplyCount[preG.hand[player1][choice1]]);

    printf("Player 1:\n");
    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);

    printf("Player 2:\n");
    universalTest(&preG, &postG, cardsDiscarded, 0, buysGained, coinsGained, actionsGained, player2);

/*
    test 6: reveal the ambassador card that was played and try to return 1 copy of it to supply
    expect: expect nothing to change
*/ 
    printf("\n\nTest 6:\n");

    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = steward;
	preG.hand[player1][2] = ambassador;
	preG.hand[player1][3] = estate;
	preG.hand[player1][4] = mine;

    handpos = 2;

    memcpy(&postG, &preG, sizeof(struct gameState));
    choice1 = 4;
    choice2 = 1; 
    cardsDiscarded = 0;
    buysGained = 0;
    coinsGained = 0;
    actionsGained = 0;
    cardsGained = 0;
	ambassadorLogic(choice1, choice2, &postG, handpos, player1);

    ASSERT(postG.supplyCount[preG.hand[player1][choice1]] == preG.supplyCount[preG.hand[player1][choice1]]);

    printf("Player 1:\n");
    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);

    printf("Player 2:\n");
    universalTest(&preG, &postG, cardsDiscarded, 0, buysGained, coinsGained, actionsGained, player2);

/*
    test 7: reveal card, try to return 0 copies but supply has 0 of that card
    expect: expect nothing to change
*/ 
    printf("\n\nTest 7:\n");

    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = steward;
	preG.hand[player1][2] = ambassador;
	preG.hand[player1][3] = estate;
	preG.hand[player1][4] = mine;

    preG.hand[player2][0] = minion;
	preG.hand[player2][1] = steward;
	preG.hand[player2][2] = ambassador;
	preG.hand[player2][3] = estate;
	preG.hand[player2][4] = mine;

    preG.supplyCount[estate] = 0;
    handpos = 2;

    memcpy(&postG, &preG, sizeof(struct gameState));
    choice1 = 3;
    choice2 = 0; 
    cardsDiscarded = 0;
    buysGained = 0;
    coinsGained = 0;
    actionsGained = 0;
    cardsGained = 0;
	ambassadorLogic(choice1, choice2, &postG, handpos, player1);

    ASSERT(postG.supplyCount[preG.hand[player1][choice1]] == preG.supplyCount[preG.hand[player1][choice1]]);

    printf("Player 1:\n");
    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);

    printf("Player 2:\n");
    universalTest(&preG, &postG, cardsDiscarded, 0, buysGained, coinsGained, actionsGained, player2);

    printf("\n\n---------------------------------End Testing Ambassador--------------------------------\n\n");

    return 0;
}