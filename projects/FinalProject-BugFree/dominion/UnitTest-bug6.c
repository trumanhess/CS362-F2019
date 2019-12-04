#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>

int main(int argc, char const *argv[]) {

	int seed = 1000;
	int numPlayers = 1;
	int k[10] = { adventurer, embargo, village,
	              minion, mine, cutpurse,
	              sea_hag, baron, smithy,
	              council_room };
	struct gameState g;
	int card = feast;
	int choice1 = gold;
	int choice2 = -1;
	int choice3 = -1;
	int handPos = -1;
	int bonus = 0;

	initializeGame(numPlayers, k, seed, &g);
	g.hand[0][0] = copper;
	g.handCount[0] = 1;
	g.supplyCount[gold] = 1;

	int res = cardEffect(card, choice1, choice2, choice3, &g, handPos, &bonus);

	printf("------------ Test 1 -------------\n");

	printf("Return value: %d\n", res);
	printf("Expected return value: -1\n");

	assert(res == -1);

	printf("HandCount value: %d\n", g.handCount[0]);
	printf("Expected handCount value: 1\n");

	assert(g.handCount[0] == 1);

	printf("Test 1 passed !!!!!!\n");

	initializeGame(numPlayers, k, seed, &g);
	g.hand[0][0] = copper;
	g.handCount[0] = 1;
	g.supplyCount[copper] = 1;
	choice1 = copper;
	int res2 = cardEffect(card, choice1, choice2, choice3, &g, handPos, &bonus);

	printf("------------Test 2 ---------------\n");

	printf("Return value: %d\n", res2);
	printf("Expected return value: 0\n");
	printf("HandCount value: %d\n", g.handCount[0]);
	printf("Expected handCount value: 2\n");

	assert(res2 == 0);
	assert(g.handCount[0] == 2);
	printf("Test 2 passed !!!!!!\n");

	return 0;
}
